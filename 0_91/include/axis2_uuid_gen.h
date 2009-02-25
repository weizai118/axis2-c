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

#ifndef AXIS2_UUID_GEN_H
#define AXIS2_UUID_GEN_H

#include <axis2_const.h>
#include <axis2_defines.h>
#include <axis2_env.h>
#include <platforms/axis2_platform_auto_sense.h>


#ifdef __cplusplus
extern "C"
{
#endif


/**
 * @defgroup axis2_uuid_gen UUID Generator
 * @ingroup axis2_util 
 * @{
 */
	
/**
 * generate a uuid
 * @return generated uuid as a string
 */ 
AXIS2_DECLARE (axis2_char_t*)
axis2_uuid_gen(axis2_env_t **env);

/** @} */
    
#ifdef __cplusplus
}
#endif

#endif                          /* AXIS2_UUID_GEN_H */