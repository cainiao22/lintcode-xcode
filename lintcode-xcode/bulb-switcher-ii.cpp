
/**
 
 704. 电灯切换 II

 一个房间中有 n 盏灯最初是开着的，并且墙上有 4 个开关。在对开关进行 m 次未知的操作后，你需要返回这 n 盏灯有多少种不同的状态。
 假设 n 盏灯的标号为 [1, 2, 3 ..., n]， 4 个开关的功能如下:
 1.将所有灯从开变成关，从关变成开。
 2.将标号为偶数的灯从开变成关，从关变成开。
 3.将标号为奇数的灯从开变成关，从关变成开。
 4.将标号为 (3k + 1) 的灯从开变成关，从关变成开，k = 0, 1, 2...
 样例

 样例1

 输入：
 1
 1
 输出： 2
 解释：
 状态可以是: [on], [off]

 样例2

 输入：
 2
 1
 输出： 3
 解释：
 状态可以是: [on, off], [off, on], [off, off]


 */

#include "CommonUtils.h"


class BulbSwitcherII
{
public:
    int flipLights(int n, int m)
    {
        if(n == 0)
        {
            return 1;
        }
        vector<int> root(n+1, 1);
        queue<vector<int>> q;
        q.push(root);
        for(int i=0; i<m; i++)
        {
            size_t len = q.size();
            for(int j=0; j<len; j++)
            {
                vector<int> top = q.front();
                q.pop();
                vector<int> s1(n+1);
                for(int k=1; k<=n; k++)
                {
                    s1[k] = top[k] ^ 1;
                }
                q.push(s1);
                vector<int> s2(n+1);
                for(int k=2; k<=n; k += 2)
                {
                    s2[k] = top[k] ^ 1;
                }
                q.push(s2);
                vector<int> s3(n+1);
                for(int k=1; k<=n; k += 2)
                {
                    s3[k] = top[k] ^ 1;
                }
                q.push(s3);
                for(int k=0; k<=n; k = k*3 + 1)
                {
                    top[k] = top[k] ^ 1;
                }
                q.push(top);
            }
        }
        //TODO 去重
        return q.size();
    }
    
    void run()
    {
        int m = 1, n = 1;
        cout<<this->flipLights(n, m)<<endl;
    }
};
