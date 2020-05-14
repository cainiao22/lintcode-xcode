/**
 1721. 使括号有效的最少添加
 中文English
 给定一个由 '(' 和 ')' 括号组成的字符串 S，我们需要添加最少的括号（ '(' 或是 ')'，可以在任何位置），以使得到的括号字符串有效。

 从形式上讲，只有满足下面几点之一，括号字符串才是有效的：

 它是一个空字符串，或者
 它可以被写成 AB （A 与 B 连接）, 其中 A 和 B 都是有效字符串，或者
 它可以被写作 (A)，其中 A 是有效字符串。
 给定一个括号字符串，返回为使结果字符串有效而必须添加的最少括号数。

 样例
 样例 1:

 输入: "())"
 输出: 1
 样例 2:

 输入: "((("
 输出: 3
 样例 3:

 输入: "()"
 输出: 0
 样例 4:

 输入: "()))(("
 输出: 4
 注意事项
 S.length <= 1000
 S 只包含 '(' 和 ')' 字符。
 */

#include "CommonUtils.h"

class MinimumAddToMakeParenthesesValid
{
public:
    int minAddToMakeValid(string &S)
    {
        int result = 0;
        int sum = 0;
        for(int i=0; i<S.size(); i++)
        {
            int x = 0;
            char a = S[i];
            if(a == '(')
            {
                x = 1;
            }
            else
            {
                x = -1;
            }
            sum += x;
            if(sum < 0)
            {
                result -= sum;
                sum = 0;
            }
        }
        
        return result + abs(sum);
    }
    
    int minAddToMakeValid2(string &S)
    {
        //需要添加的左括号和右括号数量
        int left = 0, right = 0;
        for(int i=0; i<S.size(); i++)
        {
            //如果是右括号，且当前我不需要增加右括号，那么左括号需要增加的数量要加1
            if(right == 0 && S[i] == ')')
            {
                left ++;
            }
            else
            {
                //如果当前为左括号，需要添加的右括号需要加1，如果为右括号，当前需要增加的右括号减1
                right += S[i] == '(' ? 1 : -1;
            }
        }
        
        return left + right;
    }
    
    void run()
    {
        string S = "()))((";
        int min = this->minAddToMakeValid(S);
        cout<<min<<endl;
    }
};
