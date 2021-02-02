/**

 返回
 1448. 卡牌游戏

 描述

 现在有一个卡牌游戏，先给出卡牌的数量n，再给你两个非负整数totalProfit、totalCost，然后给出每张卡牌的利润值 a[i]和成本值b[i]，现在可以从这些卡牌中任意选择若干张牌，组成一个方案，问有多少个方案满足所有选择的卡牌利润和大于totalProfit且成本和小于totalCost。

     由于这个数可能很大，因此只需返回方案数对1e9 + 7取模的结果。
     0≤n≤1000 \leq n \leq 1000≤n≤100
     0≤totalProfit≤1000 \leq totalProfit\leq 1000≤totalProfit≤100
     0≤totalCost≤1000 \leq totalCost \leq 1000≤totalCost≤100
     0≤a[i]≤1000 \leq a[i] \leq 1000≤a[i]≤100
     0≤b[i]≤1000 \leq b[i] \leq 1000≤b[i]≤100

 您在真实的面试中是否遇到过这个题？
 样例

 样例 1:

 输入：n = 2，totalProfit = 3，totalCost = 5，a = [2,3]，b = [2,2]
 输出：1
 解释：
 此时只有一个合法的方案，就是将两个卡牌都选上，此时a[1]+a[2] = 5 > totalProfit 且 b[1] + b[2] < totalCost，满足题意。

 样例 2:

 输入：n = 3，totalProfit = 5，totalCost = 10，a = [6,7,8]，b = [2,3,5]
 输出： 6
 解释：
 假设一个合法方案(i,j)表示选择了第i张卡牌和第j张卡牌。
 则此时合法的方案有：
 (1),(2),(3),(1,2),(1,3),(2,3)


 */

#include "CommonUtils.h"

class CardGame
{
public:
    
    int mod = 1000000007;
    
    //dp[i][j][k]  花费为j 收益为k的方案数量
    //dp[i][j][k] = dp[i-1][j-cost[i]][k-profit[i]] + dp[i-1][j][k]
    int numOfPlan(int n, int totalProfit, int totalCost,
                  vector<int> &a, vector<int> &b)
    {
        vector<vector<int>> dp(totalCost);
        int sum = 0;
        for(int i=0; i<totalCost; i++)
        {
            if(i < b.size())
            {
                sum += b[i];
            }
            vector<int> inner(sum, 0);
            dp[i] = inner;
        }
        
        dp[0][0] = 1;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<totalCost; j++)
            {
                for(int k=0; k<= sum - totalProfit; k++)
                {
                    dp[j + a[i]][k + b[i]] += dp[j][k];
                }
            }
        }
        sum = 0;
        int result = 0;
        for(int i=0; i<totalCost; i++)
        {
            if(i < b.size())
            {
                sum += b[i];
            }
            for(int j=totalProfit + 1; j<=sum; j++)
            {
                result += dp[i][j];
                result = result % mod;
            }
        }
        
        return result;
    }
    
    int memory[101][101][101];
    
    //递归
    int dfs(int n, int totalProfit, int totalCost,
    vector<int> &a, vector<int> &b, int index)
    {
        if(totalCost < 0)
        {
            return 0;
        }
        if(index >= n)
        {
            if(totalProfit <= 0 && totalCost >= 0)
            {
                return 1;
            }else{
                return 0;
            }
        }
        int chose = dfs(n, totalProfit - a[index], totalCost - b[index], a, b, index + 1);
        if(memory[index][totalProfit][totalCost] != -1)
        {
            return memory[index][totalProfit][totalCost];
        }
        int unchose = dfs(n, totalProfit, totalCost, a, b, index + 1);
        int sum = (chose + unchose) % mod;
        memory[index][totalProfit][totalCost] = sum;
        return sum;
    }
    
    
    void run()
    {
        int n = 2, totalProfit = 3, totalCost = 5;
        vector<int> a({2,3}), b({2,2});
        cout<<this->numOfPlan(n, totalProfit, totalCost, a, b)<<endl;
    }
};
