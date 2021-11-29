#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/compf.h"
#include "../include/loadbar.h"

void respond_to_ip_flag();
void respond_to_bin_seq_flag();
void respond_to_maleable_flag();
void respond_to_r4_flag();
void respond_to_sp_flag();

/**
 * strafan, short for "Shodan's Traffic Analyzer", is a program written as an auxiliator for a mini-project for the
 * Computer Networking Curricular Unit of the school year of 2021/2022, Bachelor's in Computer Engineering at the
 * Faculty of Sciences of the University of Lisbon (Faculdade de Ciências da Universidade de Lisboa).
 */
void main(int argc, char* argv[]){
	if(argc < 2){
		printf("Error: not enough args!\nUsage: strafan <filename> [OPTIONS]");
		return;
	}

	if(check_file(argv[1])){
		printf("Error: file does not exist or is directory");
		return;
	}

	// Confirmed good behavior, as there are enough arguments and
	// the file specified in argv[1] exists.

	// Checking program flags
	int ip_version = 0;
	char* flag_seq;
	char* m_option;
	int r4_flag = 0;
	int sp_flag = 0;
	int gnuplot_flag = 0;
	int comp_gp_flag = 0;
	int head_number = 0;
	if(argc > 2){
		int i = 2;
		while(i < argc){
			if(!strcmp(argv[i], "-a")){
				if(ip_version){
					printf("Error: duplicate flag\nUsage: strafan <filename> -a <version>\n");
					return;
				}
				if(i++ >= argc){
					printf("Error: IP version not specified!\nUsage: strafan <filename> -a <version>\n");
					return;
				} else {
					ip_version = atoi(argv[i]);
					if((ip_version != 4) && (ip_version != 6)){
						printf("Error: IP Version not valid (must be 4 or 6)\n");
						return;
					}
				}
			}
		}
	}
}

