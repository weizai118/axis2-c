/*
 * This file should be auto-generated by the Axis2 C Web Service Generator
 * This file contains the two export functions of the Web service Dynamic Library 
 */

#include "calc_skeleton.h" 
extern "C" {

int axis2_get_instance(struct axis2_svc_skeleton **inst)
{
    axis2_status_t status = AXIS2_FAILURE;
    
	*inst = axis2_svc_skeleton_create();
    if(NULL != *inst)
    {
        status = *inst->init();
    }

    return status;
}

int axis2_remove_instance(axis2_svc_skeleton *inst)
{
    axis2_status_t status = AXIS2_FAILURE;
	if (inst)
	{
        status = AXIS2_SVC_SKELETON_FREE(inst);
    }
    return status;
}

}
