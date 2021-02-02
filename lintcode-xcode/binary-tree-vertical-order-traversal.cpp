
/**
 
 651. 二叉树垂直遍历

 给定二叉树，返回其节点值的垂直遍历顺序。 (即逐列从上到下)。
 如果两个节点在同一行和同一列中，则顺序应 从左到右。
 样例

 样例1

 输入： {3,9,20,#,#,15,7}
 输出： [[9],[3,15],[20],[7]]
 解释：
    3
   /\
  /  \
  9  20
     /\
    /  \
   15   7

 样例2

 输入： {3,9,8,4,0,1,7}
 输出：[[4],[9],[3,0,1],[8],[7]]
 解释：
      3
     /\
    /  \
    9   8
   /\  /\
  /  \/  \
  4  01   7
 */



#include "CommonUtils.h"


class BinaryTreeVerticalOrderTraversal
{
    vector<vector<int>> result;
    public:
    
    vector<vector<int>> verticalOrder(TreeNode * root)
    {
        if(root == NULL)
        {
            return result;
        }
        map<int, vector<int>> nums;
        queue<TreeNode*> q;
        queue<int> orders;
        q.push(root);
        orders.push(0);
        while(!q.empty())
        {
            TreeNode* top = q.front();
            int order = orders.front();
            q.pop();
            orders.pop();
            if(nums.find(order) == nums.end())
            {
                nums[order] = vector<int>({});
            }
            auto it = nums.find(order);
            it->second.push_back(top->val);
            if(top->left != NULL)
            {
                q.push(top->left);
                orders.push(order - 1);
            }
            if(top->right != NULL)
            {
                q.push(top->right);
                orders.push(order + 1);
            }
        }
        auto it = nums.begin();
        while(it != nums.end())
        {
            result.push_back(it->second);
            it ++;
        }
        
        return result;
    }
    
    
    void run()
    {
        
    }
};
