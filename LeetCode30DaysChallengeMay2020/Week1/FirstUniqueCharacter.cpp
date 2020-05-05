

/*


First Unique Character in a String
Solution
Given a string, find the first non-repeating character in it and return it's index. If it doesn't exist, return -1.

Examples:

s = "leetcode"
return 0.

s = "loveleetcode",
return 2.
Note: You may assume the string contain only lowercase letters.




*/

// Solution explaination


/*


First we will create a array of size 26 such at a is at index 0 b at 1 and so on 

then we will count occurence of each letter

then we will once again iterate through all the characters of the string and then chcek for the first character 

in the given tring with occurence count as 1

Time comlexity O(n)
Space Complexity O(1)

*/


// Solution Code


class Solution {
public:
    int firstUniqChar(string s) {
        int list[26];
        for(int i=0;i<26;i++)
            list[i]=0;
        int x=(int) 'a';
        for(int i=0;i<s.length();i++)
        {
            int v=(int)s[i];
            list[v-x]+=1;
        }
        
        for(int i=0;i<s.length();i++)
        {
            
            int v=(int)s[i];
            int r=list[v-x];
            if(r==1)
                return (i);
        }
        return -1;
    }
};