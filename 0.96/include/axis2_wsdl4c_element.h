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
 
 #ifndef AXIS2_WSDL4C_ELEMENT_H
 #define AXIS2_WSDL4C_ELEMENT_H
 
 /**
 * @file axis2_wsdl4c_element.h
 * @brief defines WSDL4C_ELEMENT
 */
#include <axis2_array_list.h>
#include <axis2_allocator.h>
#include <axis2_env.h>
#include <axis2_error.h>
#ifdef __cplusplus
extern "C"
{
#endif

/**
 * @defgroup axis2_wsdl4c_element axis2_wsdl4c_element
 * @ingroup axis2_wsdl4c 
 * @{
 */
    void *
    axis2_wsdl4c_element_create();

    void
    axis2_wsdl4c_element_destroy(void *element);

    void
    axis2_wsdl4c_element_set_type(void *element, 
                                    int id);
  
    char *
    axis2_wsdl4c_element_get_name(void *element);

    int
    axis2_wsdl4c_element_get_type(void *element);

    int
    axis2_wsdl4c_element_get_max(void *element);

    int
    axis2_wsdl4c_element_get_min(void *element);

/** @} */

#ifdef __cplusplus
}
#endif
#endif  /* AXIS2_WSDL4C_ELEMENT_H */