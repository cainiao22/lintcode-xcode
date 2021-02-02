/**
 给出一个2维的表格图，其中每个格子上有一个数字num

 如果num是-2表示这个点是起点，num是-3表示这个点是终点，num是-1表示这个点是障碍物不能行走，num为 0 表示这个点是道路可以正常行走

 如果num是正数，表示这个点 是传送门，则这个点可以花费1的代价到达有着相同数字的传送门格子中

 每次可以花费1的代价向上下左右四个方向之一行走一格，传送门格子也可以往四个方向走求出从起点到终点的最小花费，如果不能到达返回-1
 样例

 输入：[ [1,0,-1,1],
       [-2,0,-1,-3],
       [2,2,0,0]]
 输出：3
 解释 ： 从-2起点先向上走到1，再通过传送门到达最右上角的1位置 再往下走到达-3终点
 注意事项

 图最大是400*400的;

 传送门的种类不会超过50; 即图中最大正数不会超过50

 */

#include "CommonUtils.h"

class TheMiniumDistance
{
public:
    int getMinDistance(vector<vector<int>> &mazeMap)
    {
        map<int, vector<long>> transform;
        long m = mazeMap.size();
        long n = mazeMap[0].size();
        queue<long> q;
        vector<vector<int>> direction({
            {-1, 0},
            {0, -1},
            {1, 0},
            {0, 1}
        });
        long dest = -1;
        for(int i=0; i<mazeMap.size(); i++)
        {
            for(int j=0; j<mazeMap[i].size(); j++)
            {
                int value = mazeMap[i][j];
                if(value == -2)
                {
                    q.push(i * n + j);
                    continue;
                }
                if(value == -3)
                {
                    dest = i * n + j;
                    continue;
                }
                if(value != -1 && value != 0)
                {
                    auto iter = transform.find(value);
                    if(iter == transform.end())
                    {
                        transform.insert(pair<int,vector<long>>(value, vector<long>()));
                        iter = transform.find(value);
                    }
                    iter->second.push_back(i * n + j);
                }
            }
        }
        int step = 0;
        while (!q.empty()) {
            long length = q.size();
            while(length > 0)
            {
                length --;
                long cur = q.front();
                q.pop();
                if(cur == dest)
                {
                    return step;
                }
                
                long i = cur / n;
                long j = cur % n;
                long curVal = mazeMap[i][j];
                mazeMap[i][j] = -1;
                for(int idx=0; idx<direction.size(); idx++)
                {
                    long new_i = i + direction[idx][0];
                    long new_j = j + direction[idx][1];
                    if(new_i < 0 || new_j < 0
                       || new_i >= m || new_j >= n
                       || mazeMap[new_i][new_j] == -1)
                    {
                        continue;
                    }
                    q.push(new_i * n + new_j);
                }
                auto iter = transform.find(curVal);
                if(iter != transform.end())
                {
                    for(int i=0; i<iter->second.size(); i++)
                    {
                        long next = iter->second[i];
                        long new_i = next / n;
                        long new_j = next % n;
                        if(mazeMap[new_i][new_j] == -1)
                        {
                            continue;
                        }
                        q.push(new_i * n + new_j);
                    }
                }
            }
            step ++;
        }
        
        return -1;
    }
    
    
    void run()
    {
        vector<vector<int>> mazeMap({
            {1,0,-1,1},
            {-2,0,-1,-3},
            {2,2,0,0}
        });
        cout<<this->getMinDistance(mazeMap)<<endl;
    }
};
