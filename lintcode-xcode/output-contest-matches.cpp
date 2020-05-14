/**
 在NBA季后赛期间，我们总是安排一支实力相当强的球队去和实力较弱的球队比赛，比如让排名第1的球队和第n的球队一起比赛，这是一个让比赛更有趣的好策略。现在给定n个球队，你需要以字符串的形式返回他们的最终赛程。

 n 组球队以正整数的形式给出，从1到n，表示它们的初始排名。排名第1的是实力最强的球队，排名n最弱的球队。我们将使用括号() 和逗号, 来表示比赛团队的配对——括号()表示比赛的组而逗号,表示间隔。在每一轮的配对过程中，你都需要遵循这个策略，那就是让一个相当强的和一个相当弱的配对。
 
 样例 1:

 输入: 2
 输出: "(1,2)"
 样例 2:

 输入: 4
 输出: "((1,4),(2,3))"
 解释:
   在第一轮中, 我们将球队1和4, 2和3组合在一起, 因为我们需要把强队和弱队放在一起.
   然后我们有 (1,4) 和 (2,3)。
   在第二轮中, (1,4) 和 (2,3) 的获胜者需要再次比赛以产生最终的胜利者, 所以你需要在最外面加上括号.
   我们得到了最终答案((1,4),(2,3))
 样例 3:

 输入: 8
 输出: "(((1,8),(4,5)),((2,7),(3,6)))"
 解释:
   第一轮: (1,8),(2,7),(3,6),(4,5)
   第二轮: ((1,8),(4,5)),((2,7),(3,6))
   第三轮: (((1,8),(4,5)),((2,7),(3,6)))
 
 */

#include "CommonUtils.h"

#include <sstream>

class OutputContestMatches
{
public:
    string findContestMatch(int n) {
        // write your code here
        string column[(n+1)/2];
        int count = 0;
        for(int i=1; i<=(n+1)/2; i++)
        {
            ostringstream buf;
            buf << '(' << i << ',' << (n - i + 1) << ')';
            column[count ++] = buf.str();
        }
    
        while(count > 1)
        {
            for(int i=0; i< count / 2; i++)
            {
                ostringstream buf;
                buf << '(' <<  column[i] << ',' << column[count - i - 1] << ')';
                column[i] = buf.str();
            }
            if(count % 2 == 1)
            {
                ostringstream buf;
                buf << '(' << column[count / 2] << ')';
                column[count / 2] = buf.str();
            }
            count = (count + 1) / 2;
        }
        
        return column[0];
    }
    
    void run()
    {
        string result = this->findContestMatch(8);
        cout<<result<<endl;
    }
};

