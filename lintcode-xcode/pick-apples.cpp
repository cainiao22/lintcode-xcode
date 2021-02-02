
/**

 1850. 捡苹果

 Alice 和 Bob 在一个漂亮的果园里面工作，果园里面有N棵苹果树排成了一排，这些苹果树被标记成1 - N号。
 Alice 计划收集连续的K棵苹果树上面的所有苹果，Bob计划收集连续的L棵苹果树上面的所有苹果。
 Alice和Bob选择的区间不可以重合，你需要返回他们能够最大收集的苹果数量。
 样例

 示例 1:
 输入:
 A = [6, 1, 4, 6, 3, 2, 7, 4]
 K = 3
 L = 2
 输出: 24
 解释：因为Alice 可以选择3-5颗树然后摘到4 + 6 + 3 = 13 个苹果， Bob可以选择7-8棵树然后摘到7 + 4 = 11个苹果，因此他们可以收集到13 + 11 = 24。

 示例 2:
 输入:
 A = [10, 19, 15]
 K = 2
 L = 2
 输出: -1
 解释：因为对于 Alice 和 Bob 不能选择两个互不重合的区间。

 注意事项

     N 是整数且在以下范围内：[2，600]
     K 和 L 都是整数且在以下范围内：[1，N-1]
     数组A的每个元素都是以下范围内的整数：[1，500]

 */

#include "CommonUtils.h"

class Pick_Apples
{
public:
    map<int, int> m;
    int length = 0;
    int PickApples(vector<int> &A, int K, int L)
    {
        this->length = A.size();
        if(A.size() < K + L)
        {
            return -1;
        }
        vector<int> sum(A.size()+1, 0);
        for(int i=1; i<=A.size(); i++)
        {
            sum[i] = sum[i-1] + A[i-1];
        }
        int res = 0;
        for(int i=K; i<=A.size(); i++)
        {
            res = max(res, sum[i] - sum[i-K] +
                      max(getWindowMax(sum, 0, i-K, L),
                          getWindowMax(sum, i+1, A.size(), L)));
        }
        
        return res;
    }
    
    
    int getWindowMax(vector<int> &sum, int start, int end, int L)
    {
        int key = start * length + end;
        if(m.find(key) != m.end())
        {
            return m.at(key);
        }
        int res = 0;
        for(int i=end; i>= start + L; i--)
        {
            res = max(res, sum[i] - sum[i-L]);
        }
        m.insert(pair<int, int>(key, res));
        return res;
    }
    
    
    int PickApples2(vector<int> &A, int K, int L)
    {
        if(A.size() < K + L)
        {
            return -1;
        }
        vector<int> sum(A.size()+1, 0);
        for(int i=1; i<=A.size(); i++)
        {
            sum[i] = sum[i-1] + A[i-1];
        }
        
        //前缀最大区间和
        vector<int> prefixK(A.size() + 1, 0);
        vector<int> prefixL(A.size() + 1, 0);
        
        //后缀最大区间和
        vector<int> postfixK(A.size() + 1, 0);
        vector<int> postfixL(A.size() + 1, 0);
        
        for(int i=min(L, K); i<=A.size(); i++)
        {
            if(i >= L)
            {
                prefixL[i] = max(prefixL[i-1], sum[i] - sum[i-L]);
            }
            if(i >= K)
            {
                prefixK[i] = max(prefixK[i-1], sum[i] - sum[i-K]);
            }
        }
        

        for(int i = max(A.size() - L, A.size() - K); i >= 0; i--)
        {
            if(i <= A.size() - L)
            {
                postfixL[i+1] = max(postfixL[i+2], sum[i + L] - sum[i]);
            }
            if(i <= A.size() - K)
            {
                postfixK[i+1] = max(postfixK[i+2], sum[i+K] - sum[i]);
            }
        }
        
        int res = 0;
        for(int i=1; i<A.size(); i++)
        {
            res = max(prefixK[i] + postfixL[i+1], res);
            res = max(prefixL[i] + postfixK[i+1], res);
        }
        
        return res;
    }
    
    void run()
    {
        vector<int> A({4,5,4,5,6,4,7,10,9,1});
        int  K = 1, L = 4;
        cout<<this->PickApples2(A, K, L)<<endl;
    }
};
