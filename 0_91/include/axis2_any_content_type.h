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

#ifndef AXIS2_ANY_CONTENT_TYPE_H
#define AXIS2_ANY_CONTENT_TYPE_H

/**
 * @file axis2_any_content_type.h
 * @brief Axis2 core addressing interface
 */

#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_const.h>
#include <axis2_hash.h>
#include <axis2_qname.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct axis2_any_content_type;
    struct axis2_any_content_type_ops;
    
/**
 * @defgroup axis2_any_content_type WS Addressing any content type
 * @ingroup axis2_addr
 * @{
 */

/**
 *   \brief any_content_type ops struct
 */
 AXIS2_DECLARE_DATA typedef struct axis2_any_content_type_ops
    { 
        /**
         * Adds given value to the content value map.
         * @param any_content_type any_content_type struct. cannot be NULL.
         * @param env Environment. MUST NOT be NULL.
         * @param value value to be added.
         * @return AXIS2_SUCCESS on success else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
        add_value)(struct axis2_any_content_type *any_content_type,
                   axis2_env_t **env, 
                   axis2_qname_t *qname, 
                   axis2_char_t *value); 
       
        /**
         * Gets the value from the content value map.
         * @param any_content_type any_content_type struct. cannot be NULL.
         * @param env Environment. MUST NOT be NULL.
         * @param qname qname of the corresponging value to be retrived
         * @return Pointer to the value if present, else returns NULL. 
         *          Environment status would be set to AXIS2_FAILURE on error.
         */
        axis2_char_t* (AXIS2_CALL *
		get_value)(struct axis2_any_content_type *any_content_type, 
				   axis2_env_t **env, 
				   axis2_qname_t *qname);
        /**
         * Gets the map of values
         * @param any_content_type any_content_type struct. cannot be NULL.
         * @param env Environment. MUST NOT be NULL.
         * @return Pointer to the value map. Would return NULL and set 
         *          Environment status to AXIS2_FAILURE on error.
         */
        axis2_hash_t* (AXIS2_CALL *
		get_value_map)(struct axis2_any_content_type *any_content_type, 
					   axis2_env_t **env);
		
        /**
         * Frees the given any_content_type struct
         * @param any_content_type any_content_type struct. cannot be NULL.
         * @param env Environment. MUST NOT be NULL.
         * @return AXIS2_SUCCESS on success else AXIS2_FAILURE
         */
        axis2_status_t (AXIS2_CALL *
		free)(struct axis2_any_content_type *any_content_type, 
              axis2_env_t **env);
		
    } axis2_any_content_type_ops_t;
	
   /** 
    * \brief axis2_any_content_type struct
    */
    typedef struct axis2_any_content_type
    {
        /** axis2_any_content_type related ops */
        axis2_any_content_type_ops_t *ops;
    } axis2_any_content_type_t;


/**
 * creates an instance of any_content_type struct
 * @param env Environment. MUST NOT be NULL.
 * @return Pointer to the newly created any_content_type instance. Returns NULL on error.
 */
AXIS2_DECLARE(axis2_any_content_type_t*) 
axis2_any_content_type_create(axis2_env_t **env);
    
    
/**************************** Start of function macros ************************/    
#define AXIS2_ANY_CONTENT_TYPE_ADD_VALUE(any_content_type, env, qname, value) \
    ((any_content_type)->ops->add_value(any_content_type, env, qname, value))
    
#define AXIS2_ANY_CONTENT_TYPE_GET_VALUE(any_content_type, env, qname) \
    ((any_content_type)->ops->get_value(any_content_type, env, qname))
    
#define AXIS2_ANY_CONTENT_TYPE_GET_VALUE_MAP(any_content_type, env) \
    ((any_content_type)->ops->get_value_map(any_content_type, env))
    
#define AXIS2_ANY_CONTENT_TYPE_FREE(any_content_type, env) \
    ((any_content_type)->ops->free(any_content_type, env))

    
/** @} */
    
#ifdef __cplusplus
}
#endif

#endif    /* AXIS2_ANY_CONTENT_TYPE_H */