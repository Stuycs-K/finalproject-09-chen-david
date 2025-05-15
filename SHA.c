#include <math.h>




int main(){



}


char* encode(char* input){
	char* buffer = malloc(  ((len(input) * 8 / 512) + 1) * 512);
	char* H0 = "67452301";
	char* H1 = "EFCDAB89";
	char* H2 = "98BADCFE";
	char* H3 = "10325476";
	char* H4 = "C3D2E1F0";
	int power = 0;

	//initialization
	int increment_i = 8;
	for(int i = 0; i < len(buffer); i += increment_i){
		if(i < len(input) * 8){
			for(int j = 0; j < 8; j++){
				//insert each bit
				
				buffer[i + j] = 0;
				if((input[i]%math.pow(2, 8 - j) == math.pow(2, 8-j)){
					buffer[i + j] = 1;	
				}
			}
		}
		else if(i == len(input)){
			 buffer[i] = 1;
			 increment_i = 1;
		}
		else{
			increment_i = 1;
			if(i < len(buffer) - 64) buffer[i] = 0;
			else{
				buffer[i] = 0;
				if( (len(input)&math.pow(2, 8 - power)) == math.pow(2, 8 - power)){
					buffer[i] = 1;
				}
				power += 1;

			}

		}
		


	}


	//divide into 512 bit chunks
	int chunks = (len(input)/512) + 1;

	//each chunk has 32 bit words(now 80, used to be 16)
	char ** words = malloc(chunks * 80 * 32);
	for(int i = 0; i < chunks; i ++){
		//j is one of the 80 words
		for(int j = 0; j < 80; j ++){
			//k is one of the 32 bits for each word at j
			for(int k = 0; k < 32; k ++){
				words[i][(j * 32) + k] = buffer[(i * 512) + (j * 32) + k];
				if(j >= 16){
						

				} 
				

			}

		}		

	}


}


