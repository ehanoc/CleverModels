//
//  helper_functions.c
//  CleverModels
//
//  Created by Bruno Martins on 3/27/12.
//  Copyright (c) 2012. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "helper_functions.h"

void preppend_to_file(const char *t, FILE *fp)
{
	char* buf;
	long len = 0;

	fseek(fp,0,SEEK_END);
	len = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	buf = (char *)malloc(len);
	fread(buf,len,1,fp);

	fseek(fp,0,SEEK_SET);

	fprintf(fp, "%s",t);
	fprintf(fp, "%s",buf);

	fseek(fp,0,SEEK_END);

	free(buf);
}

//TODO: Actually implement this
char* str_plural_to_singular(char str[])
{
//    long pos_s_char = str_pos_reverse('s', str, strlen(str), 1);
//    //to avoid taking away the last S on double S's ending strings. Like : Adress, is still singular.
//    long pos_s_second_char = str_pos_reverse('s', str, strlen(str),2);
//
//    if (-1 == pos_s_char || pos_s_char == pos_s_second_char+1)
//        return str;
//
//    long len = strlen(str);
//
//    printf("str : %s \n", str);
//
//    if(len > 1)
//        str[pos_s_char] = '\0';
//
//    printf("after str : %s \n", str);

    return str;
}

int str_pos(char c, char haystack[], int occurence)
{

    int times_found = 0;
    int i;
    for (i=0; i<strlen(haystack); i++) {
        if (c == haystack[i]) {
            times_found++;

            if (occurence == times_found)
                return i;
        }
    }
    return -1;
}



int str_pos_reverse (char c, char haystack[], int star_pos, int occurence)
{
    int times_found = 0;
    int i;
    for (i = star_pos; i>=0; i--) {
        if (c == haystack[i]) {
            times_found++;

            if (occurence == times_found)
                return i;
        }
    }
    return -1;
}

void str_to_lower(char str [])
{
    int i;
    for (i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

char find_first_character(char haystack[])
{
    int i;
    for (i = 0; i<strlen(haystack); i++) {
        if (' ' != haystack[i])
            return haystack[i];
    }

    return -1;
}
