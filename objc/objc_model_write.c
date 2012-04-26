/*
 * objc_model_write.c
 *
 *  Created on: Apr 23, 2012
 *      Author: bmartins
 */
#include <stdio.h>
#include "../helper_functions.h"
#include "../clever_models.h"
#include "objc_model_writer.h"

int32_t objc_write_class_header(FILE* fp, FILE* header_file, char class_name[])
{
	int32_t result = -1;

	class_name[0] = toupper(class_name[0]);
	char* singular_class_name = str_plural_to_singular(class_name);
	fprintf(header_file, "#import <Foundation/Foundation.h> \n\n");

	result = fprintf(header_file, "@interface %s : NSObject \n", singular_class_name);

	if(-1 == result)
		perror("failed writting into header file!");

	fprintf(fp, "#import \"%s.h\" \n\n",class_name);
	result = fprintf(fp, "@implementation %s \n", singular_class_name);

	if(-1 == result)
		perror("failed writting into header file!");

	return result;
}

int32_t objc_write_attribute(FILE* fp, FILE* header_file, char attribute_name[], u_int16_t type)
{
		u_int32_t result = -1;
		char c = toupper(attribute_name[0]);

		char* object_type_name = malloc(strlen(attribute_name));
		strncpy(object_type_name, attribute_name, strlen(attribute_name));
		object_type_name[strlen(attribute_name)] = '\0';

		*object_type_name = c;
		object_type_name = str_plural_to_singular(object_type_name);

		if (TYPE_OBJECT == type) {
			result = fprintf(header_file, "\t@property (strong) %s* %s; \n", object_type_name,
					attribute_name);
			result = fprintf(fp, "\t@synthesize %s; \n", attribute_name);

			char include_str[200];
			strcat(include_str, "#import \"");
			strcat(include_str, object_type_name);
			strcat(include_str, ".h\" \n");

			include_str[199] = '\0';

			preppend_to_file(include_str, header_file);
		}
		else if (TYPE_LIST == type) {
			result = fprintf(header_file, "\t@property (strong) NSArray* %s; \n", object_type_name,
					attribute_name);
			fprintf(fp, "\t@synthesize %s; \n", object_type_name,
								attribute_name);
		}
		else if (TYPE_INTEGER == type) {
			result = fprintf(header_file, "\t@property (strong) NSInteger* %s; \n", attribute_name);
			result = fprintf(fp, "\t@synthesize %s; \n", attribute_name);
		} else if (TYPE_STRING == type) {
			result = fprintf(header_file, "\t@property (strong) NSString* %s; \n", attribute_name);
			result = fprintf(fp, "\t@synthesize %s; \n", attribute_name);
		}
		else if (TYPE_BOOLEAN == type) {
			result = fprintf(header_file, "\t@property (strong) BOOL %s; \n", attribute_name);
			result = fprintf(fp, "\t@synthesize %s; \n", attribute_name);
		} else {
			result = fprintf(header_file, "\t@property (strong) NSString* %s; \n", attribute_name);
			result = fprintf(fp, "\t@synthesize %s; \n", attribute_name);
		}

		free(object_type_name);
		return result;
}

int objc_write_getters(FILE* fp, FILE* header_file, int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[])
{}

int objc_write_setters(FILE* fp, FILE* header_file,int nr_attributes, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int attr_types[])
{}

