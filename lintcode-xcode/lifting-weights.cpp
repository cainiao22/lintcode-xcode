/**
 
 1915 · 举重

 描述

 奥利第一次来到健身房，她正在计算她能举起的最大重量。杠铃所能承受的最大重量为maxCapacity，健身房里有n个杠铃片，第 i 个杠铃片的重量为 weights[i]。奥利现在需要选一些杠铃片加到杠铃上，使得杠铃的重量最大，但是所选的杠铃片重量总和又不能超过 maxCapacity ，请计算杠铃的最大重量是多少。

 比如，给定杠铃片的重量为 weights = [1, 3, 5]， 而杠铃的最大承重为 maxCapacity = 7，那么应该选择重量为 1 和 5 的杠铃片，(1 + 5 = 6)，所以最终的答案是 6。

 1≤n≤421 \le n \le 421≤n≤42
 1≤maxCapacity≤1061 \le maxCapacity \le 10^61≤maxCapacity≤10​6
 1≤weights[i]≤1061 \le weights[i] \le 10^61≤weights[i]≤10​6
 样例

 样例 1

 输入：
 [1,3,5]
 7
 输出：
 6

 
 */


#include "CommonUtils.h"

class LiftingWeights
{
public:

    int weightCapacity1(vector<int> &weights, int maxCapacity)
    {
        //dp[i][j] 重量为i前j个可以承受的最大重量
        //dp[i][j] = max(dp[i-weights[j][j-1] + weights[i], dp[i][j-1])
        //dp[i][j] = max(dp[i-weights[j][j] + weights[i], dp[i][j-1]) 这种是可以多次放置的
        vector<vector<int>> dp(maxCapacity+1);
        for(int i=0; i<=maxCapacity; i++)
        {
            dp[i] = vector<int>(weights.size(), 0);
            if(i >= weights[0])
            {
                dp[i][0] = weights[0];
            }
        }
        for(int i=1; i<=maxCapacity; i++)
        {
            for(int j=1; j<weights.size(); j++)
            {
                if(i - weights[j] >= 0)
                {
                    dp[i][j] = max(dp[i-weights[j]][j-1] + weights[j], dp[i][j-1]);
                }
                else
                {
                    dp[i][j] = dp[i][j-1];
                }
            }
        }
        return dp[maxCapacity][weights.size()-1];
    }
    
    //更加优化的方式
    int weightCapacity2(vector<int> &weights, int maxCapacity)
    {
        int ans = 0;
        vector<bool> cap(maxCapacity + 1, false);
        cap[0] = true;
        for(int i=0; i<weights.size(); i++)
        {
            //必须倒着遍历，如果正着遍历会导致老的结果影响新的结果，变成完全背包问题
            for(int j=maxCapacity; j>=weights[i]; j--)
            {
                if(cap[j - weights[i]])
                {
                    cap[j] = true;
                    ans = max(ans, j);
                }
            }
        }
        
        return ans;
    }
    
    
    //更加更加优化的方式
    int weightCapacity(vector<int> &weights, int maxCapacity)
    {
        int ans = 0;
        queue<int> q;
        q.push(0);
        for(int i=0; i<weights.size(); i++)
        {
            size_t len = q.size();
            for(int j=0; j<len; j++)
            {
                int top = q.front();
                q.pop();
                if(top + weights[i] <= maxCapacity)
                {
                    q.push(top + weights[i]);
                    ans = max(ans, top + weights[i]);
                }
                q.push(top);
            }
        }
        
        return ans;
    }
    
    
    void run()
    {
        vector<int> weights({393475,160580,732972,534138,693123,968128,568316,960203,816302,222601,914770,107641,419535,844112,262804,404124,599548,977638,693620,571373,75218,512746,876939,88477,455114,395077,784405,876985,724954,414721,963000,627072,767523,526531,112644,325038,6571,842459,884845,13454,160268,748438,53640});
        cout<<this->weightCapacity(weights, 1000000)<<endl;
        cout<<this->weightCapacity2(weights, 1000000)<<endl;
    }
};
