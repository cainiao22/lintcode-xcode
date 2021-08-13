/**
 
 在n个桶里放着一些小球，在一开始，第i个桶中的小球有A[i]个。
 你还将得到每个桶的容纳上限W，也就是说，第i个桶中存放的小球不能超过W[i]个。
 你每次可以从任意一个桶中拿走一个球，或者在任意一个桶中放置一个球。

 你最多执行k次操作，在小于等于k次操作后，你将进行如下计算：
 求出每一对相邻的桶（第0个桶和第1个桶，第1个桶和第2个桶，...，第n-2个桶和第n-1个桶）的绝对差值。

 你的任务是最小化这些绝对差值中最大值的平方，并将最后的答案返回。

 1≤k≤100
 1≤k≤100
 1≤n≤1001≤n≤100
 0≤Ai≤Wi≤100

 0≤Ai​≤Wi​≤100
 样例

 样例 1:

 输入:
 n = 5
 k = 6
 A = [1,2,3,4,5]
 W = [15,15,15,15,15]
 输出:
 0
 说明：
 共有5个桶，最多操作6次，桶内的小球分别是[1,2,3,4,5]，桶的最大容量分别是[15,15,15,15,15]。
 最好的方案在第0个桶中放入两个球，在第1个桶中放入一个球，从第3个桶中取出两个球，从第4个桶中取出一个球。
 最后你的桶中的球会变成[3,3,3,3,3]，得到的绝对差为[0,0,0,0]，所以你的答案将是 max([0,0,0,0])^2 = 0。
 其他的方案得到的答案都会比0大，因此0就是正确的答案。


 
 */

#include "CommonUtils.h"


//TODO 未通过
class PlaceTheBalls
{
public:
    
    int getAns(int n, int k, vector<int> &A, vector<int> &W)
    {
        //dp[i][j][k] 前i个桶经过j次操作重量为k时候，当前最大平方差
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(k+1, vector<int>(101, INT_MAX)));
        for(int ki = 0; ki <= k; ++ki)
        {    // 初始化
            if(A[0]-ki >= 0)//减少球
                dp[0][ki][A[0]-ki] = 0;//边界
            if(A[0]+ki <= W[0])//增加球
                dp[0][ki][A[0]+ki] = 0;
        }
        
        for(int i=1; i<n; i++)
        {
            for(int k1=0; k1<=k; k1++)
            {
                for(int k2=0; k1+k2<=k; k2++)
                {
                    for(int w=0; w<=W[i-1]; w++)
                    {
                        if(dp[i-1][k1][w] == INT_MAX)
                        {
                            continue;
                        }
                        //相加
                        if(k2 + A[i] <= W[i])
                        {
                            dp[i][k2][A[i] + k2] = min(dp[i][k2][A[i] + k2], max(dp[i-1][k1][w], (A[i] + k2 - w) * (A[i] + k2 - w)));
                        }
                        //相减
                        if(A[i] - k2 >= 0)
                        {
                            dp[i][k2][A[i] - k2] = min(dp[i][k2][A[i] - k2], max(dp[i-1][k1][w], (A[i] - k2 - w) * (A[i] - k2 - w)));
                        }
                    }
                }
            }
        }
        int result = INT_MAX;
        for(int i=0; i<W[n-1]; i++)
        {
            if(dp[n-1][k][i] < INT_MAX)
            {
                result = min(result, dp[n-1][k][i]);
            }
        }
        
        return result;
        
    }
    
    int getAns2(int n, int k, vector<int> &A, vector<int> &W)
    {
        int left = 0;
        int right = 101;
        while(left + 1 <right)
        {
            int mid = (right + left) / 2;
            if(checkOk(k, n, mid, A, W))
            {
                right = mid;
            }
            else
            {
                left = mid + 1;
            }
        }
        
        return left * left;
    }
    
    //前后差值不大于diff，最多经过多少次操作达成
    bool checkOk(int diff, int n, int k, vector<int> &A, vector<int> &W)
    {
        //前n个盒子重量之差不大于diff,需要多少次操作
        vector<vector<int>> dp(n+1, vector<int>(n, INT_MAX / 2));
        for(int i=0; i<W[0]; i++)
        {
            dp[0][i] = abs(A[0] - i);
        }
        
        for(int i=1; i<n; i++)
        {
            for(int j=0; j<=W[i]; j++)
            {
                for(int m=0; m<=W[i-1]; m++)
                {
                    if(diff < abs(j-m))
                    {
                        dp[i][j] = min(dp[i][j], dp[i-1][m] + abs(A[i] - j));
                    }
                }
            }
        }
        int result = INT_MAX;
        for(int i=0; i<W[n-1]; i++)
        {
            result = min(result, dp[n-1][i]);
        }
        return result <= k;
    }
    
    
    void run()
    {
        
    }
    
    
    
    
};
