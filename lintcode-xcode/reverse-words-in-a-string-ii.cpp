/**
 描述

 给定输入的字符数组，逐词翻转数组。单词被定义为不包含空格的字符串.
 输入字符数组不包含前导或尾部空格，单词总是用单个空格分隔。
 您在真实的面试中是否遇到过这个题？
 样例

 样例1

 输入: s = "the sky is blue"
 输出: "blue is sky the"

 样例2

 输入: "a b c"
 输出: "c b a"

 挑战

 你能在不分配额外空间的情况下原地解决这个问题吗？
 
 
 先做小翻转，在做大翻转；
 先做大翻转，在做小翻转，都可以。

 */

#include "CommonUtils.h"


class ReverseWordsInAStringII
{
public:
    
    void swap(string& str, int begin, int end)
    {
        while(begin < end)
        {
            char temp = str[begin];
            str[begin] = str[end];
            str[end] = temp;
            begin ++;
            end --;
        }
    }
    
    //先将单词单独翻转
    string reverseWords(string &str)
    {
        int i = 0, begin = 0;
        while(i < str.size())
        {
            if(str[i] == ' ')
            {
                swap(str, begin, i - 1);
                begin = i + 1;
            }
            i ++;
        }
        swap(str, begin, i - 1);
        //再将整个字符串翻转
        swap(str, 0, str.size() - 1);
        return str;
    }
    
    
    //先将整个字符串翻转
    string reverseWords2(string &str)
    {
        swap(str, 0, str.size() - 1);
        //再将单词依次翻转
        int i = 0, begin = 0;
        while(i < str.size())
        {
            if(str[i] == ' ')
            {
                swap(str, begin, i - 1);
                begin = i + 1;
            }
            i ++;
        }
        swap(str, begin, i - 1);
       
        return str;
    }
    
    //比较耗费空间的方法
    //另开辟一段空间 将原来str中的字符复制到新空间中去
    string reverseWords3(string &str)
    {
        string result = str;
        int i = 0, j = 0;
        while(j < str.size())
        {
            while(j < str.size() && str[j] != ' ')
            {
                j ++;
            }
            //找到单词对应的新位置
            int pos = str.length() - j;
            while(i < j)
            {
                result[pos ++] = str[i++];
            }
            j ++;
            result[pos] = ' ';
            i = j;
        }
        
        return result;
    }
    
    void run()
    {
        string str = "the  sky  is  blue";
        string result = this->reverseWords3(str);
        cout<<result<<endl;
    }
};
