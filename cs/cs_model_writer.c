/*
 * cs_model_writer.c
 *
 *  Created on: Jun 12, 2012
 *      Author: bmartins
 */

#include <stdio.h>
#include "cs_model_writer.h"
#include "../helper_functions.h"
#include "../clever_models.h"

int32_t cs_write_class_header(FILE* fp, char class_name[]) {
	int32_t result = -1;
	class_name[0] = toupper(class_name[0]);
	char* singular_class_name = str_plural_to_singular(class_name);
	fprintf(fp, "\n using System;");
	fprintf(fp, "\n using System.Collections.Generic;");
	result = fprintf(fp, "\n public class %s { \n", singular_class_name);
	return result;
}

int32_t cs_write_attribute(FILE* fp, char attribute_name[], u_int16_t type) {
	u_int32_t result = -1;

	char c = toupper(attribute_name[0]);

	char* object_type_name = malloc(strlen(attribute_name));
	strncpy(object_type_name, attribute_name, strlen(attribute_name));
	object_type_name[strlen(attribute_name)] = '\0';

	*object_type_name = c;
	object_type_name = str_plural_to_singular(object_type_name);

	if (TYPE_OBJECT == type)
		result = fprintf(fp, "\tprivate %s %s; \n", object_type_name,
				attribute_name);
	else if (TYPE_LIST == type)
		result = fprintf(fp, "\tprivate List<%s> %s; \n", object_type_name,
				attribute_name);
	else if (TYPE_INTEGER == type)
		result = fprintf(fp, "\tprivate int %s; \n", attribute_name);
	else if (TYPE_STRING == type)
		result = fprintf(fp, "\tprivate string %s; \n", attribute_name);
	else if (TYPE_BOOLEAN == type)
		result = fprintf(fp, "\tprivate bool %s; \n", attribute_name);
	else
		result = fprintf(fp, "\tprivate string %s; \n", attribute_name);


	free(object_type_name);
	return result;
}

int cs_write_getters(FILE* fp, int nr_attributes, char attributes[50][100], int attr_types[]) {
	int i;
	for (i = 0; i < nr_attributes; ++i) {

		char* uppercase_attribute_name = malloc(sizeof(attributes[i]));
		strncpy(uppercase_attribute_name, attributes[i], sizeof(attributes[i]));
		uppercase_attribute_name[strlen(uppercase_attribute_name)] = '\0';
		uppercase_attribute_name[0] = toupper(uppercase_attribute_name[0]);

		char* object_type_name = malloc(sizeof(uppercase_attribute_name));
		strncpy(object_type_name, uppercase_attribute_name, sizeof(uppercase_attribute_name));
		object_type_name[strlen(uppercase_attribute_name)] = '\0';

		object_type_name = str_plural_to_singular(object_type_name);

		if (TYPE_OBJECT == attr_types[i])
			fprintf(fp, "\n\tpublic %s get%s() { \n", object_type_name, uppercase_attribute_name);
		else if (TYPE_LIST == attr_types[i])
			fprintf(fp, "\n\tpublic List<%s> get%s() { \n", object_type_name, uppercase_attribute_name);
		else if (TYPE_INTEGER == attr_types[i])
			fprintf(fp, "\n\tpublic int get%s() { \n", uppercase_attribute_name);
		else if (TYPE_STRING == attr_types[i])
			fprintf(fp, "\n\tpublic string get%s() { \n", uppercase_attribute_name);
		else if (TYPE_BOOLEAN == attr_types[i])
			fprintf(fp, "\n\tpublic bool get%s() { \n", uppercase_attribute_name);
		else
			fprintf(fp, "\n\tpublic string get%s() { \n", uppercase_attribute_name);



		fprintf(fp, "\t\t return %s; \n", attributes[i]);
		fprintf(fp, "\t} \n");

		free(object_type_name);
		free(uppercase_attribute_name);
	}

	return i;
}

int cs_write_setters(FILE* fp, int nr_attributes, char attributes[50][100], int attr_types[]) {
	int i;
		for (i = 0; i < nr_attributes; ++i) {

			char* uppercase_attribute_name = malloc(sizeof(attributes[i]));
			strncpy(uppercase_attribute_name, attributes[i], sizeof(attributes[i]));
			uppercase_attribute_name[strlen(uppercase_attribute_name)] = '\0';
			uppercase_attribute_name[0] = toupper(uppercase_attribute_name[0]);

			char* object_type_name = malloc(sizeof(uppercase_attribute_name));
			strncpy(object_type_name, uppercase_attribute_name, sizeof(uppercase_attribute_name));
			object_type_name[strlen(uppercase_attribute_name)] = '\0';

			object_type_name = str_plural_to_singular(object_type_name);

			if (TYPE_OBJECT == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(%s %s) { \n", uppercase_attribute_name, object_type_name, attributes[i]);
			else if (TYPE_LIST == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(List<%s> %s) { \n", uppercase_attribute_name, object_type_name, attributes[i]);
			else if (TYPE_INTEGER == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(int %s) { \n", uppercase_attribute_name, attributes[i]);
			else if (TYPE_STRING == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(string %s) { \n", uppercase_attribute_name, attributes[i]);
			else if (TYPE_BOOLEAN == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(bool %s) { \n", uppercase_attribute_name, attributes[i]);
			else
				fprintf(fp, "\n\tpublic void set%s(string %s) { \n", uppercase_attribute_name, attributes[i]);

			fprintf(fp, "\t\t this.%s = %s; \n", attributes[i], attributes[i]);
			fprintf(fp, "\t} \n");

			free(object_type_name);
			free(uppercase_attribute_name);
		}

		return i;
}
