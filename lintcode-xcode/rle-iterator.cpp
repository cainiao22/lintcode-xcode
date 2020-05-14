/**
 1741. RLE 迭代器
 中文English
 编写一个遍历游程编码序列的迭代器.

 迭代器由 RLEIterator(int[] A) 初始化, 其中 A 是某个序列的游程编码. 更具体地, 对于所有偶数 i，A[i] 告诉我们在序列中非负整数值 A[i + 1] 重复连续出现的次数.

 迭代器支持一个函数 next(int n), 它取出接下来的 n 个元素（n >= 1）并返回取出来的最后一个元素. 如果剩余元素以及不足 n 个, 则再取完所有元素后返回 -1.

 例如, A = [3, 8, 0, 9, 2, 5]，这是序列 [8, 8, 8, 5, 5] 的游程编码. A 可以读作 "三个八, 零个九, 两个五".

 样例
 样例 1:

 输入: A = [3, 8, 0, 9, 2, 5]
     next(2)
     next(1)
     next(1)
     next(2)
 输出: [8, 8, 5, -1]
 解释:
     RLEIterator 由 RLEIterator([3,8,0,9,2,5]) 初始化
     对应序列 [8,8,8,5,5]
     然后调用了 4 次 next()

     1. next(2) 拿去序列的 2 项, 返回 8. 然后剩下 [8, 5, 5]。

     2. next(1) 拿去序列的 1 项, 返回 8. 然后剩下 [5, 5]

     3. next(1) 拿去序列的 1 项, 返回 5. 然后剩下 [5]

     4. next(2) 拿去序列的 2 项, 返回 -1. 因为这次想要取两个元素, 但是取了第一个之后, 序列变成空的, 第二次什么也取不到, 所以返回 -1.

 样例 2:

 输入: A = [0, 0]
     next(1)
     next(2)
 输出: [null, null]
 解释: 这个序列一开始就是空的
 注意事项
 0 <= A.length <= 1000
 保证 A.length 是偶数.
 0 <= A[i] <= 10^9
 每个测试点最多调用 1000 次 next()
 1 <= n <= 10^9
 */


#include "CommonUtils.h"


class RleIterator
{
public:
    vector<int> v;
    RleIterator()
    {
        
    }
    RleIterator(vector<int> &A):v(A)
    {
        
    }
    
    int next(int n)
    {
        int cur = 0;
        for(int i=0; i<v.size(); i+=2)
        {
            cur += v[i];
            if(cur < n)
            {
                v[i] = 0;
            }
            else
            {
                v[i] = cur - n;
                if(i + 1 < v.size())
                {
                    return v[i+1];
                }
            }
        }
        return -1;
    }
    
    void run()
    {
        vector<int> A({3, 8, 0, 9, 2, 5});
        this->v = A;
        cout<<this->next(2)<<endl;
        cout<<this->next(1)<<endl;
        cout<<this->next(1)<<endl;
        cout<<this->next(2)<<endl;
    }
};
