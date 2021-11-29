#include <regex.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

/**
 * Takes a line from a csv file, splits it by its commas, and then
 * removes the quotes ("") from the beginning and end of each item,
 * making the line prepared for analysis.
 */
void splitter(char* line, char** output){
	char* token;
	int counter = 0;

	token = strtok(line,",");
	counter++;
	while(token != NULL ) {
		token = strtok(NULL, ",");
		counter++;
	}

	char** splitted = malloc(counter * sizeof(char*));
	for(int i = 0; i < counter; i++){
		if(i == 0) token = strtok(line, ",");
		else token = strtok(NULL, ",");
		splitted[i] = malloc(strlen(token) * sizeof(char));
		strcpy(token, splitted[i]);
	}

	output = malloc(counter * sizeof(char*));
	// remove the quotes from the string ""
	for(int i = 0; i < counter; i++){
        output[i] = malloc(strlen(splitted[i]) * sizeof(char) - 2);
        memcpy(output[i], &splitted[1], strlen(splitted[i])-3);
    }
    
    free(splitted);
}

/**
 * Checks if a file exists and is not a directory 
 */
int check_file(char* filename){
	int status = 1;
	struct stat statbuf;
	if(stat(filename, &statbuf) == -1)
		status = 0;
	
	if(S_ISDIR(statbuf.st_mode))
		status = 0;
	return status;
}

/**
 * Checks if a supplied string is an IP Address of a specific version. 
 */
int check_IP_address_version(char* address, int version){
	int status = 1;
	regex_t regex;

	switch(version){
		case 4 : regcomp(&regex, "\\b((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.|$)){4}\\b", 0);
				 break;
		case 6 : regcomp(&regex, "(([0-9a-fA-F]{1,4}:){7,7}[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,7}:|([0-9a-fA-F]{1,4}:){1,6}:[0-9a-fA-F]{1,4}|([0-9a-fA-F]{1,4}:){1,5}(:[0-9a-fA-F]{1,4}){1,2}|([0-9a-fA-F]{1,4}:){1,4}(:[0-9a-fA-F]{1,4}){1,3}|([0-9a-fA-F]{1,4}:){1,3}(:[0-9a-fA-F]{1,4}){1,4}|([0-9a-fA-F]{1,4}:){1,2}(:[0-9a-fA-F]{1,4}){1,5}|[0-9a-fA-F]{1,4}:((:[0-9a-fA-F]{1,4}){1,6})|:((:[0-9a-fA-F]{1,4}){1,7}|:)|fe80:(:[0-9a-fA-F]{0,4}){0,4}%[0-9a-zA-Z]{1,}|::(ffff(:0{1,4}){0,1}:){0,1}((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])|([0-9a-fA-F]{1,4}:){1,4}:((25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9])\\.){3,3}(25[0-5]|(2[0-4]|1{0,1}[0-9]){0,1}[0-9]))", 0);
				 break;
	}

	status = regexec(&regex, address, 0, NULL, 0);
	if(status == 0)
		return 1;
	else if(status == REG_NOMATCH);
		return 0;
}

/**
 * Takes a string containing a binary sequence with 6 bits, converts it
 * to a string containing a 3 digit hexadecimal sequence.
 */
void bin_seq_to_hex(char* bin_seq, char* to){
	unsigned int binaryval;
	binaryval = strtol(bin_seq, NULL, 2);

	sprintf(to,"0x%03x",binaryval);
}