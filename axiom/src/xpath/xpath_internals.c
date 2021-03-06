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

#include <axiom_xpath.h>
#include "xpath_internals.h"

/* Make a copy of the xpath expression */
void
axiom_xpath_expression_copy(
    axiom_xpath_context_t *context,
    axiom_xpath_expression_t* expr)
{
    int i;
    axiom_xpath_operation_t *op;

    if (context->expr)
        axiom_xpath_free_expression(context->env, context->expr);

    context->expr = expr;

    /* Set value of pos in every operation to 0 */
    for(i = 0; i < axutil_array_list_size(expr->operations, context->env); i++)
    {
        op = AXIOM_XPATH_OPR_GET(i);
        op->pos = 0;
    }
}
