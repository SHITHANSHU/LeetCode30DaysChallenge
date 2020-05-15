

//Question 

/*

 Maximum Sum Circular Subarray
Solution
Given a circular array C of integers represented by A, find the maximum possible sum of a non-empty subarray of C.

Here, a circular array means the end of the array connects to the beginning of the array.  (Formally, C[i] = A[i] when 0 <= i < A.length, and C[i+A.length] = C[i] when i >= 0.)

Also, a subarray may only include each element of the fixed buffer A at most once.  (Formally, for a subarray C[i], C[i+1], ..., C[j], there does not exist i <= k1, k2 <= j with k1 % A.length = k2 % A.length.)

 

Example 1:

Input: [1,-2,3,-2]
Output: 3
Explanation: Subarray [3] has maximum sum 3
Example 2:

Input: [5,-3,5]
Output: 10
Explanation: Subarray [5,5] has maximum sum 5 + 5 = 10
Example 3:

Input: [3,-1,2,-1]
Output: 4
Explanation: Subarray [2,-1,3] has maximum sum 2 + (-1) + 3 = 4
Example 4:

Input: [3,-2,2,-3]
Output: 3
Explanation: Subarray [3] and [3,-2,2] both have maximum sum 3
Example 5:

Input: [-2,-3,-1]
Output: -1
Explanation: Subarray [-1] has maximum sum -1
 

Note:

-30000 <= A[i] <= 30000
1 <= A.length <= 30000
   Hide Hint #1  
For those of you who are familiar with the Kadane's algorithm, think in terms of that. For the newbies, 
Kadane's algorithm is used to finding the maximum sum subarray from a given array. This problem is a twist 
on that idea and it is advisable to read up on that algorithm first before starting this problem. Unless 
you already have a great algorithm brewing up in your mind in which case, go right ahead!



*/

//Solution


/*

Time Complexity O(n)
Space Complexity O(1)

*/

//Solution 1

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& A) {
        
        int f=0;
        int min=A[0];
        for(int i=0;i<A.size();i++)
        {
            if(A[i]>0)
                f=1;
            if(min<A[i])
                min=A[i];
        }
        if(f==0)
            return min;
        
        int max=0;
        int cmax=0;
        for(int i=0;i<A.size();i++)
        {
            cmax+=A[i];
            if(cmax<0)
                cmax=0;
            if(max<cmax)
                max=cmax;
        }
        
        int sum=0;
        for(int i=0;i<A.size();i++)
        {
            sum+=A[i];
            A[i]=-A[i];
        }
        
        int nmax=0;
        int ncmax=0;
        for(int i=0;i<A.size();i++)
        {
            ncmax+=A[i];
            if(ncmax<0)
                ncmax=0;
            if(nmax<ncmax)
                nmax=ncmax;
        }
        
        int total=sum+nmax;
        
        if(total>max)
            return total;
        return max;
    }
};

//Solution 2

class Solution {
public:
    int maxSubarraySumCircular(vector<int>& v) {
        int max_so_far = v[0];
        int max_end_here = v[0];
        int totalsum = v[0];
        int min_so_far = v[0];
        int min_end_here = v[0];
        for(int i=1;i<v.size();i++){
            totalsum +=v[i];
            max_end_here = max(max_end_here + v[i],v[i]);
            max_so_far = max(max_end_here,max_so_far);
            min_end_here = min(min_end_here + v[i],v[i]);
            min_so_far = min(min_so_far,min_end_here);
        }
        if(max_so_far < 0){//means all element are negative
            return max_so_far;
        }
        return max(max_so_far,(totalsum - min_so_far));
    }
};