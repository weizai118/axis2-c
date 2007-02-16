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

#ifndef OXS_KEY_MGR_H
#define OXS_KEY_MGR_H


/**
  * @file oxs_key_mgr.h
  * @brief the Key Manager responsible for loading keys for OMXMLSecurity
  */

#include <axis2_defines.h>
#include <oxs_ctx.h>
#include <oxs_asym_ctx.h>
#include <axis2_env.h>
#include <axis2_qname.h>
#include <oxs_x509_cert.h>
#include <openssl_pkey.h>
#include <openssl_x509.h>
#include <openssl_pkcs12.h>

#ifdef __cplusplus
extern "C"
{
#endif
	
/**
 * Loads keys/certificates from a keystore or a PEm file depending on information available in the @ctx
 * @ctx pointer to the OMXMLSec asymmetric encryption context struct
 * @env pointer to environment struct
 * @password the password for the key store
 * @return AXIS2_SUCCESS on success, else AXIS2_FAILURE	
 */	
AXIS2_EXTERN axis2_status_t AXIS2_CALL
oxs_key_mgr_load_key(const axis2_env_t *env,
    oxs_asym_ctx_t *ctx,
    axis2_char_t *password);

AXIS2_EXTERN openssl_pkey_t* AXIS2_CALL
oxs_key_mgr_load_private_key_from_string(const axis2_env_t *env,
    axis2_char_t *pem_buf, /*in PEM format*/
    axis2_char_t *password);

AXIS2_EXTERN openssl_pkey_t* AXIS2_CALL
oxs_key_mgr_load_private_key_from_file(const axis2_env_t *env,
    axis2_char_t *file_name,
    axis2_char_t *password);

AXIS2_EXTERN oxs_x509_cert_t* AXIS2_CALL
oxs_key_mgr_load_x509_cert_from_pem_file(const axis2_env_t *env,
    axis2_char_t *filename);

AXIS2_EXTERN oxs_x509_cert_t* AXIS2_CALL
oxs_key_mgr_load_x509_cert_from_buf(const axis2_env_t *env,
    axis2_char_t *pem_buf);
/** @} */
#ifdef __cplusplus
}
#endif

#endif                          /* OXS_KEY_MGR_H */
