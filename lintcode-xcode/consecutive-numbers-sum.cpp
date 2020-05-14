/**
 1439. 连续整数求和

 给定一个正整数 N，试求有多少组连续正整数满足所有数字之和为 N?

 样例
 样例 1:

 输入: 5
 输出: 2
 解释: 5 = 5 = 2 + 3，共有两组连续整数([5],[2,3])求和后为 5。
 样例 2:

 输入: 9
 输出: 3
 解释: 9 = 9 = 4 + 5 = 2 + 3 + 4
 样例 3:

 输入: 15
 输出: 4
 解释: 15 = 15 = 8 + 7 = 4 + 5 + 6 = 1 + 2 + 3 + 4 + 5
 注意事项
 1 <= N <= 10 ^ 9.
 */

#include "CommonUtils.h"

class ConsecutiveNumbersSum
{
public:
    /**
            
     */
    int consecutiveNumbersSum(int N)
    {
        int sum = 0;
        N = N * 2;
        int end =sqrt(N);
        for(int i=1; i<=end; i++)
        {
            if(i == end && N % i == 0 && (i & 1) == 1)
            {
                sum ++;
            }
            else if(N % i == 0 && ((N / i - i) & 1) == 1)
            {
                sum ++;
            }
        }
        return sum;
    }
    
    /**
        对于N 假设有k个数可以组成它 则有 x + (x+1) + (x+2) + ..... + (x+k-1) = N
                  即 kx + (k-1)*k / 2 = N
                                        kx = N - (k-1)*k / 2
                                       2kx = 2N - (k-1)*k
     */
    int consecutiveNumbersSum2(int N)
    {
        int sum = 0;
        N = N * 2;
        int end =sqrt(N);
        for(int i=1; i<=end; i++)
        {
            if((N - (i-1)*i) % (2 * i) == 0)
            {
                sum ++;
            }
        }
        return sum;
    }
    
    /**
     还可以换一种写法，核心思路还是跟上面的解法相同，要找是否存在和为N的等差数列，根据上面的分析，需要看等差数列的起始值x是否为整数，若这个等差数列每个数字都减去一个 x-1，就变成了一个从1开始的差值为1的等差数列，那就让i从1开始遍历，用一个变量 sum，每次都加上i值，这样就相当于计算了这个等差数列的和，然后每次看 N-sum 是否能整除i，能的话就表明存在长度为i的等差数列和为N
     */
    int consecutiveNumbersSum3(int N)
    {
        int sum = 0;
        int result = 0;
        for(int i=1; sum < N; i++)
        {
            sum += i;
            if((N - sum) % i == 0)
            {
                result ++;
            }
        }
        
        return result;
    }
    
    
    //超时了
    int consecutiveNumbersSum1(int N) {
        int sum = 0;
        for(int i=1; i<=N / 2; i+=2)
        {
            if(N % i == 0)
            {
                sum ++;
            }
        }
        if(N % 2 != 0)
        {
            sum ++;
        }
        
        return sum;
    }
    
    void run()
    {
        int N = 9;
        int sum = this->consecutiveNumbersSum3(N);
        cout<<sum<<endl;
    }
};
