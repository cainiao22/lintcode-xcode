/**
 207. 区间求和 II
 中文
 English

 在类的构造函数中给一个整数数组, 实现两个方法 query(start, end) 和 modify(index, value):

     对于 query(start, end), 返回数组中下标 start 到 end 的 和。
     对于 modify(index, value), 修改数组中下标为 index 上的数为 value.

 样例

 样例1

 输入:
 [1,2,7,8,5]
 [query(0,2),modify(0,4),query(0,1),modify(2,1),query(2,4)]
 输出: [10,6,14]
 说明:
 给定数组 A = [1,2,7,8,5].
 在query(0, 2)后, 1 + 2 + 7 = 10,
 在modify(0, 4)后, 将 A[0] 修改为 4， A = [4,2,7,8,5].
 在query(0, 1)后, 4 + 2 = 6.
 在modify(2, 1)后, 将 A[2] 修改为 1，A = [4,2,1,8,5].
 After query(2, 4), 1 + 8 + 5 = 14.

 样例2

 输入:
 [1,2,3,4,5]
 [query(0,0),query(1,2),quert(3,4)]
 输出: [1,5,9]
 说明:
 1 = 1
 2 + 3 = 5
 4 + 5 = 9

 挑战

 query 和 modify的时间复杂度需要为O(logN).
 
 树状数组解法
 线段树解法
 */

#include "CommonUtils.h"


class IntervalSumII
{
public:
    /* you may need to use some attributes here */

    vector<long long> sum;
    vector<int> original;
    /*
    * @param A: An integer array
    */
    
    IntervalSumII()
    {
        
    }
    
    IntervalSumII(vector<int> A) {
        vector<long long> sum(A.size());
        original = A;
        for(int i=0; i<A.size(); i++)
        {
            int cur = i;
            while(cur < A.size())
            {
                sum[cur] += A[i];
                cur = cur + lowbit(cur + 1);
            }
        }
        this->sum = sum;
    }
    
    //-i是补码 也就是i取反加1，i取反之后，lowbit后面的全部为1，lowbit包括前面的全部为0，加1之后，lowbit为1，其他全部为0
    //二者相与刚好剩下lowbit
    int lowbit(int i)
    {
        return i & (-i);
    }

    /*
     * @param start: An integer
     * @param end: An integer
     * @return: The sum from start to end
     */
    long long query(int start, int end)
    {
        long long sumStart = sumPre(start - 1);
        long long sumEnd = sumPre(end);
        return sumEnd - sumStart;
    }
    
    long long sumPre(int end)
    {
        long long result = 0;
        end ++;
        while(end > 0)
        {
            result += sum[end - 1];
            end = end - lowbit(end);
        }
        return result;
    }
    /*
     * @param index: An integer
     * @param value: An integer
     * @return: nothing
     */
    void modify(int index, int value) {
        int add = value - original[index];
        original[index] = value;
        index ++;
        while(index <= original.size())
        {
            sum[index - 1] += add;
            index = index + lowbit(index);
        }
    }
    
    void run()
    {
        vector<int> A({10});
        IntervalSumII a(A);
        //query(0,0),modify(0,9),query(0,0)
        cout<<a.query(0, 0)<<endl;
        a.modify(0, 9);
        cout<<a.query(0, 0)<<endl;
    }
};

/**
 在原有基础上做加法操作
 */
class SegmentTree
{
public:
    long long sum;
    int start, end;
    SegmentTree* left;
    SegmentTree* right;
    
    static SegmentTree* build(vector<int> A, int start, int end)
    {
        if(start > end)
        {
            return NULL;
        }
        SegmentTree* root = new SegmentTree;
        if(start == end)
        {
            root->sum = A[start];
            return root;
        }
        int mid = (start + end) / 2;
        root->left = build(A, start, mid);
        root->right = build(A, mid+1, end);
        if(root->left)
        {
            root->sum += root->left->sum;
        }
        if(root->right)
        {
            root->sum += root->right->sum;
        }
        
        return root;
    }
    
    long long query(int start, int end)
    {
        if(start > this->end || end < this->start || start > end)
        {
            return 0;
        }
        int sum = 0;
        if(start <= this->start && end >= this->end)
        {
            return this->sum;
        }
        sum += this->left->query(start, end);
        sum += this->right->query(start, end);
        return sum;
    }
    
    void modify(int index, int value)
    {
        if(index < start || index > end)
        {
            return;
        }
        
        this-> sum += value;
        if(this->left != NULL)
        {
            this->left->modify(index, value);
        }
        if(this->right != NULL)
        {
            this->right->modify(index, value);
        }
    }
};

/**
 直接更新值的方式
 */
class SegmentTreeNode{
public:
    int start, end;
    long long sum;
    SegmentTreeNode* left, *right;
    SegmentTreeNode(int start, int end, long long sum = 0): start(start),end(end),sum(sum){};
    
    static SegmentTreeNode* build(int start, int end, vector<int> &A) {
        if (start > end) return nullptr;
        SegmentTreeNode* head = new SegmentTreeNode(start, end, A[start]);
        if (start == end) return head;
        int mid = (start + end) /2;
        head->left = build(start, mid, A);
        head->right = build(mid+1, end, A);
        
        head->sum = 0;
        if (head->left)
            head->sum += head->left->sum;
        if (head->right)
            head->sum += head->right->sum;
        return head;
    }
    
    static long long query(SegmentTreeNode* head, int start, int end) {
        if (start > head->end || end < head->start) return 0;
        if (start <= head->start && end >= head->end) {
            return head->sum;
        }
        long long l = query(head->left, start, end);
        long long r = query(head->right, start, end);
        return l + r;
    }
    
    static void modify(SegmentTreeNode* head, int index, int value) {
        if (head->start == head->end) {
            head->sum = value;
            return;
        }
        int mid = (head->start + head->end) /2;
        if (index > mid) {
            modify(head->right, index, value);
        }
        else if(index <= mid) {
            modify(head->left, index, value);
        }
        
        head->sum = 0;
        if (head->left)
            head->sum += head->left->sum;
        if (head->right)
            head->sum += head->right->sum;
    }
};

//线段树
class IntervalSumII_SegmentTree
{
public:
    SegmentTree* head;
    vector<int> original;
     /*
     * @param A: An integer array
     */
     
     IntervalSumII_SegmentTree(vector<int> A)
     {
         head = SegmentTree::build(A, 0, A.size() - 1);
         this->original = A;
     }

     /*
      * @param start: An integer
      * @param end: An integer
      * @return: The sum from start to end
      */
     long long query(int start, int end)
     {
         return head->query(start, end);
     }
     
     /*
      * @param index: An integer
      * @param value: An integer
      * @return: nothing
      */
     void modify(int index, int value) {
         int add = value - original[index];
         this->head->modify(index, add);
         original[index] = value;
     }
};
