/*

Cousins in Binary Tree
Solution
In a binary tree, the root node is at depth 0, and children of each depth k node are at depth k+1.

Two nodes of a binary tree are cousins if they have the same depth, but have different parents.

We are given the root of a binary tree with unique values, and the values x and y of two different nodes in the tree.

Return true if and only if the nodes corresponding to the values x and y are cousins.

 

Example 1:


Input: root = [1,2,3,4], x = 4, y = 3
Output: false
Example 2:


Input: root = [1,2,3,null,4,null,5], x = 5, y = 4
Output: true
Example 3:



Input: root = [1,2,3,null,4], x = 2, y = 3
Output: false
 

Note:

The number of nodes in the tree will be between 2 and 100.
Each node has a unique integer value from 1 to 100.
 



*/


// Solution 

/*

To chcek if 2 nodes are sibing the codition is that they should not have the same parents 

but their level should be same

Time Complexity O(log(n))

Space Complexity O(1) // for the algorithm 

*/


//Solution Code


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int depth(TreeNode* root,int ptr,int depthval)
    {
        if(root==NULL)
            return 0;
        if(ptr==root->val)
            return depthval;
        int leftdepth=depth(root->left,ptr,depthval+1);
        if(leftdepth!=0)
            return leftdepth;
        return depth(root->right,ptr,depthval+1);
    }
    
    int isSiblings(TreeNode *root,int x,int y)
    {
        if(root==NULL)
            return 0;
        bool b1=0,b2=0;
        if(root->left!=NULL && root->right!=NULL)
        {   
            b1=root->left->val==y && root->right->val==x;
        
            b2=root->left->val==x && root->right->val==y;
        }
        bool b3=isSiblings(root->right,x,y);
        bool b4=isSiblings(root->left,x,y);
        return b1||b2||b3||b4;
    }
    
    bool isCousins(TreeNode* root, int x, int y) {
        if(depth(root,x,1)==depth(root,y,1) && !isSiblings(root,x,y))
            return true;
        return false;
    }
    
    
};
