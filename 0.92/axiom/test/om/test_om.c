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

#include <axiom_stax_builder.h>
#include <axiom_document.h>
#include <axiom_node.h>
#include <axiom_element.h>
#include <axiom_text.h>
#include <axis2_stream.h>
#include <axis2_log_default.h>
#include <axis2_error_default.h>
#include <axiom_xml_reader.h>
#include <stdio.h>
#include <axiom_xml_writer.h>
#include <axis2_env.h>
/** 
   Define the environment related variables globaly so that they are available 
   for both functions 
*/

axis2_allocator_t *allocator = NULL;
axis2_env_t *environment = NULL;
axis2_stream_t *stream = NULL;
axis2_error_t *error = NULL;
axis2_log_t *axis_log     = NULL;
FILE *f = NULL;
/** a method that demonstrate creating a om model using an xml file */


int read_input(char *buffer,int size,void* ctx)
{
   int len = 0;
   char* pos = NULL;
   len = fread(buffer, sizeof(char),size,f);
   if (buffer)
       pos = strstr(buffer, "---");
   if (pos)
   {
        len = pos - buffer;
        *pos = '\0';
   }
   return len;
}

int
test_om_build (const char *filename)
{
    axiom_element_t *ele1 = NULL, *ele2 = NULL;
    axiom_stax_builder_t *builder = NULL;
    axiom_text_t *text = NULL;
    axiom_document_t *document = NULL;
    axiom_node_t *node1 = NULL, *node2 = NULL;
    axiom_output_t *om_output = NULL;
    axiom_namespace_t* ns = NULL;
    axiom_xml_reader_t *reader = NULL;
    axiom_xml_writer_t *writer = NULL;
    char *buffer = NULL;
    f =fopen(filename, "r");
    if(!f)
        return -1;
      
    /** create pull parser */
     reader = axiom_xml_reader_create_for_io(environment, read_input,NULL ,NULL, NULL);
    
    if(!reader)
    {
        printf("ERROR CREATING PULLPARSER");
        return -1;
    }
    /** create axiom_stax_builder by parsing pull_parser struct */
    
    builder = axiom_stax_builder_create (environment,reader);
    
    if(!builder)
    {
        printf("ERROR CREATING PULL PARSER");
        return -1;
    }
    /** 
        create an om document
        document is the container of om model created using builder 
    */
           
    document = AXIOM_STAX_BUILDER_GET_DOCUMENT (builder, environment);
    /**
        get root element , building starts hear 
     */
    if(!document)
        return -1;

    node1 = AXIOM_DOCUMENT_GET_ROOT_ELEMENT (document, environment);
    if(!node1)
    {
        printf(" root element null ");
        AXIOM_STAX_BUILDER_FREE(builder, environment);
        return -1;
    }
    if(node1)
    {
        /** print root node information */
        
       
        ele1 =AXIOM_NODE_GET_DATA_ELEMENT(node1,environment);
        if(ele1)
             
        printf ("root localname %s\n",AXIOM_ELEMENT_GET_LOCALNAME(ele1,environment));
         
        ns = AXIOM_ELEMENT_GET_NAMESPACE(ele1,environment, node1);
    
        if (ns)
        {
            printf ("root ns prefix %s\n", AXIOM_NAMESPACE_GET_PREFIX(ns,environment));
            printf ("root ns uri %s\n", AXIOM_NAMESPACE_GET_URI(ns,environment));

        }
    }
    /** build the document continuously untill all the xml file is built in to a om model */
    
    
    node2 = AXIOM_DOCUMENT_BUILD_NEXT( document , environment);
    do
    {

        if (!node2)
            break;

        switch (AXIOM_NODE_GET_NODE_TYPE(node2,environment))
        {
        case AXIOM_ELEMENT:
            ele2 =(axiom_element_t*) AXIOM_NODE_GET_DATA_ELEMENT(node2, environment);
            if(ele2 && AXIOM_ELEMENT_GET_LOCALNAME(ele2,environment))
            {
                printf("\n localname %s\n" , AXIOM_ELEMENT_GET_LOCALNAME(ele2,environment)); 
            }
                        
            break;
        case AXIOM_TEXT:
            
            text = (axiom_text_t *)AXIOM_NODE_GET_DATA_ELEMENT(node2,environment);    
            if( text && AXIOM_TEXT_GET_VALUE(text ,environment))
                printf("\n text value  %s \n", AXIOM_TEXT_GET_VALUE(text,environment));
            break;

        default:
            break;
        }

        node2 = AXIOM_DOCUMENT_BUILD_NEXT (document , environment);
    }
    while (node2);
    printf ("END: pull document\n");

    printf ("Serialize pulled document\n");
    
    writer = axiom_xml_writer_create_for_memory(environment, NULL, AXIS2_TRUE, 0,
                                       AXIS2_XML_PARSER_TYPE_BUFFER);
    om_output = axiom_output_create (environment, writer);

    AXIOM_NODE_SERIALIZE (node1, environment , om_output);
    
    buffer = (axis2_char_t*)AXIOM_XML_WRITER_GET_XML(writer, environment);
    
    AXIOM_OUTPUT_FREE(om_output, environment);  
    if(buffer)
        printf("%s",buffer);
  
    AXIOM_STAX_BUILDER_FREE(builder, environment);
    if(buffer)
        AXIS2_FREE(environment->allocator, buffer); 
    printf ("\ndone\n");
    fclose(f);
    return 0;
}



int
test_om_serialize ()
{

    /*
       <book xmlns:axiomc="http://ws.apache.org/axis2/c/om" xmlns:isbn="urn:ISBN:0-395-74341-6">
       <title>Axis2/C OM HOWTO</title>
       <isbn:number>1748491379</isbn:number>
       <author title="Mr" name="Axitoc Oman" />
       <notes>
       <p xmlns="urn:w3-org-ns:HTML">
       This is <i>vey good</i> book on OM!
       </p>
       </notes>
       </book>
    */
    int status;
    axiom_element_t *ele1 = NULL, *ele2 = NULL, *ele3 = NULL, *ele4 =
        NULL;
    axiom_node_t *node1 = NULL, *node2 = NULL, *node3 = NULL, *node4 =
        NULL, *node5 = NULL, *node6 = NULL;
    axiom_attribute_t *attr1 = NULL, *attr2 = NULL;
    axiom_namespace_t *ns1 = NULL, *ns2 = NULL;
    axiom_text_t *text1 = NULL;
    axiom_output_t *om_output = NULL;
    axiom_xml_writer_t *writer = NULL;
    axis2_char_t *output_buffer = NULL;

    ns1 =
        axiom_namespace_create (environment,
                                   "http://ws.apache.org/axis2/c/om",
                                   "axiom");
    ns2 =
        axiom_namespace_create (environment, "urn:ISBN:0-395-74341-6",
                                   "isbn");
    ele1 = axiom_element_create (environment, NULL, "book", ns1, &node1);
    AXIOM_ELEMENT_DECLARE_NAMESPACE(ele1,environment,node1,ns2);
    
    ele2 = axiom_element_create (environment, node1, "title", ns1, &node2);
    
    text1 = axiom_text_create (environment, node2, "Axis2/C OM HOWTO", &node3);
    
    ele3 = axiom_element_create (environment, node1, "number", ns2, &node4);
    
    text1 = axiom_text_create (environment, node4, "1748491379", &node5);
    
    ele4 = axiom_element_create (environment, node1, "author", ns1, &node6);
    
    attr1 = axiom_attribute_create (environment, "title", "Mr", ns1);
    
    AXIOM_ELEMENT_ADD_ATTRIBUTE(ele4, environment,attr1, node6);
    
    attr2 = axiom_attribute_create (environment, "name", "Axitoc Oman", ns1);
    
    AXIOM_ELEMENT_ADD_ATTRIBUTE(ele4,environment, attr2, node6);
    
   
    /* serializing stuff */
    writer = axiom_xml_writer_create_for_memory(environment, NULL, AXIS2_TRUE, 0,
                                    AXIS2_XML_PARSER_TYPE_BUFFER);
    om_output = axiom_output_create (environment, writer);

    printf ("Serialize built document\n");
    status = AXIOM_NODE_SERIALIZE (node1,environment ,om_output);
    if (status != AXIS2_SUCCESS)
    {
        printf ("\naxiom_node_serialize failed\n");
        return status;
    }
    else
        printf ("\naxiom_node_serialize success\n");
    /* end serializing stuff */

     AXIOM_NODE_FREE_TREE(node1,environment);
     output_buffer = (axis2_char_t*)AXIOM_XML_WRITER_GET_XML(writer, environment);
     
     AXIOM_OUTPUT_FREE(om_output, environment);
     if(output_buffer)
     {
        printf("%s",output_buffer);
        AXIS2_FREE(environment->allocator, output_buffer); 
     }        
     printf ("\nDONE\n");
     

    return 0;
}


int
main (int argc, char *argv[])
{
    const char *file_name = "./../../resources/xml/om/test.xml";
    if (argc > 1)
        file_name = argv[1];
    allocator = axis2_allocator_init (NULL);
    axis_log = axis2_log_create(allocator, NULL, NULL);
    error = axis2_error_create(allocator);
    
    environment = axis2_env_create_with_error_log(allocator, error,  axis_log);
    test_om_build (file_name); 
    test_om_serialize(); 

    axis2_env_free(environment); 
    axis2_allocator_free(allocator);
    return 0;
}

