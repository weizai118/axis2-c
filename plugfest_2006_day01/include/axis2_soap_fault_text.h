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
 
 #ifndef AXIS2_SOAP_FAULT_TEXT_H
 #define AXIS2_SOAP_FAULT_TEXT_H
 
   /**
    * @file axis2_soap_fault_text.h
    * @brief axis2_soap_fault_text 
    */
#include <axis2_env.h>
#include <axis2_soap_fault_reason.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct axis2_soap_fault_text_ops axis2_soap_fault_text_ops_t;
    typedef struct axis2_soap_fault_text axis2_soap_fault_text_t;
/**
 * @defgroup axis2_soap_fault_text
 * @ingroup axis2_soap
 * @{
 */

/**
 *   \brief soap_fault_text operations struct
 *   ops Encapsulator struct of axis2_soap_fault_text
 */
 AXIS2_DECLARE_DATA   struct axis2_soap_fault_text_ops
    {
      /**
        * Free an axis2_soap_fault_text
        * @param  fault_text pointer to soap_fault_text struct
        * @param  env Environment. MUST NOT be NULL
        * @return satus of the op. AXIS2_SUCCESS on success 
        *         else AXIS2_FAILURE
        */

        axis2_status_t (AXIS2_CALL *free_fn)
                                    (axis2_soap_fault_text_t *fault_text,
                                     axis2_env_t **env);

        axis2_status_t (AXIS2_CALL *set_lang)
                                    (axis2_soap_fault_text_t *fault_text,
                                     axis2_env_t **env,
                                     axis2_char_t* lang);
                                     
        axis2_char_t* (AXIS2_CALL *get_lang)                                         
                                    (axis2_soap_fault_text_t *fault_text,
                                     axis2_env_t **env);
                                     
        axis2_status_t (AXIS2_CALL *set_base_node)
                                    (axis2_soap_fault_text_t *fault_text,
                                     axis2_env_t **env,
                                     axis2_om_node_t *node);
    
        axis2_om_node_t* (AXIS2_CALL *get_base_node)
                                (axis2_soap_fault_text_t *fault_text,
                                 axis2_env_t **env);
                                 
        int (AXIS2_CALL *get_soap_version)
                                       (axis2_soap_fault_text_t *fault_text,
                                        axis2_env_t **env);
                                        
        axis2_status_t (AXIS2_CALL *set_soap_version)
                                       (axis2_soap_fault_text_t *fault_text,
                                        axis2_env_t **env,
                                        int soap_version);                                  
                                                                                                                
    };      

  /**
    * \brief soap_fault_text struct
    * represent a soap_fault_text
    */
    struct axis2_soap_fault_text
    {
        /** operation of axis2_soap_fault_text struct */
        axis2_soap_fault_text_ops_t *ops;
       
    };

  /**
    * creates a soap struct 
    * @param env Environment. MUST NOT be NULL
    */
AXIS2_DECLARE(axis2_soap_fault_text_t *)
axis2_soap_fault_text_create_with_parent(axis2_env_t **env,
                            axis2_soap_fault_reason_t *fault);
                            

AXIS2_DECLARE(axis2_soap_fault_text_t *)
axis2_soap_fault_text_create(axis2_env_t **env);

                                     

/******************** Macros **************************************************/
    
    
/** free soap_fault_text */
#define AXIS2_SOAP_FAULT_TEXT_FREE(fault_text , env) \
        ((fault_text)->ops->free_fn(fault_text, env))

#define AXIS2_SOAP_FAULT_TEXT_SET_LANG(fault_text , env, lang) \
        ((fault_text)->ops->set_lang(fault_text, env, lang))
        
#define AXIS2_SOAP_FAULT_TEXT_GET_LANG(fault_text , env) \
        ((fault_text)->ops->get_lang(fault_text, env)) 
        
#define AXIS2_SOAP_FAULT_TEXT_GET_BASE_NODE(fault_text, env) \
        ((fault_text)->ops->get_base_node(fault_text, env))         

#define AXIS2_SOAP_FAULT_TEXT_SET_BASE_NODE(fault_text, env, node) \
        ((fault_text)->ops->set_base_node(fault_text, env, node))
        
#define AXIS2_SOAP_FAULT_TEXT_GET_SOAP_VERSION(fault_text, env) \
        ((fault_text)->ops->get_soap_version(fault_text, env))
        
#define AXIS2_SOAP_FAULT_TEXT_SET_SOAP_VERSION(fault_text, env, version) \
        ((fault_text)->ops->set_soap_version(fault_text, env, version))
/** @} */

#ifdef __cplusplus
}
#endif 
 
#endif /* AXIS2_SOAP_FAULT_TEXT_H */
