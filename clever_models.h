//
//  clever_models.h
//  CleverModels
//
//  Created by Bruno Martins on 3/27/12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef CleverModels_clever_models_h
#define CleverModels_clever_models_h

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"

const static int TYPE_OBJECT    = 0;
const static int TYPE_LIST      = 1;
const static int TYPE_INTEGER   = 2;
const static int TYPE_BOOLEAN   = 3;
const static int TYPE_STRING    = 4;
const static int TYPE_OTHER     = 5;

unsigned int write_json_class_model(char name[], char json[], int language_code, char path[], char* class_headers, int multiple_objects);
int get_attribute_type(char json[], int colon_pos);
int already_wrote_attribute(char* attribute_name, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int nr_attributes);

int pos_end_of_attribute_and_value(char* json, int current_pos);

int find_pos_end_object_array(char *json);

#endif
