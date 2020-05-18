//Question

/*

Permutation in String
Solution
Given two strings s1 and s2, write a function to return true if s2 contains the permutation of s1. In other words, one of the first string's permutations is the substring of the second string.

 

Example 1:

Input: s1 = "ab" s2 = "eidbaooo"
Output: True
Explanation: s2 contains one permutation of s1 ("ba").
Example 2:

Input:s1= "ab" s2 = "eidboaoo"
Output: False
 

Note:

The input strings only contain lower case letters.
The length of both given strings is in range [1, 10,000].
   Hide Hint #1  
Obviously, brute force will result in TLE. Think of something else.
   Hide Hint #2  
How will you check whether one string is a permutation of another string?
   Hide Hint #3  
One way is to sort the string and then compare. But, Is there a better way?
   Hide Hint #4  
If one string is a permutation of another string then they must one common metric. What is that?
   Hide Hint #5  
Both strings must have same character frequencies, if one is permutation of another. Which data structure should be used to store frequencies?
   Hide Hint #6  
What about hash table? An array of size 26?

*/

//Solution 

/*

    Time Complexity O(n)
    Space Complexity O(1)

*/

//Solution Code

class Solution {
public:
    bool comp(int patArray[26],int stringArray[26])
    {
        for(int i=0;i<26;i++)
            if(patArray[i]!=stringArray[i])
                return false;
        return true;
    }
    bool checkInclusion(string s1, string s2) {
        int patArr[26]={0};
        int stringArr[26]={0};
        
        int l1=s1.length();
        int l2=s2.length();
        if(l1>l2)
            return false;
        
        for(int i=0;i<l1;i++)
        {
            patArr[s1[i]-'a']++;
            stringArr[s2[i]-'a']++;
        }
        for(int i=l1;i<l2;i++)
        {
            if(comp(patArr,stringArr))
                return true;
            stringArr[s2[i]-'a']++;
            stringArr[s2[i-l1]-'a']--;
            
        }
    
        
        if(comp(patArr,stringArr))
            return true;
        
        return false;
    }
};
