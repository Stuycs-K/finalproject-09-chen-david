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
(if the result exceeds 512 bits, we store the information in multiple 512 bit arrays until there is enough space to store the input in binary and the length of the input) 

Now, we will append 0s until our array is 448 bits long(or 448 integers long if you are storing the bits in an integer array), where the remaining 64 bits will be the length of the input string in binary. 
 
Our array now looks like this:
```
01010100011001010111001101110100011010010110111001100111001000000100010101101110011000110110111101100100011001010111001010000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000001111000
```



**Creating The List of 80 Words**

After initializing the buffer of 512 bits, we will now use that buffer to create a list of 80 words.

First, we will split our 512 bit array in 16 32 bit words(or 4 characters). Now, starting at word 16(our words are indexed at 0), we will take each word at index i(i = 16 in this case), and perform a bitwise XOR operation on words:
`[i - 3]`
`[i - 8]`
`[i - 14]`
`[i - 16]`

After getting the result from the bitwise XOR operations, we will perform a circular shift function on the resulting binary.
A circular shift function shifts each bit by a number n to the left, and the n bits at the front that were replaced replaces the missing bits at the right. This is very similar to the bitwise left shift operation(<<).
For example, if we have the word:
`01010100 01100101 01110011 01110100`("test" in binary)
After performing the circular shift function, our word looks like this:
`10101000 11001010 11100110 11101000`

**Creation of Variables A, B, C, D, And E**
  
After getting 80 words by performing the XOR and circular shift operations, we will now use the resulting list of 80 words to modify 5 variables, where:
`A = h0`
`B = h1`
`C = h2`
`D = h3`
`E = h4`

We will use the results of modifying these 5 variables to modify the initial variables(h1, h2, h3, h4, h5) and eventually get our encoded output. I will elaborate more on this towards the end. 

There will be 4 functions that we will be using with the wordlist to modify these 5 variables. 

For each function, we will get a different value for the variables `f` and `k`, where we will then use the values of `f` and `k`, along with the current word itself(which will be passed into the function), to modify A, B, C, D, and E.

**Function 1**

We will pass in  words 0 to 19 to the first function to get our values for `f` and `k`.

We will set `f` equal to `(B & C) | (~B & D)`, where & is the bitwise AND operator, ~ is the bitwise NOT operator, and | is the bitwise OR operator. 

We will set `k` equal to `01011010100000100111100110011001` in binary. 


**Function 2**

We will pass in words 20 to 39 to the second function to get our values for `f` and `k`.

We will set `f` equal to `((B ^ C) ^ D)`, where ^ is the bitwise XOR operator. 

We will set `k` equal to `01101110110110011110101110100001` in binary.


**Function 3**

We will pass in words 40 to 59 to the third function to get our values for `f` and `k`.

We will set `f` equal to `(B & C) | (B & D) | (C & D)`. 

We will set `k` equal to `10001111000110111011110011011100` in binary.


**Function 4**

We will pass in words 60 to 79 to the fourth function to get our values for `f` and `k`.

We will set `f` to the same value as the one in the second function.

We will set `k` to `10001111000110111011110011011100` in binary. 



**Modifying Variables A, B, C, D, And E**

After getting the values for variables `f` and `k` for each word, we will create an integer called `temp`. 

We will store the result of

`(A circular shift 5) + f + E + k + current word`

in temp, where + is a bitwise addition(convert the binary to integer, add the result, and convert back into binary. 

Since our encoded output is 32 bits long, our resulting binary must be 32 bits long as well. This means that we will have to truncate the result(temp) at the end. 

Temp is an integer. We are using an integer because if we want to truncate the binary from the left of the result, we can just store the bits in an 32 bit unsigned integer because the integer will automatically truncate the extra bits to the left until the result is 32 bits long(at least in C).

After getting the value for temp, we will modify A, B, C, D, and E, where 

```
E = D
D = C
C = B circular shift 30
B = A
A = temp
```

**Final Steps And Converting The Results To Hexadecimal** 

After looping through the list of 80 words and eventually getting our results for variables A, B, C, D, and E, we will set our initial variables as:
```
h0 += A
h1 += B
h2 += C
h3 += D
h4 += E
```
where += represents a bitwise addition to the current value. 

Now that we have the results for h0, h1, h2, h3, and h4, we will convert them to hexadecimal, 

and join them together. 

The encoded string is: `da2e412299ae8ed1c1ee6057a5c7aa879e59b576`
