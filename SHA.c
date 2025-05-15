#include <math.h>




int main(){



}


char* encode(char* input){
	char* buffer = malloc(  ((len(input) / 64) + 1) * 64);
	char* H0 = "67452301";
	char* H1 = "EFCDAB89";
	char* H2 = "98BADCFE";
	char* H3 = "10325476";
	char* H4 = "C3D2E1F0";
	int power = 0;

	//initialization

	for(int i = 0; i < len(buffer); i ++){
		if(i < len(input)) buffer[i] = input[i];
		else if(i == len(input)) buffer[i] = 1;
		else{
			if(i < len(buffer) - 64) buffer[i] = 0;
			else{
				buffer[i] = 0;
				if( (len(input)&pow(2, power)) == pow(2, power)){
					buffer[i] = 1;	
				}
				power += 1;

			}

		}
		


	}


	//divide into 512 bit chunks
	
	char ** chunks = malloc( len(buffer));
	int chunk_index = 0;
	
	for(int i = 0; i < len(buffer); i ++){
		if(i % 64 == 0 && i != 0) chunk_index += 1;
		chunks[chunk_index][i % 64] = buffer[i];

	}
	
	//divide into 32 bit chunks
	char *** words = malloc(30000);
	chunk_index = 0;
	int word_index = 0;
	for(int i = 0; i < len(buffer); i ++){
		if(i % 8 == 0) word_index += 1;
		if(word_index % 16 == 0 && word_index != 0) chunk_index += 1;
		words[chunk_index][word_index][i % 8] = buffer[i];

	}

		
	for(int i = 0; i < chunk_index; i ++){
		for(int j = 16; j < 80; j ++){
			words[i][j] = words[i][j - 16] ^ words[i][j - 14] ^ words[i][j - 8] ^ words[i][j - 3] << 1;
			
		}

	}


	


}
