/**
 253. 最少打字方式


 给出一个只包含大小写英文字符的字符串，你需要打出这个字符串。
 一开始键盘的 Capslock 是关闭的，即小写状态，要求打出这个字符串后还是小写状态。
 你可以进行以下三种操作：

     输入一个字符，屏幕上将打印出一个相应大小写状态的字符。视为敲击 1 次键盘。
     按下 Capslock，切换键盘当前的大小写状态。视为敲击 1 次键盘。
     按下 Shift 加某个字符，屏幕上将打印出一个与当前大小写状态相反的字符。视为敲击 2 次键盘。例如小写状态上，Shift + 'p' 将会输出 ‘P’。

 样例

 输入：
 "Hello"

 输出：
 6

 说明

 样例中的输入步骤为：Shift + 'h', 'e', 'l', 'l', 'o'。
 注意事项

 字符串的长度为 NNN，1≤N≤1051 \le N \le 10^51≤N≤10​5
 

 */

#include "CommonUtils.h"


class MinimumTypeWay
{
public:
    //0代表最终状态小写，1代表最终状态大写，
    //                  当前字母大写: dp[i][0] = min{dp[i-1][0] + 2, dp[i-1][1] + 2}
    //                              dp[i][1] = min(dp[i-1][0] + 2, dp[i-1][1] + 1}
    //                  当前字母小写: dp[i][0] = min(dp[i-1][0] + 1, dp[i-1][1] + 2}
    //                              dp[i][1] = min(dp[i-1][0] + 2, dp[i-1][1] + 1)
    int minimumTyping(string &str)
    {
        vector<vector<int>> dp(str.size());
        for(int i=0; i<=str.size(); i++)
        {
            dp[i] = vector<int>(2);
        }
        char start = str.at(0);
        if(start >= 'A' and start <= 'Z')
        {
            //写完大写字母后要切换回小写 直接shift+字母
            dp[0][0] = 2;
            //直接切换大写，然后写字母
            dp[0][1] = 2;
        }
        else
        {
            dp[0][0] = 1;
            dp[0][1] = 2;
        }
        
        for(int i=1; i<str.size(); i++)
        {
            char cur = str.at(i);
            if(cur >= 'A' and cur <= 'Z')
            {
                dp[i][0] = min(dp[i-1][0] + 2, dp[i-1][1] + 2);
                dp[i][1] = min(dp[i-1][0] + 2, dp[i-1][1] + 1);
            }
            else
            {
                dp[i][0] = min(dp[i-1][0] + 1, dp[i-1][1] + 2);
                dp[i][1] = min(dp[i-1][0] + 2, dp[i-1][1] + 1);
            }
        }
        
        return dp[str.size() - 1][0];
    }
    
    void run()
    {
        string s = "Hello";
        cout<<this->minimumTyping(s)<<endl;
    }
};
