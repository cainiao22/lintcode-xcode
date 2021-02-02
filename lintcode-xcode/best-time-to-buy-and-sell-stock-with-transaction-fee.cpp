/**


 返回
 1000. 买卖股票的最佳时机含手续费

 描述

 给定一个数组，其中第i个元素是一支股票在第i天的价格，以及一个非负数 fee 代表了交易手续费。（只需要在卖出时支付 fee）

 你可以进行任意次交易，而每次交易都必须付手续费，而且你不能持有超过1支数量的股票（也就是说，你在买入之前需要先把之前买入的卖出）。

 返回可以获得的最大利润。

 0 < prices.length <= 50000.
 0 < prices[i] < 50000.
 0 <= fee < 50000.
 您在真实的面试中是否遇到过这个题？
 样例

 样例 1:

 输入: prices = [1, 3, 2, 8, 4, 9], fee = 2
 输出: 8
 解释: 最大利润的获得方式为:
   买入 prices[0] = 1
   卖出 prices[3] = 8
   买入 prices[4] = 4
   卖出 prices[5] = 9
   总利润为 ((8 - 1) - 2) + ((9 - 4) - 2) = 8.

 样例 2:

 输入: prices = [1, 4, 6, 2, 8, 3, 10, 14], fee = 3
 输出: 13
 
 */

#include "CommonUtils.h"


class BestTimeToBuyAndSellStockWithTransactionFee
{
public:
    int INF = 0xFFFFFFF;
    int maxProfit(vector<int> &prices, int fee)
    {
         return helper(0, prices, fee, 0, false);
    }
    
    //递归方式
    int helper(int profile, vector<int> &prices, int fee, int day, bool hasStock)
    {
        if(day >= prices.size())
        {
            return profile;
        }
        int res = - INF;
        if(hasStock){
            int profileSell = profile + prices[day] - fee;
            res = helper(profileSell, prices, fee, day + 1, false);
            res = max(res, helper(profile, prices, fee, day + 1, true));
        }else {
            int profileBuy = profile - prices[day];
            res = helper(profileBuy, prices, fee, day + 1, true);
            res = max(res, helper(profile, prices, fee, day + 1, false));
        }
        
        return res;
    }
    
    //动态规划
    int maxProfitDP(vector<int> &prices, int fee)
    {
        vector<int> profileBuy(prices.size(), 0), profileSell(prices.size(), 0);
        profileBuy[0] = - prices[0];
        profileSell[0] = 0;
        
        int res = 0;
        for(int i=1; i<prices.size(); i++)
        {
            profileBuy[i] = - INF;
            profileSell[i] = - INF;
            for(int j=0; j<i; j++)
            {
                profileBuy[i] = max(profileBuy[i], profileSell[j] - prices[i]);
                profileSell[i] = max(profileSell[i], profileBuy[j] + prices[i] - fee);
                
                res = max(res, max(profileSell[i], profileBuy[i]));
            }
        }
        return res;
    }
    
    
    //动态规划
    int maxProfitDP2(vector<int> &prices, int fee)
    {
        vector<int> profileHold(prices.size(), 0), profileUnHold(prices.size(), 0);
        profileHold[0] = - prices[0];
        profileUnHold[0] = 0;

        for(int i=1; i<prices.size(); i++)
        {
            profileHold[i] = max(profileHold[i-1], profileUnHold[i-1] - prices[i]);
            profileUnHold[i] = max(profileUnHold[i-1], profileHold[i-1] + prices[i] - fee);
        }
        return profileHold[prices.size() - 1];
    }
    
    void run()
    {
        vector<int> prices({1, 3, 2, 8, 4, 9});
        int fee = 2;
        cout<<this->maxProfitDP(prices, fee)<<endl;
    }
};
