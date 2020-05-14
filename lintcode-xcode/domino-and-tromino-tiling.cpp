/**
 1026. 多米诺和三格骨牌铺瓦问题
 中文English
 我们有两种瓷砖：一种 2x1 多米诺形状，一种“L”型三格骨牌形状。这些形状可以被旋转。

 XX  <- 多米诺

 XX  <- 三格骨牌
 X

 给定N，有多少方法可以铺完一个2 x N的地板？返回答案模 10^9 + 7 之后的结果.

 (在铺地板的过程中，一个方格必须被一块砖覆盖。两种铺法是不同的当且仅当在地板上存在两个上下或左右相邻的格子，只有一种铺法使得这两个格子被同一块瓷砖覆盖）

 样例
 样例 1:

 输入: 3
 输出: 5
 解释: 下列为5种方式, 不同的字母表示不同的瓷砖
   1. XYZ  2. XXZ  3. XYY  4. XXY  5. XYY
     XYZ     YYZ       XZZ      XYY      XXY
    这里其实还有一个6 就是下面这个和2重复了
         YYZ
         XXZ
 样例 2:

 输入: 1
 输出: 1
 注意事项
 N 在 [1, 1000] 范围内.
 */


#include "CommonUtils.h"


class DominoAndTrominoTiling
{
public:
    
    //多米诺竖着放  多米诺骨牌两个横放的方式有重复
    int op[7][2] = {{1, 1} /*多米诺竖着放*/, {2, 0} /*多米诺放上面*/, {0, 2} /*多米诺放下面*/, {1, 2}/*L型正放3*/, {1, 2}/*L型正放4*/, {2, 1}/*L型倒放5*/, {2, 1}/*L型倒放6*/};
    
    int sum = 0;
    
    //九章算法的解法
    int numTilings(int N)
    {
        //return helper(0, 0, N);
        //当dp[i][j] 当达到第i个位置时候，上面和下面的情况,i表示短的那个，因为当N为0时候，少的那个不可能是负数
        //dp[i][0] 表示上面和下面数量相等
        //dp[i][1] 表示上面比下面多一个
        //dp[i][2] 表示上面比下面少一个
        //参考 https://www.bbsmax.com/A/ZOJPrp8odv/
        //    https://blog.csdn.net/fuxuemingzhu/article/details/83059602
        long MOD = 1000000007;
        long dp[N+1][3];
        dp[0][1] = dp[0][2] = 0;
        dp[0][0] = dp[1][0] = 1;
        //L型骨牌
        dp[1][1] = dp[1][2] = 1;
        for(int i=2; i<=N; i++)
        {
            //dp[i-2][0]不能乘2 因为dp[i-1][0]包含了两个竖着g放置的多米诺骨牌
            //
            dp[i][0] = (dp[i-1][0] + dp[i-2][0] + dp[i-2][1] + dp[i-2][2]) % MOD;
            dp[i][1] = (dp[i-1][0] + dp[i-1][2]) % MOD;
            dp[i][2] = (dp[i-1][0] + dp[i-1][1]) % MOD;
        }
        
        return int(dp[N][0]);
    }
    
    //TODO 还有另一种类似斐波那契堆的解法暂未看懂
    int numTilings2(int N)
    {
        int dp[N+1];
        dp[1] = dp[0] = 1;
        for(int i=2; i<=N; i++)
        {
            dp[i] = dp[i-1] + dp[i-2];
        }
        
        return dp[N];
    }
    
    
    //TODO bug 需要排除重复事件
    int helper(int up, int down, int N)
    {
        if(up == N && down == N)
        {
            return 1;
        }
        else if(up >= N || down >= N)
        {
            return 0;
        }
        
        int sum = 0;
        for(int i=0; i<7; i++)
        {
            if(i < 3)
            {
                sum += helper(up + op[i][0], down + op[i][1], N);
            }
            //正L 或者 F
            else if((i - 2) % 2 == 1 && up == down)
            {
                sum += helper(up + op[i][0], down + op[i][1], N);
            }
            //倒L
            else if(i == 4 && up - down == 1)
            {
                sum += helper(up + op[i][0], down + op[i][1], N);
            }
            else if(down - up == 1)
            {
                sum += helper(up + op[i][0], down + op[i][1], N);
            }
        }
        
        return sum;
    }
    
    
    
    
    void run()
    {
        cout<<this->numTilings(3)<<endl;
    }
};
