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

#ifndef XML_SCHEMA_APP_INFO_H
#define XML_SCHEMA_APP_INFO_H

/**
 * @file xml_schema_app_info.h
 * @brief Axis2 Xml Schema App Info Interface
 *          Defines application specific information within an annotation.
 *          Represents the World Wide Web Consortium (W3C) appinfo element.
 *
 */

#include <xml_schema_defines.h>
#include <xml_schema_obj.h>
#include <axis2_hash.h>

/** @defgroup xml_schema_app_info Xml Schema App Info
  * @ingroup xml_schema
  * @{
  */

typedef struct xml_schema_app_info xml_schema_app_info_t;
typedef struct xml_schema_app_info_ops xml_schema_app_info_ops_t;

#ifdef __cplusplus
extern "C"
{
#endif

struct xml_schema_app_info_ops
{
   /** 
     * Deallocate memory
     * @return status code
     */
    axis2_status_t (AXIS2_CALL *
    free) (
            void *app_info,
            const axis2_env_t *env);

    axis2_hash_t *(AXIS2_CALL *
    super_objs) (
            void *app_info,
            const axis2_env_t *env);

    xml_schema_types_t (AXIS2_CALL *
    get_type) (
            void *app_info,
            const axis2_env_t *env);

    xml_schema_obj_t *(AXIS2_CALL *
    get_base_impl) (void *app_info,
                        const axis2_env_t *env);
    
    axis2_char_t *(AXIS2_CALL *
    get_source)(void *app_info,
                const axis2_env_t *env);

    axis2_status_t (AXIS2_CALL *
    set_source) (void *app_info,
                const axis2_env_t *env,
                axis2_char_t *source);

    /* TODO replace (void *) mark up with node list */
    void *(AXIS2_CALL *
    get_markup) (void *app_info,
                    const axis2_env_t *env);

    /* TODO replace (void *) mark up with node list */
    axis2_status_t (AXIS2_CALL *
    set_markup) (void *app_info,
                    const axis2_env_t *env,
                    void *markup);

};

struct xml_schema_app_info
{
    xml_schema_obj_t base;
    xml_schema_app_info_ops_t *ops;
};

AXIS2_EXTERN xml_schema_app_info_t * AXIS2_CALL
xml_schema_app_info_create(const axis2_env_t *env);


/*********************** macros ***********************************************/

#define XML_SCHEMA_APP_INFO_FREE(app_info, env) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            free(app_info, env))

#define XML_SCHEMA_APP_INFO_SUPER_OBJS(app_info, env) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            super_objs(app_info, env))

#define XML_SCHEMA_APP_INFO_GET_TYPE(app_info, env) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            get_type(app_info, env))

#define XML_SCHEMA_APP_INFO_GET_SOURCE(app_info, env) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            get_source(app_info, env))

#define XML_SCHEMA_APP_INFO_SET_SOURCE(app_info, env, source) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            set_source(app_info, env, source))

#define XML_SCHEMA_APP_INFO_GET_MARKUP(app_info, env) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            get_markup(app_info, env))

#define XML_SCHEMA_APP_INFO_SET_MARKUP(app_info, env, markup) \
      (((xml_schema_app_info_t *) app_info)->ops->\
            set_markup(app_info, env, markup))

/************************ end macros ******************************************/
/** @} */
#ifdef __cplusplus
}
#endif
#endif /* XML_SCHEMA_APP_INFO_H */
