/*
You're given strings J representing the types of stones that are jewels, and S representing the stones you have.  Each character in S is a type of stone you have.  You want to know how many of the stones you have are also jewels.

The letters in J are guaranteed distinct, and all characters in J and S are letters. Letters are case sensitive, so "a" is considered a different type of stone from "A".

Example 1:

Input: J = "aA", S = "aAAbbbb"
Output: 3
Example 2:

Input: J = "z", S = "ZZ"
Output: 0
Note:

S and J will consist of letters and have length at most 50.
The characters in J are distinct.

*/

//Solution

/*

there are may possible solution to this problem 
but we will go with the optimal one 

We will 2 strings and count total jewels in the first string 

*/

// Solition 1 

/*
one of the solution is to iterate through the characters of string 1 
for each character of string one if the characters are same then increase 
the count by one 
Time complexity = O(n^2) (n=length of string)
space complexity = O(1)
*/

// Solution 2 dynamic programming (dp)

/*
Instead of iterrating the characters of first string all the time we will store the count of occurence
of all 52 characters (52 because its case sensitive so A & a are different)
so we will make a array of 52 length and increment the value on each occurance

in string 2 we will iterate through the characters and find the occurence
in time complexity O(1) by its index value 

here we have se
character and index are as follows  
a=0 b=1 ...
z=25
A=26
Z=51


as we are making array of size 52 and its independent of the input so 
Time Complexity O(n)  (n=max length of string 1 and string 2)
Space Complexity O(1)
*/

// Solution 1 





class Solution {
public:
    int numJewelsInStones(string J, string S) {
        int co=0;                       // set counter
        for(int i=0;i<S.length();i++)
        {
            char a=S[i]
            for(int j=0;j<J.length();j++)
            {
                if(a==J[j])
                {
                    co++;               // incriment counter if character is found and break the inner loop
                    break;
                }
            }
        }
        return co;
    }
};


// Solution 2 Dynamic Programming dp

class Solution {
public:
    int numJewelsInStones(string J, string S) {
        
        int arr[52];                    // setup array
        for(int i=0;i<52;i++)
        {
           arr[i]=0; 
        }
        int a1=(int) 'A';
        int a2=(int) 'a';
        for(int i=0;i<J.length();i++)
        {
            int v=(int) J[i];
            if(v>90)
            {
                int k=v-a2;
                arr[k]+=1;
            }
            else
            {
                 int k=v-a1;
                arr[k+26]+=1;
            }
        }
        int co=0;
        for(int i=0;i<S.length();i++)
        {
            int k=0;
            int v=(int) S[i];
             if(v>90)
            {
                k=v-a2;
            }
            else
            {
                 k=v-a1+26;
            }
            if(arr[k]==0)               // checking occurence in time O(1)
                continue;
            else
                co++;
        }
        return co;
    }
};
