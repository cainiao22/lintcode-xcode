/**
 
 统计负数 · Count Negative Number
 贪心法
 Bloomberg
 Greedy
 描述

 给一个横向排序的且纵向也排序的的 n * m 的矩阵， 问里面有几个负数。

     输入的矩阵大小为 n x m ，n <= 500，m <= 500。
     为了约束程序的时间复杂度，你的程序将会运行 10^5 次

 样例

 样例 1：

 输入：
 [
     [-5,-3,-1,0,1],
     [-2,-1,0,0,1],
     [0,11,12,12,14]
 ]
 输出：5
 解释：只有 5 个负数。

 样例 2：

 输入：
 [
     [-50,-30,-10,-5],
     [-30,-20,-5,-1],
     [-10,-5,-1,0]
 ]
 输出：11
 解释：只有 11 个负数。

 */


#include "CommonUtils.h"


class count_negative_number
{
public:
    int countNumber(vector<vector<int>> &nums)
    {
        size_t n = nums.size();
        size_t m = nums[0].size();
        int index = (int)m - 1;
        int ans = 0;
        for(int i=0; i<n; i++)
        {
            while(index > 0 && nums[i][index] > 0)
            {
                index --;
            }
            ans += index + 1;
        }
        
        return ans;
    }
    
    void run()
    {
        
    }
};
