/**
 描述

 给你一个数组boxes和一个整数target。第i个盒子中有boxes[i]根钢笔。如果sum(boxes[i] + boxes[i+1] + ... + boxes[j]) == target，那么区间[i,j]被成为有效区间。请你找出两个不重叠的有效区间，并且使这两个区间长度之和最小，将最小长度返回。如果没有这样的两个有效区间，返回-1。

 boxes的长度<= 10610 ^ 6106 且boxes[i] > 0
 样例

 样例 1

 输入:
 boxes = [1,2,2,1,1,1],
 target = 3
 输出:
 4
 
 */

#include "CommonUtils.h"


class PenBox
{
public:
    // dp[i][j] 表示i~j 可以组成target的最小区间长度
    int minimumBoxes(vector<int> &boxes, int target)
    {
        vector<int> sum(boxes.size() + 1, 0);
        vector<vector<int>> dp;
        
        for(int i=0; i<boxes.size(); i++)
        {
            sum[i+1] = sum[i] + boxes[i];
        }
        
        for(int i=1; i<sum.size(); i++)
        {
            for(int j=0; i+j < sum.size(); j++)
            {
                int k = i + j;
                dp[j][k] = min(dp[j+1][k], dp[j][k-1]);
                if(sum[k] - sum[j] == target)
                {
                    dp[j][k] = min(dp[j][k], i);
                }
            }
        }
        
        int ans = INT_MAX;
        for(int i=0; i<dp.size() - 1; i++)
        {
            ans = min(ans, dp[0][i] + dp[i+1][dp.size() - 1]);
        }
        
        return ans;
    }
    
    
    void run()
    {
        
    }
};
