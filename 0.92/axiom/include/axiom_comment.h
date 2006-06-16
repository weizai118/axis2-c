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

#ifndef AXIOM_COMMENT_H
#define AXIOM_COMMENT_H

/**
 * @file axiom_comment.h
 * @brief defines axiom_comment_t struct, and manipulation functions
 */

#include <axiom_node.h>
#include <axiom_output.h>

#ifdef __cplusplus
extern "C"
{
#endif

    struct axiom_comment;
    struct axiom_comment_ops;

/**
 * @defgroup axiom_comment OM Comment
 * @ingroup axiom 
 * @{
 */


  /** 
    *   @brief OM comment ops struct
    *   Encapsulator struct for ops of axiom_comment_t
    */
 AXIS2_DECLARE_DATA  typedef struct axiom_comment_ops
    {
      /**
        * Free a axis2_comment_t struct
        * @param om_comment pointer to axis2_commnet_t struct to be freed
        * @param env Environment. MUST NOT be NULL.
        * @return satus of the op. 
        *                AXIS2_SUCCESS on success ,AXIS2_FAILURE on error.
        */
        axis2_status_t (AXIS2_CALL *
        free) (struct axiom_comment *om_comment,
               const axis2_env_t *env);
       /** get the comments data
        * @param om_comment a pointer to axiom_comment_t struct
        * @param env environment, MUST NOT be NULL 
        * @returns comment text
        */
               
        axis2_char_t* (AXIS2_CALL *
        get_value)(struct axiom_comment *om_comment,
                   const axis2_env_t *env);
       /**
        * set comment data
        * @param om_comment pointer to axiom_comment_t struct
        * @param env environment, MUST NOT be NULL.
        * @param value comment text
        * @returns AXIS2_SUCCESS on success , AXIS2_FAILURE on error
        */
        axis2_status_t (AXIS2_CALL *
        set_value)(struct axiom_comment *om_comment,
                  const axis2_env_t *env,
                  const axis2_char_t* value);
        /**
         *  serialize function 
         *  @param om_comment pointer to axiom_comment_t struct
         *  @param env environment, MUST NOT be NULL.
         *  @param om_output pointer to om_output_t struct
         *  @return AXIS2_SUCCESS on success, AXIS2_FAILURE on error.
         */
        axis2_status_t (AXIS2_CALL *
        serialize)(struct axiom_comment *om_comment,
                   const axis2_env_t *env,
                   axiom_output_t *om_output);
                                                                                            
                                              
    } axiom_comment_ops_t;

  /** 
    * \brief OM comment struct
    * Handles the XML comment in OM
    */
    typedef struct axiom_comment
    {
        /** ops struct */
        axiom_comment_ops_t *ops;

    } axiom_comment_t;

  /**
    * Creates a comment struct
    * @param env Environment. MUST NOT be NULL,
    * @param parent This is the parent node of the comment is any, can be NULL.
    * @param value comment text
    * @param node This is an out parameter.cannot be NULL.
    *        Returns the node corresponding to the comment created.
    *        Node type will be set to AXIOM_COMMENT
    * @return a pointer to the newly created comment struct
    */
    AXIS2_EXTERN axiom_comment_t * AXIS2_CALL 
    axiom_comment_create (const axis2_env_t *env,
                             axiom_node_t *parent,
                             const axis2_char_t *value,
                             axiom_node_t **node);


/** free given comment */
#define AXIOM_COMMENT_FREE(om_comment, env) \
        ((om_comment)->ops->free(om_comment, env))
/** get comment text */
#define AXIOM_COMMENT_GET_VALUE(om_comment, env) \
        ((om_comment)->ops->get_value(om_comment, env))
/** set comment text */        
#define AXIOM_COMMENT_SET_VALUE(om_comment, env, value) \
        ((om_comment)->ops->set_value(om_comment, env, value))
/** serialize */
#define AXIOM_COMMENT_SERIALIZE(om_comment, env, om_output) \
        ((om_comment)->ops->serialize(om_comment, env, om_output))

/** @} */

#ifdef __cplusplus
}
#endif

#endif                          /* AXIOM_COMMENT_H */
