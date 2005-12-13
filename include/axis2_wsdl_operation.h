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

#ifndef AXIS2_WSDL_OPERATION_H
#define AXIS2_WSDL_OPERATION_H

/**
 * @file axis2_wsdl_op.h
 * @brief axis2 wsdl op interface
 */

#include <axis2.h>
#include <axis2_error.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_allocator.h>
#include <axis2_string.h>
#include <axis2_hash.h>

#include <axis2_qname.h>
#include <axis2_wsdl_component.h>
#include <axis2_linked_list.h>
#include <axis2_wsdl_msg_ref.h>
#include <axis2_wsdl_fault_ref.h>
#include <axis2_wsdl_svc.h>

#ifdef __cplusplus
extern "C"
{
#endif
struct axis2_wsdl_extensible_component;	
struct axis2_wsdl_fault_ref;    
typedef struct axis2_wsdl_op_ops axis2_wsdl_op_ops_t;
typedef struct axis2_wsdl_op axis2_wsdl_op_t;	
	

/** @defgroup axis2_wsdl_op Wsdl Operation
  * @ingroup axis2_wsdl
  * @{
  */

struct axis2_wsdl_op_ops
{
	/** Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (axis2_wsdl_op_t *wsdl_op,
            axis2_env_t **env);
        
    /**
     * set the message exchange pattern
     * @param axis2_char_t message exchange pattern
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    set_msg_exchange_pattern) (axis2_wsdl_op_t *wsdl_op, 
                                axis2_env_t **env, 
                                axis2_char_t *msg_exchange_pattern);
  
    /**
     * get the message exchange pattern
     * @return axis2_char_t message exchange pattern
     */
    axis2_char_t *(AXIS2_CALL *
    get_msg_exchange_pattern) (axis2_wsdl_op_t *wsdl_op, 
                                axis2_env_t **env);

    /**
     * Set the wsdl op name
     * @param axis2_qname_t* op name
     */
    axis2_status_t (AXIS2_CALL *
    set_name) (axis2_wsdl_op_t *wsdl_op, 
                axis2_env_t **env,
                axis2_qname_t *name);
                                        
    /**
     * Get the name of wsdl op
     * @return axis2_qname_t wsdl op name
     */
    axis2_qname_t *(AXIS2_CALL *
    get_name) (axis2_wsdl_op_t *wsdl_op,
                axis2_env_t **env);
    

    /**
     * set style
     * @param axis2_char_t style
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    set_style) (axis2_wsdl_op_t *wsdl_op,
                axis2_env_t **env,
                axis2_char_t *style);
    
    /**
     * Get style
     * @return axis2_char_t style
     */
    axis2_char_t *(AXIS2_CALL *
    get_style) (axis2_wsdl_op_t *wsdl_op,
                axis2_env_t **env);
    
    
    /**
     * Method getInfaults
     *
     * @return
     */
    axis2_linked_list_t * (AXIS2_CALL *
    get_infaults) (axis2_wsdl_op_t *wsdl_op,
                   axis2_env_t **env);
    
    /**
     * Method setInfaults
     *
     * @param infaults
     */
    axis2_status_t (AXIS2_CALL *
    set_infaults) (axis2_wsdl_op_t *wsdl_op,
                    axis2_env_t **env,
                    axis2_linked_list_t *infaults);
    
    /**
     * Method getInputMessage
     *
     * @return
     */
    struct axis2_wsdl_msg_ref *(AXIS2_CALL *
    get_input_msg) (axis2_wsdl_op_t *wsdl_op,
                                        axis2_env_t **env);
    
    /**
     * Method setInputMessage
     *
     * @param inputMessage
     */
    axis2_status_t (AXIS2_CALL *
    set_input_msg) (axis2_wsdl_op_t *wsdl_op,
                    axis2_env_t **env,
                    struct axis2_wsdl_msg_ref *input_msg);
    
    /**
     * Method getOutfaults
     *
     * @return
     */
    axis2_linked_list_t *(AXIS2_CALL *
    get_outfaults)(axis2_wsdl_op_t *wsdl_op,
                                        axis2_env_t **env);
    
    /**
     * Method setOutfaults
     *
     * @param outfaults
     */
    axis2_status_t (AXIS2_CALL *
    set_outfaults) (axis2_wsdl_op_t *wsdl_op,
                                        axis2_env_t **env,
                                        axis2_linked_list_t *outfaults);
    
    /**
     * Method getOutputMessage
     *
     * @return
     */
    struct axis2_wsdl_msg_ref *(AXIS2_CALL *
    get_output_msg) (axis2_wsdl_op_t *wsdl_op,
                                        axis2_env_t **env);
    
    /**
     * Method setOutputMessage
     *
     * @param outputMessage
     */
    axis2_status_t (AXIS2_CALL *
    set_output_msg) (axis2_wsdl_op_t *wsdl_op,
                        axis2_env_t **env,
                        struct axis2_wsdl_msg_ref *output_msg);
    
    /**
     * Method isSafe
     *
     * @return
     */
    axis2_bool_t (AXIS2_CALL *
    is_safe) (axis2_wsdl_op_t *wsdl_op,
                axis2_env_t **env);
    
    /**
     * Method setSafety
     *
     * @param safe
     */
    axis2_status_t (AXIS2_CALL *
    set_safety) (axis2_wsdl_op_t *wsdl_op,
                    axis2_env_t **env,
                    axis2_bool_t safe);
    
    /**
     * Will return the Namespace of the QName of this <code>WSDLOperation</code>. Will return null if not set.
     *
     * @return
     */
    axis2_char_t *(AXIS2_CALL *
    get_target_namespace) (axis2_wsdl_op_t *wsdl_op,
                            axis2_env_t **env);
    
    /**
     * Add the InFault to the Components InFaults
     *
     * @param inFault
     */
    axis2_status_t (AXIS2_CALL *
    add_infault) (axis2_wsdl_op_t *wsdl_op,
                    axis2_env_t **env,
                    struct axis2_wsdl_fault_ref *infault);
    
    /**
     * Add the OutFault to the Component OutFaults
     *
     * @param outFault
     */
    axis2_status_t (AXIS2_CALL *
    add_outfault) (axis2_wsdl_op_t *wsdl_op,
                    axis2_env_t **env,
                    struct axis2_wsdl_fault_ref *outfault);
};

struct axis2_wsdl_op
{
	axis2_wsdl_op_ops_t *ops;
    struct axis2_wsdl_extensible_component *extensible_component;
};

AXIS2_DECLARE(axis2_wsdl_op_t *) axis2_wsdl_op_create (
                                                            axis2_env_t **env);

/**************************** Start of function macros ************************/

#define AXIS2_WSDL_OPERATION_FREE(wsdl_op, env) \
		((wsdl_op->ops)->free (wsdl_op, env))
	
#define AXIS2_WSDL_OPERATION_GET_MSG_EXCHANGE_PATTERN(wsdl_op, env) \
		((wsdl_op->ops)->get_msg_exchange_pattern(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_MSG_EXCHANGE_PATTERN(wsdl_op, env, pattern) \
		((wsdl_op->ops)->set_msg_exchange_pattern(wsdl_op, env, pattern))
		
#define AXIS2_WSDL_OPERATION_GET_NAME(wsdl_op, env) \
		((wsdl_op->ops)->get_name(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_NAME(wsdl_op, env, name) \
		((wsdl_op->ops)->set_name(wsdl_op, env, name))
		
#define AXIS2_WSDL_OPERATION_SET_STYLE(wsdl_op, env, style) \
		((wsdl_op->ops)->set_style(wsdl_op, env, style))
		
#define AXIS2_WSDL_OPERATION_GET_STYLE(wsdl_op, env) \
		((wsdl_op->ops)->get_style(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_GET_INFAULTS(wsdl_op, env) \
		((wsdl_op->ops)->get_infaults(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_INFAULTS(wsdl_op, env, infaults) \
		((wsdl_op->ops)->set_infaults(wsdl_op, env, infaults))

#define AXIS2_WSDL_OPERATION_GET_INPUT_MSG(wsdl_op, env) \
		((wsdl_op->ops)->get_input_msg(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_INPUT_MSG(wsdl_op, env, input_msg) \
		((wsdl_op->ops)->set_input_msg(wsdl_op, env, input_msg))		

#define AXIS2_WSDL_OPERATION_GET_OUTFAULTS(wsdl_op, env) \
		((wsdl_op->ops)->get_outfaults(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_OUTFAULTS(wsdl_op, env, outfaults) \
		((wsdl_op->ops)->set_outfaults(wsdl_op, env, outfaults))

#define AXIS2_WSDL_OPERATION_GET_OUTPUT_MSG(wsdl_op, env) \
		((wsdl_op->ops)->get_output_msg(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_OUTPUT_MSG(wsdl_op, env, output_msg) \
		((wsdl_op->ops)->set_output_msg(wsdl_op, env, output_msg))

#define AXIS2_WSDL_OPERATION_IS_SAFE(wsdl_op, env) \
		((wsdl_op->ops)->is_safe(wsdl_op, env))
		
#define AXIS2_WSDL_OPERATION_SET_SAFETY(wsdl_op, env, safe) \
		((wsdl_op->ops)->set_safety(wsdl_op, env, safe))
        
#define AXIS2_WSDL_OPERATION_GET_TARGET_NAMESPACE(wsdl_op, env) \
		((wsdl_op->ops)->get_target_namespace(wsdl_op, env))        

#define AXIS2_WSDL_OPERATION_ADD_INFAULT(wsdl_op, env, infault) \
		((wsdl_op->ops)->add_infault(wsdl_op, env, infault))
		
#define AXIS2_WSDL_OPERATION_ADD_OUTFAULT(wsdl_op, env, outfault) \
		((wsdl_op->ops)->add_outfault(wsdl_op, env, outfault))

/**************************** End of function macros **************************/

/** @} */
#ifdef __cplusplus
}
#endif
#endif /* AXIS2_WSDL_OPERATION_H  */
