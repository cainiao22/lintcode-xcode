/**
 1076. 两字符串ASCII的最小删除和

 给定两个字符串s1，s2，找出最小的需要删除的字符ASCII之和，使得剩余两个字符串相等。
 样例

 样例 1:
     输入:  s1 = "sea", s2 = "eat"
     输出:  231
     
     解释:
     从 "sea" 中删除's'
     从 "eat" 中删除't'
     115(s) + 116(t) = 231是最小的。

     
 样例 2:
     输入: s1 = "delete", s2 = "leet"
     输出:  403
     
     解释:
     从 "delete" 中删除 "dee" 得到 "let",
     adds 100[d]+101[e]+101[e] to the sum.
     从"leet" 中删除'e'得到 "let".
     最后是100+101+101+101 = 403.
     如果我们最后保留的是"lee" 或 "eet", 和都比403大.

 注意事项

     0 < s1.length, s2.length <= 1000。
     每个字符串中所有元素的ASCIl值范围为[97, 122]。


 */

#include "CommonUtils.h"

class MinimumAsciiDeleteSumForTwoStrings
{
public:
    //使用最长公共子序列 做排除，因为一个26个字母，ascii码是从97开始，
    //不存在一个字母长度是另一个字母的两倍,所以多匹配一个肯定比少匹配一个的ascii和大
    int minimumDeleteSum(string &s1, string &s2) {
        vector<vector<int>> dp;
        int sum = 0;
        for(int i=0; i<s1.size(); i++)
        {
            sum += s1.at(i);
            dp.push_back(vector<int>(s2.size() + 1, 0));
        }
        dp.push_back(vector<int>(s2.size() + 1, 0));
        for(int i=0; i<s2.size(); i++)
        {
            sum += s2.at(i);
        }
        for(int i=1; i<= s1.size(); i++)
        {
            for(int j=1; j<=s2.size(); j++)
            {
                if(s1.at(i-1) == s2.at(j-1))
                {
                    dp[i][j] = max(s1.at(i-1) + dp[i-1][j-1], max(dp[i-1][j], dp[i][j-1]));
                }
                else
                {
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
                }
            }
        }
        
        return sum - 2 * dp[s1.size()][s2.size()];
    }
    
    //直接求解
    int minimumDeleteSum2(string &s1, string &s2)
    {
        vector<vector<int>> dp;
        for(int i=0; i<s1.size(); i++)
        {
            dp.push_back(vector<int>(s2.size() + 1, 0));
        }
        dp.push_back(vector<int>(s2.size() + 1, 0));
        for(int i=1; i<=s1.size(); i++)
        {
            dp[i][0] = s1.at(i-1) + dp[i-1][0];
        }
        for(int j=1; j<=s2.size(); j++)
        {
            dp[0][j] = s2.at(j-1) + dp[0][j-1];
        }
        for(int i=1; i<=s1.size(); i++)
        {
            for(int j=1; j<=s2.size(); j++)
            {
                if(s1.at(i - 1) == s2.at(j - 1))
                {
                    dp[i][j] = dp[i-1][j-1];
                }
                else
                {
                    dp[i][j] = min(s1.at(i-1) + dp[i-1][j], s2.at(j-1) + dp[i][j-1]);
                    //dp[i][j] = min(dp[i][j], s1.at(i-1) + s2.at(j-1) + dp[i-1][j-1]);
                }
            }
        }
        
        return dp[s1.size()][s2.size()];
    }
    
    //递归求解
    int minimumDeleteSum3(string &s1, string &s2)
    {
        return helper(s1, s1.size() - 1, s2, s2.size() - 1);
    }
    
    int helper(string &s1, int i, string s2, int j)
    {
        if(i == 0 && j == 0)
        {
            return 0;
        }
        else if(i == 0)
        {
            int sum = 0;
            while(j >=0)
            {
                sum += s2.at(j);
                j --;
            }
            return sum;
        }else if(j == 0)
        {
            int sum = 0;
            while(i >=0 )
            {
                sum += s1.at(i);
                i --;
            }
            return sum;
        }
        if(s1.at(i) == s2.at(j))
        {
            return helper(s1, i-1, s2, j-1);
        }
        
        return min(helper(s1, i-1, s2, j) + s1.at(i),
                   helper(s1, i, s2, j-1) + s2.at(j));
    }
    
    void run()
    {
        string s1 = "delete";
        string s2 = "leet";
        cout<<this->minimumDeleteSum2(s1, s2)<<endl;
    }
};
