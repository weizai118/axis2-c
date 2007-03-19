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


/**
 * axis2_skel_calculator.c
 *
 * This file was auto-generated from WSDL for "Calculator|http://localhost/axis/Calculator" service
 * by the Apache Axis2/C version: #axisVersion# #today#
 * axis2_skel_calculator Axis2/C skeleton for the axisService
 */

#include "axis2_skel_calculator.h"


/**
 * auto generated function definition signature
 * for "add|http://localhost/axis/Calculator" operation.
 * @param content0
 */
axiom_node_t* axis2_skel_calculator_add(const axis2_env_t *env  ,
        axiom_node_t* content0)
{
    /* TODO fill this with the necessary business logic */
    axiom_node_t* req = content0;
    axiom_node_t* node = NULL;
    axiom_element_t* ele = NULL;
    axis2_char_t* text =  NULL;

    axiom_node_t *op_node = NULL;
    axiom_element_t* op_ele = NULL;
    axiom_node_t* value_node = NULL;
    axiom_element_t * value_ele = NULL;
    axiom_namespace_t *ns1 = NULL;

    char value_str[64];

    int result = 0;

    int value1, value2;
    if (! req)
    {
        printf("request null\n");
        return NULL;
    }
    else
    {
        node = AXIOM_NODE_GET_FIRST_CHILD(req, env);
        ele = AXIOM_NODE_GET_DATA_ELEMENT(node, env);
        text = axiom_element_get_text(ele, env, node);
        value1 = atoi(text);

        node = AXIOM_NODE_GET_NEXT_SIBLING(node, env);
        ele = AXIOM_NODE_GET_DATA_ELEMENT(node, env);
        text = axiom_element_get_text(ele, env, node);
        value2 = atoi(text);

    }

    result = value1 + value2;
    printf("%d = %d + %d\n", result, value1, value2);

    ns1 = axiom_namespace_create(env, "http://localhost/axis/Calculator", "ns1");
    op_ele = axiom_element_create(env, NULL, "addResponse", ns1, &op_node);

    value_ele = axiom_element_create(env, op_node, "in1", NULL, &value_node);
    sprintf(value_str, "%d", result);
    axiom_element_set_text(value_ele, env, value_str , value_node);

    return op_node;
}

/**
 * auto generated function definition signature
 * for "sub|http://localhost/axis/Calculator" operation.
 * @param content2
 */
axiom_node_t* axis2_skel_calculator_sub(const axis2_env_t *env  ,
        axiom_node_t* content2)
{
    /* TODO fill this with the necessary business logic */
    return NULL;
}

/**
 * auto generated function definition signature
 * for "mul|http://localhost/axis/Calculator" operation.
 * @param content4
 */
axiom_node_t* axis2_skel_calculator_mul(const axis2_env_t *env  ,
        axiom_node_t* content4)
{
    /* TODO fill this with the necessary business logic */
    return NULL;
}

/**
 * auto generated function definition signature
 * for "div|http://localhost/axis/Calculator" operation.
 * @param content6
 */
axiom_node_t* axis2_skel_calculator_div(const axis2_env_t *env  ,
        axiom_node_t* content6)
{
    /* TODO fill this with the necessary business logic */
    return NULL;
}

