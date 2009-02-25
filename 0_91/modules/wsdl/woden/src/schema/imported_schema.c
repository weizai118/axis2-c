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

#include <woden/schema/axis2_woden_imported_schema.h>
#include <xml_schema/axis2_xml_schema.h>
#include <axis2_url.h>

typedef struct axis2_woden_imported_schema_impl axis2_woden_imported_schema_impl_t;

/** 
 * @brief Imported Schema Struct Impl
 *	Axis2 Imported Schema  
 */ 
struct axis2_woden_imported_schema_impl
{
    axis2_woden_imported_schema_t imported_schema;
    axis2_woden_schema_t *schema;
    axis2_woden_obj_types_t obj_type;
    axis2_hash_t *methods;
    axis2_url_t *f_schema_location;
};

#define INTF_TO_IMPL(schema) \
    ((axis2_woden_imported_schema_impl_t *) schema)

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_free(
        void *schema,
        axis2_env_t **env);

axis2_woden_obj_types_t AXIS2_CALL 
axis2_woden_imported_schema_type(
        void *schema,
        axis2_env_t **env);

axis2_woden_schema_t *AXIS2_CALL
axis2_woden_imported_schema_get_base_impl(
        void *schema,
        axis2_env_t **env);

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_location(
        void *schema,
        axis2_env_t **env,
        axis2_url_t *location);

axis2_url_t *AXIS2_CALL
axis2_woden_imported_schema_get_location(
        void *schema,
        axis2_env_t **env);

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_namespace(
        void *schema,
        axis2_env_t **env,
        axis2_url_t *namespc);

axis2_url_t *AXIS2_CALL 
axis2_woden_imported_schema_get_namespace(
        void *schema,
        axis2_env_t **env);

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_schema_def(
        void *schema,
        axis2_env_t **env,
        axis2_xml_schema_t *schema_def);

axis2_xml_schema_t *AXIS2_CALL 
axis2_woden_imported_schema_get_schema_def(
        void *schema,
        axis2_env_t **env);

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_referenceable(
        void *schema,
        axis2_env_t **env,
        axis2_bool_t referenceable);

axis2_bool_t AXIS2_CALL 
axis2_woden_imported_schema_is_referenceable(
        void *schema,
        axis2_env_t **env);

axis2_char_t *AXIS2_CALL 
axis2_woden_imported_schema_get_namespace_as_string(
        void *schema,
        axis2_env_t **env);


static axis2_woden_imported_schema_t *
create(axis2_env_t **env);

/************************Woden C Internal Methods******************************/
AXIS2_DECLARE(axis2_woden_imported_schema_t *)
axis2_woden_imported_schema_to_schema(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    if(!schema)
    {
        schema_impl = (axis2_woden_imported_schema_impl_t *) create(env);
    }
    else
        schema_impl = (axis2_woden_imported_schema_impl_t *) schema;
    schema_impl->imported_schema.schema.ops = 
            AXIS2_MALLOC((*env)->allocator, 
            sizeof(axis2_woden_schema_ops_t));
    axis2_woden_schema_resolve_methods(&(schema_impl->imported_schema.schema), 
            env, schema_impl->methods);

    return schema;
}

axis2_status_t AXIS2_CALL
axis2_woden_imported_schema_to_schema_free(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    if(schema_impl->imported_schema.schema.ops)
    {
        AXIS2_FREE((*env)->allocator, schema_impl->imported_schema.schema.ops);
        schema_impl->imported_schema.schema.ops = NULL;
    }
    return AXIS2_SUCCESS;
}
/************************End of Woden C Internal Methods***********************/

static axis2_woden_imported_schema_t *
create(
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;
     
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = AXIS2_MALLOC((*env)->allocator, 
                    sizeof(axis2_woden_imported_schema_impl_t));

    schema_impl->schema = NULL;
    schema_impl->obj_type = AXIS2_WODEN_IMPORTED_SCHEMA;
    schema_impl->methods = NULL;
    schema_impl->f_schema_location = NULL;

    schema_impl->imported_schema.schema.ops = NULL;

    schema_impl->imported_schema.ops = 
        AXIS2_MALLOC((*env)->allocator, 
                sizeof(axis2_woden_imported_schema_ops_t));

    schema_impl->imported_schema.ops->free = 
        axis2_woden_imported_schema_free;
    schema_impl->imported_schema.ops->type = 
        axis2_woden_imported_schema_type;
    schema_impl->imported_schema.ops->get_base_impl = 
        axis2_woden_imported_schema_get_base_impl;
    schema_impl->imported_schema.ops->set_location = 
        axis2_woden_imported_schema_set_location;
    schema_impl->imported_schema.ops->get_location = 
        axis2_woden_imported_schema_get_location;
    
    
    schema_impl->methods = axis2_hash_make(env);
    if(!schema_impl->methods) 
    {
        AXIS2_ERROR_SET((*env)->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    axis2_hash_set(schema_impl->methods, "free", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_free);
    axis2_hash_set(schema_impl->methods, "to_schema_free", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_to_schema_free);
    axis2_hash_set(schema_impl->methods, "type", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_type);
    axis2_hash_set(schema_impl->methods, "set_location", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_set_location);
    axis2_hash_set(schema_impl->methods, "get_location", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_get_location);
    axis2_hash_set(schema_impl->methods, "set_namespace", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_set_namespace);
    axis2_hash_set(schema_impl->methods, "get_namespace", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_get_namespace);
    axis2_hash_set(schema_impl->methods, "set_schema_def", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_set_schema_def);
    axis2_hash_set(schema_impl->methods, "get_schema_def", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_get_schema_def);
    axis2_hash_set(schema_impl->methods, "set_referenceable", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_set_referenceable);
    axis2_hash_set(schema_impl->methods, "is_referencealbe", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_is_referenceable);
    axis2_hash_set(schema_impl->methods, "get_namespace_as_string", 
            AXIS2_HASH_KEY_STRING, axis2_woden_imported_schema_get_namespace_as_string);

    return &(schema_impl->imported_schema);
}
AXIS2_DECLARE(axis2_woden_imported_schema_t *)
axis2_woden_imported_schema_create(
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;
     
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = (axis2_woden_imported_schema_impl_t *) create(env);

    schema_impl->schema = axis2_woden_schema_create(env);
    return &(schema_impl->imported_schema);
}

axis2_woden_obj_types_t AXIS2_CALL 
axis2_woden_imported_schema_type(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return schema_impl->obj_type;
}

axis2_status_t AXIS2_CALL
axis2_woden_imported_schema_free(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    if(schema_impl->f_schema_location)
    {
        AXIS2_URL_FREE(schema_impl->f_schema_location, env);
        schema_impl->f_schema_location = NULL;
    }
 
    if(schema_impl->methods)
    {
        axis2_hash_free(schema_impl->methods, env);
        schema_impl->methods = NULL;
    }  

    if(schema_impl->schema)
    {
        AXIS2_WODEN_SCHEMA_FREE(schema_impl->schema, env);
        schema_impl->schema = NULL;
    }
    
    if(schema_impl->imported_schema.schema.ops)
    {
        AXIS2_FREE((*env)->allocator, schema_impl->imported_schema.schema.ops);
        schema_impl->imported_schema.schema.ops = NULL;
    }

    if((&(schema_impl->imported_schema))->ops)
    {
        AXIS2_FREE((*env)->allocator, (&(schema_impl->imported_schema))->ops);
        (&(schema_impl->imported_schema))->ops = NULL;
    }

    if(schema_impl)
    {
        AXIS2_FREE((*env)->allocator, schema_impl);
        schema_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

axis2_woden_schema_t *AXIS2_CALL
axis2_woden_imported_schema_get_base_impl(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    schema_impl = INTF_TO_IMPL(schema);

    return schema_impl->schema;
}

axis2_status_t AXIS2_CALL
axis2_woden_imported_schema_resolve_methods(
        axis2_woden_imported_schema_t *schema,
        axis2_env_t **env,
        axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, methods, AXIS2_FAILURE);
    
    schema->ops->free = 
                axis2_hash_get(methods, "free", AXIS2_HASH_KEY_STRING);
    schema->ops->to_imported_schema_free = 
                axis2_hash_get(methods, "to_imported_schema_free", 
                AXIS2_HASH_KEY_STRING);
    schema->ops->type = 
                axis2_hash_get(methods, "type", AXIS2_HASH_KEY_STRING);
    schema->ops->set_location = axis2_hash_get(methods, "set_location", 
            AXIS2_HASH_KEY_STRING);
    schema->ops->get_location = axis2_hash_get(methods, "get_location", 
            AXIS2_HASH_KEY_STRING);;
    
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_location(
        void *schema,
        axis2_env_t **env,
        axis2_url_t *location)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    if(schema_impl->f_schema_location)
    {
        AXIS2_URL_FREE(schema_impl->f_schema_location, env);
        schema_impl->f_schema_location = NULL;
    }
    schema_impl->f_schema_location = location;
    return AXIS2_SUCCESS;
}

axis2_url_t *AXIS2_CALL 
axis2_woden_imported_schema_get_location(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return schema_impl->f_schema_location;
}

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_namespace(
        void *schema,
        axis2_env_t **env,
        axis2_url_t *namespc)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, namespc, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_SET_NAMESPACE(schema_impl->schema, env, namespc);
}

axis2_url_t *AXIS2_CALL 
axis2_woden_imported_schema_get_namespace(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_GET_NAMESPACE(schema_impl->schema, env);
}

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_schema_def(
        void *schema,
        axis2_env_t **env,
        axis2_xml_schema_t *schema_def)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, schema_def, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);
    
    return AXIS2_WODEN_SCHEMA_SET_SCHEMA_DEF(schema_impl->schema, env, 
            schema_def);
}

axis2_xml_schema_t *AXIS2_CALL 
axis2_woden_imported_schema_get_schema_def(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_GET_SCHEMA_DEF(schema_impl->schema, env);
}

axis2_status_t AXIS2_CALL 
axis2_woden_imported_schema_set_referenceable(
        void *schema,
        axis2_env_t **env,
        axis2_bool_t referenceable)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_SET_REFERENCEABLE(schema_impl->schema, env, 
            referenceable); 
}

axis2_bool_t AXIS2_CALL 
axis2_woden_imported_schema_is_referenceable(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_IS_REFERENCEABLE(schema_impl->schema, env);
}

axis2_char_t *AXIS2_CALL 
axis2_woden_imported_schema_get_namespace_as_string(
        void *schema,
        axis2_env_t **env)
{
    axis2_woden_imported_schema_impl_t *schema_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    schema_impl = INTF_TO_IMPL(schema);

    return AXIS2_WODEN_SCHEMA_GET_NAMESPACE_AS_STRING(schema_impl->schema, env);
}
