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


#include <rp_wss10_builder.h>

AXIS2_EXTERN rp_wss10_t *AXIS2_CALL
rp_wss10_builder_build(
            const axis2_env_t *env,
            axiom_node_t *wss)
{
    rp_wss10_t *wss10 = NULL;
    axis2_status_t status = AXIS2_SUCCESS;
    axiom_node_t *policy = NULL;
    axiom_element_t *pol_ele = NULL;

    AXIS2_ENV_CHECK(env,NULL);

    wss10 = rp_wss10_create(env);
    if(!wss10)
        return NULL;

    policy = AXIOM_NODE_GET_FIRST_CHILD(wss,env);

    if(AXIOM_NODE_GET_NODE_TYPE(policy, env) == AXIOM_ELEMENT)
    {
        pol_ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(policy, env);
        if(pol_ele)
        {
            axiom_children_iterator_t *children_iter = NULL;
            children_iter = AXIOM_ELEMENT_GET_CHILDREN(pol_ele, env, policy);
            if(children_iter )
            {
                while(AXIOM_CHILDREN_ITERATOR_HAS_NEXT(children_iter, env))
                {
                    axiom_node_t *node = NULL;
                    axiom_element_t *ele = NULL;
                    axis2_char_t *local_name = NULL;
                    node = AXIOM_CHILDREN_ITERATOR_NEXT(children_iter, env);
                    if(node)
                    {
                        if(AXIOM_NODE_GET_NODE_TYPE(node, env) == AXIOM_ELEMENT)
                        {
                            ele = (axiom_element_t*)AXIOM_NODE_GET_DATA_ELEMENT(node, env);
                            if(ele)
                            {
                                local_name = AXIOM_ELEMENT_GET_LOCALNAME(ele,env);
                                if(local_name)
                                {
                                    status = rp_wss10_builder_set_properties(node,ele,local_name,wss10,env);
                                    if(status!=AXIS2_SUCCESS)
                                    {
                                        rp_wss10_free(wss10,env);
                                        wss10 = NULL;
                                    }                           
                                }
                            }
                            
                        }
                    }
                }
            }
        }
    }
    return wss10;
}            


AXIS2_EXTERN axis2_status_t AXIS2_CALL
rp_wss10_builder_set_properties(
        axiom_node_t *node,
        axiom_element_t *element,
        axis2_char_t *local_name,
        rp_wss10_t *wss10,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env,AXIS2_FAILURE);

    if(strcmp(local_name,RP_MUST_SUPPORT_REF_KEY_IDENTIFIER)==0)
    {
        if(rp_match_secpolicy_qname(env,RP_MUST_SUPPORT_REF_KEY_IDENTIFIER,node,element))
        {
            rp_wss10_set_must_support_ref_key_identifier(wss10,env,AXIS2_TRUE);
            printf("%s\n",local_name);
            return AXIS2_SUCCESS;
        }
        else
            return AXIS2_FAILURE;
    }
    else if(strcmp(local_name,RP_MUST_SUPPORT_REF_ISSUER_SERIAL)==0)
    {
        if(rp_match_secpolicy_qname(env,RP_MUST_SUPPORT_REF_ISSUER_SERIAL,node,element))
        {
            rp_wss10_set_must_support_ref_issuer_serial(wss10,env,AXIS2_TRUE);
            printf("%s\n",local_name);
            return AXIS2_SUCCESS;
        }
        else
            return AXIS2_FAILURE;
    }
    else if(strcmp(local_name,RP_MUST_SUPPORT_REF_EXTERNAL_URI)==0)
    {
        if(rp_match_secpolicy_qname(env,RP_MUST_SUPPORT_REF_EXTERNAL_URI,node,element))
        {
            rp_wss10_set_must_support_ref_external_uri(wss10,env,AXIS2_TRUE);
            printf("%s\n",local_name);
            return AXIS2_SUCCESS;
        }
        else
            return AXIS2_FAILURE;
    }
    else if(strcmp(local_name,RP_MUST_SUPPORT_REF_EMBEDDED_TOKEN)==0)
    {
        if(rp_match_secpolicy_qname(env,RP_MUST_SUPPORT_REF_EMBEDDED_TOKEN,node,element))
        {
            rp_wss10_set_must_support_ref_embedded_token(wss10,env,AXIS2_TRUE);
            printf("%s\n",local_name);
            return AXIS2_SUCCESS;
        }
        else
            return AXIS2_FAILURE;
    }
    else
        return AXIS2_FAILURE;
}