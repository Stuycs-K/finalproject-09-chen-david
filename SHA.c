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
	int* buffer = (int*)calloc((((((strlen(input) - exclude_newline) * 8 / 512) + 1) * 512)), sizeof(int));
	
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
		
		printf("WORD: %d    I: %d    VALUE: %d \n", (int)(i/32), i, buffer[i]);
		bits ++;
	}
	
	
	//divide into 512 bit chunks
	int chunks = (strlen(input)/512) + 1;
	printf("chunks: %d \n", chunks);
	printf("CHECKPOINT \n");
	//each chunk has 32 bit words(now 80, used to be 16)
	unsigned char*** words = (unsigned char***) malloc(chunks * sizeof(unsigned char**));
	//each chunk has a list of 80 words

	int printed = 1;



	printf("Checkpoint \n");
	for(int i = 0; i < chunks; i ++){


		//each word is 4 characters



		//j is one of the 80 words
		unsigned char** chunk = (unsigned char**)malloc(sizeof(unsigned char*) * 80); 
		words[i] = chunk;
		for(int j = 0; j < 80; j ++){
			//k is one of the 32 bits for each word at j
			unsigned char* next_word = calloc(4, sizeof(unsigned char));
			chunk[j] = next_word;

			unsigned char* minus_three = calloc(4, sizeof(unsigned char));
			unsigned char* minus_eight = calloc(4, sizeof(unsigned char));
			unsigned char* minus_fourteen = calloc(4, sizeof(unsigned char));
			unsigned char* minus_sixteen = calloc(4, sizeof(unsigned char));
			
			
			if(j < 16){
				for(int k = 0; k < 32; k ++){
					if(buffer[(i * 512) + (j * 32) + k] != 0) next_word[(int)(k/8)] += (int)pow(2, (7 - (k%8))); 
					if(buffer[(i * 512) + (j * 32) + k] != 0) printf("WORD_INDEX: %d   CHAR_INDEX: %d      VAL: %d \n", j, (int)(k/8), next_word[(int)(k/8)]);
					
				
				

				}
			}	
			
			//SHOULD NOT BE USING BUFFER HERE, BUFFER ONLY EXTENDS TO 16 WORDS, USE THE WORDS ARRAY
			if(j >= 16){

				//print out words until 16




				if(printed == 1){
				for(int ww = 0; ww < 16; ww ++){
					for(int ii = 0; ii < 4; ii++)
					printf("WORD: %d     VALUE: %d \n", ww, words[0][ww][ii]);

				}
				printed = 0;
				}


				//later loop and xor the previous words
				printf("RIGHT VALUE: %d \n", words[0][15][3]);
				memcpy(minus_three, words[i][j - 3], 4);
				memcpy(minus_eight, words[i][j - 8], 4);
				memcpy(minus_fourteen, words[i][j - 14], 4);
				memcpy(minus_sixteen, words[i][j - 16], 4);

				if(j == 18){

					printf("EIGHTEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEN \n");
					printf("WORD VALUE: %d \n", words[0][15][3]);
					printf("I: %d \n", i);
					printf("J - 3: %d \n", j - 3);
					printf("STRNCPY VALUE: %d \n",  minus_three[3]);
				}


				for(int w = 0; w < 4; w ++){
					//error is with the left shift 
					//left shifting every character, should be left shifting the entire string once
					next_word[w] = (((minus_three[w]^minus_eight[w])^minus_fourteen[w])^minus_sixteen[w]);
					printf("INDEX: %d      CHARACTER %d    MINUS THREE: %d \n", j - 3, w, minus_three[w]);

				}
				
                                memcpy(next_word, left_shift_string(next_word), 4);
				printf("OK \n");
                                

			}
		}		

	}
	



	printf("STARTING LOOP \n");
	//check if everything is running correctly
	for(int i = 0; i < 80; i += 1){
		for(int j = 0; j < 4; j ++){

			printf("word %d: %d \n", i, words[0][i][j]);
		}
	}


}





unsigned char* left_shift_string(unsigned char* str){
	unsigned char* new_str = calloc(4, sizeof(unsigned char));
	
	//convert to bits
	int* str_bits = calloc(32, sizeof(int));
	printf("STARTING ROTATION! \n");
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 8; j++){
		
			if((str[i]&(int)pow(2, 7 - j)) == (int)pow(2, 7 - j)) str_bits[(i * 8) + j] = 1;
			else str_bits[(i * 8) + j] = 0;
			
			printf("bit val: %d \n", str_bits[(i * 8) + j]); 
		}
	
	}
	
	

	int first_bit = str_bits[0];
	for(int i = 1; i < 32; i ++){

		if(str_bits[i] == 1) new_str[(int)((i - 1)/8)] += (int)pow(2, 7 - ((i - 1) % 8));
 
	}
	if(first_bit == 1)new_str[3] += 2;
	printf("PRINTING: \n");
	for(int i = 0; i < 4; i ++){
		printf("CHAR_VAL: %d \n", new_str[i]);
	}

	printf("FINISHED ROTATION! \n");
	return new_str;	 

}




