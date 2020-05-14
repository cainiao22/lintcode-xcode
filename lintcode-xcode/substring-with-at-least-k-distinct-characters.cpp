/**
 描述
 给定一个仅包含小写字母的字符串 S.

 返回 S 中至少包含 k 个不同字符的子串的数量.
 10 ≤ length(S) ≤ 1,000,000
 1 ≤ k ≤ 26
 您在真实的面试中是否遇到过这个题？  是
 题目纠错
 样例
 样例 1:

 输入: S = "abcabcabca", k = 4
 输出: 0
 解释: 字符串中一共就只有 3 个不同的字符.
 样例 2:

 输入: S = "abcabcabcabc", k = 3
 输出: 55
 解释: 任意长度不小于 3 的子串都含有 a, b, c 这三个字符.
     比如,长度为 3 的子串共有 10 个, "abc", "bca", "cab" ... "abc"
     长度为 4 的子串共有 9 个, "abca", "bcab", "cabc" ... "cabc"
     ...
     长度为 12 的子串有 1 个, 就是 S 本身.
     所以答案是 1 + 2 + ... + 10 = 55.
 
 
    2019-11-06 13:50
 */

#include<iostream>

using namespace std;

class SubstringWithAtLeastkDistinctCharacters
{
public:
    long long kDistinctCharacters(string &s, int k) {
        // Write your code here
        int cnt[26] = {0};
        long long sum = 0;
        int length = s.size();
        int l = 0, r = 0;
        int count = 0;
        //有可能 r已经到头了，但是里面的字母都有若干个，l在向前没啥影响
        while (l <= r && l < length)
        {
            while (count < k && r < length)
            {
                if(cnt[s.at(r) - 'a'] ++ == 0)
                {
                    count ++;
                }
                
                r ++;
            }
            
            if(count >= k)
            {
                sum += length - r + 1;
            }
            
            if(-- cnt[s.at(l ++) - 'a'] == 0)
            {
                count --;
            }
        }
        
        return sum;
    }
    
    void run()
    {
        string s = "abcabcabcabc";
        long long a = this->kDistinctCharacters(s, 3);
        cout<<a<<endl;
    }
};
