
/**
 1702. 不同的子序列 II

 给定一个字符串 S，计算 S 的不同非空子序列的个数。

 因为结果可能很大，所以返回答案模 10^9 + 7.
 样例

 示例 1:

 输入: "abc"
 输出: 7
 解释: 7 个不同的子序列分别是 "a", "b", "c", "ab", "ac", "bc", 以及 "abc"。

 示例 2:

 输入: "aba"
 输出: 6
 解释: 6 个不同的子序列分别是 "a", "b", "ab", "ba", "aa" 以及 "aba"。

 示例 3:

 输入: "aaa"
 输出: 3
 解释: 3 个不同的子序列分别是 "a", "aa" 以及 "aaa"。

 注意事项

     S 只包含小写字母。
     1 <= S.length <= 2000

 */

#include "CommonUtils.h"


class DistinctSubsequencesii
{
public:
    
    int INF = 1e9 + 7;
    int distinctSubseqII(string &S)
    {
        int length = S.length();
        if(length == 0)
        {
            return 0;
        }
        vector<int> dp(length);
        dp[0] = 1;
        int sum = 1;
        for(int i=1; i<length; i++)
        {
            //截止到i的整个字符串都算上，肯定会有一个
            dp[i] = 0;
            int j=i-1;
            for(; j>=0; j--)
            {
                dp[i] = (dp[i] + dp[j]) % INF;
                if(S[i] == S[j])
                {
                    break;
                }
            }
            //如果前面没有以dp[i]结尾的字符串，它自己可以算一个
            if(j < 0)
            {
                dp[i] = (dp[i] + 1) % INF;
            }
            sum = (sum + dp[i]) % INF;
        }
        return sum;
    }
    void run()
    {
        string S = "abab";
        cout<<this->distinctSubseqII(S)<<endl;
    }
};
