/**
 
 旅行计划2 · Travel Plan II
 
 有n个城市，给出邻接矩阵arr代表任意两个城市的距离。arr[i][j]代表从城市i到城市j的距离。Alice在周末制定了一个游玩计划，她从所在的0号城市开始，游玩其他的1~n-1个城市，最后回到0号。Alice想知道她能完成游玩计划需要行走的最小距离。返回这个最小距离。除了城市0之外每个城市只能经过一次。
 
 */

#include "CommonUtils.h"


class TravelPlanII
{
public:
    
    int travelPlanII_BUG(vector<vector<int>> &arr)
    {
        size_t n = arr.size();
        vector<vector<int>> dp(1 << n);
        for(int i=0; i<dp.size(); i++)
        {
            dp[i] = vector<int>(n);
            for(int j=0; j<n; j++)
            {
                dp[i][j] = INT_MAX / 2;
            }
        }
        //这里后面的结果可能会影响前面的，导致不再更新它以后的
        for(int i=1; i<dp.size(); i++)
        {
            for(int j=0; j<n; j++)
            {
                for(int k=0; k<n; k++)
                {
                    //dp[i][j] 表示最后一步到j点，达到i这种状态需要走多少路
                    //所以只有 i & (1 << k)==1时候才表示最后可以到k,然后从k再到j,达成的状态自然是 dp[i | 1 << j]
                    if((i & (1 << k)) && (i | 1 << j) < n && (i | 1 << j) != i)
                    {
                        dp[i | 1 << j][j] = min(dp[i | 1 << j][j], dp[i][k] + arr[k][j]);
                    }
                }
            }
        }
        
        int result = INT_MAX;
        for(int i=0; i<n; i++)
        {
            result = min(result, dp[(i << n) - 1][i] + arr[i][0]);
        }
        
        return result;
    }
    
    
    int travelPlanII(vector<vector<int>> &arr)
    {
        size_t n = arr.size();
        vector<vector<int>> dp(1 << n);
        for(int i=0; i<dp.size(); i++)
        {
            dp[i] = vector<int>(n);
            for(int j=0; j<n; j++)
            {
                dp[i][j] = INT_MAX / 2;
            }
        }
        //这里后面的结果可能会影响前面的，导致不再更新它以后的
        for(int i=1; i<dp.size(); i++)
        {
            for(int j=0; j<n; j++)
            {
                for(int k=0; k<n; k++)
                {
                    //dp[i][j] 表示最后一步到j点，达到i这种状态需要走多少路
                    //所以只有 i & (1 << k)==1时候才表示最后可以到k,然后从k再到j,达成的状态自然是 dp[i | 1 << j]
                    if((i & (1 << k)) && (i | 1 << j) < n && (i | 1 << j) != i)
                    {
                        dp[i | 1 << j][j] = min(dp[i | 1 << j][j], dp[i][k] + arr[k][j]);
                    }
                }
            }
        }
        
        int result = INT_MAX;
        for(int i=0; i<n; i++)
        {
            result = min(result, dp[(i << n) - 1][i] + arr[i][0]);
        }
        
        return result;
    }
    
    
    void run()
    {
        
    }
};
