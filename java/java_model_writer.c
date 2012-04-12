//
//  java_model_writer.c
//  CleverModels
//
//  Created by Bruno Martins on 3/29/12.
//  Copyright (c) 2012. All rights reserved.
//

#include <stdio.h>
#include "java_model_writer.h"
#include "../helper_functions.h"
#include "../clever_models.h"

int32_t java_write_class_header(FILE* fp, char class_name[]) {
	int32_t result = -1;
	class_name[0] = toupper(class_name[0]);
	char* singular_class_name = str_plural_to_singular(class_name);
	fprintf(fp, "import java.util.List; \n\n");
	result = fprintf(fp, "public class %s { \n", singular_class_name);
	return result;
}

int32_t java_write_attribute(FILE* fp, char attribute_name[], u_int16_t type) {
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
		result = fprintf(fp, "\tprivate Integer %s; \n", attribute_name);
	else if (TYPE_STRING == type)
		result = fprintf(fp, "\tprivate String %s; \n", attribute_name);
	else if (TYPE_BOOLEAN == type)
		result = fprintf(fp, "\tprivate Boolean %s; \n", attribute_name);
	else
		result = fprintf(fp, "\tprivate String %s; \n", attribute_name);


	free(object_type_name);
	return result;
}

int java_write_getters(FILE* fp, int nr_attributes, char attributes[50][100], int attr_types[]) {
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
			fprintf(fp, "\n\tpublic Integer get%s() { \n", uppercase_attribute_name);
		else if (TYPE_STRING == attr_types[i])
			fprintf(fp, "\n\tpublic String get%s() { \n", uppercase_attribute_name);
		else if (TYPE_BOOLEAN == attr_types[i])
			fprintf(fp, "\n\tpublic Boolean get%s() { \n", uppercase_attribute_name);
		else
			fprintf(fp, "\n\tpublic String get%s() { \n", uppercase_attribute_name);



		fprintf(fp, "\t\t return %s; \n", attributes[i]);
		fprintf(fp, "\t} \n");

		free(object_type_name);
		free(uppercase_attribute_name);
	}

	return i;
}

int java_write_setters(FILE* fp, int nr_attributes, char attributes[50][100], int attr_types[]) {
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
				fprintf(fp, "\n\tpublic void set%s(Integer %s) { \n", uppercase_attribute_name, attributes[i]);
			else if (TYPE_STRING == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(String %s) { \n", uppercase_attribute_name, attributes[i]);
			else if (TYPE_BOOLEAN == attr_types[i])
				fprintf(fp, "\n\tpublic void set%s(Boolean %s) { \n", uppercase_attribute_name, attributes[i]);
			else
				fprintf(fp, "\n\tpublic void set%s(String %s) { \n", uppercase_attribute_name, attributes[i]);

			fprintf(fp, "\t\t this.%s = %s; \n", attributes[i], attributes[i]);
			fprintf(fp, "\t} \n");

			free(object_type_name);
			free(uppercase_attribute_name);
		}

		return i;
}
