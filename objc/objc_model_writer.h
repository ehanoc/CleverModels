/*
 * objc_model_writer.h
 *
 *  Created on: Apr 23, 2012
 *      Author: bmartins
 */

#ifndef OBJC_MODEL_WRITER_H_
#define OBJC_MODEL_WRITER_H_

#include <stdlib.h>
#include <stdio.h>
#include "../constants.h"

int32_t objc_write_class_header(FILE* fp, FILE* header_file, char class_name[]);
int32_t objc_write_attribute(FILE* fp, FILE* header_file, char attribute_name[], u_int16_t type);
int objc_write_getters(FILE* fp, FILE* header_file, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);
int objc_write_setters(FILE* fp, FILE* header_file,int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);

#endif /* OBJC_MODEL_WRITER_H_ */
