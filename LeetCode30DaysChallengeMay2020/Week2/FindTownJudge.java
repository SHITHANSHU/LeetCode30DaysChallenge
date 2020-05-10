/*

ind the Town Judge
Solution
In a town, there are N people labelled from 1 to N.  There is a rumor that one of these people is secretly the town judge.

If the town judge exists, then:

1. The town judge trusts nobody.
2. Everybody (except for the town judge) trusts the town judge.
3. There is exactly one person that satisfies properties 1 and 2.
You are given trust, an array of pairs trust[i] = [a, b] representing that the person labelled a trusts the person labelled b.

If the town judge exists and can be identified, return the label of the town judge.  Otherwise, return -1.

 

Example 1:

Input: N = 2, trust = [[1,2]]
Output: 2
Example 2:

Input: N = 3, trust = [[1,3],[2,3]]
Output: 3
Example 3:

Input: N = 3, trust = [[1,3],[2,3],[3,1]]
Output: -1
Example 4:

Input: N = 3, trust = [[1,2],[2,3]]
Output: -1
Example 5:

Input: N = 4, trust = [[1,3],[1,4],[2,3],[2,4],[4,3]]
Output: 3
 

Note:

1 <= N <= 1000
trust.length <= 10000
trust[i] are all different
trust[i][0] != trust[i][1]
1 <= trust[i][0], trust[i][1] <= N

*/

// Solution

/*

As we can clearly see that the codition to be judge is 

1. The town judge trusts nobody.
2. Everybody (except for the town judge) trusts the town judge.
3. There is exactly one person that satisfies properties 1 and 2.

So first we will create a array 'a' of size n then we will count the people whom they trust i.e. value at index 0 

We will also create a array 'b' of size n then we will count the people who trust them

now comes the intersting part 

we will itterate through all the values of array 'a' & 'b'

and find 'i' such that they trust no one trust them and every other trust them

i.e. a[i]==0 && b[i]==n-1

if any such i is found we return i+1 because i is index so i+1

and at the end of the loop return -1 in case if none of the value of i stands through the condition

Time Complexity O(n) number of trusts
Space Complexity O(m) number of people

*/

// Solution

class Solution {
    public int findJudge(int N, int[][] trust) {
      int n=N;
        int a[]=new int[n];
        int b[]=new int[n];
        for(int i=0;i<n;i++)
        {
            a[i]=0;
                
        }
        for(int i=0;i<trust.length;i++)
        {
            a[trust[i][0]-1]+=1;
            b[trust[i][1]-1]+=1;
        }
        

        
        for(int i=0;i<n;i++)
        {
            if(a[i]==0 && b[i]==n-1)
                return(i+1);
        }
        return(-1);
   
    }
}