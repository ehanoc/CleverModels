//
//  java_model_writer.h
//  CleverModels
//
//  Created by Bruno Martins on 3/29/12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef CleverModels_java_model_writer_h
#define CleverModels_java_model_writer_h

#include <stdlib.h>
#include <stdio.h>
#include "../constants.h"

int32_t java_write_class_header(FILE* fp, char class_name[]);
int32_t java_write_attribute(FILE* fp, char attribute_name[], u_int16_t type);
int java_write_getters(FILE* fp, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);
int java_write_setters(FILE* fp, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);

#endif
