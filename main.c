//
//  main.c
//  CleverModels
//
//  Created by Bruno Martins on 3/20/12.
//  Copyright (c) 2012. All rights reserved.
//
#include <stdio.h>
#include "clever_models.h"
#include <sys/stat.h>
#include "languages.h"
#include <getopt.h>
#include <unistd.h>
#include "helper_functions.h"


int main(int argc, char * argv[]) {

	int as_model_path 	= 0;
	int as_name 		= 0;
	int as_language 	= 0;
	int as_url			= 0;
	int as_class_header = 0;
	int as_json_string	= 0;

	char* feed_string_file = "/tmp/clevermodels_http_response_body";

	char* models_path 	= 0;
	char* name 			= 0;
	char* json 			= malloc(1024*8);
	char* class_headers = 0;

	int language_code = -1;

	int c;
	int pid;

	opterr = 0;

	while ((c = getopt(argc, argv, "u:l:n:p:h:j:")) != -1) {
		switch (c) {
		case 'u': {
			as_url = 1;
			pid = fork();

			if (0 == pid) {
				execl("/usr/bin/curl", "curl", "-o", feed_string_file, optarg, NULL);
				return 0;
			}
		}
			break;
		case 'l': {
			as_language = 1;
			language_code = get_language_code(optarg);
			if (-1 == language_code) {
				printf("unknown language : %s \n", optarg);
				exit(-1);
			}
		}
			break;
		case 'n': {
			as_name = 1;
			name = optarg;
		}
			break;
		case 'p': {
			as_model_path = 1;
			models_path = optarg;
		}
			break;
		case 'h': {
			as_class_header = 1;
			class_headers = optarg;
		}
			break;
		case 'j': {
			as_json_string = 1;
			json = optarg;
		}
			break;
		case '?':
			if (optopt == 'c')
				fprintf(stderr, "Option -%c requires an argument.\n", optopt);
			else if (isprint(optopt))
				fprintf(stderr, "Unknown option `-%c'.\n", optopt);
			else
				fprintf(stderr, "Unknown option character `\\x%x'.\n", optopt);
			//return 1;
			break;
		default:
			//abort();
			break;
		}
	}
	//wait for curl to finish requesting the feed
	wait(&pid);

	system("cat /tmp/clevermodels_http_response_body | sed \"s/'//g\" -i /tmp/clevermodels_http_response_body");

	if (0 == as_model_path || 0 == as_name || 0 == as_language) {
		perror("missing arguments! Required -n -l -p");
		exit(-1);
	}
//
	if (0 == as_json_string) {
		FILE* feed_file_stream;
		feed_file_stream = fopen(feed_string_file, "r");
		char ch;
		while ((ch = fgetc(feed_file_stream)) != EOF) {
			json[strlen(json)] = ch;
		}
	}
//
	printf("json : %s \n", json);

	json[strlen(json)] = '\0';

	write_json_class_model(name, json, language_code, models_path, class_headers, 0);
	free(json);

	printf("done!");

	return 0;
}
