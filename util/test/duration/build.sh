#!/bin/bash

gcc duration_test.c ../util/create_env.c -g -I$AXIS2C_HOME/include/axis2-1.3.0 -L$AXIS2C_HOME/lib -laxutil -laxis2_axiom -laxis2_parser -o duration_test  -ldl -Wl,--rpath -Wl,$AXIS2C_HOME/lib 
