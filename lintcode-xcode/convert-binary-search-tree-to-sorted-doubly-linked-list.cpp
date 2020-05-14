/**
 1534. 将二进制搜索树转换为已排序的双向链接列表
 描述
 将BST转换为已排序的循环双向链表。可以将左右指针视为双向链表中上一个和下一个指针的同义词。

 我们以下面的BST为例，它可以帮助您更好地理解问题：

 我们希望将此BST转换为循环双向链表。双向链表中的每个节点都有一个前任和后继。对于循环双向链表，第一个元素的前导是最后一个元素，最后一个元素的后继是第一个元素。

 下图显示了上述BST的循环双向链表。“head”符号表示它指向的节点是链表的最小元素。

 bstdllreturndll

 具体来说，我们希望进行转型。转换后，树节点的左指针应指向其前一个指针，右指针应指向其后继指针。我们应该将指针返回到链表的第一个元素。

 下图显示了转换后的BST。实线表示后继关系，而虚线表示前趋关系。

 bstdllreturnbst

 您在真实的面试中是否遇到过这个题？
 样例
 Example 1:

 Input: {4,2,5,1,3}
         4
        /  \
       2   5
      / \
     1   3
 Output: "left:1->5->4->3->2  right:1->2->3->4->5"
 Explanation:
 Left: reverse output
 Right: positive sequence output
 Example 2:

 Input: {2,1,3}
         2
        /  \
       1   3
 Output: "left:1->3->2  right:1->2->3"

 */

#include "CommonUtils.h"

class ConvertBinarySearchTreeToSortedDoublyLinkedList
{
public:
    //递归方式
    TreeNode * treeToDoublyList1(TreeNode * root)
    {
        TreeNode* head = new TreeNode(0);
        if(root == NULL)
        {
            return NULL;
        }
        TreeNode* tail = helper(head, root);
        tail->right = head->right;
        head->right->left = tail;
        return head->right;
    }
    
    //看起来比较复杂的话可以借助队列来存放各node,遍历完成后再将各node串起来
    //但是效果没有这个好
    TreeNode* helper(TreeNode* pre, TreeNode* node)
    {
        if(node == NULL)
        {
            return pre;
        }
        TreeNode* tail = helper(pre, node->left);
        node->left = tail;
        tail->right = node;
        return helper(node, node->right);
    }
    
    //非递归方式
    TreeNode * treeToDoublyList(TreeNode * root)
    {
        if(root == NULL)
        {
            return NULL;
        }
        stack<TreeNode*> stack;
        TreeNode* head = new TreeNode(0);
        TreeNode* top = root;
        while (top != NULL) {
            stack.push(top);
            top = top->left;
        }
        TreeNode* cur = head;
        while(!stack.empty())
        {
            top = stack.top();
            stack.pop();
            cur->right = top;
            top->left = cur;
            cur = top;
            top = top->right;
            while(top != NULL)
            {
                stack.push(top);
                top = top->left;
            }
        }
        cur->right = head->right;
        head->right->left = cur;
        return head->right;
    }
    
    void run()
    {
        TreeNode* root = new TreeNode(4);
        TreeNode* left = new TreeNode(2);
        root->left = left;
        root->right = new TreeNode(5);
        left->left = new TreeNode(1);
        left->right = new TreeNode(3);
        
        TreeNode* head = this->treeToDoublyList(root);
        root = head->right;
        left = root->left;
        cout<<"left:"<<root->val<<'\t';
        while(left != root)
        {
            cout<<left->val<<'\t';
            left = left->left;
        }
        cout<<endl;
        
        TreeNode* right = root->right;
        cout<<"right:"<<root->val<<'\t';
        while(right != root)
        {
            cout<<right->val<<'\t';
            right = right->right;
        }
        cout<<endl;
    }
};
