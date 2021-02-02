/**
 
 1516. 异或和


 给定一个n×m矩阵arr，矩阵中的路径定义为从(0, 0) 走到 (n-1, m-1) 且只能往下和往右走。对于每一条路径都有一个goal，goal等于这条路径上经过的所有数的异或。 现在你需要找到有多少条路径上的goal等于target，返回这个数目。
 样例

 例1:

 输入:arr=[[2,1,5],[7,10,0],[12,6,4]],target=11
 输出:3
 解释:
 2 1 5
 7 10 0
 12 6 4
 (0,0)→(1,0)→(2,0)→(2,1)→(2,2).   2^7^12^6^4=11
 (0,0)→(1,0)→(1,1)→(1,2)→(2,2).   2^7^10^0^4=11
 (0,0)→(0,1)→(1,1)→(2,1)→(2,2).   2^1^10^6^4=11

 例2:

 输入:arr=[[1,3,3,3],[0,3,3,2],[3,0,1,1]],target=2
 输出:5

 注意事项

 xor操作是按位异或，在Java或C ++或python中表示为“ ^”
 对xor有疑问ke查询 xor
 1<=n,m<=20
 */

#include "CommonUtils.h"

//todo 待优化
class XORSum
{
public:
    
    map<long, vector<int>> pool;
    
    //暴力求解 超时
    long long xorSum(vector<vector<int>> &arr, int target)
    {
        size_t height = arr.size();
        size_t width = arr[0].size();
        int seed = arr[0][0];
        vector<int> hashset;
        hashset.push_back(seed);
        pool[0] = hashset;
        for(int i=1; i<height; i++)
        {
            seed = seed ^ arr[i][0];
            vector<int> hashset;
            hashset.push_back(seed);
            pool[i * width] = hashset;
        }
        seed = arr[0][0];
        for(int j=1; j<width; j++)
        {
            vector<int> hashset;
            seed = seed ^ arr[0][j];
            hashset.push_back(seed);
            pool[j] = hashset;
        }
        
        for(int i=1; i<height; i++)
        {
            for(int j=1; j<width; j++)
            {
                long key = i * width + j;
                if(pool.find(key) == pool.end())
                {
                    vector<int> hashset;
                    pool[key] = hashset;
                }

                {
                    vector<int> before = pool[key - 1];
                    auto it = before.begin();
                    while (it != before.end())
                    {
                       int item = *it ^ arr[i][j];
                       it ++;
                       pool[key].push_back(item);
                    }
                }

                {
                    vector<int> before = pool[key - width];
                    auto it = before.begin();
                    while (it != before.end())
                    {
                       int item = *it ^ arr[i][j];
                       it ++;
                       pool[key].push_back(item);
                    }
                }
            }
        }
        long long res = 0;
        auto it = pool[width * height - 1].begin();
        while(it != pool[width * height - 1].end())
        {
            if(*it == target)
            {
                res ++;
            }
            it ++;
        }
        return res;
    }
    
    
    void run()
    {
        vector<int> a({1,3,3,3});
        vector<int> b({0,3,3,2});
        vector<int> c({3,0,1,1});
        vector<vector<int>> d;
        d.push_back(a);
        d.push_back(b);
        d.push_back(c);
        cout<<this->xorSum(d, 2)<<endl;
    }
};
