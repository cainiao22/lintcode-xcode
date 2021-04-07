/**
 聪明的销售 · Smart Sale
 
 销售主管的任务是出售一系列的物品，其中每个物品都有一个编号。
 由于出售具有相同编号的商品会更容易，所以销售主管决定删除一些物品。
 现在她知道她最多能删除多少物品，她想知道最终袋子里最少可以包含多少种不同编号的物品。
 例如，最开始她有n = 6 个物品，编号为：ids = [1,1,1,2,2,3]，她最多可以删除 m = 2 个物品。
 如果删除两个物品 1，则剩下的物品 ids = [1,2,2,3]，此时她拥有三种不同编号的物品。
 如果删除两个物品 2，则剩下的物品 ids = [1,1,1,3]，此时她拥有两种不同编号的物品。
 如果删除物品 2 和物品 3 各 1个，则剩下的物品 ids = [1,1,1,2]，此时她拥有两种不同编号的物品。
 我们发现，物品最多可以剩下两种不同的编号，所以你的程序要返回 2

 ids 的大小不超过 105
 105
 1≤ids[i]≤1000001≤ids[i]≤100000
 1≤m≤100000

 1≤m≤100000
 样例

 样例 1

 输入：
 [1,1,1,2,2,3]
 2
 输出：
 2

 */


#include "CommonUtils.h"


class SmartSale
{
public:
    
    static int compare(const pair<int, int> &x, const pair<int, int> &y)
    {
        return x.second - y.second;
    }
    
    int minItem(vector<int> &ids, int m)
    {
        map<int, int> container;
        for(int i=0; i<ids.size(); i++)
        {
            if(container.find(ids[i]) != container.end())
            {
                container[ids[i]] = container[ids[i]] + 1;
            }
            else
            {
                container[ids[i]] = 1;
            }
        }
        sort(container.begin(), container.end(), &SmartSale::compare);
        while(m > 0)
        {
            auto it = container.begin();
            if(it->second <= m)
            {
                container.erase(it);
                m = m - it->second;
                continue;
            }
            break;
        }
        
        return (int)container.size();
    }
    
    void run()
    {
        vector<int> ids({1,1,1,2,2,3});
        int m = 2;
        cout<<this->minItem(ids, m)<<endl;
    }
};
