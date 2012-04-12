//
//  model_builder.h
//  CleverModels
//
//  Created by Bruno Martins on 3/29/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef CleverModels_model_builder_h
#define CleverModels_model_builder_h

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "constants.h"

int write_setters(FILE* implementation_file, FILE* header_file, int language_code, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[], int nr_attributes);
int write_getters(FILE* implementation_file, FILE* header_file, int language_code, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[], int nr_attributes);
int write_class_header(char class_name[], int16_t language, FILE* implementation_file, FILE* header_file);
int write_attribute(char attribute_name[], int16_t type, int16_t language, FILE* implementation_file, FILE* header_file);
void create_class_files(char name[], char path[], int language_code, char class_headers[], FILE** implementation, FILE** header);

#endif
