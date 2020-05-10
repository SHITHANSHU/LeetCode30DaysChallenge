/*

Check If It Is a Straight Line
You are given an array coordinates, coordinates[i] = [x, y], where [x, y] represents the coordinate of a point. Check if these points make a straight line in the XY plane.

 

 

Example 1:



Input: coordinates = [[1,2],[2,3],[3,4],[4,5],[5,6],[6,7]]
Output: true
Example 2:



Input: coordinates = [[1,1],[2,2],[3,4],[4,5],[5,6],[7,7]]
Output: false
 

Constraints:

2 <= coordinates.length <= 1000
coordinates[i].length == 2
-10^4 <= coordinates[i][0], coordinates[i][1] <= 10^4
coordinates contains no duplicate point.

*/


//Solution 


/*
To be on the same line the slope of line joining any two points should be equal to slope

of line formed by joining othre two lines

here we have taken first two points as refference and calculated the solpe of line 

by joining them 

Slope m= (y2-y2)/(x2-x1) or inverse as (x2-x1)/y2-y1)

then compare it with the slope of line formed by joining first point nad the next point 

if anywhere the slope is mismatched it returns false 

else it returns true

Time Complexity O(n)
Space Complecity O(1) 

*/



// Solution 

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) {
        int siz=coordinates.size();
        if(coordinates.size()<=2)
            return true;
        
        int x1=coordinates[0][0];
        int y1=coordinates[0][1];
        int x2=coordinates[1][0];
        int y2=coordinates[1][1];
    
        double slope=0;
        int inf=0;
        if(y2==y1)
        {
            slope=0;
            inf=1;
        }
        else
        {
            slope=(x2-x1)/(y2-y1);
        }
        
        
        for(int i=0;i<siz-2;i++)
        {
            
            int x3=coordinates[i+2][0];
            int y3=coordinates[i+2][1];
            
            int locinf=0;
            double locslope=0;
            
             if(y3==y1)
            {
                locslope=0;
                locinf=1;
            }
            else
            {
                locslope=(x3-x1)/(y3-y1);
            }
            
            if(locslope!=slope || locinf!=inf)
                return false;
            
          }
            
        return true;
        
        
        
    }
};