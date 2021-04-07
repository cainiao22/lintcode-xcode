/**
 34. N皇后问题 II

 根据n皇后问题，现在返回n皇后不同的解决方案的数量而不是具体的放置布局。
 样例

 例1:

 输入: n=1
 输出: 1
 解释:
 1:
 1

 例2:

 输入: n=4
 输出: 2
 解释:
 1:
 0 0 1 0
 1 0 0 0
 0 0 0 1
 0 1 0 0
 2:
 0 1 0 0
 0 0 0 1
 1 0 0 0
 0 0 1 0

 */

#include "CommonUtils.h"


class NQueensII
{
public:
    int result = 0;
    int totalNQueens(int n)
    {
        vector<int> dp(n, 0);
        helper(0, dp, n);
        return result;
    }
    
    void helper(int index, vector<int>& dp, int n)
    {
        if(index == n)
        {
            result ++;
            return;
        }
        for(int i=0; i<n; i++)
        {
            int j=index-1;
            for(; j>=0; j--)
            {
                if(dp[j] == i || abs(dp[j] - i) == (index - j))
                {
                    break;
                }
            }
            if(j >= 0)
            {
                continue;
            }
            dp[index] = i;
            helper(index + 1, dp, n);
        }
    }
    
    
    void run()
    {
        cout<<this->totalNQueens(4)<<endl;
    }
};
