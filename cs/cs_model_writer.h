/*
 * cs_model_writer.h
 *
 *  Created on: Jun 12, 2012
 *      Author: bmartins
 */

#ifndef CS_MODEL_WRITER_H_
#define CS_MODEL_WRITER_H_

#include <stdlib.h>
#include <stdio.h>
#include "../constants.h"

int32_t cs_write_class_header(FILE* fp, char class_name[]);
int32_t cs_write_attribute(FILE* fp, char attribute_name[], u_int16_t type);
int cs_write_getters(FILE* fp, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);
int cs_write_setters(FILE* fp, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[]);


#endif /* CS_MODEL_WRITER_H_ */
