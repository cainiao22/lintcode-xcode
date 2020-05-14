/**
 描述
 中文
 给定一个非空字符串，包含用英文单词对应的数字0-9，但是字母顺序是打乱的，以升序输出数字。

     字符串只包含小写的英文字母。
     字符串保证是有效的，并且能够转换成数字。这意味着无效输入比如 "abc"或者"zerone" 是不允许出现的。
     字符串的长度小于50,000.字符串是one two three ... nine 几个英文字母相互掺和在一起的，找出他们

 您在真实的面试中是否遇到过这个题？
 样例

 样例1:

 输入: "owoztneoer"

 输出: "012"

 样例 2:

 输入: "fviefuro"

 输出: "45"

 */

#pragma once

#include "CommonUtils.h"

class  ReconstructOriginalDigitsFromEnglish
{
public:
    string digits[10] = {"zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    string index[10] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9"};
    int curLength;
    

    string originalDigits(string &s)
    {
        string result = "";
        curLength = s.length();
        for(int i=0; i<10; i++)
        {
            if(s.length() >= digits[i].length() && contains_sub_string(s, digits[i]))
            {
                curLength = curLength - digits[i].length();
                result.append(index[i]);
            }
        }
        
        return result;
    }
    
    bool contains_sub_string(string &s, string& num)
    {
        for(int i=0; i<num.length(); i++)
        {
            if(s.find(num[i]) == -1)
            {
                return false;
            }
        }
        for(int i=0; i<num.length(); i++)
        {
            int index = s.find(num[i]);
            s[index] = '0';
        }
        
        return true;
    }
    
    //TODO BUG 字符串没有顺序
    bool longest_common_sub_string(string& s, string& num)
    {
        int dp[s.length()+1][num.length()+1];
        dp[0][0] = 0;
        for(int i=0; i<num.length(); i++)
        {
            dp[0][i] = 0;
        }
        for(int i=0; i<s.length(); i++)
        {
            dp[i][0] = 0;
        }
        
        for(int i=0; i<s.length(); i++)
        {
            for(int j=0; j<num.length(); j++)
            {
                if(s[i] == num[j])
                {
                    dp[i+1][j+1] = dp[i][j] + 1;
                }
                else
                {
                    int greater = dp[i][j+1];
                    if(dp[i+1][j] > greater)
                    {
                        greater = dp[i+1][j];
                    }
                    dp[i+1][j+1] = greater;
                }
            }
        }
        
        
        bool result = dp[s.length()][num.length()] == num.length();
        if(result)
        {
            int i = s.length();
            int j = num.length();
            while(i > 0 && j > 0)
            {
                if(dp[i][j] == dp[i-1][j-1] + 1)
                {
                    s[i] = '0';
                    i --;
                    j --;
                }
                else if(dp[i][j] == dp[i-1][j])
                {
                    i --;
                }
                else
                {
                    j --;
                }
            }
        }
        
        return false;
    }
    void run()
    {
        string s = "owoztneoer";
        string result = this->originalDigits(s);
        cout<<result<<endl;
    }
};
