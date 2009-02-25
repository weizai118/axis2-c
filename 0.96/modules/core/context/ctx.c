/*
 * Licensed to the Apache Software Foundation (ASF) under one or more
 * contributor license agreements.  See the NOTICE file distributed with
 * this work for additional information regarding copyright ownership.
 * The ASF licenses this file to You under the Apache License, Version 2.0
 * (the "License"); you may not use this file except in compliance with
 * the License.  You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <axis2_ctx.h>
#include <axis2_const.h>
#include <axis2_hash.h>

typedef struct axis2_ctx_impl
{
    /** context base struct */
    axis2_ctx_t ctx;
    /** non persistent map */
    axis2_hash_t *non_persistent_map;
    axis2_bool_t non_persistent_map_deep_copy;
    /** persistent map */
    axis2_hash_t *persistent_map;
    /*axis2_ctx_t *parent; This will not be required as the responsibility of
    knowing the parent is  delegated to impl structs */
}
axis2_ctx_impl_t;

/** Interface to implementation conversion macro */
#define AXIS2_INTF_TO_IMPL(ctx) ((axis2_ctx_impl_t *)ctx)

axis2_property_t *AXIS2_CALL
axis2_ctx_get_property(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env,
    const axis2_char_t *key,
    const axis2_bool_t persistent);

axis2_hash_t *AXIS2_CALL
axis2_ctx_get_all_properties(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_ctx_set_property(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    const axis2_char_t *key,
    axis2_property_t *value,
    const axis2_bool_t persistent);

axis2_hash_t *AXIS2_CALL
axis2_ctx_get_non_persistent_map(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env);


axis2_hash_t *AXIS2_CALL
axis2_ctx_get_persistent_map(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_ctx_set_non_persistent_map(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    axis2_hash_t *map);

axis2_status_t AXIS2_CALL
axis2_ctx_set_persistent_map(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    axis2_hash_t *map);

axis2_status_t AXIS2_CALL
axis2_ctx_free(
    struct axis2_ctx *ctx,
    const axis2_env_t *env);


AXIS2_EXTERN axis2_ctx_t *AXIS2_CALL
axis2_ctx_create(
    const axis2_env_t *env)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);

    ctx_impl = AXIS2_MALLOC(env->allocator, sizeof(axis2_ctx_impl_t));
    if (!ctx_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    ctx_impl->persistent_map = NULL;
    ctx_impl->non_persistent_map = NULL;

    ctx_impl->persistent_map = axis2_hash_make(env);
    if (!(ctx_impl->persistent_map))
    {
        axis2_ctx_free(&(ctx_impl->ctx), env);
        return NULL;
    }

    ctx_impl->non_persistent_map = axis2_hash_make(env);
    ctx_impl->non_persistent_map_deep_copy = AXIS2_TRUE;
    if (!(ctx_impl->non_persistent_map))
    {
        axis2_ctx_free(&(ctx_impl->ctx), env);
        return NULL;
    }

    /* initialize ops */
    ctx_impl->ctx.ops = NULL;
    ctx_impl->ctx.ops  = AXIS2_MALLOC(env->allocator, sizeof(axis2_ctx_ops_t));
    if (!ctx_impl->ctx.ops)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        axis2_ctx_free(&(ctx_impl->ctx), env);
        return NULL;
    }

    ctx_impl->ctx.ops->get_property = axis2_ctx_get_property;
    ctx_impl->ctx.ops->get_all_properties = axis2_ctx_get_all_properties;
    ctx_impl->ctx.ops->set_property = axis2_ctx_set_property;
    ctx_impl->ctx.ops->get_non_persistent_map = axis2_ctx_get_non_persistent_map;
    ctx_impl->ctx.ops->get_persistent_map = axis2_ctx_get_persistent_map;
    ctx_impl->ctx.ops->set_non_persistent_map = axis2_ctx_set_non_persistent_map;
    ctx_impl->ctx.ops->set_persistent_map = axis2_ctx_set_persistent_map;
    ctx_impl->ctx.ops->free = axis2_ctx_free;

    return &(ctx_impl->ctx);
}

axis2_status_t AXIS2_CALL
axis2_ctx_set_property(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    const axis2_char_t *key,
    axis2_property_t *value,
    const axis2_bool_t persistent)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    if (persistent)
    {
        if (ctx_impl->persistent_map)
            axis2_hash_set(ctx_impl->persistent_map, key,
                    AXIS2_HASH_KEY_STRING, value);
    }
    else
    {
        if (value)
        {
            /* handle the case where we are setting a new value with the 
               same key, we would have to free the existing value */
            axis2_property_t *temp_value = 
                axis2_hash_get(ctx_impl->non_persistent_map, key, 
                    AXIS2_HASH_KEY_STRING);
			if (temp_value)
			{
				void *temp_value_value = AXIS2_PROPERTY_GET_VALUE (temp_value, env);
				void *value_value = AXIS2_PROPERTY_GET_VALUE (value, env);
				if (temp_value_value != value_value)
				{
					AXIS2_PROPERTY_FREE(temp_value, env);
				}
			}
        }
        if (ctx_impl->non_persistent_map)
            axis2_hash_set(ctx_impl->non_persistent_map, key,
                    AXIS2_HASH_KEY_STRING, value);
    }
    return AXIS2_SUCCESS;
}

axis2_property_t *AXIS2_CALL
axis2_ctx_get_property(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env,
    const axis2_char_t *key,
    const axis2_bool_t persistent)
{
    axis2_ctx_impl_t *ctx_impl = NULL;
    axis2_property_t *ret = NULL;

    AXIS2_ENV_CHECK(env, NULL);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    if (persistent)
    {
        if (ctx_impl->persistent_map)
            ret = axis2_hash_get(ctx_impl->persistent_map, key, AXIS2_HASH_KEY_STRING);
    }

    if (!ret)
    {
        if (ctx_impl->non_persistent_map)
            ret = axis2_hash_get(ctx_impl->non_persistent_map, key, AXIS2_HASH_KEY_STRING);
    }
    /** it is the responsibility of the caller to look-up parent if key is not found here
        Note that in C implementation it is the responsibility of the deriving struct to 
        handle the parent as we do not have the inheritance facility. In case of 
        context it is not worth trying to mimic inheritance. */

    return ret;
}

axis2_hash_t *AXIS2_CALL
axis2_ctx_get_all_properties(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    return ctx_impl->non_persistent_map;
}


axis2_hash_t *AXIS2_CALL
axis2_ctx_get_non_persistent_map(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(ctx)->non_persistent_map;
}

axis2_hash_t *AXIS2_CALL
axis2_ctx_get_persistent_map(
    const axis2_ctx_t *ctx,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(ctx)->persistent_map;
}

axis2_status_t AXIS2_CALL
axis2_ctx_free(
    struct axis2_ctx *ctx,
    const axis2_env_t *env)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    if (ctx_impl->ctx.ops)
    {
        AXIS2_FREE(env->allocator, ctx_impl->ctx.ops);
        ctx_impl->ctx.ops = NULL;
    }

    if (ctx_impl->non_persistent_map && ctx_impl->non_persistent_map_deep_copy)
    {
        axis2_hash_index_t *hi = NULL;
        void *val = NULL;
        const void *key = NULL;
        for (hi = axis2_hash_first(ctx_impl->non_persistent_map, env);
                hi; hi = axis2_hash_next(env, hi))
        {
            axis2_property_t *property = NULL;

            axis2_hash_this(hi, &key, NULL, &val);
            property = (axis2_property_t *) val;

            if (property)
            {
                AXIS2_PROPERTY_FREE(property, env);
                property = NULL;
            }

            val = NULL;
            key = NULL;
        }
        axis2_hash_free(ctx_impl->non_persistent_map, env);
        ctx_impl->non_persistent_map = NULL;
    }

    if (ctx_impl->persistent_map)
    {
        axis2_hash_index_t *hi = NULL;
        void *val = NULL;
        const void *key = NULL;
        for (hi = axis2_hash_first(ctx_impl->persistent_map, env);
                hi; hi = axis2_hash_next(env, hi))
        {
            axis2_property_t *property = NULL;

            axis2_hash_this(hi, &key, NULL, &val);
            property = (axis2_property_t *) val;

            if (property)
            {
                AXIS2_PROPERTY_FREE(property, env);
                property = NULL;
            }

            val = NULL;
            key = NULL;
        }
        axis2_hash_free(ctx_impl->persistent_map, env);
        ctx_impl->persistent_map = NULL;
    }

    AXIS2_FREE(env->allocator, ctx_impl);
    ctx_impl = NULL;

    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_ctx_set_non_persistent_map(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    axis2_hash_t *map)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    if (ctx_impl->non_persistent_map && ctx_impl->non_persistent_map_deep_copy)
    {
        axis2_hash_index_t *hi = NULL;
        void *val = NULL;
        const void *key = NULL;
        for (hi = axis2_hash_first(ctx_impl->non_persistent_map, env);
                hi; hi = axis2_hash_next(env, hi))
        {
            axis2_property_t *property = NULL;

            axis2_hash_this(hi, &key, NULL, &val);
            property = (axis2_property_t *) val;

            if (property)
            {
                AXIS2_PROPERTY_FREE(property, env);
                property = NULL;
            }

            val = NULL;
            key = NULL;
        }
        if (ctx_impl->non_persistent_map != map) /* handle repeated invocation case */
        {
            axis2_hash_free(ctx_impl->non_persistent_map, env);
            ctx_impl->non_persistent_map = NULL;
        }
    }

    ctx_impl->non_persistent_map = map;
    ctx_impl->non_persistent_map_deep_copy = AXIS2_FALSE;

    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_ctx_set_persistent_map(
    struct axis2_ctx *ctx,
    const axis2_env_t *env,
    axis2_hash_t *map)
{
    axis2_ctx_impl_t *ctx_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    ctx_impl = AXIS2_INTF_TO_IMPL(ctx);

    if (ctx_impl->persistent_map)
    {
        axis2_hash_index_t *hi = NULL;
        void *val = NULL;
        const void *key = NULL;
        for (hi = axis2_hash_first(ctx_impl->persistent_map, env);
                hi; hi = axis2_hash_next(env, hi))
        {
            axis2_property_t *property = NULL;

            axis2_hash_this(hi, &key, NULL, &val);
            property = (axis2_property_t *) val;

            if (property)
            {
                AXIS2_PROPERTY_FREE(property, env);
                property = NULL;
            }

            val = NULL;
            key = NULL;
        }
        axis2_hash_free(ctx_impl->persistent_map, env);
        ctx_impl->persistent_map = NULL;
    }

    ctx_impl->persistent_map = map;

    return AXIS2_SUCCESS;
}