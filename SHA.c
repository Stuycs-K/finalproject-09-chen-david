#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SHA.h"
int main(int argc, char* argv[]){
	
	char* string = (char*) malloc(10000);
	int string_index = 0;
	for(int i = 1; i < argc; i ++){
		for(int j = 0; j < strlen(argv[i]); j++){
			string[string_index] = argv[i][j];
			string_index += 1;

		}
		string[string_index] = ' ';
		string_index += 1;
		printf("STRING INDEX: %d \n", string_index);

	}
	string[string_index] = 0;
	printf("STRING: %s \n", string);
	encode(string, 1);

}


char* encode(char* input, int exclude_newline){
	int* buffer = (int*)malloc(sizeof(int) * (((((strlen(input) - exclude_newline) * 8 / 512) + 1) * 512)+1));
	printf("SIZE: %ld \n",   ((((strlen(input) - exclude_newline) * 8 / 512) + 1) * 512)+1);
	char* H0 = "67452301";
	char* H1 = "EFCDAB89";
	char* H2 = "98BADCFE";
	char* H3 = "10325476";
	char* H4 = "C3D2E1F0";
	int power = 1;
	
	//initialization
	int increment_i = 8;
	for(int i = 0; i < (((strlen(input) - exclude_newline)*8/512) + 1) * 512; i += increment_i){
		if(i < (strlen(input) - exclude_newline) * 8){
			for(int j = 0; j < 8; j++){
				//insert each bit
				
				buffer[i + j] = 0;
				if(((unsigned int)input[i/8]&(unsigned int)pow(2, 7 - j)) == (unsigned int)pow(2, 7-j)){
					
					buffer[i + j] = 1;	
				}
				
				
		
			}

			
			if(i == (strlen(input) - exclude_newline) * 7) increment_i = 1;
		}
		else if(i == (strlen(input) - exclude_newline) * 8){
			 buffer[i] = 1;
			 increment_i = 1;
		}
		else{
			increment_i = 1;
			if(i < ((((strlen(input) - exclude_newline) * 8 / 512) + 1) * 512)  - 64) buffer[i] = 0;
			else{
				buffer[i] = 0;
				if(((unsigned long) (((strlen(input) - exclude_newline) * 8)&(unsigned long)pow(2, 64 - power))) == (unsigned long)pow(2, 64 - power)){
					buffer[i] = 1;
				}
				
				power += 1;

			}

		}
		

		
	}

	
 	int bits = 0;
	for(int i = 0; i < (((strlen(input) - exclude_newline)* 8 / 512) + 1) * 512; i ++){
		if(i >= ((((strlen(input) - exclude_newline) * 8 / 512) + 1) * 512)  - 64) printf("SIZE: ");
		printf("%d \n", buffer[i]);
		bits ++;
	}
	
	
	//divide into 512 bit chunks
	int chunks = (strlen(input)/512) + 1;
	printf("chunks: %d \n", chunks);
	printf("CHECKPOINT \n");
	//each chunk has 32 bit words(now 80, used to be 16)
	char*** words = (char***) malloc(chunks * 80 * 4 * sizeof(char));
	//each chunk has a list of 80 words





	printf("Checkpoint \n");
	for(int i = 0; i < chunks; i ++){


		//each word is 4 characters



		//j is one of the 80 words
		char** chunk = (char**)malloc(sizeof(char*) * 80); 
		words[i] = chunk;
		for(int j = 0; j < 80; j ++){
			//k is one of the 32 bits for each word at j
			char* next_word = malloc(4);
			chunk[j] = next_word;

			char* minus_three = malloc(4);
			char* minus_eight = malloc(4);
			char* minus_fourteen = malloc(4);
			char* minus_sixteen = malloc(4);
			//increment every 8 bits
			
			for(int k = 0; k < 32; k ++){
				if(j < 16){
			
					next_word[(int)(k/8)] += (int)pow(2, (8 - (k % 8)) * buffer[(i * 512) + (j * 32) + (k % 8)]); 
				

				}
				if(j >= 16){
					//left shift doesn't work with one int

					//set each of the four previous words
					minus_three[(int)(k/8)] += (int)pow(2, (8 - (k % 8)) * buffer[(i * 512) + ((j - 3) * 32) + (k % 8)]);
					minus_eight[(int)(k/8)] += (int)pow(2, (8 - (k % 8)) * buffer[(i * 512) + ((j - 8) * 32) + (k % 8)]);
					minus_fourteen[(int)(k/8)] += (int)pow(2, (8 - (k % 8)) * buffer[(i * 512) + ((j - 14) * 32) + (k % 8)]);
					minus_sixteen[(int)(k/8)] += (int)pow(2, (8 - (k % 8)) * buffer[(i * 512) + ((j - 16) * 32) + (k % 8)]);
				} 
				

			}


			if(j >= 16){
				//later loop and xor the previous words
				char* val = malloc(32);
				for(int w = 0; w < 32; w ++){
					val[w] = (((minus_three[w]^minus_eight[w])^minus_fourteen[w])^minus_sixteen[w]) << 1;

				}
				
                                next_word =  val;
                                

			}
		}		

	}
	



	printf("STARTING LOOP \n");
	//check if everything is running correctly
	for(int i = 0; i < 80; i += 1){
		for(int j = 0; j < 4; j ++){

			printf("%d \n", words[0][i][j]);
		}
	}


}


