//
//  languages.h
//  CleverModels
//
//  Created by Bruno Martins on 3/29/12.
//  Copyright (c) 2012. All rights reserved.
//

#ifndef CleverModels_languages_h
#define CleverModels_languages_h

#include <stdlib.h>

const static int JAVA     = 0;
const static int PHP      = 1;
const static int CSHARP   = 2;
const static int CPP      = 3;
const static int OBJC	  = 4;

int get_language_code(char* language);

#endif
