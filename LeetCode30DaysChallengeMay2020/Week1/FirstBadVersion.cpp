/*

First Bad Version
Solution
You are a product manager and currently leading a team to develop a new product. Unfortunately, the latest version of your product fails the quality check. Since each version is developed based on the previous version, all the versions after a bad version are also bad.

Suppose you have n versions [1, 2, ..., n] and you want to find out the first bad one, which causes all the following ones to be bad.

You are given an API bool isBadVersion(version) which will return whether version is bad. Implement a function to find the first bad version. You should minimize the number of calls to the API.

Example:

Given n = 5, and version = 4 is the first bad version.

call isBadVersion(3) -> false
call isBadVersion(5) -> true
call isBadVersion(4) -> true

Then 4 is the first bad version. 

*/


// Solution
/*

As they have already specified that we have to minimize the api calls 
it means we cannot use the linear approach as it wont be efficient enough
they have also told us that the versions are in form [1,2,3,....n]
so it means the api call will have values as
[false,false,false,false,... true,true]
that means we have to find the index of first true value 

we know that all values on right of true will be true
& 
all the values on left of flase will be false  

so that means we can use the minary search approach in which we will be searching till leaf node

if the value is true then we have to look into the left side of the array i.e. value has to be reduced

now we will be using a binary search approch but unlike binary search we will keep on drilling 
untill we reach a point in which we dont move 


Time Complexity     O(log(n))
Space Complexity    O(1)
*/



// The API isBadVersion is defined for you.
// bool isBadVersion(int version);

class Solution {
public:
    int firstBadVersion(int n) {
        // have to use ling long int as one of the test case failed because of larger value
        long long int v=n/2;
        long long int lbound=0;         //lbound is the left bounding
        long long int rbound=n-1;       //rbound is the right bounding
        long long int vp=-1;            // to store the previous value of v
        while(true)
        {
            if(!isBadVersion(v))
            {
                //if the rsponse is false it means the culprit is in second half
                lbound=v+1;
                v=(lbound+rbound)/2;
            }
            else
            {
                //if the response is true tit means the culprit is in first half
                rbound=v-1;
                v=(lbound+rbound)/2;
            }
            if(v==vp) // if v and vp are equal then stop
                break;
            vp=v;
        }
        // return v+1 as v is last false value of the array
        return v+1;
    }
};