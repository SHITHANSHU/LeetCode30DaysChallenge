//Question

/*

Remove K Digits
Solution
Given a non-negative integer num represented as a string, remove k digits from the number so that the new number is the smallest possible.

Note:
The length of num is less than 10002 and will be ≥ k.
The given num does not contain any leading zero.
Example 1:

Input: num = "1432219", k = 3
Output: "1219"
Explanation: Remove the three digits 4, 3, and 2 to form the new number 1219 which is the smallest.
Example 2:

Input: num = "10200", k = 1
Output: "200"
Explanation: Remove the leading 1 and the number is 200. Note that the output must not contain leading zeroes.
Example 3:

Input: num = "10", k = 2
Output: "0"
Explanation: Remove all the digits from the number and it is left with nothing which is 0.

*/

//Solution

/*
Time complexity O(n)
Space Complexity O(n)
*/

//Solution

class Solution {
public:
    void insertInNonDecOrder(deque<char> &dq, char ch) 
{ 
    if (dq.empty()) 
        dq.push_back(ch); 
  
    else
    { 
        char temp = dq.back(); 
  
        while( temp > ch && !dq.empty()) 
        { 
            dq.pop_back(); 
            if (!dq.empty()) 
                temp = dq.back(); 
        } 
        dq.push_back(ch); 
    } 
    return; 
} 
    
string removeKdigits(string num, int n) {
       int len = num.length(); 
  
    int k = len - n; 
  
    deque<char> dq; 
    string res = ""; 
    int i; 
    for (i=0; i<=len-k; i++) 
        insertInNonDecOrder(dq, num[i]); 
    while (i < len) 
    { 
        res += dq.front(); 
        dq.pop_front(); 
        insertInNonDecOrder(dq, num[i]); 
        i++; 
    } 
    res += dq.front(); 
    dq.pop_front();
    int f=0;
    string res2="";
    for(int i=0;i<res.length();i++)
    {
        if(f==0 && res[i]=='0')
            continue;
        f=1;
        res2+=res[i];
    }
    int re=res2[0];
    if(re==0)
        res2="0";
    return res2;
    }
};