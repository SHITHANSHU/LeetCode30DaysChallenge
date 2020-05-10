/*

Valid Perfect Square
Solution
Given a positive integer num, write a function which returns True if num is a perfect square else False.

Note: Do not use any built-in library function such as sqrt.

Example 1:

Input: 16
Output: true
Example 2:

Input: 14
Output: false

*/

// Solution 

/*

to check if the number is a perfect square without sqrt method 

we need to itterate throuhgh all the values to its root 

but since we cannot use square root method so 

we will itterate till i*i<=n

Time Complexity O(log(n))
Space Complexity O(1)
*/

class Solution {
public:
    bool isPerfectSquare(int num) {
        for(long long int i=1;i*i<=num;i++)
        {
            if(num%i==0 && num/i==i)
                return true;
        }
        return false;
    }
};