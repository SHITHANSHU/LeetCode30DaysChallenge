/*

Number Complement
Solution
Given a positive integer, output its complement number. The complement strategy is to flip the bits of its binary representation.

 

Example 1:

Input: 5
Output: 2
Explanation: The binary representation of 5 is 101 (no leading zero bits), and its complement is 010. So you need to output 2.
 

Example 2:

Input: 1
Output: 0
Explanation: The binary representation of 1 is 1 (no leading zero bits), and its complement is 0. So you need to output 0.
 

Note:

The given integer is guaranteed to fit within the range of a 32-bit signed integer.
You could assume no leading zero bit in the integer’s binary representation.
This question is the same as 1009: https://leetcode.com/problems/complement-of-base-10-integer/



*/

// Solution explaination

/*

This is a easy one as compared to others 

All you need to know is some basic knowledge of binary numbers and their compliment

in binary complement means simply change 0s to 1s and 1s to 0s

lets say input is 5

5 -> binary -> 1 0 1 -> compliment -> 0 1 0 -> decimal -> 2

easy to understand approach

there are 2 ways first convert number to binary and then change 0s to 1s and 1s to 0s (inefficient)

a bit complicated but a better one 

find the number higher than the given number in given format 

first value of x such that 2^(x)>num

then reduce 1 from that number and then apply XOR of that number with the given input 

lets say if the number was 5

find x ->
        x=floor(log2(5))+1      -> x=3
        newnumber= pow(2,x)-1   -> newnumber = 7

        then 5^7 = 2

        explaination 

        for any number n we will find the number with same bit count and all the bits as 1

        so if the number is 5 its binary value will be 101

        now the number we want is a number with same bit count 3 i.e. 111 the number is 7

        now we know that xor with 1 will return the compliment of that bit 

        i.e. 1^0=1  1   1^1=0

        so xor with 1 will return the compliment value 

        Time Comlexity O(log(n)) 

        Space Complexity O(1) 

*/



// Solution Code


class Solution {
public:
    int findComplement(int num) {
        if(num==0)
            return 1;
         int nitcount= floor(log2(num))+1; 
 
   return (int)(pow(2,bitcount) - 1) ^ num; 
    }
};