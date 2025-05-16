#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA.h"
int main(int argc, char* argv[]){
	
	char* string = malloc(10000);
	int string_index = 0;
	for(int i = 1; i < argc; i ++){
		for(int j = 0; j < strlen(argv[i]); j++){
			string[string_index] = argv[i][j];
			string_index += 1;

		}
		string[string_index] = ' ';
		string_index += 1;

	}
	printf("%s \n", string);
	encode(string);

}


char* encode(char* input){
	char* buffer = malloc(  ((strlen(input) * 8 / 512) + 1) * 512);
	char* H0 = "67452301";
	char* H1 = "EFCDAB89";
	char* H2 = "98BADCFE";
	char* H3 = "10325476";
	char* H4 = "C3D2E1F0";
	int power = 0;

	//initialization
	int increment_i = 8;
	for(int i = 0; i < strlen(buffer); i += increment_i){
		if(i < strlen(input) * 8){
			for(int j = 0; j < 8; j++){
				//insert each bit
				
				buffer[i + j] = 0;
				if(input[i]%(int)pow(2, 8 - j) == (int)pow(2, 8-j)){
					buffer[i + j] = 1;	
				}
			}
		}
		else if(i == strlen(input)){
			 buffer[i] = 1;
			 increment_i = 1;
		}
		else{
			increment_i = 1;
			if(i < strlen(buffer) - 64) buffer[i] = 0;
			else{
				buffer[i] = 0;
				if( (strlen(input)&(int)pow(2, 8 - power)) == (int)pow(2, 8 - power)){
					buffer[i] = 1;
				}
				power += 1;

			}

		}
		

		
	}


	//divide into 512 bit chunks
	int chunks = (strlen(input)/512) + 1;

	//each chunk has 32 bit words(now 80, used to be 16)
	char ** words = malloc(chunks * 80 * 32);
	for(int i = 0; i < chunks; i ++){
		//j is one of the 80 words
		for(int j = 0; j < 80; j ++){
			//k is one of the 32 bits for each word at j
			for(int k = 0; k < 32; k ++){
				words[i][(j * 32) + k] = buffer[(i * 512) + (j * 32) + k];
				if(j >= 16){
					int minus_three = words[i][ ((j - 3)*32) + k];
					int minus_eight = words[i][ ((j - 8)*32) + k];
					int minus_fourteen = words[i][ ((j - 14)*32) + k];
					int minus_sixteen = words[i][ ((j - 16)*32) + k];
					words[i][(j * 32) + k] = ((minus_three&minus_eight)&(minus_fourteen&minus_sixteen)) << 1;
				} 
				

			}

		}		

	}


}


