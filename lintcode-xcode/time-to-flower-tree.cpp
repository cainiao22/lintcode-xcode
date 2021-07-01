/**
 
 给树浇水的时间 · Time to Flower Tree
 
 描述

 有一棵n
 n个节点的树，节点编号是0至n−1，其中0号节点是根节点，i号节点的父亲节点是
 father[i]。现在要对树浇水，把水撒到根节点上，水会顺着每一条边流下去，从i号节点的父亲流到i号节点需要time[i]
 的时间，请问需要多久水才能流到所有节点上。


 样例

 输入:
 [-1,0,0]
 [-1,3,5]
 输出:
 5
 解释:
 这棵树如下所示：
   0
  3/\5
 1    2
 从0到1需要花费3个单位时间，从0到2需要花费5个单位时间，因此花费5个单位时间可以让水流到所有节点上。
 
 */

#include "CommonUtils.h"


class TimeToFlowerTree
{
public:
    
    int max = 0;
    vector<int> memory;
    int INF = 0xfffffff;
    int timeToFlowerTree(vector<int> &father, vector<int> &time)
    {
        memory = vector<int>(father.size(), INF);
        for(int i=father.size()-1; i>=0; i--)
        {
            dfs(father, time, i);
        }
        return max;
    }
    
    int dfs(vector<int> &father, vector<int> &time, int i)
    {
        if(i == -1)
        {
            return 0;
        }
        if(memory[i] != INF)
        {
            return memory[i];
        }
        int cur = time[i] + dfs(father, time, father[i]);
        if(max < cur)
        {
            max = cur;
        }
        memory[i] = cur;
        return cur;
    }
    
    /**
         BFS搜索
     */
    int timeToFlowerTreeBFS(vector<int> &father, vector<int> &time)
    {
        vector<vector<int>> G(father.size(), vector<int>());
        for(int i=1; i<father.size(); i++)
        {
            G[father[i]].push_back(i);
        }
        queue<int> q, timeq;
        q.push(0);
        time.push_back(0);
        while(!q.empty())
        {
            int top = q.front();
            q.pop();
            int cur = timeq.front();
            timeq.pop();
            if(max < cur)
            {
                max = cur;
            }
            for(int i=0; i<G[top].size(); i++)
            {
                q.push(G[top][i]);
                timeq.push(cur + time[G[top][i]]);
            }
            
        }
        
        return max;
    }
    
    void run()
    {
        vector<int> father({-1, 0, 0});
        vector<int> time({0, 5, 3});
        cout<<this->timeToFlowerTree(father, time)<<endl;
    }
};
