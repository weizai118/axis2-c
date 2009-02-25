/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "guththila_hash.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * The internal form of a hash table.
 *
 * The table is an array indexed by the hash of the key; collisions
 * are resolved by hanging a linked list of hash entries off each
 * element of the array. Although this is a really simple design it
 * isn't too bad given that environments have a low allocation overhead.
 */

typedef struct guththila_hash_entry_t guththila_hash_entry_t;

struct guththila_hash_entry_t
{
    guththila_hash_entry_t *next;
    unsigned int hash;
    const void *key;
    guththila_ssize_t klen;
    const void *val;
};

/*
 * Data structure for iterating through a hash table.
 *
 * We keep a pointer to the next hash entry here to allow the current
 * hash entry to be freed or otherwise mangled between calls to
 * guththila_hash_next().
 */
struct guththila_hash_index_t
{
    guththila_hash_t *ht;
    guththila_hash_entry_t *this, *next;
    unsigned int index;
};

/*
 * The size of the array is always a power of two. We use the maximum
 * index rather than the size so that we can use bitwise-AND for
 * modular arithmetic.
 * The count of hash entries may be greater depending on the chosen
 * collision rate.
 */
struct guththila_hash_t
{
    guththila_environment_t *environment;
    guththila_hash_entry_t **array;
    guththila_hash_index_t iterator;    /* For guththila_hash_first(NULL, ...) */
    unsigned int count, max;
    guththila_hashfunc_t hash_func;
    guththila_hash_entry_t *free;   /* List of recycled entries */
};

#define INITIAL_MAX 15          /* tunable == 2^n - 1 */


/*
 * Hash creation functions.
 */

static guththila_hash_entry_t **
alloc_array (guththila_hash_t * ht, unsigned int max)
{
    return memset (GUTHTHILA_MALLOC (ht->environment->allocator,
                                     sizeof (*ht->array) * (max + 1)), 0,
                   sizeof (*ht->array) * (max + 1));
}

GUTHTHILA_DECLARE (guththila_hash_t *)
guththila_hash_make (guththila_environment_t * environment)
{
    guththila_hash_t *ht;
    ht = GUTHTHILA_MALLOC (environment->allocator, sizeof (guththila_hash_t));
    ht->environment = environment;
    ht->free = NULL;
    ht->count = 0;
    ht->max = INITIAL_MAX;
    ht->array = alloc_array (ht, ht->max);
    ht->hash_func = guththila_hashfunc_default;
    return ht;
}

GUTHTHILA_DECLARE (guththila_hash_t *)
guththila_hash_make_custom (guththila_environment_t * environment,
                            guththila_hashfunc_t hash_func)
{
    guththila_hash_t *ht = guththila_hash_make (environment);
    ht->hash_func = hash_func;
    return ht;
}


/*
 * Hash iteration functions.
 */

GUTHTHILA_DECLARE (guththila_hash_index_t *)
guththila_hash_next (guththila_hash_index_t * hi)
{
    hi->this = hi->next;
    while (!hi->this)
    {
        if (hi->index > hi->ht->max)
            return NULL;

        hi->this = hi->ht->array[hi->index++];
    }
    hi->next = hi->this->next;
    return hi;
}

GUTHTHILA_DECLARE (guththila_hash_index_t *)
guththila_hash_first (guththila_environment_t * environment,
                      guththila_hash_t * ht)
{
    guththila_hash_index_t *hi;
    if (environment)
        hi = GUTHTHILA_MALLOC (environment->allocator, sizeof (*hi));
    else
        hi = &ht->iterator;

    hi->ht = ht;
    hi->index = 0;
    hi->this = NULL;
    hi->next = NULL;
    return guththila_hash_next (hi);
}

GUTHTHILA_DECLARE (void) guththila_hash_this (guththila_hash_index_t * hi,
                                              const void **key,
                                              guththila_ssize_t * klen,
                                              void **val)
{
    if (key)
        *key = hi->this->key;
    if (klen)
        *klen = hi->this->klen;
    if (val)
        *val = (void *) hi->this->val;
}


/*
 * Expanding a hash table
 */

static void
expand_array (guththila_hash_t * ht)
{
    guththila_hash_index_t *hi;
    guththila_hash_entry_t **new_array;
    unsigned int new_max;

    new_max = ht->max * 2 + 1;
    new_array = alloc_array (ht, new_max);
    for (hi = guththila_hash_first (NULL, ht); hi;
         hi = guththila_hash_next (hi))
    {
        unsigned int i = hi->this->hash & new_max;
        hi->this->next = new_array[i];
        new_array[i] = hi->this;
    }
    ht->array = new_array;
    ht->max = new_max;
}

unsigned int
guththila_hashfunc_default (const guththila_char_t * char_key,
                            guththila_ssize_t * klen)
{
    unsigned int hash = 0;
    const guththila_unsigned_char_t *key =
        (const guththila_unsigned_char_t *) char_key;
    const guththila_unsigned_char_t *p;
    guththila_ssize_t i;

    /*
     * This is the popular `times 33' hash algorithm which is used by
     * perl and also appears in Berkeley DB. This is one of the best
     * known hash functions for strings because it is both computed
     * very fast and distributes very well.
     *
     * The originator may be Dan Bernstein but the code in Berkeley DB
     * cites Chris Torek as the source. The best citation I have found
     * is "Chris Torek, Hash function for text in C, Usenet message
     * <27038@mimsy.umd.edu> in comp.lang.c , October, 1990." in Rich
     * Salz's USENIX 1992 paper about INN which can be found at
     * <http://citeseer.nj.nec.com/salz92internetnews.html>.
     *
     * The magic of number 33, i.e. why it works better than many other
     * constants, prime or not, has never been adequately explained by
     * anyone. So I try an explanation: if one experimentally tests all
     * multipliers between 1 and 256 (as I did while writing a low-level
     * data structure library some time ago) one detects that even
     * numbers are not useable at all. The remaining 128 odd numbers
     * (except for the number 1) work more or less all equally well.
     * They all distribute in an acceptable way and this way fill a hash
     * table with an average percent of approx. 86%.
     *
     * If one compares the chi^2 values of the variants (see
     * Bob Jenkins ``Hashing Frequently Asked Questions'' at
     * http://burtleburtle.net/bob/hash/hashfaq.html for a description
     * of chi^2), the number 33 not even has the best value. But the
     * number 33 and a few other equally good numbers like 17, 31, 63,
     * 127 and 129 have nevertheless a great advantage to the remaining
     * numbers in the large set of possible multipliers: their multiply
     * op can be replaced by a faster op based on just one
     * shift plus either a single addition or subtraction op. And
     * because a hash function has to both distribute good _and_ has to
     * be very fast to compute, those few numbers should be preferred.
     *
     *                  -- Ralf S. Engelschall <rse@engelschall.com>
     */

    if (*klen == GUTHTHILA_HASH_KEY_STRING)
    {
        for (p = key; *p; p++)
        {
            hash = hash * 33 + *p;
        }
        *klen = p - key;
    }
    else
    {
        for (p = key, i = *klen; i; i--, p++)
        {
            hash = hash * 33 + *p;
        }
    }

    return hash;
}


/*
 * This is where we keep the details of the hash function and control
 * the maximum collision rate.
 *
 * If val is non-NULL it creates and initializes a new hash entry if
 * there isn't already one there; it returns an updatable pointer so
 * that hash entries can be removed.
 */

static guththila_hash_entry_t **
find_entry (guththila_hash_t * ht,
            const void *key, guththila_ssize_t klen, const void *val)
{
    guththila_hash_entry_t **hep, *he;
    unsigned int hash;

    hash = ht->hash_func (key, &klen);

    /* scan linked list */
    for (hep = &ht->array[hash & ht->max], he = *hep;
         he; hep = &he->next, he = *hep)
    {
        if (he->hash == hash
            && he->klen == klen && memcmp (he->key, key, klen) == 0)
            break;
    }
    if (he || !val)
        return hep;

    /* add a new entry for non-NULL values */
    if ((he = ht->free) != NULL)
        ht->free = he->next;
    else
        he = GUTHTHILA_MALLOC (ht->environment->allocator, sizeof (*he));
    he->next = NULL;
    he->hash = hash;
    he->key = key;
    he->klen = klen;
    he->val = val;
    *hep = he;
    ht->count++;
    return hep;
}

GUTHTHILA_DECLARE (guththila_hash_t *)
guththila_hash_copy (guththila_environment_t * environment,
                     const guththila_hash_t * orig)
{
    guththila_hash_t *ht;
    guththila_hash_entry_t *new_vals;
    unsigned int i, j;

    ht = GUTHTHILA_MALLOC (environment->allocator, sizeof (guththila_hash_t) +
                           sizeof (*ht->array) * (orig->max + 1) +
                           sizeof (guththila_hash_entry_t) * orig->count);
    ht->environment = environment;
    ht->free = NULL;
    ht->count = orig->count;
    ht->max = orig->max;
    ht->hash_func = orig->hash_func;
    ht->array =
        (guththila_hash_entry_t **) ((guththila_char_t *) ht +
                                     sizeof (guththila_hash_t));

    new_vals =
        (guththila_hash_entry_t *) ((guththila_char_t *) (ht) +
                                    sizeof (guththila_hash_t) +
                                    sizeof (*ht->array) * (orig->max + 1));
    j = 0;
    for (i = 0; i <= ht->max; i++)
    {
        guththila_hash_entry_t **new_entry = &(ht->array[i]);
        guththila_hash_entry_t *orig_entry = orig->array[i];
        while (orig_entry)
        {
            *new_entry = &new_vals[j++];
            (*new_entry)->hash = orig_entry->hash;
            (*new_entry)->key = orig_entry->key;
            (*new_entry)->klen = orig_entry->klen;
            (*new_entry)->val = orig_entry->val;
            new_entry = &((*new_entry)->next);
            orig_entry = orig_entry->next;
        }
        *new_entry = NULL;
    }
    return ht;
}

GUTHTHILA_DECLARE (void *) guththila_hash_get (guththila_hash_t * ht,
                                               const void *key,
                                               guththila_ssize_t klen)
{
    guththila_hash_entry_t *he;
    he = *find_entry (ht, key, klen, NULL);
    if (he)
        return (void *) he->val;
    else
        return NULL;
}

GUTHTHILA_DECLARE (void) guththila_hash_set (guththila_hash_t * ht,
                                             const void *key,
                                             guththila_ssize_t klen,
                                             const void *val)
{
    guththila_hash_entry_t **hep;
    hep = find_entry (ht, key, klen, val);
    if (*hep)
    {
        if (!val)
        {
            /* delete entry */
            guththila_hash_entry_t *old = *hep;
            *hep = (*hep)->next;
            old->next = ht->free;
            ht->free = old;
            --ht->count;
        }
        else
        {
            /* replace entry */
            (*hep)->val = val;
            /* check that the collision rate isn't too high */
            if (ht->count > ht->max)
            {
                expand_array (ht);
            }
        }
    }
    /* else key not present and val==NULL */
}

unsigned int
guththila_hash_count (guththila_hash_t * ht)
{
    return ht->count;
}

GUTHTHILA_DECLARE (guththila_hash_t *)
guththila_hash_overlay (guththila_environment_t * environment,
                        const guththila_hash_t * overlay,
                        const guththila_hash_t * base)
{
    return guththila_hash_merge (environment, overlay, base, NULL, NULL);
}

GUTHTHILA_DECLARE (guththila_hash_t *)
guththila_hash_merge (guththila_environment_t * environment,
                      const guththila_hash_t * overlay,
                      const guththila_hash_t * base,
                      void *(*merger) (guththila_environment_t * environment,
                                       const void *key,
                                       guththila_ssize_t klen,
                                       const void *h1_val, const void *h2_val,
                                       const void *data), const void *data)
{
    guththila_hash_t *res;
    guththila_hash_entry_t *new_vals = NULL;
    guththila_hash_entry_t *iter;
    guththila_hash_entry_t *ent;
    unsigned int i, j, k;

#if GUTHTHILA_POOL_DEBUG
    /* we don't copy keys and values, so it's necessary that
     * overlay->a.environment and base->a.environment have a life span at least
     * as long as p
     */
    if (!guththila_environment_is_ancestor (overlay->environment, p))
    {
        fprintf (stderr,
                 "guththila_hash_merge: overlay's environment is not an ancestor of p\n");
        abort ();
    }
    if (!guththila_environment_is_ancestor (base->environment, p))
    {
        fprintf (stderr,
                 "guththila_hash_merge: base's environment is not an ancestor of p\n");
        abort ();
    }
#endif

    res =
        GUTHTHILA_MALLOC (environment->allocator, sizeof (guththila_hash_t));
    res->environment = environment;
    res->free = NULL;
    res->hash_func = base->hash_func;
    res->count = base->count;
    res->max = (overlay->max > base->max) ? overlay->max : base->max;
    if (base->count + overlay->count > res->max)
    {
        res->max = res->max * 2 + 1;
    }
    res->array = alloc_array (res, res->max);
    if (base->count + overlay->count)
    {
        new_vals =
            GUTHTHILA_MALLOC (environment->allocator,
                              sizeof (guththila_hash_entry_t) * (base->count +
                                                                 overlay->
                                                                 count));
    }
    j = 0;
    for (k = 0; k <= base->max; k++)
    {
        for (iter = base->array[k]; iter; iter = iter->next)
        {
            i = iter->hash & res->max;
            new_vals[j].klen = iter->klen;
            new_vals[j].key = iter->key;
            new_vals[j].val = iter->val;
            new_vals[j].hash = iter->hash;
            new_vals[j].next = res->array[i];
            res->array[i] = &new_vals[j];
            j++;
        }
    }

    for (k = 0; k <= overlay->max; k++)
    {
        for (iter = overlay->array[k]; iter; iter = iter->next)
        {
            i = iter->hash & res->max;
            for (ent = res->array[i]; ent; ent = ent->next)
            {
                if ((ent->klen == iter->klen) &&
                    (memcmp (ent->key, iter->key, iter->klen) == 0))
                {
                    if (merger)
                    {
                        ent->val =
                            (*merger) (environment, iter->key, iter->klen,
                                       iter->val, ent->val, data);
                    }
                    else
                    {
                        ent->val = iter->val;
                    }
                    break;
                }
            }
            if (!ent)
            {
                new_vals[j].klen = iter->klen;
                new_vals[j].key = iter->key;
                new_vals[j].val = iter->val;
                new_vals[j].hash = iter->hash;
                new_vals[j].next = res->array[i];
                res->array[i] = &new_vals[j];
                res->count++;
                j++;
            }
        }
    }
    return res;
}


static void
guththila_hash_entry_free (guththila_environment_t *environment,
                           guththila_hash_entry_t *hash_entry)
{
    if(!environment)    return;
    if (!hash_entry)
        return;
    if (hash_entry->next)
    {
        guththila_hash_entry_free (environment, hash_entry->next);
    }
    GUTHTHILA_FREE (environment->allocator, hash_entry);
    return;
}

GUTHTHILA_DECLARE(guththila_status_t)
guththila_hash_free (guththila_environment_t *environment,
                     guththila_hash_t *ht)
{
    if(!environment) return GUTHTHILA_FAILURE;
    if (ht)
    {
        if (ht->free)
            guththila_hash_entry_free (environment, ht->free);
        GUTHTHILA_FREE(environment->allocator, ht->array);
        GUTHTHILA_FREE (environment->allocator, ht);
        return GUTHTHILA_SUCCESS;
    }
    return GUTHTHILA_FAILURE;
}