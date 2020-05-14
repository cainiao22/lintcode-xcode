/**
 1581. 最长子序列
 中文English
 给一个词典和一个字符串s，你只能删除s里的某些字符。你需要找到在词典里最长的可以生成的词，如果有多个，请输出字典序最小的一个。

 样例
 样例1

 输入：dic = ["technology", "nology", "google", "technique", "coo"]
 s = "chnology"
 输出"nology"
 样例 2

 输入： dic = ["abc", "bcd"]
 s = "abcd"
 输出："abc"
 */

#include "CommonUtils.h"

class LongestSubsequence
{
public:
    string longestSubsequence(unordered_set<string> &dic, string &s)
    {
        string result = "";
        int min = s.size();
        for(auto x=dic.begin(); x != dic.end(); x++)
        {
            if(x->size() > s.size() || s.size() - x->size() > min)
            {
                continue;
            }
            int i, j;
            for(i=0, j=0; i<s.size() && j<(*x).size(); )
            {
                if(s[i] == (*x)[j])
                {
                    i ++;
                    j ++;
                }
                else
                {
                    i++;
                }
            }
            if(j == (*x).size())
            {
                cout<<*x<<endl;
                if(min == s.size() - (*x).size())
                {
                    result = result > *x ? *x : result;
                }
                else
                {
                    min = s.size() - (*x).size();
                    result = *x;
                }
                
            }
        }
        
        return result;
    }
        
    void run()
    {
        unordered_set<string> dic;
        dic.insert("technology");
        dic.insert("nology");
        dic.insert("google");
        dic.insert("technique");
        dic.insert("coo");
        dic.insert("chnolo");
        string s = "chnology";
        cout<<this->longestSubsequence(dic, s)<<endl;
    }
};
