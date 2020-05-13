/*

Single Element in a Sorted Array
Solution
You are given a sorted array consisting of only integers where every element appears exactly twice, except for one element which appears exactly once. Find this single element that appears only once.

 

Example 1:

Input: [1,1,2,3,3,4,4,8,8]
Output: 2
Example 2:

Input: [3,3,7,7,10,11,11]
Output: 10
 

Note: Your solution should run in O(log n) time and O(1) space.

*/

// Solution 

/*

The key to this solution is that as we have repetative numbers so 

let is consider a array of size n and all the numbers have occured twice 

So now for every value of n where n is even we know a[n]==a[n+1]
 and similarly for odd valye of n a[n]==a[n-1]

now we know that we can search it by a method similar to binary search 

if vale of n is even 
            and a[n]==a[n+1] then the number is on right side
            else the number is on right 

if vale of n is odd 
            and a[n]==a[n+1] then the number is on left side
            else the number is on left 



Time Complexity O(log(n))
Space Complexity O(1)
*/


//Solution

class Solution {
public:
    int getValue(vector<int>& nums,int l,int h)
    {
        if(h<l)
            return(-1);
        int v=(l+h)/2;
        int flag=0;
        int mid=l+(h-l)/2;
        if((nums[v]==nums[v+1] && v%2==0)||(nums[v]==nums[v-1] && v%2==1))
        {
            return getValue(nums,mid+1,h); 
        }
        if((nums[v]==nums[v-1] && v%2==0)||(nums[v]==nums[v+1] && v%2==1))
            return getValue(nums,l,mid-1); 
        return(nums[v]);
        

    }
    int singleNonDuplicate(vector<int>& nums) 
    {
        if(nums.size()==1|| nums[0]!=nums[1])
            return nums[0];
        return getValue(nums,0,nums.size()-1);  
    }


};