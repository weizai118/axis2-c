/*
 *   Copyright 2003-2004 The Apache Software Foundation.
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 */

#include <stdio.h>
#include <axis2_util.h>
#include <oxs_constants.h>
#include <oxs_axiom_util.h>
#include <axiom_node.h>
#include <axiom_namespace.h>
#include <axiom_attribute.h>


AXIS2_EXTERN int AXIS2_CALL
oxs_axiom_check_node_name(const axis2_env_t *env, axiom_node_t* node, axis2_char_t* name, axis2_char_t* ns)
{
    int ret_name, ret_ns;
    axiom_element_t * ele = NULL;
    axis2_char_t* namestr = NULL;
    axis2_char_t* ns_str = NULL;
    axis2_qname_t* qname = NULL;

    ele = AXIOM_NODE_GET_DATA_ELEMENT(node, env);
    qname = AXIOM_ELEMENT_GET_QNAME(ele, env, node);

    namestr = AXIS2_QNAME_GET_LOCALPART(qname, env);    
    ret_name =  AXIS2_STRCMP(namestr, name) ;
    
    if(ret_name < 0) return 0;   

    if(ns != NULL){
        ns_str = AXIS2_QNAME_GET_URI(qname, env);    
        ret_ns =  AXIS2_STRCMP(ns_str, ns) ;
        if(ret_ns<0) return 0;
        else   return 1;   
        
    }else{
        return 1;
    }
    

}
