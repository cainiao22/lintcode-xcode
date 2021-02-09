/**
 
 99. 重排链表
 中文
 English

 给定一个单链表L: L0→L1→…→Ln-1→Ln,

 重新排列后为：L0→Ln→L1→Ln-1→L2→Ln-2→…

 必须在不改变节点值的情况下进行原地操作。
 样例

 样例 1:
     输入: 1->2->3->4->null
     输出: 1->4->2->3->null

 样例 2:
     输入: 1->2->3->4->5->null
     输出: 1->5->2->4->3->null
     

 挑战

 你能在不改变节点值的情况下原地完成吗？

 
 */

#include "CommonUtils.h"


class ReOrderList
{
public:
    
    void reorderList_ERROR(ListNode * head)
    {
        if(head == NULL || head->next == NULL)
        {
            return;
        }
        int i=0;
        ListNode *h1 = new ListNode(0);
        ListNode *h2 = new ListNode(0);
        ListNode *cur1, *cur2, *cur;
        cur = head;
        cur1 = h1;
        cur2 = h2;
        //将链表按奇偶数分离
        while(cur != NULL)
        {
            if(i % 2 == 0)
            {
                cur1->next = cur;
                cur1 = cur;
            }
            else
            {
                cur2->next = cur;
                cur2 = cur;
            }
            cur = cur->next;
            i ++;
        }
        
        cur1->next = NULL;
        cur2->next = NULL;
        
        cur1 = h1->next;
        cur2 = h2->next;
        head = cur = new ListNode(0);
        //将奇数链表翻转
        cur2 = reverseList(cur2);
        i = 0;
        //归并算法
        while(cur1 != NULL && cur2 != NULL)
        {
            if(i % 2 == 0)
            {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            cur = cur->next;
        }
        
        if(cur1 != NULL)
        {
            cur->next = cur1;
        }
        if(cur2 != NULL)
        {
            cur->next = cur2;
        }
        cur = head;
        head = head->next;
        
        delete cur;
        delete h1;
        delete h2;
        
    }
    
    
    void reorderList(ListNode * head)
    {
        if(head == NULL)
        {
            return;
        }
        ListNode* mid = findMiddle(head);
        ListNode* head2 = reverseList(mid->next);
        mid->next = NULL;
        ListNode *cur1 = head, *cur2 = head2;
        ListNode temp(0);
        ListNode * cur = &temp;
        int i = 0;
        while(cur1 != NULL && cur2 != NULL)
        {
            if(i % 2 == 0)
            {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            else
            {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            cur = cur->next;
            i ++;
        }
        
        if(cur1 != NULL)
        {
            cur->next = cur1;
        }
        else
        {
            cur->next = cur2;
        }
        
    }
    
    ListNode* findMiddle(ListNode* head)
    {
        if(head == NULL)
        {
            return head;
        }
        ListNode *slow = head, *fast = head->next;
        while(fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
            if(fast != NULL)
            {
                fast = fast->next;
            }
        }
        
        return slow;
    }
    
    ListNode* reverseList(ListNode *head)
    {
        ListNode* cur = NULL, *temp = NULL;
        while(head != NULL)
        {
            temp = head->next;
            head->next = cur;
            cur = head;
            head = temp;
        }
        return cur;
    }
    
    ListNode* reverseList2(ListNode *head)
    {
        if(head == NULL || head->next == NULL)
        {
            return head;
        }
        ListNode *cur = head;
        ListNode *next = cur->next;
        ListNode * pre = NULL;
        
        while(next != NULL)
        {
            cur->next = pre;
            pre = cur;
            cur = next;
            next = next->next;
        }
        cur->next = pre;
        return cur;
    }
    
    void run()
    {
        ListNode * head = new ListNode(0);
        ListNode * cur = head;
        for(int i=1; i<=4; i++)
        {
            cur->next = new ListNode(i);
            cur = cur->next;
        }
        cur = head->next;
        this->reorderList(cur);
        while(cur != NULL)
        {
            cout<<cur->val<<"->";
            cur = cur->next;
        }
        cout<<"NULL"<<endl;
    }
};
