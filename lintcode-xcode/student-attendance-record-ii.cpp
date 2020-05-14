/**
 给定一个正整数n，返回所有可能的长度为n的会受到奖励的出勤记录情况。结果可能会很大，请模1000000007（即res = res % 109 + 7)。

 学生出勤记录是一个字符串，记录仅由下列三个字符组成：

     'A' : 缺席（Absent）.
     'L' : 迟到（Late）.
     'P' : 到场（Present）.

 如果记录包含不超过1个缺席且不超过2个连续迟到，那么该学生会受到表扬。

 The value of n won't exceed 100,000.
 您在真实的面试中是否遇到过这个题？
 样例

 样例 1:

 输入：1
 输出：3
 解释：'A','P','L'都会受到奖励。

 样例 2:

 输入: 2
 输出: 8
 解释:
 有8种会受到奖励的记录，分别是:
 "PP" , "AP", "PA", "LP", "PL", "AL", "LA", "LL"
 只有"AA"不会被奖励，因为缺席超过1次
 
 */

#include "CommonUtils.h"


class StudentAttendanceRecordII
{
public:
    // 超时了
    int checkRecord(int n)
    {
        if(n == 0)
        {
            return 0;
        }
        queue<string> q;
        map<string, int> absent;
        
        q.push("A");
        absent.insert(pair<string, int>("A", 1));
        q.push("L");
        absent.insert(pair<string, int>("L", 0));
        q.push("P");
        absent.insert(pair<string, int>("P", 0));
        
        
        int result = 0;
        while(!q.empty())
        {
            string top = q.front();
            q.pop();
            if(top.size() == n)
            {
                result ++;
                result = result % 1000000007;
            }
            else
            {
                //添加P
                q.push(top + 'P');
                int absentNum = absent.at(top);
                absent.erase(top);
                absent.insert(pair<string, int>(top + 'P', absentNum));
                
                //添加A
                if(absentNum == 0)
                {
                    q.push(top + 'A');
                    absent.insert(pair<string, int>(top + 'A', 1));
                }
                
                //添加L 因为有continue 只能放最后了
                if(top.length() >= 2 && top[top.length() - 1] == 'L'
                   && top[top.length() - 2] == 'L')
                {
                    continue;
                }
                q.push(top + 'L');
                absent.insert(pair<string, int>(top + 'L', absentNum));
            }
        }
        
        return result;
    }
    
    //dp问题
    int checkRecordDP(int n)
    {
        if(n == 0) return 0;
        int M = 1000000007;
        //定义三位数组dp[i][j][k] 表示数组前i个字母中，最多有j个A，结尾最多有k个连续L的组合方式
        int dp[n+1][2][3];
        //初始化
        for (int j = 0; j < 2; ++j) {
            for (int k = 0; k < 3; ++k) {
                dp[0][j][k] = 1;
            }
        }
        
        for(int i=1; i <= n; i++)
        {
            for(int j=0; j<2; j++)
            {
                for(int k=0; k<3; k++)
                {
                    //这里是直接加 ‘P'
                    int val = dp[i-1][j][2] % M ;
                    //这里是加 'A'
                    if(j > 0)
                    {
                        val = (val + dp[i-1][j-1][2]) % M;
                    }
                    //这里是直接加 ‘L'
                    if(k > 0)
                    {
                        val = (val + dp[i-1][j][k-1]) % M;
                    }
                    
                    dp[i][j][k] = val;
                }
            }
        }
        
        
        return dp[n][1][2];
    }
    
    int checkRecordDP2(int n) {
        if(n == 0) return 0;
        int M = 1000000007;
        //分别代表以P结尾 以A结尾 和以L结尾的数量  P1和L1表示前面没有A的情况
        int P[n+1], A[n+1], L[n+1], P1[n+1], L1[n+1];
        P[1] = A[1] = L[1] = P1[1] = L1[1] = 1;
        P[0] = A[0] = L[0] = P1[0] = L1[0] = 0;
        P1[0] = L1[0] = 1;
        for(int i=2; i<=n; i++)
        {
            P1[i] = P1[i-1] + L1[i-1];
            //这里P1[i-2]表示后面两个都加L
            L1[i] = P1[i-1] + P1[i-2];
            P[i] = P[i-1] + A[i-1] + L[i-1];
            //因为A只能有一个，那么只要前面有A了就不能再出现A了
            A[i] = P1[i-1] + L1[i-1];
            /**
             这种情况有问题，以i-2为例，P[i-1] + L[i-1] 都会加一遍d，但是这里只减去了一次
             for(int j=1; j<i - 1; j++)
             {
                 A[i] -= A[j];
             }
             */
            //TODO 加全集再减去的方式有问题 暂时不知道怎么解决
            //这块加的是全集 需要减去连续三个是L的
            //也可以这样算 L[i] = P[i-1] + A[i-1] + P[i-2] + A[i-2];
            //针对上面的公式，前两项是一样的，后两项代表是在P或A后面连续加两个L
            L[i] = P[i-1] + A[i-1] + L[i-1];
            //   P[i-2] + A[i-2] + L[i-2] - L[i-3] = L[i-1];
            //L[i-1] = P[i-2] + A[i-2] + L[i-2] - L[i-3]
            //这块意思是L[i-2]代表以L为结尾的数据后面加两个L
            L[i] = L[i] - L[i-2];
            if(i >= 3)
            {
                L[i] = L[i] + L[i-3];
            }
        }
        
        return (P[n] + A[n] + L[n]) % M;
    }
    
    int checkRecordDP3(int n)
    {
        int M = 1e9 + 7;
        vector<int> P(n), L(n), A(n);
        P[0] = 1; L[0] = 1; A[0] = 1;
        if (n > 1) { L[1] = 3; A[1] = 2; }
        if (n > 2) A[2] = 4;
        for (int i = 1; i < n; ++i) {
            P[i] = ((P[i - 1] + L[i - 1]) % M + A[i - 1]) % M;
            if (i > 1) L[i] = ((A[i - 1] + P[i - 1]) % M + (A[i - 2] + P[i - 2]) % M) % M;
            if (i > 2) A[i] = ((A[i - 1] + A[i - 2]) % M + A[i - 3]) % M;
        }

        return ((A[n - 1] + P[n - 1]) % M + L[n - 1]) % M;
    }
    
    
    /**
     这里面定义了两个数组P和 PorL，其中 P[i] 表示数组前i个数字中1以P结尾的排列个数，PorL[i] 表示数组前i个数字中已P或者L结尾的排列个数。这个解法的精髓是先不考虑字符A的情况，而是先把定义的这个数组先求出来，由于P字符可以再任意字符后面加上，所以 P[i] = PorL[i-1]；而 PorL[i] 由两部分组成，P[i] + L[i]，其中 P[i] 已经更新了，L[i] 只能当前一个字符是P，或者前一个字符是L且再前一个字符是P的时候加上，即为 P[i-1] + P[i-2]，所以 PorL[i] = P[i] + P[i-1] + P[i-2]。

     那么这里就已经把不包含A的情况求出来了，存在了 PorL[n] 中，下面就是要求包含一个A的情况，那么就得去除一个字符，从而给A留出位置。就相当于在数组的任意一个位置上加上A，数组就被分成左右两个部分了，而这两个部分当然就不能再有A了，实际上所有不包含A的情况都已经在数组 PorL 中计算过了，而分成的子数组的长度又不会大于原数组的长度，所以直接在 PorL 中取值就行了，两个子数组的排列个数相乘，然后再把所有分割的情况累加起来就是最终结果啦
     */
    int checkRecordDP4(int n)
    {
        int M = 1e9 + 7;
        int P[n+1], PorL[n+1];
        P[0] = PorL[0] = 1;
        
        for(int i=1; i<=n; i++)
        {
            P[i] = PorL[i-1];
            PorL[i] = P[i] + P[i-1];
            if(i >= 2)
            {
                PorL[i] = (PorL[i] + P[i-2]) % M;
            }
        }
        
        long res = PorL[n];
        
        for(int i=0; i < n; i++)
        {
            //result = (result + (PorL[i] * PorL[n-1-i]) % M) % M;
            cout<<i<<"x"<<(n-1-i)<<endl;
            long t = (PorL[i] * PorL[n - 1 - i]) % M;
            res = (res + t) % M;
        }
        
        return res;
    }
    
    /**解法思路和4一样*/
    int checkRecordDP5(int n)
    {
        int M = 1e9 + 7;
        vector<long> P(n + 1), PorL(n + 1);
        P[0] = 1; PorL[0] = 1; PorL[1] = 2;
        for (int i = 1; i <= n; ++i) {
            P[i] = PorL[i - 1];
            if (i > 1) PorL[i] = (P[i] + P[i - 1] + P[i - 2]) % M;
        }
        long res = PorL[n];
        for (int i = 0; i < n; ++i) {
            cout<<i<<"##x##"<<(n-1-i)<<endl;
            long t = (PorL[i] * PorL[n - 1 - i]) % M;
            res = (res + t) % M;
        }
        return res;
    }
    
    
    void run()
    {
        for(int i=5; i<7; i++)
        {
            int x1 = checkRecordDP4(i);
            int x2 = checkRecordDP5(i);
            if(x1 != x2)
            {
                cout<<"i="<<i<<"\t x1="<<x1<<"\t x2="<<x2<<endl;
            }
        }
    }
};
