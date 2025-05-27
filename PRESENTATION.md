**How The SHA1 Encoder Works**

**Initialization**

First, we have to set up 5 variables named `h0`, `h1`, `h2`, `h3`, `h4`, where 
`h0 = 01100111010001010010001100000001`
`h1 = 11101111110011011010101110001001`
`h2 = 10011000101110101101110011111110`
`h3 = 00010000001100100101010001110110`
`h4 = 11000011110100101110000111110000`
in binary. 

For our example, we will be encoding the string "Testing Encoder". 

After initializing the 5 variables above, we will begin encoding by managing everything in bytes. 

We will have a 512 bit array containing the necessary information to create a list of 80 words, which will then be used to modify our initial 5 variables. The creation of a list of 80 words to modify our variables(and eventually get to our message digest, or encoded output) contributes to the avalanche effect of the encoder, where even a change in one bit leads to a completely different message digest, a key characteristic of a block cipher. 

In the 512 bit array, we will combine the 5 variables(in binary), and then append a 1 to the array. 
Our array now looks like this:
`
