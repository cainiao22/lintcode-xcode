/**
 948. 序列计数

 求有多少个长为 n 的序列满足如下要求:

     序列中的数都是不超过 m 的正整数
     这 n 个数的和是 p 的倍数
     这 n 个数中至少有一个是质数

 返回满足要求的序列个数对 10000007 取模的结果
 样例

 样例 1:
 输入: n = 2, m = 3, p = 4
 输出: 3
 解释: 这三个序列是 [2, 2], [1, 3] 和 [3, 1]

 
 样例 2:
 输入: n = 2, m =5, p = 4
 输出: 5
 解释: 这 5 个序列是 [2, 2], [1, 3], [3, 1], [3, 5], [5, 3]

 注意事项

     1 <= n <= 10^9
     1 <= m <= 2 x 10^7
     1 <= p <= 100


 */

#include "CommonUtils.h"


class SquenceCount
{
public:
    int INF = 1e9 + 7;
    stack<int> s;
    int count = 0;
    int sum = 0;
    int prime = 0;
    
    int sequenceCount(int n, int m, int p)
    {
        helper(n, m, p);
        return count;
    }
    //超时了
    void helper(int n, int m, int p)
    {
        if(s.size() == n && sum % p == 0 && prime > 0)
        {
            count = (count + 1) % INF;
            return;
        }
        else if(s.size() == n)
        {
            return;
        }
        for(int i=1; i<=m; i++)
        {
            sum += i;
            s.push(i);
            bool is_Prime = isPrime(i);
            if(is_Prime)
            {
                prime ++;
            }
            helper(n, m, p);
            s.pop();
            sum -= i;
            if(is_Prime)
            {
                prime --;
            }
        }
    }
    
    
    
    
    //TODO 回溯
    int sequenceCount_bad(int n, int m, int p)
    {
        
        int sum = 0;
        int prime = 0;
        int count = 0;
        s.push(1);
        sum = 1;
        while(!s.empty())
        {
            if(s.size() == n)
            {
                if(sum % p == 0 && prime > 0)
                {
                    count = (count + 1) % INF;
                }
                int top = s.top();
                s.pop();
                sum -= top;
                if(isPrime(top))
                {
                    prime --;
                }
                while(!s.empty() && s.top() > m)
                {
                    int top = s.top();
                    sum -= top;
                    if(isPrime(top))
                    {
                        prime --;
                    }
                    s.pop();
                }
                if(!s.empty())
                {
                    int top = s.top();
                    sum -= top;
                    if(isPrime(top))
                    {
                        prime --;
                    }
                    s.pop();
                    top ++;
                    s.push(top);
                    sum += top;
                    if(isPrime(top))
                    {
                        prime ++;
                    }
                    
                }
            }
            else
            {
                int top = s.top();
                if(top <= m)
                {
                    s.push(top);
                }
                else
                {
                    s.pop();
                }
            }
        }
        
        return count;
    }
                   
    bool isPrime(int num)
    {
        if(num == 1)
        {
            return false;
        }
        for(int i=2; i<=sqrt(num); i++)
        {
            if(num % i == 0)
            {
                return false;
            }
        }
        return true;
    }
    
    void run()
    {
        int n = 4, m = 10, p = 4;
        cout<<this->sequenceCount(n, m, p)<<endl;
    }
};
