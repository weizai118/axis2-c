#!/bin/bash

gcc allocator_test.c ../util/create_env.c -g -I$AXIS2C_HOME/include/axis2-1.2 -L$AXIS2C_HOME/lib -laxutil -laxis2_axiom -laxis2_parser -o allocator_test 
