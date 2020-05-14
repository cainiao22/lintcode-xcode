/**
 给定一个整数数组nums，返回一个新的counts数组。counts[i]表示：nums[i]右侧比它小的数的个数。
 样例

 样例1

 输入: [5, 2, 6, 1]
 输出: [2, 1, 1, 0]
 说明:
 5的右侧有2个元素比它小 (2 and 1).
 2的右侧有1个元素比它小 (1).
 6的右侧有1个元素比它小 (1).
 1的右侧有0个元素比它小.

 样例2

 输入: [1, 2, 3, 4]
 输出: [0, 0, 0, 0]
 
 树状数组的应用

 */

#include "CommonUtils.h"


class CountOfSmallerNumbersAfterSelf
{
public:
    // n^2的时间复杂度
    vector<int> countSmaller(vector<int> &nums)
    {
        int len = nums.size();
        if(len == 0)
        {
            return vector<int>();
        }
        vector<int> result(len);
        result[len - 1] = 0;
        for(int i=len - 2; i>=0; i--)
        {
            int j = i + 1;
            int num = nums[i];
            while(j < len && nums[j] >=num)
            {
                nums[j-1] = nums[j];
                j ++ ;
            }
            nums[j - 1] = num;
            result[i] = len - j;
        }
        
        return result;
    }
    
    //树状数组的实现方式 一个非常经典的应用
    vector<int> countSmaller2(vector<int> &nums)
    {
        vector<int> order(nums.size());
        for(int i=0; i<nums.size(); i++)
        {
            order[i] = nums[i];
        }
        sort(order.begin(), order.end());
        for(int i=0; i<nums.size(); i++)
        {
            nums[i] = lower_bound(order.begin(), order.end(), nums[i]) - order.begin() + 1;
        }
        
        vector<int> bit(nums.size());
        vector<int> count(nums.size());
        
        for(int i=nums.size() - 1; i>=0; i --)
        {
            count[i] = getSum(bit, nums[i] - 1);
            update(bit, nums[i]);
        }
        
        return count;
        
    }
    
    //找出树状数组中比我小的数，相当于查找我的子节点
    int getSum(vector<int> &bit, int num)
    {
        int sum = 0;
        for(int index=num; index>0; index = index - lowbit(index))
        {
            sum += bit[index];
        }
        return sum;
    }
    
    //更新的时候要更新我的父节点
    void update(vector<int>& bit, int num)
    {
        for(int i=num; i<bit.size(); i= i+lowbit(i))
        {
            bit[i] ++;
        }
    }
    
    int lowbit(int x)
    {
        return x & -x;
    }
    
    //二叉树解法
    vector<int> countSmaller3(vector<int> &nums)
    {
        TreeNode* root = NULL;
        vector<int> result(nums.size());
        for(int i=nums.size() - 1; i>=0; i--)
        {
            this->insert(root, nums[i], i, result, 0);
        }
        return result;
    }
                   
    TreeNode* insert(TreeNode* node, int num, int index, vector<int>& result, int preSum)
    {
        if(node == NULL)
        {
            node = new TreeNode(num);
            node->sum = preSum;
            node->sub = 1;
            result[index] = preSum;
        }
        else if(node->val == num)
        {
            node->sub += 1;
            result[index] = preSum + node->sum;
        }
        else if(node->val < num)
        {
            node->right = insert(node->right, num, index, result, preSum + node->sum + node-> sub);
        }
        else
        {
            //如果node->val > num 表示以后的node中在大于等于node->val的时候，后面会多一个比它小的数
            node->sum ++;
            node->left = insert(node->left, num, index, result, preSum);
        }
        
        return node;
    }
    
    void run()
    {
        vector<int> nums({5, 2, 6, 1});
        vector<int> result = this->countSmaller2(nums);
        cout<<result[0]<<endl;
    }
};
