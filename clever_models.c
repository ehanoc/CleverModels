//
//  clever_models.c
//  CleverModels
//
//  Created by Bruno Martins on 3/27/12.
//  Copyright (c) 2012. All rights reserved.
//

#include <stdio.h>
#include "constants.h"
#include "clever_models.h"
#include "helper_functions.h"
#include "model_builder.h"
#include "languages.h"

unsigned int write_json_class_model(char name[], char json[], int language_code, char path[], char* class_headers, int multiple_objects)
{
	//printf("entering for class : %s \n", name);
	int opening_tag = 0;
	int closing_tag = 0;
	int opening_square_brackets = 0;
	int closing_square_brackets = 0;

	char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH];
	int attr_types[MAX_ATTRIBUTES];
	int nr_attributes = 0;

	FILE* implementation_file = 0;
	FILE* header_file = 0;
	printf("writting class files ! language_code : %d \n", language_code);
	create_class_files(name, path, language_code, class_headers, &implementation_file,	&header_file);
	write_class_header(name, language_code, implementation_file, header_file);
	printf("wrote class files ! \n");
//	char* json = malloc(strlen(json) + 1);
//	strncpy(json, json, strlen(json));
//	json[strlen(json)] = '\0';

	int i;
	for (i = 0; i < strlen(json); i++) {
		char current_char = json[i];
		switch (current_char) {
		case '{':
			opening_tag++;
			break;

		case ':': {

			//checking if : character is part of a string
			//if not, meaning its part of key:value notation, we proceed
			char next_char = (char)json[i+1];
			char prev_char = (char)json[i-1];
			if ('"' != prev_char && '"' != next_char) //found a : character whitin a string. Ignore!
				continue;

			//Get the name of the attribute / key by finding the string between quotes
			//#1 - get quotes position
			int key_second_quote = str_pos_reverse('"', json, i, 1);
			int key_first_quote = str_pos_reverse('"', json, i, 2);

			//printf("second_quote : %d, first_quote : %d \n", pos_attr_name_second_quote, pos_attr_name_first_quote);

			//#2 compute size of key/attribute
			int length_attr_name = (key_second_quote - key_first_quote) - 1;

			//+1 for the string tail character
			char attribute_name[length_attr_name + 1];
			//build attribute string & terminate string
			strncpy(attribute_name, json + key_first_quote + 1, length_attr_name);
			attribute_name[length_attr_name] = '\0';

			//printf("Class : %s -> Attribute name : %s, length : %d \n", name, attribute_name, length_attr_name);

			int attr_type = get_attribute_type(json, i);
			if (0 == already_wrote_attribute(attribute_name, attributes, nr_attributes) && strcmp(":", attribute_name) != 0) {
				//keep track of the attributes being added so we can generate getters & setters later on
				int z;
				for (z = 0; z <= length_attr_name; ++z) {
					attributes[nr_attributes][z] = attribute_name[z];
				}

				attr_types[nr_attributes] = attr_type;
				nr_attributes++;

				write_attribute(attribute_name, attr_type, language_code,implementation_file, header_file);

				if (TYPE_OBJECT == attr_type || TYPE_LIST == attr_type) {
					int multiple = 0;
					if (TYPE_LIST == attr_type) {
						multiple = 1;
					}

					char* partial_json = malloc(strlen(json+i+1));
					strncpy(partial_json, json+i+1, strlen(json+i+1));

					i += write_json_class_model(attribute_name, partial_json, language_code, path, class_headers, multiple);


					free(partial_json);
					//printf("# # back from class : %s rest json : %s, class name : %s, position : %d \n",attribute_name ,json+i, name, i);
				}
			}

			break;
		}

		case '[': //array
			opening_square_brackets++;
			break;

		case '}': {
			closing_tag++;
			if (opening_tag == closing_tag) {
				//printf("# end of object ! rest json : %s, class name : %s, position : %d \n", json+i, name, i);

				if (opening_square_brackets > closing_square_brackets) {
					//find position of the end of the list of objects of this type
					i += find_pos_end_object_array(json+i);
				} else {
					i++;
				}
				goto close_class;
			}
		}
			break;

		case ']': {
			closing_square_brackets++;
			if (opening_tag == closing_tag && closing_square_brackets == opening_square_brackets) {
				//printf("# end ] rest json : %s, class name : %s, position : %d \n", json+i, name, i);
				i++;
				goto close_class;
			}
		}
			break;
		default:
			//ignore
			break;
		}
	}

	close_class:
		write_getters(implementation_file, header_file, language_code, attributes, attr_types, nr_attributes);
		write_setters(implementation_file, header_file, language_code, attributes, attr_types, nr_attributes);

		if(OBJC == language_code)
			fprintf(implementation_file, "@end");
	    else
	    	fprintf(implementation_file, "}");

		fclose(implementation_file);
		if (NULL != header_file) {
			if(OBJC == language_code)
				fprintf(header_file, "@end");
			else
				fprintf(header_file, "}");
			fclose(implementation_file);
		}
		//free(mutable_json);

	return i;
}

int get_attribute_type(char json[], int colon_pos) {
	int attr_type = TYPE_OTHER;
	char next_char = find_first_character(json + colon_pos + 1);

	switch (next_char) {
	case '{':
		attr_type = TYPE_OBJECT;
		break;

	case '[':
		attr_type = TYPE_LIST;
		break;

	default: {
		//try to find if attribute is a number,string or boolean

		//find ending character after the value
		//its either } or , (in case that there is more attributes defined after)
		int pos_next_closing_bracket = str_pos('}', json + colon_pos + 1, 1);
		int pos_next_comma = str_pos(',', json + colon_pos + 1, 1);

		//default we assume that the length of value is until the closing bracket
		int value_length = (colon_pos + (pos_next_closing_bracket))	- (colon_pos) - 2;

		//string ?
		int first_quote = str_pos('"', json + colon_pos, 1);
		int second_quote = str_pos('"', json + colon_pos, 2);

		//but we found a comma
		if (-1 != pos_next_comma) {
			//first found comma comes first than the closing bracket ?
			if (pos_next_comma < pos_next_closing_bracket)
				value_length = (colon_pos + (pos_next_comma)) - (colon_pos) - 2;
			else
				value_length = (colon_pos + (pos_next_closing_bracket))	- (colon_pos) - 2;
		}

		if (value_length >= 0) {
			char* value = malloc(value_length + 1);
			strncpy(value, json + colon_pos + 2, value_length);
			value[value_length] = '\0';

			if (-1 != first_quote && -1 != second_quote) {
				attr_type = TYPE_STRING;
			} else if (NULL != strstr(value, "false") || NULL != strstr(value, "true")) {
				attr_type = TYPE_BOOLEAN;
			} else if (-1 != atoi(value)) {
				attr_type = TYPE_INTEGER;
			} else if(NULL != strstr(value, "null")) {
				printf("NULL Object !! \n");
				attr_type = TYPE_OBJECT;
			}

			//printf("value : %s length : %d \n", value, value_length);

			free(value);
		}
	}
		break;
	}
	return attr_type;
}

int already_wrote_attribute(char* attribute_name, char attributes[MAX_ATTRIBUTES][MAX_ATTRIBUTE_NAME_LENGTH], int nr_attributes) {
	int i;
	for (i = 0; i < nr_attributes; ++i) {
		if (strcmp(attribute_name, attributes[i]) == 0)
			return 1;
	}

	return 0;
}

int find_pos_end_object_array(char *json)
{
	int opening_square_brackets = 1;
	int closing_square_brackets = 0;

	char c;
	int i;
	for (i = 0; i < strlen(json); ++i) {
		c = json[i];
		switch (c) {
			case '[':
				opening_square_brackets++;
				break;
			case ']': {
				closing_square_brackets++;
				if (opening_square_brackets == closing_square_brackets) {
					return i;
				}
			}
				break;
			default:
				continue;
				break;
		}
	}
	return -1;
}
