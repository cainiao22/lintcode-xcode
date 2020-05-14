/**
 给定一个有根的二分搜索树和两个数字min和max，修整这个树使得所有的数字在这个新的树种都是在min和max之间（包括min和max）。然后这个所得的树仍然是合法的二分搜索树。举个例子，输入是:
 http://www.ardendertat.com/wp-content/uploads/2012/01/bst.png
 然后我们给定min为5和max为13，这样得到的二分搜索树的结果应该是：
 http://www.ardendertat.com/wp-content/uploads/2012/01/bst_trim.png
 样例

 样例1

 输入：
 {8,3,10,1,6,#,14,#,#,4,7,13}
 5
 13
 输出： {8, 6, 10, #, 7, #, 13}
 说明：树的图片在题面描述里已经给出

 样例2

 输入：
 {1,0,2}
 1
 2
 输出： {1,#,2}
 说明:
 输入是
   1
  / \
 0   2
 输出是
   1
    \
     2
*/

#include "CommonUtils.h"

class TrimABinarySearchTree
{
public:
    TreeNode * trimBST(TreeNode * root, int minimum, int maximum)
    {
        if(root == NULL)
        {
            return NULL;
        }
        if(root->val < minimum)
        {
            return trimBST(root->right, minimum, maximum);
        }
        if(root->val > maximum)
        {
            return trimBST(root->left, minimum, maximum);
        }
        
        root->left = trimBST(root->left, minimum, maximum);
        root->right = trimBST(root->right, minimum, maximum);
        
        return root;
    }
    
    //TODO BUG 待修改
    TreeNode* trimBST2(TreeNode* root, int minimum, int maximum)
    {
        if(root == NULL)
        {
            return root;
        }
        TreeNode* head = root;
        //如果根节点的值大于maximum 取其左子树
        while(head->val > maximum)
        {
            head = head->left;
            if(head == NULL)
            {
                return head;
            }
        }
        
        //如果根节点的值小于minimum 取其右子树
        while(head->val < minimum)
        {
            head = head->right;
            if(head == NULL)
            {
                return head;
            }
        }
        
        //走到这里说明head的值在区间内
        stack<TreeNode*> s;
        s.push(head);
        //去除左子树中小于minimum的节点
        while(!s.empty())
        {
            TreeNode* current = s.top();
            s.pop();
            //如果中间节点的值小于minimum，那么它的左子树肯定全部小于minimum，
            //右子树可能存在大于minimum的节点
            while(current->left != NULL && current->left->val < minimum)
            {
                current->left = current->left->right;
            }
            if(current->left != NULL)
            {
                s.push(current->left);
            }
        }
        
        if(head->right != NULL)
        {
            s.push(head);
        }
        
        while(!s.empty())
        {
            TreeNode* current = s.top();
            s.pop();
            //如果中间节点的值大于maxmum，那么它的右子树肯定全部大于maxmum，
            //左子树可能存在小于maxmum的节点
            while(current->right != NULL && current->right->val > maximum)
            {
                current->right = current->right->left;
            }
            
            if(current->right != NULL)
            {
                s.push(current->right);
            }
        }
        
        
        return head;
    }
    
    void run()
    {
        
    }
};
