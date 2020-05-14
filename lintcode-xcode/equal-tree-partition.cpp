/**
 给定一个有 n个节点的二叉树，请问可否在去掉恰好一条边的情况下，将原有的树分成两个节点值总和相等的两个树。

 样例
 样例 1:

 输入: {5,10,10,#,#,2,3}
 输出: true
 解释:
   原始的树:
      5
     / \
    10 10
      /  \
     2    3
   两棵子树:
      5       10
     /       /  \
    10      2    3
 样例 2:

 输入: {1,2,10,#,#,2,20}
 输出: false
 解释:
   原始的树:
      1
     / \
    2  10
      /  \
     2    20
 说明
 二叉树的表示

 注意事项
 树的节点的值在[-100000, 100000]范围内。
 1 <= n <= 10000
 保证树不为 null
 */

#include "CommonUtils.h"

class EqualTreePartition
{
public:
    bool checkEqualTree(TreeNode * root)
    {
        if(root == NULL)
        {
            return false;
        }
        // write your code here
        dfs(root);
        if((root->val & 2) == 1)
        {
            return false;
        }
        int mid = root->val / 2;
        bool left = dfsscan(mid, root->left);
        bool right = left ? left : dfsscan(mid, root->right);
        return right;
    }
    
    bool dfsscan(int val, TreeNode* node)
    {
        if(node == NULL)
        {
            return false;
        }
        cout<<node->val<<endl;
        if(node->val == val)
        {
            return true;
        }else if(node->val > val)
        {
            bool left = dfsscan(val, node->left);
            bool right = left ? left : dfsscan(val, node->right);
            return right;
        }else
        {
            return false;
        }
        
    }
    
    void dfs(TreeNode* node)
    {
        if(node == NULL)
        {
            return;
        }
        if(node->left != NULL)
        {
            dfs(node->left);
            node->val += node->left->val;
        }
        if(node->right != NULL)
        {
            dfs(node->right);
            node->val += node->right->val;
        }
    }
    
    
    void run()
    {
        
    }
};
