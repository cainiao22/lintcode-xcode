/**

 最短子数组 II · Shortest subarray II
 
 描述

 给定一个整数数组和正整数 K，找到最小的连续子数组使得子数组的和>=K，返回子数组的长度。如果没有与条件匹配的子数组，则返回-1

 
 */

#include "CommonUtils.h"

class ShortestSubarrayII
{
public:
    int INF = 0xfffffff;
    int smallestLengthII(vector<int> &nums, int K)
    {
        if(nums.size() == 0)
        {
            return K <= 0 ? 0 : -1;
        }
        int i = 0, j = 0;
        int sum = 0;
        int len = INF;
        while(j < nums.size())
        {
            sum += nums[j];
            j ++;
            while(j < nums.size() && sum < K)
            {
                sum += nums[j];
                j ++;
            }
            while(i < j && sum - nums[i] >= K)
            {
                sum -= nums[i];
                i ++;
            }
            if(sum >= K)
            {
                len = min(len, j - i);
            }
        }
        
        return len == INF ? -1 : len;
        
    }
    
    
    void run()
    {
        vector<int> nums({1,2,3,4,5});
        int K = 5;
        cout<<this->smallestLengthII(nums, K)<<endl;
    }
};
