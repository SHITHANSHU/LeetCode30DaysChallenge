//Question 

/*

Find All Anagrams in a String
Solution
Given a string s and a non-empty string p, find all the start indices of p's anagrams in s.

Strings consists of lowercase English letters only and the length of both strings s and p will not be larger than 20,100.

The order of output does not matter.

Example 1:

Input:
s: "cbaebabacd" p: "abc"

Output:
[0, 6]

Explanation:
The substring with start index = 0 is "cba", which is an anagram of "abc".
The substring with start index = 6 is "bac", which is an anagram of "abc".
Example 2:

Input:
s: "abab" p: "ab"

Output:
[0, 1, 2]

Explanation:
The substring with start index = 0 is "ab", which is an anagram of "ab".
The substring with start index = 1 is "ba", which is an anagram of "ab".
The substring with start index = 2 is "ab", which is an anagram of "ab".

*/

//Solution 

/*

Time Complexity O(n)
Space Complexity O(1)

*/

//Solution Code

class Solution {

public:
    bool compare(char a[],char b[])
    {
        for(int i=0;i<256;i++)
            if(a[i]!=b[i])
                return false;
        return true;
    }
    vector<int> findAnagrams(string s, string p) 
    {
        int a = p.length(), b = s.length(); 
        vector<int> ans;
        if(a>b)
            return ans;
        char patternArray[256] = {0}, stringArray[256] = {0}; 
        for (int i = 0; i < a; i++) 
        { 
            (patternArray[p[i]])++; 
            (stringArray[s[i]])++; 
        } 
  
        for (int i = a; i < b; i++) 
        { 
            if (compare(patternArray, stringArray)) 
                ans.push_back(i-a);
  
            (stringArray[s[i]])++; 
  
            stringArray[s[i-a]]--; 
        } 
  
    if (compare(patternArray, stringArray))  
            ans.push_back(b-a);
        return ans;
    }
};