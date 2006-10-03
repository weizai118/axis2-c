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

#include <axis2_transport_out_desc.h>

typedef struct axis2_transport_out_desc_impl
{
    axis2_transport_out_desc_t transport_out;
    axis2_flow_t *out_flow;
    axis2_flow_t *fault_out_flow;
    axis2_qname_t *qname;
    axis2_transport_sender_t *sender;
    axis2_phase_t *out_phase;
    axis2_phase_t *fault_phase;
}
axis2_transport_out_desc_impl_t;

#define AXIS2_INTF_TO_IMPL(transport_out) ((axis2_transport_out_desc_impl_t *)transport_out)

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_free(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

const axis2_qname_t *AXIS2_CALL
axis2_transport_out_desc_get_qname(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_qname(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    const axis2_qname_t *qname);

axis2_flow_t *AXIS2_CALL
axis2_transport_out_desc_get_out_flow(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_flow(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_flow_t *out_flow);

axis2_flow_t *AXIS2_CALL
axis2_transport_out_desc_get_fault_out_flow(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_fault_out_flow(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_flow_t *fault_out_flow);

axis2_transport_sender_t *AXIS2_CALL
axis2_transport_out_desc_get_sender(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_sender(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_transport_sender_t *sender);

axis2_phase_t *AXIS2_CALL
axis2_transport_out_desc_get_out_phase(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_phase(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_phase_t *out_phase);

axis2_phase_t *AXIS2_CALL
axis2_transport_out_desc_get_fault_phase(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_fault_phase(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_phase_t *fault_phase);

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_add_param(
    axis2_transport_out_desc_t *transport_out_desc,
    const axis2_env_t *env,
    axis2_param_t *param);

axis2_param_t *AXIS2_CALL
axis2_transport_out_desc_get_param(
    const axis2_transport_out_desc_t *transport_out_desc,
    const axis2_env_t *env,
    const axis2_char_t *param_name);

axis2_bool_t AXIS2_CALL
axis2_transport_out_desc_is_param_locked(
    axis2_transport_out_desc_t *
    transport_out_desc,
    const axis2_env_t *env,
    const axis2_char_t *param_name);

AXIS2_EXTERN axis2_transport_out_desc_t *AXIS2_CALL
axis2_transport_out_desc_create_with_qname(
    const axis2_env_t *env,
    const axis2_qname_t *qname)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;

    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, qname, NULL);

    transport_out_impl = (axis2_transport_out_desc_impl_t *) AXIS2_MALLOC(env->
            allocator, sizeof(axis2_transport_out_desc_impl_t));

    if (NULL == transport_out_impl)
    {
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    transport_out_impl->qname = NULL;
    transport_out_impl->out_phase = NULL;
    transport_out_impl->fault_phase = NULL;
    transport_out_impl->out_flow = NULL;
    transport_out_impl->fault_out_flow = NULL;
    transport_out_impl->sender = NULL;
    transport_out_impl->transport_out.ops = NULL;
    transport_out_impl->transport_out.param_container = NULL;

    transport_out_impl->transport_out.param_container = axis2_param_container_create(env);
    if (NULL == transport_out_impl->transport_out.param_container)
    {
        axis2_transport_out_desc_free(&(transport_out_impl->transport_out), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    transport_out_impl->qname = AXIS2_QNAME_CLONE(qname, env);

    transport_out_impl->transport_out.ops =
        AXIS2_MALLOC(env->allocator, sizeof(axis2_transport_out_desc_ops_t));
    if (NULL == transport_out_impl->transport_out.ops)
    {
        axis2_transport_out_desc_free(&(transport_out_impl->transport_out), env);
        AXIS2_ERROR_SET(env->error, AXIS2_ERROR_NO_MEMORY, AXIS2_FAILURE);
        return NULL;
    }

    transport_out_impl->transport_out.ops->free = axis2_transport_out_desc_free;
    transport_out_impl->transport_out.ops->free_void_arg =
        axis2_transport_out_desc_free_void_arg;

    transport_out_impl->transport_out.ops->get_qname =
        axis2_transport_out_desc_get_qname;
    transport_out_impl->transport_out.ops->set_qname =
        axis2_transport_out_desc_set_qname;
    transport_out_impl->transport_out.ops->get_out_flow =
        axis2_transport_out_desc_get_out_flow;
    transport_out_impl->transport_out.ops->set_out_flow =
        axis2_transport_out_desc_set_out_flow;
    transport_out_impl->transport_out.ops->get_fault_out_flow =
        axis2_transport_out_desc_get_fault_out_flow;
    transport_out_impl->transport_out.ops->set_fault_out_flow =
        axis2_transport_out_desc_set_fault_out_flow;
    transport_out_impl->transport_out.ops->get_sender =
        axis2_transport_out_desc_get_sender;
    transport_out_impl->transport_out.ops->set_sender =
        axis2_transport_out_desc_set_sender;
    transport_out_impl->transport_out.ops->get_out_phase =
        axis2_transport_out_desc_get_out_phase;
    transport_out_impl->transport_out.ops->set_out_phase =
        axis2_transport_out_desc_set_out_phase;
    transport_out_impl->transport_out.ops->get_fault_phase =
        axis2_transport_out_desc_get_fault_phase;
    transport_out_impl->transport_out.ops->set_fault_phase =
        axis2_transport_out_desc_set_fault_phase;
    transport_out_impl->transport_out.ops->add_param =
        axis2_transport_out_desc_add_param;
    transport_out_impl->transport_out.ops->get_param =
        axis2_transport_out_desc_get_param;
    transport_out_impl->transport_out.ops->is_param_locked =
        axis2_transport_out_desc_is_param_locked;

    return &(transport_out_impl->transport_out);
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_free(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);

    if (transport_out_impl->sender)
    {
        AXIS2_TRANSPORT_SENDER_FREE(transport_out_impl->sender, env);
        transport_out_impl->sender = NULL;
    }

    if (transport_out->ops)
    {
        AXIS2_FREE(env->allocator, transport_out->ops);
        transport_out->ops = NULL;
    }

    if (transport_out_impl->transport_out.param_container)
    {
        AXIS2_PARAM_CONTAINER_FREE(transport_out_impl->transport_out.param_container, env);
        transport_out_impl->transport_out.param_container = NULL;
    }

    if (transport_out_impl->qname)
    {
        AXIS2_QNAME_FREE(transport_out_impl->qname, env);
        transport_out_impl->qname = NULL;
    }

    if (transport_out_impl->out_flow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->out_flow, env);
        transport_out_impl->out_flow = NULL;
    }

    if (transport_out_impl->fault_out_flow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->fault_out_flow, env);
        transport_out_impl->fault_out_flow = NULL;
    }

    if (transport_out_impl->out_phase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->out_phase, env);
        transport_out_impl->out_phase = NULL;
    }

    if (transport_out_impl->fault_phase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->fault_phase, env);
        transport_out_impl->fault_phase = NULL;
    }

    AXIS2_FREE(env->allocator, transport_out_impl);

    return AXIS2_SUCCESS;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_free_void_arg(
    void *transport_out,
    const axis2_env_t *env)
{
    axis2_transport_out_desc_t *transport_out_l = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);

    transport_out_l = (axis2_transport_out_desc_t *) transport_out;
    return axis2_transport_out_desc_free(transport_out_l, env);
}

const axis2_qname_t *AXIS2_CALL
axis2_transport_out_desc_get_qname(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->qname;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_qname(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    const axis2_qname_t *qname)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, qname, AXIS2_FAILURE);

    if (transport_out_impl->qname)
    {
        AXIS2_QNAME_FREE(transport_out_impl->qname, env);
        transport_out_impl->qname = NULL;
    }
    transport_out_impl->qname = AXIS2_QNAME_CLONE(qname, env);
    return AXIS2_SUCCESS;
}

axis2_flow_t *AXIS2_CALL
axis2_transport_out_desc_get_out_flow(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->out_flow;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_flow(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_flow_t *out_flow)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, out_flow, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if (transport_out_impl->out_flow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->out_flow, env);
        transport_out_impl->out_flow = NULL;
    }
    transport_out_impl->out_flow = out_flow;
    return AXIS2_SUCCESS;
}

axis2_flow_t *AXIS2_CALL
axis2_transport_out_desc_get_fault_out_flow(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    return AXIS2_INTF_TO_IMPL(transport_out)->fault_out_flow;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_fault_out_flow(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_flow_t *fault_out_flow)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, fault_out_flow, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if (transport_out_impl->fault_out_flow)
    {
        AXIS2_FLOW_FREE(transport_out_impl->fault_out_flow, env);
        transport_out_impl->fault_out_flow = NULL;
    }
    transport_out_impl->fault_out_flow = fault_out_flow;
    return AXIS2_SUCCESS;
}

axis2_transport_sender_t *AXIS2_CALL
axis2_transport_out_desc_get_sender(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);
    return AXIS2_INTF_TO_IMPL(transport_out)->sender;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_sender(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_transport_sender_t *sender)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, sender, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);

    if (transport_out_impl->sender)
    {
        AXIS2_TRANSPORT_SENDER_FREE(transport_out_impl->sender, env);
        transport_out_impl->sender = NULL;
    }

    transport_out_impl->sender = sender;
    return AXIS2_SUCCESS;
}

axis2_phase_t *AXIS2_CALL
axis2_transport_out_desc_get_out_phase(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);

    return AXIS2_INTF_TO_IMPL(transport_out)->out_phase;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_out_phase(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_phase_t *out_phase)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, out_phase, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if (transport_out_impl->out_phase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->out_phase, env);
        transport_out_impl->out_phase = NULL;
    }
    transport_out_impl->out_phase = out_phase;
    return AXIS2_SUCCESS;
}

axis2_phase_t *AXIS2_CALL
axis2_transport_out_desc_get_fault_phase(
    const axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env)
{
    AXIS2_ENV_CHECK(env, NULL);

    return AXIS2_INTF_TO_IMPL(transport_out)->fault_phase;
}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_set_fault_phase(
    axis2_transport_out_desc_t *transport_out,
    const axis2_env_t *env,
    axis2_phase_t *fault_phase)
{
    axis2_transport_out_desc_impl_t *transport_out_impl = NULL;

    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, fault_phase, AXIS2_FAILURE);

    transport_out_impl = AXIS2_INTF_TO_IMPL(transport_out);
    if (transport_out_impl->fault_phase)
    {
        AXIS2_FLOW_FREE(transport_out_impl->fault_phase, env);
        transport_out_impl->fault_phase = NULL;
    }
    transport_out_impl->fault_phase = fault_phase;
    return AXIS2_SUCCESS;

}

axis2_status_t AXIS2_CALL
axis2_transport_out_desc_add_param(
    axis2_transport_out_desc_t *transport_out_desc,
    const axis2_env_t *env,
    axis2_param_t *param)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, param, AXIS2_FAILURE);

    return AXIS2_PARAM_CONTAINER_ADD_PARAM(transport_out_desc->
            param_container, env, param);
}

axis2_param_t *AXIS2_CALL
axis2_transport_out_desc_get_param(
    const axis2_transport_out_desc_t *transport_out_desc,
    const axis2_env_t *env,
    const axis2_char_t *param_name)
{
    AXIS2_ENV_CHECK(env, NULL);
    AXIS2_PARAM_CHECK(env->error, param_name, NULL);

    return AXIS2_PARAM_CONTAINER_GET_PARAM(transport_out_desc->param_container,
            env, param_name);
}

axis2_bool_t AXIS2_CALL
axis2_transport_out_desc_is_param_locked(
    axis2_transport_out_desc_t *
    transport_out_desc,
    const axis2_env_t *env,
    const axis2_char_t *param_name)
{
    AXIS2_ENV_CHECK(env, AXIS2_FAILURE);
    AXIS2_PARAM_CHECK(env->error, param_name, AXIS2_FAILURE);

    return AXIS2_PARAM_CONTAINER_IS_PARAM_LOCKED(transport_out_desc->
            param_container, env, param_name);
}
