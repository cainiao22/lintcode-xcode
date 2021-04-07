/**
 
 单词拆分 I · Word Break
 
 给定字符串 s 和单词字典 dict，确定 s 是否可以分成一个或多个以空格分隔的子串，并且这些子串都在字典中存在。
 因为我们已经使用了更强大的数据，所以普通的DFS方法已经无法通过此题。

 s.length <= 1e5
 dict.size <= 1e5
 样例

 样例 1:
     输入:  "lintcode", ["lint", "code"]
     输出:  true

 样例 2:
     输入: "a", ["a"]
     输出:  true
     
 */

#include "CommonUtils.h"


class WordBreak
{
public:
    
    bool wordBreak(string &s, unordered_set<string> &wordSet)
    {
        bool dp[s.size() + 1];
        dp[0] = true;
        for(int i=1; i<=s.size(); i++)
        {
            int j=0;
            for(; j<i; j++)
            {
                if(!dp[j])
                {
                    continue;
                }
                string sub = s.substr(j, i-j);
                if(wordSet.find(sub) != wordSet.end())
                {
                    dp[i] = true;
                    break;
                }
            }
            if(j >= i)
            {
                dp[i] = false;
            }
        }
        
        return dp[s.size()];
    }
    
    bool dfs(vector<string> &container, unordered_set<string> &wordSet)
    {
        return false;
    }
    
    
    void run()
    {
        
    }
};
