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

Now, we will append 0s until our array is 448 bits long(or 448 integers long if you are storing the bits in an integer array), where the remaining 64 bits will be the length of the input string in binary. 
 
Our array now looks like this:
```
01010100011001010111001101110100011010010110111001100111001000000100010101101110011000110110111101100100011001010111001010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111000
```



**Creating the list of 80 words**

After initializing the buffer of 512 bits, we will now use that buffer to create a list of words.
