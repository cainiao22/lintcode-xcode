/**

 二叉树的最长连续子序列 II


 给定一棵二叉树，找到最长连续序列(单调且相邻节点值相差为1)路径的长度(节点数)。
 路径起点跟终点可以为二叉树的任意节点。
 您在真实的面试中是否遇到过这个题？
 样例

 例1:

 输入:
 {1,2,0,3}
 输出:
 4
 解释:
     1
    / \
   2   0
  /
 3
 0-1-2-3

 例2:

 输入:
 {3,2,2}
 输出:
 2
 解释:
     3
    / \
   2   2
 2-3
 
 */

#include "CommonUtils.h"

class binaryTreeLongestConsecutiveSequenceII
{
public:
    map<TreeNode*, map<int, int>> memory;
    int longestConsecutive2(TreeNode * root)
    {
        int max = 0;
        queue<TreeNode*> q;
        if(root != NULL)
        {
            q.push(root);
        }
        while(!q.empty())
        {
            TreeNode* top = q.front();
            q.pop();
            if(top->left != NULL)
            {
                q.push(top->left);
            }
            if(top->right != NULL)
            {
                q.push(top->right);
            }
            int left = dfs(top->left, top->val, 1);
            int right = dfs(top->right, top->val, -1);
            int tmp = left + right + 1;
            if(max < tmp)
            {
                max = tmp;
            }
            left = dfs(top->left, top->val, -1);
            right = dfs(top->right, top->val, 1);
            tmp = left + right + 1;
            if(max < tmp)
            {
                max = tmp;
            }
            
        }
        
        return max;
    }
    
    int dfs(TreeNode* root, int parent, int dValue)
    {
        /**
        auto iter = memory.find(root);
        if(iter != memory.end())
        {
            map<int, int> v = iter->second;
            auto val = v.find(dValue);
            if(val != v.end())
            {
                return val->second;
            }
        }else{
            map<int, int> m;
            memory[root] = m;
        }
        */
       int max = 0;
       if(root != NULL && parent - root->val == dValue)
       {
           int right = dfs(root->right, root->val, dValue);
           int left = dfs(root->left, root->val, dValue);
           max = right > left ? right : left;
           max ++;
       }
        /**
        iter = memory.find(root);
        iter->second.insert(dValue, max);
         */
        return max;
    }
    
    
    void run()
    {
        TreeNode root(3);
        TreeNode left(2);
        TreeNode right(1);
        root.left = &left;
        root.right = &right;
        cout<<this->longestConsecutive2(&root)<<endl;
    }
};
