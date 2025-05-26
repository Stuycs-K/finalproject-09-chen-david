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
	
	unsigned char* H0 = calloc(4, sizeof(unsigned char*));
	unsigned char* H1 = calloc(4, sizeof(unsigned char*));
	unsigned char* H2 = calloc(4, sizeof(unsigned char*));
	unsigned char* H3 = calloc(4, sizeof(unsigned char*));
	unsigned char* H4 = calloc(4, sizeof(unsigned char*));

	H0[0] = 103;
	H0[1] = 69;
	H0[2] = 35;
	H0[3] = 1;

	H1[0] = 239;
	H1[1] = 205;
	H1[2] = 171;
	H1[3] = 137;

	H2[0] = 152;
	H2[1] = 186;
	H2[2] = 220;
	H2[3] = 254;

	H3[0] = 16;
	H3[1] = 50;
	H3[2] = 84;
	H3[3] = 118;

	H4[0] = 195;
	H4[1] = 210;
	H4[2] = 225;
	H4[3] = 240;

		


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
	
	//each chunk has 32 bit words(now 80, used to be 16)
	unsigned char*** words = (unsigned char***) malloc(chunks * sizeof(unsigned char**));
	//each chunk has a list of 80 words

	int printed = 1;


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




				


				//later loop and xor the previous words
			
				memcpy(minus_three, words[i][j - 3], 4);
				memcpy(minus_eight, words[i][j - 8], 4);
				memcpy(minus_fourteen, words[i][j - 14], 4);
				memcpy(minus_sixteen, words[i][j - 16], 4);

				


				for(int w = 0; w < 4; w ++){
					//error is with the left shift 
					//left shifting every character, should be left shifting the entire string once
					next_word[w] = (((minus_three[w]^minus_eight[w])^minus_fourteen[w])^minus_sixteen[w]);
				

				}
				
                                memcpy(next_word, left_shift_string(next_word), 4);
				
                                

			}
		}		

	}
	



	printf("STARTING LOOP FOR 80 WORDS \n");
	//check if everything is running correctly
	for(int i = 0; i < 80; i += 1){
		for(int j = 0; j < 4; j ++){

			printf("word %d: %d \n", i, words[0][i][j]);
		}
	}



	//init A B C D E
	unsigned char* A = calloc(4, sizeof(unsigned char*));
	unsigned char* B = calloc(4, sizeof(unsigned char*));
	unsigned char* C = calloc(4, sizeof(unsigned char*));
	unsigned char* D = calloc(4, sizeof(unsigned char*));
	unsigned char* E = calloc(4, sizeof(unsigned char*));

	memcpy(A, H0, 4);
	memcpy(B, H1, 4);
	memcpy(C, H2, 4);
	memcpy(D, H3, 4);
	memcpy(E, H4, 4);






	printf("STARTING LOOP FOR NEW VALUES \n");
	for(int i = 0; i < chunks; i ++){

		
				

		for(int j = 0; j < 80; j++){
			//function 1: 0-19
			//function 2: 20-39
			//function 3: 40-59
			//function 4: 60-79
			unsigned char* f = calloc(4, sizeof(unsigned char*));
			unsigned char* k = calloc(4, sizeof(unsigned char*));

		
			//each function will set 'f' and 'k' to a different value

			if(j >= 0 && j < 20){
				//function 1
				
				for(int k = 0; k < 4; k++){
					unsigned char temp1 = B[k]&C[k];
					unsigned char temp2 = (~B[k])&D[k];
					f[k] = temp1|temp2;
				}
				k[0] = 90;
				k[1] = 130;
				k[2] = 121;
				k[3] = 153;
				

			}
			else if(j >= 20 && j < 40){
				//function 2
				for(int k = 0; k < 4; k ++){
					unsigned char temp1 = B[k]^C[k];
					f[k] = temp1^D[k];
				}
				k[0] = 110;
				k[1] = 217;
				k[2] = 235;
				k[3] = 161;

			}
			else if(j >= 40 && j < 60){
				//function 3
				for(int k = 0; k < 4; k ++){

					unsigned char temp1 = B[k]&C[k];
					unsigned char temp2 = B[k]&D[k];
					unsigned char temp3 = C[k]&D[k];
					f[k] = (temp1|temp2)|temp3;
				}
				k[0] = 143;
				k[1] = 27;
				k[2] = 188;
				k[3] = 220;
			}
			else{
				//function 4
				for(int k = 0; k < 4; k ++){
					unsigned char temp1 = B[k]^C[k];
					f[k] = temp1^D[k];
				}

				k[0] = 202;
				k[1] = 98;
				k[2] = 193;
				k[3] = 214;
			}
			

			//longer_temp will be truncated to temp
			unsigned int temp_int = 0;
			unsigned char* A_5 = calloc(4, sizeof(unsigned char*));
			memcpy(A_5, left_shift_string(A), 4);
			memcpy(A_5, left_shift_string(A_5), 4);
			memcpy(A_5, left_shift_string(A_5), 4);
			memcpy(A_5, left_shift_string(A_5), 4);
			memcpy(A_5, left_shift_string(A_5), 4);




			//A_5 + f + E + k + current word
			for(int ww = 0; ww < 32; ww ++){
				if((A_5[(int)(ww/8)]&(int)pow(2, 7 - (ww%8))) == (int)pow(2, 7 - (ww%8))) temp_int += (int)pow(2, 31 - ww);
				if((f[(int)(ww/8)]&(int)pow(2, 7 - (ww%8))) == (int)pow(2, 7 - (ww%8))) temp_int += (int)pow(2, 31 - ww);
				if((E[(int)(ww/8)]&(int)pow(2, 7 - (ww%8))) == (int)pow(2, 7 - (ww%8))) temp_int += (int)pow(2, 31 - ww);
				if((k[(int)(ww/8)]&(int)pow(2, 7 - (ww%8))) == (int)pow(2, 7 - (ww%8))) temp_int += (int)pow(2, 31 - ww);
				if((words[i][j][(int)(ww/8)]&(int)pow(2, 7 - (ww%8))) == (int)pow(2, 7 - (ww%8))) temp_int += (int)pow(2, 31 - ww);

				
			}
			for(int ww = 0; ww < 4; ww ++){
				printf("A_5: %u \n", A_5[ww]);
				printf("f: %u \n", f[ww]);
				printf("E: %u \n", E[ww]);
				printf("k: %u \n", k[ww]);
				printf("word: %u \n", words[i][j][(int)(ww)]);
			}



			//reset var
			memcpy(E, D, 4);
			memcpy(D, C, 4);
			memcpy(C, B, 4);
			for(int k = 0; k < 30; k ++){
				memcpy(C, left_shift_string(C), 4);
			}
			memcpy(B, A, 4);
			A = calloc(4, sizeof(unsigned char*));
			for(int k = 0; k < 32; k ++){
				if((temp_int&(int)pow(2, 31 - k)) == (int)pow(2, 31 - k)) A[(int)(k/8)] += (int)pow(2, 7 - (k%8));

			}
			printf("WORD: %d            TEMP: %u \n", j, temp_int);
			printf("WORD: %d            A: %d \n", j, A[0]);
			printf("WORD: %d            A: %d \n", j, A[1]);
			printf("WORD: %d            A: %d \n", j, A[2]);
			printf("WORD: %d            A: %d \n", j, A[3]);
		
			printf("WORD: %d            B: %d \n", j, B[0]);
			printf("WORD: %d            B: %d \n", j, B[1]);
			printf("WORD: %d            B: %d \n", j, B[2]);
			printf("WORD: %d            B: %d \n", j, B[3]);

			printf("WORD: %d            C: %d \n", j, C[0]);
			printf("WORD: %d            C: %d \n", j, C[1]);
			printf("WORD: %d            C: %d \n", j, C[2]);
			printf("WORD: %d            C: %d \n", j, C[3]);

			printf("WORD: %d            D: %d \n", j, D[0]);
			printf("WORD: %d            D: %d \n", j, D[1]);
			printf("WORD: %d            D: %d \n", j, D[2]);
			printf("WORD: %d            D: %d \n", j, D[3]);

			printf("WORD: %d            E: %d \n", j, E[0]);
			printf("WORD: %d            E: %d \n", j, E[1]);
			printf("WORD: %d            E: %d \n", j, E[2]);
			printf("WORD: %d            E: %d \n", j, E[3]);

			printf("__________________________________________________________________\n");
			
			

		}

	}



	unsigned int H0_int = 0;
	unsigned int H1_int = 0;
	unsigned int H2_int = 0;
	unsigned int H3_int = 0;
	unsigned int H4_int = 0;

	//set initial values 
	for(int i = 0; i < 32; i++){
		if((A[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H0_int += (int)pow(2, 31 - i);
		if((H0[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H0_int += (int)pow(2, 31 - i);

		if((B[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H1_int += (int)pow(2, 31 - i);
		if((H1[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H1_int += (int)pow(2, 31 - i);

		if((C[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H2_int += (int)pow(2, 31 - i);
		if((H2[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H2_int += (int)pow(2, 31 - i);

		if((D[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H3_int += (int)pow(2, 31 - i);
		if((H3[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H3_int += (int)pow(2, 31 - i);

		if((E[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H4_int += (int)pow(2, 31 - i);
		if((H4[(int)(i/8)]&(int)pow(2, 7 - (i%8))) == (int)pow(2, 7 - (i%8))) H4_int += (int)pow(2, 31 - i);
	}
	




	printf("A: %u \n", H0_int);






}





unsigned char* left_shift_string(unsigned char* str){
	unsigned char* new_str = calloc(4, sizeof(unsigned char));
	
	//convert to bits
	int* str_bits = calloc(32, sizeof(int));
	
	for(int i = 0; i < 4; i++){
		for(int j = 0; j < 8; j++){
		
			if((str[i]&(int)pow(2, 7 - j)) == (int)pow(2, 7 - j)) str_bits[(i * 8) + j] = 1;
			else str_bits[(i * 8) + j] = 0;
			
			
		}
	
	}
	
	

	int first_bit = str_bits[0];
	for(int i = 1; i < 32; i ++){

		if(str_bits[i] == 1) new_str[(int)((i - 1)/8)] += (int)pow(2, 7 - ((i - 1) % 8));
 
	}
	if(first_bit == 1)new_str[3] += 1;
	//printf("PRINTING: \n");
	//for(int i = 0; i < 4; i ++){
		//printf("CHAR_VAL: %d \n", new_str[i]);
	//}

	//printf("FINISHED ROTATION! \n");
	return new_str;	 

}





























