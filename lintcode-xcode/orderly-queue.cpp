/**
 1742. 有序队列
 中文English
 给出了一个由小写字母组成的字符串 S。然后，我们可以进行任意次数的移动。

 在每次移动中，我们选择前 K 个字母中的一个（从左侧开始），将其从原位置移除，并放置在字符串的末尾。

 返回我们在任意次数的移动之后可以拥有的按字典顺序排列的最小字符串。

 样例
 样例 1:

 输入：S = "cba", K = 1
 输出："acb"
 解释：
 在第一步中，我们将第一个字符（“c”）移动到最后，获得字符串 “bac”。
 在第二步中，我们将第一个字符（“b”）移动到最后，获得最终结果 “acb”。
 样例 2:

 输入：S = "baaca", K = 3
 输出："aaabc"
 解释：
 在第一步中，我们将第一个字符（“b”）移动到最后，获得字符串 “aacab”。
 在第二步中，我们将第三个字符（“c”）移动到最后，获得最终结果 “aaabc”。
 注意事项
 1 \leq K \leq S.length \leq 10001≤K≤S.length≤1000
 S 只由小写字母组成。
 有点像贪心
 */

#include "CommonUtils.h"

class OrderlyQueue
{
public:
    string orderlyQueue(string &S, int K)
    {
        //如果K>1，理论上任何一个字母都可以到最后一个位置。
        //做递归，假设当前最小元素s可以到最后，那么当他移动到最后之后，就可以忽略他，对剩余的字符
        //做相同操作，以此类推达到最后
        if(K > 1)
        {
            sort(S.begin(), S.end());
            return S;
        }
        string res = S;
        for(int i=0; i<S.size(); i++)
        {
            res = min(res, S.substr(i) + S.substr(0, i));
        }
        
        return res;
    }
    
    
    void run()
    {
        string S = "cdsboxnraqpokjz";
        cout<<this->orderlyQueue(S, 1)<<endl;
    }
};
