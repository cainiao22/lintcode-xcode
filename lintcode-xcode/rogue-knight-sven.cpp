/**
 
 返回752. 流浪剑客斯温


 在物质位面“现实”中，有n+1个星球，分别为星球0，星球1，……，星球n。

 每一个星球都有一个传送门，通过传送门可以直接到达目标星球而不经过其他的星球。

 不过传送门有两个缺点。

 第一，从星球i通过传送门只能到达编号比i大，且与i的差不超过limit的星球。

 第二，通过传送门到达星球j，需要cost[j]个金币。

 现在，流浪剑客斯温到达星球0后身上有m个金币，请问他有多少种方法通过传送门到达星球n？

     1 <= n <= 50, 0 <= m <= 100, 1 <= limit <= 50, 0 <= cost[i] <= 100。
     由于cost[0]没有意义，题目保证cost[0] = 0。

 您在真实的面试中是否遇到过这个题？
 样例

 例1:

 输入:
 n = 1
 m = 1,
 limit = 1
 cost = [0, 1]
 输出:
 1
 解释:
 方案1：星球0→星球1

 例2:

 输入:
 n = 1
 m = 1
 limit = 1
 cost = [0,2]
 输出:
 0
 解释:
 无合法方案

 注意事项

     1 <= n <= 50, 0 <= m <= 100, 1 <= limit <= 50, 0 <= cost[i] <= 100。
     由于cost[0]没有意义，题目保证cost[0] = 0。
 */


#include "CommonUtils.h"

class RogueKnightSven
{
public:
    long long result = 0;
    int dest = 0;
    long long getNumberOfWays(int n, int m, int limit, vector<int> &cost)
    {
        this->dest = n;
        helper(0, m, limit, cost);
        
        return result;
    }
    
    //TODO 超时
    void helper(int start, int cur, int limit, vector<int> &cost)
    {
        if(start == dest && cur >= 0)
        {
            result ++;
            return;
        }
        for(int i=1; i<=limit; i++)
        {
            if(start + i > dest)
            {
                break;
            }
            if(cur >= cost[start + i])
            {
                helper(start + i, cur - cost[start + i], limit, cost);
            }
            
        }
    }
    
    vector<vector<long>> dp;
    vector<int> cost;
    int m;
    int limit;
    //当前已经消耗了i个金币 到达n的数量是dp[n][j]
    void cal_dp(int n, int i)
    {
        if(dp[n][i] < -1)
        {
            cout<<"n:"<<n<<endl;
            cout<<"i:"<<i<<endl;
        }        //记忆化搜索，如果不为-1代表已经计算过了
        if(dp[n][i] != -1)
        {
            return;
        }
        
        if(n == 0 && i== m)
        {
            dp[n][i] = 1;
            return;
        }else if(n == 0 && i != m)
        {
            dp[n][i] = 0;
            return;
        }
        
        if(i + cost[n] > this->m)
        {
            dp[n][i] = 0;
            return;
        }
        dp[n][i] = 0;
        for(int k=1; k<= this->limit; k++)
        {
            if(n - k < 0)
            {
                break;
            }
            //如果想让他到达n还剩i个金币，到达n-k必须还剩i + cost[n]个金币
            cal_dp(n - k, i + cost[n]);
            dp[n][i] += dp[n-k][i + cost[n]];
        }
    }
    
    //记忆化搜索
    long long getNumberOfWaysMemory(int n, int m, int limit, vector<int> &cost)
    {
        for(int i=0; i<=n; i++)
        {
            vector<long> tmp(m+1, -1);
            this->dp.push_back(tmp);
        }
        this->m = m;
        this->cost = cost;
        this->limit = limit;
        long res = 0;
        for(int i=0; i<=m; i++)
        {
            cal_dp(n, i);
            res += dp[n][i];
        }
        
        return res;
    }
    
    long long getNumberOfWaysDP(int n, int m, int limit, vector<int> &cost)
    {
        //dp[i][j] 从0到i剩余j个金币到达方式有几种
        vector<vector<long>> dp(n+1);
        for(int i=0; i<=n; i++)
        {
            dp[i] = vector<long>(m+1, 0);
        }
        dp[0][m] = 1;
        
        for(int i=1; i<=n; i++)
        {
            for(int j=cost[i]; j<=m; j++)
            {
                for(int k=1; k<=limit && i-k>=0; k++)
                {
                    int current = j - cost[i];
                    dp[i][current] += dp[i-k][j];
                    
                }
            }
        }
        
        long result = 0;
        for(int i=0; i<=m; i++)
        {
            result += dp[n][i];
        }
        
        return result;
    }
    
    void run()
    {
        vector<int> cost({0,1,3,1,1,3,2,0,3,2,0,3,1,0,3,3,3,3,0,1,3,1,2,1,0,0,2,0,3,2,1,3,2,2,3,2,0,3});
        cout<<this->getNumberOfWaysDP(37, 73, 20, cost)<<endl;
        cout<<this->getNumberOfWaysMemory(37, 73, 20, cost)<<endl;
    }
};
