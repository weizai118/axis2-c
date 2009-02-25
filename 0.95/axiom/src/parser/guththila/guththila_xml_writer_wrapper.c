/*
 *   Copyright 2004,2005 The Apache Software Foundation.
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

#include <guththila_xml_writer.h>
#include <guththila.h>
#include <axis2_utils.h>
#include <axis2_env.h>
#include <axiom_xml_writer.h>
/* /\*********************** function prototypes ***********************************\/ */
axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_free(axiom_xml_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_end_start_element(axiom_xml_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_end_element(axiom_xml_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_end_document(axiom_xml_writer_t *writer,
        const axis2_env_t *env);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *value);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *value,
    axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *value,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *prefix,
    axis2_char_t *namespace_uri);


axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_default_namespace(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *namespace_uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_comment(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *value);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_processing_instruction(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *target);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_processing_instruction_data(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *target,
    axis2_char_t *data);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_cdata(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *data);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_dtd(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *dtd);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_entity_ref(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *name);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document_with_version(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *version);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document_with_version_encoding(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *encoding,
    axis2_char_t *version);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_characters(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *text);

axis2_char_t* AXIS2_CALL
guththila_xml_writer_wrapper_get_prefix(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_set_prefix(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *prefix,
        axis2_char_t *uri);
axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_set_default_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *uri);

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_encoded(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *text,
    int in_attr);

void* AXIS2_CALL
guththila_xml_writer_wrapper_get_xml(axiom_xml_writer_t *writer,
        const axis2_env_t *env);



/* /\**************************** end function pointers ****************************\/ */

typedef struct guththila_xml_writer_wrapper_impl
{
    axiom_xml_writer_t writer;
    guththila_t *parser;
}
guththila_xml_writer_wrapper_impl_t;


/* /\***************************** Macros ******************************************\/ */

#define AXIS2_INTF_TO_IMPL(p) ((guththila_xml_writer_wrapper_impl_t*)p)

/* /\****************************** End macro **************************************\/ */

AXIS2_EXTERN axiom_xml_writer_t * AXIS2_CALL
axiom_xml_writer_create(const axis2_env_t *env,
        axis2_char_t *filename,
        axis2_char_t *encoding,
        int is_prefix_default,
        int compression)
{
    guththila_xml_writer_wrapper_impl_t *writer_impl;

    axis2_allocator_t *allocator;
    AXIS2_ENV_CHECK(env, NULL);

    writer_impl = (guththila_xml_writer_wrapper_impl_t *)AXIS2_MALLOC(env->allocator,
            sizeof(guththila_xml_writer_wrapper_impl_t));

    if (!writer_impl)
    {

        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    allocator = axis2_allocator_init(NULL);
    writer_impl->parser = guththila_create((axis2_env_t *)env, NULL);

    if (!(writer_impl->parser))
    {
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    guththila_create_xml_stream_writer((axis2_env_t*) env,
            writer_impl->parser,
            filename);

    if (!(writer_impl->parser->xsw))
    {
        AXIS2_FREE(env->allocator, writer_impl->parser);
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    writer_impl->writer.ops = NULL;
    writer_impl->writer.ops = (axiom_xml_writer_ops_t*)AXIS2_MALLOC(env->allocator,
            sizeof(axiom_xml_writer_ops_t));
    if (!(writer_impl->writer.ops))
    {
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);

        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    /* ops */
    writer_impl->writer.ops->free = guththila_xml_writer_wrapper_free;
    writer_impl->writer.ops->write_start_element = guththila_xml_writer_wrapper_write_start_element;
    writer_impl->writer.ops->write_start_element_with_namespace =
        guththila_xml_writer_wrapper_write_start_element_with_namespace;
    writer_impl->writer.ops->write_start_element_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_start_element_with_namespace_prefix;

    writer_impl->writer.ops->write_empty_element = guththila_xml_writer_wrapper_write_empty_element;
    writer_impl->writer.ops->write_empty_element_with_namespace  =
        guththila_xml_writer_wrapper_write_empty_element_with_namespace;
    writer_impl->writer.ops->write_empty_element_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_empty_element_with_namespace_prefix;

    writer_impl->writer.ops->write_end_element =
        guththila_xml_writer_wrapper_write_end_element;
    writer_impl->writer.ops->write_end_document =
        guththila_xml_writer_wrapper_write_end_document;

    writer_impl->writer.ops->write_attribute =
        guththila_xml_writer_wrapper_write_attribute;
    writer_impl->writer.ops->write_attribute_with_namespace =
        guththila_xml_writer_wrapper_write_attribute_with_namespace;
    writer_impl->writer.ops->write_attribute_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_attribute_with_namespace_prefix;
    writer_impl->writer.ops->write_namespace =
        guththila_xml_writer_wrapper_write_namespace;
    writer_impl->writer.ops->write_default_namespace =
        guththila_xml_writer_wrapper_write_default_namespace;
    writer_impl->writer.ops->write_comment =
        guththila_xml_writer_wrapper_write_comment;
    writer_impl->writer.ops->write_processing_instruction =
        guththila_xml_writer_wrapper_write_processing_instruction;
    writer_impl->writer.ops->write_processing_instruction_data =
        guththila_xml_writer_wrapper_write_processing_instruction_data;
    writer_impl->writer.ops->write_cdata =
        guththila_xml_writer_wrapper_write_cdata;
    writer_impl->writer.ops->write_dtd =
        guththila_xml_writer_wrapper_write_dtd;
    writer_impl->writer.ops->write_entity_ref =
        guththila_xml_writer_wrapper_write_entity_ref;
    writer_impl->writer.ops->write_start_document =
        guththila_xml_writer_wrapper_write_start_document;
    writer_impl->writer.ops->write_start_document_with_version =
        guththila_xml_writer_wrapper_write_start_document_with_version;
    writer_impl->writer.ops->write_start_document_with_version_encoding =
        guththila_xml_writer_wrapper_write_start_document_with_version_encoding;
    writer_impl->writer.ops->write_characters =
        guththila_xml_writer_wrapper_write_characters;
    writer_impl->writer.ops->get_prefix =
        guththila_xml_writer_wrapper_get_prefix;
    writer_impl->writer.ops->set_prefix = guththila_xml_writer_wrapper_set_prefix;
    writer_impl->writer.ops->set_default_prefix =
        guththila_xml_writer_wrapper_set_default_prefix;
    writer_impl->writer.ops->write_encoded =
        guththila_xml_writer_wrapper_write_encoded;
    writer_impl->writer.ops->get_xml =
        guththila_xml_writer_wrapper_get_xml;

    return &(writer_impl->writer);
}

AXIS2_EXTERN axiom_xml_writer_t * AXIS2_CALL
axiom_xml_writer_create_for_memory(const axis2_env_t *env,
        axis2_char_t *encoding,
        int is_prefix_default,
        int compression,
        int type)
{
    guththila_xml_writer_wrapper_impl_t *writer_impl = NULL;

    axis2_allocator_t *allocator = NULL;
    AXIS2_ENV_CHECK(env, NULL);

    writer_impl = (guththila_xml_writer_wrapper_impl_t *)AXIS2_MALLOC(env->allocator,
            sizeof(guththila_xml_writer_wrapper_impl_t));

    if (!writer_impl)
    {

        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    allocator = axis2_allocator_init(NULL);
    /* creating guththila parser */
    writer_impl->parser = guththila_create((axis2_env_t *)env, NULL);

    if (!(writer_impl->parser))
    {
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    /* guththila xml stream writer for memory */
    guththila_create_xml_stream_writer_for_memory((axis2_env_t*) env,
            writer_impl->parser);

    if (!(writer_impl->parser->xsw))
    {
        AXIS2_FREE(env->allocator, writer_impl->parser);
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    writer_impl->writer.ops = NULL;
    writer_impl->writer.ops = (axiom_xml_writer_ops_t*)AXIS2_MALLOC(env->allocator,
            sizeof(axiom_xml_writer_ops_t));
    if (!(writer_impl->writer.ops))
    {
        AXIS2_FREE(env->allocator, writer_impl);
        AXIS2_FREE(env->allocator, allocator);

        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }
    /* ops */
    writer_impl->writer.ops->free = guththila_xml_writer_wrapper_free;
    writer_impl->writer.ops->write_start_element = guththila_xml_writer_wrapper_write_start_element;
    writer_impl->writer.ops->write_start_element_with_namespace =
        guththila_xml_writer_wrapper_write_start_element_with_namespace;
    writer_impl->writer.ops->write_start_element_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_start_element_with_namespace_prefix;

    writer_impl->writer.ops->write_empty_element = guththila_xml_writer_wrapper_write_empty_element;
    writer_impl->writer.ops->write_empty_element_with_namespace  =
        guththila_xml_writer_wrapper_write_empty_element_with_namespace;
    writer_impl->writer.ops->write_empty_element_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_empty_element_with_namespace_prefix;

    writer_impl->writer.ops->write_end_element =
        guththila_xml_writer_wrapper_write_end_element;
    writer_impl->writer.ops->write_end_document =
        guththila_xml_writer_wrapper_write_end_document;

    writer_impl->writer.ops->write_attribute =
        guththila_xml_writer_wrapper_write_attribute;
    writer_impl->writer.ops->write_attribute_with_namespace =
        guththila_xml_writer_wrapper_write_attribute_with_namespace;
    writer_impl->writer.ops->write_attribute_with_namespace_prefix =
        guththila_xml_writer_wrapper_write_attribute_with_namespace_prefix;
    writer_impl->writer.ops->write_namespace =
        guththila_xml_writer_wrapper_write_namespace;
    writer_impl->writer.ops->write_default_namespace =
        guththila_xml_writer_wrapper_write_default_namespace;
    writer_impl->writer.ops->write_comment =
        guththila_xml_writer_wrapper_write_comment;
    writer_impl->writer.ops->write_processing_instruction =
        guththila_xml_writer_wrapper_write_processing_instruction;
    writer_impl->writer.ops->write_processing_instruction_data =
        guththila_xml_writer_wrapper_write_processing_instruction_data;
    writer_impl->writer.ops->write_cdata =
        guththila_xml_writer_wrapper_write_cdata;
    writer_impl->writer.ops->write_dtd =
        guththila_xml_writer_wrapper_write_dtd;
    writer_impl->writer.ops->write_entity_ref =
        guththila_xml_writer_wrapper_write_entity_ref;
    writer_impl->writer.ops->write_start_document =
        guththila_xml_writer_wrapper_write_start_document;
    writer_impl->writer.ops->write_start_document_with_version =
        guththila_xml_writer_wrapper_write_start_document_with_version;
    writer_impl->writer.ops->write_start_document_with_version_encoding =
        guththila_xml_writer_wrapper_write_start_document_with_version_encoding;
    writer_impl->writer.ops->write_characters =
        guththila_xml_writer_wrapper_write_characters;
    writer_impl->writer.ops->get_prefix =
        guththila_xml_writer_wrapper_get_prefix;
    writer_impl->writer.ops->set_prefix = guththila_xml_writer_wrapper_set_prefix;
    writer_impl->writer.ops->set_default_prefix =
        guththila_xml_writer_wrapper_set_default_prefix;
    writer_impl->writer.ops->write_encoded =
        guththila_xml_writer_wrapper_write_encoded;
    writer_impl->writer.ops->get_xml =
        guththila_xml_writer_wrapper_get_xml;

    return &(writer_impl->writer);

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_free(axiom_xml_writer_t *writer,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    if (AXIS2_INTF_TO_IMPL(writer)->parser)
    {
        if (AXIS2_INTF_TO_IMPL(writer)->parser->xsw)
            guththila_xml_writer_free((axis2_env_t *)env,
                    AXIS2_INTF_TO_IMPL(writer)->parser);

        guththila_free((axis2_env_t *)env,
                AXIS2_INTF_TO_IMPL(writer)->parser);
    }

    if (writer->ops)
        AXIS2_FREE(env->allocator, writer->ops);

    if (writer)
        AXIS2_FREE(env->allocator, AXIS2_INTF_TO_IMPL(writer));

    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname)
{
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    guththila_write_start_element(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        localname);
    return status;
}

/* axis2_status_t AXIS2_CALL */
/* guththila_xml_writer_wrapper_end_start_element(axiom_xml_writer_t *writer, */
/*                                                const axis2_env_t *env) */
/* { */
/*     AXIS2_ENV_CHECK( env, AXIS2_FAILURE); */
/*     return guththila_xml_stream_writer_end_start_element( */
/*                     (axis2_env_t *)env, */
/*                     AXIS2_INTF_TO_IMPL(writer)->guththila_writer); */
/* } */

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri)
{
    int status = AXIS2_SUCCESS;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    guththila_write_start_element_with_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        localname,
        namespace_uri);
    return status;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_element_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
    guththila_write_start_element_with_prefix_and_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        prefix, namespace_uri, localname);
    return AXIS2_SUCCESS;

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    guththila_write_empty_element(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser, localname);
    return AXIS2_SUCCESS;


}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    guththila_write_empty_element_with_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        namespace_uri, localname);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_empty_element_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);

    guththila_write_empty_element_with_prefix_and_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        prefix, namespace_uri, localname);
    return AXIS2_SUCCESS;


}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_end_element(axiom_xml_writer_t *writer,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    guththila_write_end_element(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_end_document(axiom_xml_writer_t *writer,
        const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    guththila_write_end_document(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser);
    return AXIS2_SUCCESS;

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *localname,
        axis2_char_t *value)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    guththila_write_attribute(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        localname, value);
    return AXIS2_SUCCESS;



}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute_with_namespace(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *value,
    axis2_char_t *namespace_uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname,  AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);

    guththila_write_attribute_with_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        namespace_uri, localname, value);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_attribute_with_namespace_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *localname,
    axis2_char_t *value,
    axis2_char_t *namespace_uri,
    axis2_char_t *prefix)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, localname, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix , AXIS2_FAILURE);
    guththila_write_attribute_with_prefix_and_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        prefix, namespace_uri, localname, value);
    return AXIS2_SUCCESS;



}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_namespace(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *prefix,
        axis2_char_t *namespace_uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    /*     AXIS2_PARAM_CHECK(env->error, prefix , AXIS2_FAILURE); */
    /* when defult namespace comes prefix is null */
    guththila_write_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        prefix, namespace_uri);
    return AXIS2_SUCCESS;

}


axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_default_namespace(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *namespace_uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, namespace_uri, AXIS2_FAILURE);
    guththila_write_default_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        namespace_uri);
    return AXIS2_SUCCESS;

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_comment(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *value)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, value, AXIS2_FAILURE);
    guththila_write_comment(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        value);
    return AXIS2_SUCCESS;

}


axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_processing_instruction(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *target)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, target, AXIS2_FAILURE);
    /*     return guththila_write_processing_instruction( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     target); */
    return AXIS2_SUCCESS;

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_processing_instruction_data(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *target,
    axis2_char_t *data)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, target, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, data, AXIS2_FAILURE);
    /*     return guththila_write_processing_instruction_data( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     target, data); */
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_cdata(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *data)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, data, AXIS2_FAILURE);
    /*     return guththila_write_cdata( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     data); */
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_dtd(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *dtd)
{
    /* AXIS2_ENV_CHECK( env, AXIS2_FAILURE); */
    /*     AXIS2_PARAM_CHECK(env->error, dtd, AXIS2_FAILURE); */
    /*     return guththila_write_dtd( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     dtd); */
    return 0;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_entity_ref(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *name)
{
    /* AXIS2_ENV_CHECK( env, AXIS2_FAILURE); */
    /*     AXIS2_PARAM_CHECK(env->error, name, AXIS2_FAILURE); */
    /*     return guththila_write_entity_ref( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     name); */
    return 0;

}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    guththila_write_start_document(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document_with_version(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *version)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, version, AXIS2_FAILURE);
    /* return guththila_write_start_document_with_version( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     version); */
    guththila_write_start_document(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_start_document_with_version_encoding(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *encoding,
    axis2_char_t *version)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, encoding, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, version, AXIS2_FAILURE);

    /*     return guththila_write_start_document_with_version_encoding( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, */
    /*                     encoding, version); */
    guththila_write_start_document(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser);
    return AXIS2_SUCCESS;
}


axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_characters(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *text)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, text, AXIS2_FAILURE);
    guththila_write_characters(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser,
        text);
    return AXIS2_SUCCESS;
}

axis2_char_t* AXIS2_CALL
guththila_xml_writer_wrapper_get_prefix(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *uri)
{
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, uri, NULL);
    return guththila_get_prefix_for_namespace(
                (axis2_env_t *)env,
                AXIS2_INTF_TO_IMPL(writer)->parser, uri);
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_set_prefix(axiom_xml_writer_t *writer,
        const axis2_env_t *env,
        axis2_char_t *prefix,
        axis2_char_t *uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, prefix, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, uri, AXIS2_FAILURE);
    guththila_write_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser, prefix, uri);
    return AXIS2_SUCCESS;

}
axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_set_default_prefix(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *uri)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, uri, AXIS2_FAILURE);
    guththila_write_default_namespace(
        (axis2_env_t *)env,
        AXIS2_INTF_TO_IMPL(writer)->parser, uri);
    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
guththila_xml_writer_wrapper_write_encoded(
    axiom_xml_writer_t *writer,
    const axis2_env_t *env,
    axis2_char_t *text,
    int in_attr)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, text, AXIS2_FAILURE);
    /*     return guththila_write_encoded( */
    /*                     (axis2_env_t *)env, */
    /*                     AXIS2_INTF_TO_IMPL(writer)->parser, text,
    		       in_attr); */
    return AXIS2_SUCCESS;
}

void* AXIS2_CALL
guththila_xml_writer_wrapper_get_xml(axiom_xml_writer_t *writer,
        const axis2_env_t *env)
{
    char *buffer = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    buffer = guththila_get_memory_buffer((axis2_env_t *)env,
            AXIS2_INTF_TO_IMPL(writer)->parser);
    return (void*)buffer ;
}