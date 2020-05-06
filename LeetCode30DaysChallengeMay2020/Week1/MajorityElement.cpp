
/*

Majority Element
Solution
Given an array of size n, find the majority element. The majority element is the element that appears more than ⌊ n/2 ⌋ times.

You may assume that the array is non-empty and the majority element always exist in the array.

Example 1:

Input: [3,2,3]
Output: 3
Example 2:

Input: [2,2,1,1,1,2,2]
Output: 2


*/


// Solution
/*


Time complexity O(n)
Space Complexity O(1)
*/


// Solution Code

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int co=0;
        int currentValue;
        for(int i=0;i<nums.size();i++)
        {
            if(i==0 || co==0)
            {
                currentValue= nums[i];
            }
            
            if(currentValue==nums[i])
                co++;
            else
                co--;
            
        }
        return currentValue;
    }
};