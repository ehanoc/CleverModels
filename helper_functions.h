//
//  helper_functions.h
//  CleverModels
//
//  Created by Bruno Martins on 3/27/12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef CleverModels_helper_functions_h
#define CleverModels_helper_functions_h

#include <stdlib.h>

int str_pos(char c, char haystack[], int occurence);
int str_pos_reverse (char c, char haystack[], int start_pos, int occurence);
void str_to_lower(char str []);
char find_first_character(char haystack[]);
char* str_plural_to_singular(char str[]);

void preppend_to_file(const char *t, FILE *fp);

#endif
