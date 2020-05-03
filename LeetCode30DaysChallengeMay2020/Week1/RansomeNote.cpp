

/*
Given an arbitrary ransom note string and another string containing letters from all the magazines, write a function that will return true if the ransom note can be constructed from the magazines ; otherwise, it will return false.

Each letter in the magazine string can only be used once in your ransom note.

Note:
You may assume that both strings contain only lowercase letters.

canConstruct("a", "b") -> false
canConstruct("aa", "ab") -> false
canConstruct("aa", "aab") -> true

*/

// solution 

/*

Here we are given 2 strings and we are asked that can we generate first string from the second string

Here we can use the logic and code of out previous problem "JewelsAndStones" 

this can be solved in O(n) time where n is length of the string 

The logic used here is that we count occurence of each character in first string (ransome) and store it in an array 
here array arr

then count the occurence of ecah character in string 2 (magazine) and store it in another array arr2

now iterate through each values of both arrays if there are 

3 a's in ransome and 2 a's in magazien then obviously you cannot generate the ransome message 

i.e for each character a b c d ... count of occurence in array 1 has to be strictly less than or equal to
their occurence in magazine

and if you iterate through all the values without returning false then return true


Time Complexity O(n)  where n is length of max of length of ransome and magazine strings 
Sapce Complexity O(1)  as its idependent of length of string

*/


// Solution Code 


class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        string J=ransomNote;
        string S=magazine;
        
        int arr[52];                    // setup array 1 to keep track of characters of ransom
        int arr2[52];                   // setup array 2 to keep track of characters of magazine
        for(int i=0;i<52;i++)
        {
           arr[i]=0;
           arr2[i]=0;
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
        
        
        
        for(int i=0;i<S.length();i++)
        {
            int v=(int) S[i];
            if(v>90)
            {
                int k=v-a2;
                arr2[k]+=1;
            }
            else
            {
                 int k=v-a1;
                arr2[k+26]+=1;
            }
        }
        
        for(int i=0;i<52;i++)
        {
            if(arr2[i]<arr[i])
                return false;
        }
        
        
        return true;
    }
};