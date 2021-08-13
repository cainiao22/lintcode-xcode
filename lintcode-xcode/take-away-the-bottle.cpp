/**
 有一排有编号的瓶子，现在你需要将这些瓶子全部拿走。
 你每次只可以拿走连续的若干个瓶子，并且需要保证瓶子的编号是一个“回文串”。
 回文串指的是正着和反着读都一样的串，例如“121”和“4664”。
 返回拿走所有瓶子所需要的最少次数。

 1、瓶子的数量不超过500
 2、瓶子的编号不超过1000
 样例

 例1:

 输入：
 [1,3,4,1,5]
 输出：
 3
 说明：
 第一次先拿走[4]，剩余[1,3,1,5]
 第二次拿走[1,3,1]，剩余[5]
 第三次拿走[5]

 例2:

 输入：
 [1,2,3,5,3,1]
 输出：
 2

  类似矩阵乘积问题
 */

#include "CommonUtils.h"


class TakeAwayTheBottle
{
public:
    int takeAwayTheBottle(vector<int> &arr)
    {
        vector<vector<int>> dp;
        for(int i=0; i<arr.size(); i++)
        {
            dp.push_back(vector<int>(arr.size()));
        }
        for(int i=0; i<arr.size(); i++)
        {
            dp[i][i] = 1;
            if(i+1 < arr.size())
            {
                if(arr[i] == arr[i+1])
                {
                    dp[i][i+1] = 1;
                }
                else
                {
                    dp[i][i+1] = 2;
                }
            }
        }
        
        for(int len = 2; len < arr.size(); len++)
        {
            for(int i=0; i+len < arr.size(); i++)
            {
                int j = i+len;
                if(arr[i] == arr[j])
                {
                    dp[i][j] = dp[i+1][j - 1];
                }
                else
                {
                    dp[i][j] = INT_MAX;
                }
                for(int k=i; k<j; k++)
                {
                    dp[i][j] = min(dp[i][j], dp[i][k] + dp[k+1][j]);
                }
                
            }
        }
        
        return dp[0][arr.size() - 1];
    }
    
    
    void run()
    {
        // [1,2,3,5,3,1]
        //[1,1,2,2,3,3,5,5,3,3,1,1]
    }
};
