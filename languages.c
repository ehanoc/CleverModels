//
//  languages.c
//  CleverModels
//
//  Created by Bruno Martins on 3/29/12.
//  Copyright (c) 2012. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "helper_functions.h"
#include "languages.h"

int get_language_code(char* language)
{
    int code = -1;
    
    if (strcmp(language, "java") == 0) {
        code = JAVA;
    }
    
    if (strcmp(language, "php") == 0) {
        code = PHP;
    }
    
    if (strcmp(language, "csharp") == 0) {
        code = CSHARP;
    }
    
    if (strcmp(language, "cpp") == 0) {
        code = CPP;
    }
    
    return code;
}
