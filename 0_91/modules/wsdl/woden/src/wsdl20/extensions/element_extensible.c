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
 
#include <woden/wsdl20/extensions/axis2_woden_element_extensible.h>
#include <woden/wsdl20/extensions/axis2_woden_ext_element.h>
#include <axis2_url.h>
#include <axis2_hash.h>

typedef struct axis2_woden_element_extensible_impl axis2_woden_element_extensible_impl_t;

/** 
 * @brief Element Extensible Struct Impl
 *	Axis2 Element Extensible  
 */ 
struct axis2_woden_element_extensible_impl
{
    axis2_woden_element_extensible_t extensible;
    axis2_woden_obj_types_t obj_type;
    axis2_array_list_t *f_ext_elements;
    axis2_array_list_t *temp_elems;
};

#define INTF_TO_IMPL(extensible) \
    ((axis2_woden_element_extensible_impl_t *) extensible)

axis2_status_t AXIS2_CALL 
axis2_woden_element_extensible_free(
        void *extensible,
        axis2_env_t **envv);

axis2_woden_obj_types_t AXIS2_CALL 
axis2_woden_element_extensible_type(
        void *extensible,
        axis2_env_t **envv);

axis2_status_t AXIS2_CALL 
axis2_woden_element_extensible_add_ext_element(
        void *extensible,
        axis2_env_t **env,
        axis2_woden_ext_element_t *ext_el); 

axis2_status_t AXIS2_CALL 
axis2_woden_element_extensible_remove_ext_element(
        void *extensible,
        axis2_env_t **env,
        axis2_woden_ext_element_t *ext_el); 

axis2_array_list_t *AXIS2_CALL 
axis2_woden_element_extensible_get_ext_elements(
        void *extensible,
        axis2_env_t **env); 

axis2_array_list_t *AXIS2_CALL 
axis2_woden_element_extensible_get_ext_elements_of_type(
        void *extensible,
        axis2_env_t **env,
        axis2_qname_t *ext_type);

axis2_bool_t AXIS2_CALL 
axis2_woden_element_extensible_has_ext_elements_for_namespace(
        void *extensible,
        axis2_env_t **env,
        axis2_url_t *namespc);



AXIS2_DECLARE(axis2_woden_element_extensible_t *)
axis2_woden_element_extensible_create(
        axis2_env_t **env)
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    extensible_impl = AXIS2_MALLOC((*env)->allocator, 
                    sizeof(axis2_woden_element_extensible_impl_t));

    extensible_impl->obj_type = AXIS2_WODEN_ELEMENT_EXTENSIBLE;
    extensible_impl->f_ext_elements = NULL;
    extensible_impl->temp_elems = NULL;

    extensible_impl->extensible.ops = 
        AXIS2_MALLOC((*env)->allocator, 
                sizeof(axis2_woden_element_extensible_ops_t)); 
    
    extensible_impl->extensible.ops->free = 
        axis2_woden_element_extensible_free;
    extensible_impl->extensible.ops->type = 
        axis2_woden_element_extensible_type;
    extensible_impl->extensible.ops->add_ext_element = 
        axis2_woden_element_extensible_add_ext_element;
    extensible_impl->extensible.ops->remove_ext_element = 
        axis2_woden_element_extensible_remove_ext_element;
    extensible_impl->extensible.ops->get_ext_elements = 
        axis2_woden_element_extensible_get_ext_elements;
    extensible_impl->extensible.ops->get_ext_elements_of_type = 
        axis2_woden_element_extensible_get_ext_elements_of_type;
    extensible_impl->extensible.ops->has_ext_elements_for_namespace = 
        axis2_woden_element_extensible_has_ext_elements_for_namespace;
    
    return &(extensible_impl->extensible);
}

axis2_status_t AXIS2_CALL
axis2_woden_element_extensible_free(void *extensible,
                axis2_env_t **env)
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);

    if(extensible_impl->f_ext_elements)
    {
        AXIS2_ARRAY_LIST_FREE(extensible_impl->f_ext_elements, env);
        extensible_impl->f_ext_elements = NULL;
    }
    
    if(extensible_impl->temp_elems)
    {
        int size = 0, i = 0;
        size = AXIS2_ARRAY_LIST_SIZE(extensible_impl->temp_elems, env);
        for(i = 0; i < size; i++)
        {
            void *ext_el = NULL;

            ext_el = AXIS2_ARRAY_LIST_GET(extensible_impl->temp_elems, env, i);
            AXIS2_WODEN_XML_ATTR_FREE(ext_el, env);
        }
        AXIS2_ARRAY_LIST_FREE(extensible_impl->temp_elems, env);
        extensible_impl->temp_elems = NULL;
    }

    if((&(extensible_impl->extensible))->ops)
    {
        AXIS2_FREE((*env)->allocator, (&(extensible_impl->extensible))->ops);
        (&(extensible_impl->extensible))->ops = NULL;
    }

    if(extensible_impl)
    {
        AXIS2_FREE((*env)->allocator, extensible_impl);
        extensible_impl = NULL;
    }
    return AXIS2_SUCCESS;
}

axis2_woden_obj_types_t AXIS2_CALL 
axis2_woden_element_extensible_type(
        void *extensible,
        axis2_env_t **env)
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);
    
    return extensible_impl->obj_type;
}

axis2_status_t AXIS2_CALL
axis2_woden_element_extensible_resolve_methods(
        axis2_woden_element_extensible_t *extensible,
        axis2_env_t **env,
        axis2_hash_t *methods)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, methods, AXIS2_FAILURE);
    
    extensible->ops->free = axis2_hash_get(methods, "free", 
            AXIS2_HASH_KEY_STRING);
    extensible->ops->to_element_extensible_free = axis2_hash_get(methods, 
            "to_element_extensible_free", AXIS2_HASH_KEY_STRING); 
    extensible->ops->add_ext_element = axis2_hash_get(methods, 
            "add_ext_element", AXIS2_HASH_KEY_STRING); 
    extensible->ops->remove_ext_element = axis2_hash_get(methods, 
            "remove_ext_element", AXIS2_HASH_KEY_STRING); 
    extensible->ops->get_ext_elements = axis2_hash_get(methods, 
            "get_ext_elements", AXIS2_HASH_KEY_STRING); 
    extensible->ops->get_ext_elements_of_type = axis2_hash_get(methods, 
            "get_ext_elements_of_type", AXIS2_HASH_KEY_STRING);
    extensible->ops->has_ext_elements_for_namespace = axis2_hash_get(methods, 
            "has_ext_elements_for_namespace", AXIS2_HASH_KEY_STRING);

    return AXIS2_SUCCESS;    
}

axis2_status_t AXIS2_CALL 
axis2_woden_element_extensible_add_ext_element(
                                    void *extensible,
                                    axis2_env_t **env,
                                    axis2_woden_ext_element_t *ext_el) 
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, ext_el, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);
    
    return AXIS2_ARRAY_LIST_ADD(extensible_impl->f_ext_elements, env, ext_el);
}

axis2_status_t AXIS2_CALL 
axis2_woden_element_extensible_remove_ext_element(
                                    void *extensible,
                                    axis2_env_t **env,
                                    axis2_woden_ext_element_t *ext_el) 
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;
    int index = -1;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, ext_el, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);

    index = AXIS2_ARRAY_LIST_INDEX_OF(extensible_impl->f_ext_elements, env, ext_el);
    AXIS2_ARRAY_LIST_REMOVE(extensible_impl->f_ext_elements, env, index);
    return AXIS2_SUCCESS;
}

axis2_array_list_t *AXIS2_CALL 
axis2_woden_element_extensible_get_ext_elements(void *extensible,
                                                axis2_env_t **env) 
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);
    
    return extensible_impl->f_ext_elements;
}

axis2_array_list_t *AXIS2_CALL 
axis2_woden_element_extensible_get_ext_elements_of_type(void *extensible,
                                                        axis2_env_t **env,
                                                        axis2_qname_t *ext_type) 
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;
    int i = 0;
    int size = 0;
    
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, ext_type, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);

    if(extensible_impl->temp_elems)
    {
        int size = 0, i = 0;
        size = AXIS2_ARRAY_LIST_SIZE(extensible_impl->temp_elems, env);
        for(i = 0; i < size; i++)
        {
            void *ext_el = NULL;

            ext_el = AXIS2_ARRAY_LIST_GET(extensible_impl->temp_elems, env, i);
            AXIS2_WODEN_XML_ATTR_FREE(ext_el, env);
        }
        AXIS2_ARRAY_LIST_FREE(extensible_impl->temp_elems, env);
        extensible_impl->temp_elems = NULL;
    }

    extensible_impl->temp_elems = axis2_array_list_create(env, 0);
    size = AXIS2_ARRAY_LIST_SIZE(extensible_impl->f_ext_elements, env);
    for(i = 0; i < size; i++)
    {
        axis2_woden_ext_element_t *ext_elem = NULL;
        axis2_qname_t *ext_type_l = NULL;
        
        ext_elem = (axis2_woden_ext_element_t *)AXIS2_ARRAY_LIST_GET(
                extensible_impl->f_ext_elements, env, i);
        ext_type_l = AXIS2_WODEN_EXT_ELEMENT_GET_EXT_TYPE(ext_elem, env);
        if(AXIS2_TRUE == AXIS2_QNAME_EQUALS(ext_type, env, ext_type_l))
        {
            AXIS2_ARRAY_LIST_ADD(extensible_impl->temp_elems, env, ext_elem);
        }
    }
    return extensible_impl->temp_elems;
}

axis2_bool_t AXIS2_CALL 
axis2_woden_element_extensible_has_ext_elements_for_namespace(void *extensible,
                                                                axis2_env_t **env,
                                                                axis2_url_t *namespc)
{
    axis2_woden_element_extensible_impl_t *extensible_impl = NULL;
    axis2_bool_t result = AXIS2_FALSE;
    axis2_char_t *ext_ns = NULL;
    int i = 0;
    int size = 0;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK((*env)->error, namespc, AXIS2_FAILURE);
    extensible_impl = INTF_TO_IMPL(extensible);

    ext_ns = AXIS2_URL_TO_EXTERNAL_FORM(namespc, env);
    size = AXIS2_ARRAY_LIST_SIZE(extensible_impl->f_ext_elements, env);
    for(i = 0; i < size; i++)
    {
        axis2_woden_ext_element_t *ext_elem = NULL;
        axis2_qname_t *ext_type = NULL;
        axis2_char_t *uri = NULL;
        
        ext_elem = (axis2_woden_ext_element_t *) AXIS2_ARRAY_LIST_GET(
                extensible_impl->f_ext_elements, env, i);
        ext_type = AXIS2_WODEN_EXT_ELEMENT_GET_EXT_TYPE(ext_elem, env);
        uri = AXIS2_QNAME_GET_URI(ext_type, env);
        if(0 == AXIS2_STRCMP(uri, ext_ns))
        {
            result = AXIS2_TRUE;
            break;
        }
    }
    return result;
}

