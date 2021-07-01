/**
 描述

 给定字符串 s, 需要将它分割成一些子串, 使得每个子串都是回文串.

 返回所有可能的分割方案.

     不同的方案之间的顺序可以是任意的.
     每种分割方案中的每个子串都必须是 s 中连续的一段.

 样例

 样例 1:

 输入: "a"
 输出: [["a"]]
 解释: 字符串里只有一个字符, 也就只有一种分割方式 (就是它本身)

 样例 2:

 输入: "aab"
 输出: [["aa", "b"], ["a", "a", "b"]]
 解释: 有两种分割的方式.
     1. 将 "aab" 分割成 "aa" 和 "b", 它们都是回文的.
     2. 将 "aab" 分割成 "a", "a" 和 "b", 它们全都是回文的.


 */

#include "CommonUtils.h"


class PalindromePartitioning
{
public:
    
    vector<vector<string>> result;
    vector<vector<string>> partition(string &s)
    {
        vector<string> item;
        dfs(s, 0, item);
        return result;
    }
    
    void dfs(string &s, int index, vector<string> item)
    {
        if(index >= s.size())
        {
            result.push_back(item);
            return;
        }
        for(int edx=index; edx<s.size(); edx++)
        {
            if(isPalindrome(s, index, edx))
            {
                item.push_back(s.substr(index, edx+1));
                dfs(s, edx+1, item);
                item.pop_back();
            }
        }
        
    }
    
    bool isPalindrome(string &s, int start, int end)
    {
        for(int i=start, j=end; i<j; i++, j--)
        {
            if(s.at(i) != s.at(j))
            {
                return false;
            }
        }
        return true;
    }
    
    void run()
    {
        
    }
};
