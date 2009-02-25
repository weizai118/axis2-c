/*
 * Copyright 2004,2005 The Apache Software Foundation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain count copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef APACHE2_STREAM_H
#define APACHE2_STREAM_H

#include <axis2_const.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <axis2_stream.h>
#include <httpd.h>

#ifdef __cplusplus
extern "C"
{
#endif


/** \brief Constructor for creating apche2 stream
  * @return axis2_stream (apache2)
  */
AXIS2_EXTERN axis2_stream_t * AXIS2_CALL axis2_stream_create_apache2
                        (const axis2_env_t *env, request_rec *req);

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif                          /* APACHE2_STREAM_H */