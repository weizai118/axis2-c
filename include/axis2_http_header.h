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

#ifndef AXIS2_HTTP_HEADER_H
#define AXIS2_HTTP_HEADER_H

/**
 * @defgroup axis2_http_header http header
 * @ingroup axis2_core_trans_http
 * Description
 * @{
 */


/**
 * @file axis2_http_header.h
 * @brief axis2 HTTP Header name:value pair implementation
 */

#include <axis2_const.h>
#include <axis2_defines.h>
#include <axis2_env.h>

#ifdef __cplusplus
extern "C"
{
#endif

    /** Type name for struct axis2_http_header */
    typedef struct axis2_http_header axis2_http_header_t;

    /**
     * @param header pointer to header
     * @param env pointer to environment struct
     */
    AXIS2_EXTERN axis2_char_t *AXIS2_CALL
    axis2_http_header_to_external_form(axis2_http_header_t *header,
        const axis2_env_t *env);

    /**
     * @param header pointer to header
     * @param env pointer to environment struct
     */
    AXIS2_EXTERN axis2_char_t *AXIS2_CALL
    axis2_http_header_get_name(const axis2_http_header_t *header,
        const axis2_env_t *env);

    /**
     * @param header pointer to header
     * @param env pointer to environment struct
     */
    AXIS2_EXTERN axis2_char_t *AXIS2_CALL
    axis2_http_header_get_value(const axis2_http_header_t *header,
        const axis2_env_t *env);

    /**
     * @param header pointer to header
     * @param env pointer to environment struct
     * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE
     */
    AXIS2_EXTERN axis2_status_t AXIS2_CALL
    axis2_http_header_free(axis2_http_header_t *header,
        const axis2_env_t *env);

    /**
     * @param env pointer to environment struct
     * @param name pointer to name
     * @param value pointer to value
     */
    AXIS2_EXTERN axis2_http_header_t *AXIS2_CALL
    axis2_http_header_create (const axis2_env_t *env,
        const axis2_char_t *name,
        const axis2_char_t *value);

    /**
     * @param env pointer to environment struct
     * @param str pointer to str
     */
    AXIS2_EXTERN axis2_http_header_t *AXIS2_CALL
    axis2_http_header_create_by_str (const axis2_env_t *env,
        const axis2_char_t *str);

/** To external from. */
#define AXIS2_HTTP_HEADER_TO_EXTERNAL_FORM(header, env) \
                                axis2_http_header_to_external_form(header, env)

/** Gets the name. */
#define AXIS2_HTTP_HEADER_GET_NAME(header, env) \
                                axis2_http_header_get_name(header, env)

/** Get value. */
#define AXIS2_HTTP_HEADER_GET_VALUE(header, env) \
                                axis2_http_header_get_value(header, env)

/** Frees the http header. */
#define AXIS2_HTTP_HEADER_FREE(header, env) \
                                axis2_http_header_free(header, env)

/** @} */
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_HTTP_HEADER_H */
