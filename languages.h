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

enum {
	JAVA     = 0,
	PHP      = 1,
	CSHARP   = 2,
	CPP      = 3,
	OBJC	 = 4
};

int get_language_code(char* language);

#endif
