
/**
 
 地图分析 · As Far from Land as Possible
 宽度优先搜索
 描述

 你现在手里有一份大小为 N x N 的网格grid，上面的每个单元格都用 0 和 1 标记好了。其中 0 代表海洋，1 代表陆地，请你找出一个海洋单元格，这个海洋单元格到离它最近的陆地单元格的距离是最大的。
 我们这里说的距离是「曼哈顿距离」（ Manhattan Distance）：(x0, y0) 和 (x1, y1) 这两个单元格之间的距离是 |x0 - x1| + |y0 - y1| 。
 如果网格上只有陆地或者海洋，请返回 -1。

 1 <= grid.length == grid[0].length <= 100
 grid[i][j] 不是 0 就是 1
 样例

 样例 1：

 输入：
 [[1,0,1],[0,0,0],[1,0,1]]
 输出：
 2
 解释：
 海洋单元格 (1, 1) 和所有陆地单元格之间的距离都达到最大，最大距离为 2。

 样例 2：

 输入：
 [
  [1,0,0],
  [0,0,0],
  [0,0,0]
 ]
 输出：
 4
 解释：
 海洋单元格 (2, 2) 和所有陆地单元格之间的距离都达到最大，最大距离为 4。
 
 */


#include "CommonUtils.h"


class AsFarfromLandasPossible
{
public:
    
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    int INF = 0xfffffff;
    int maxDistance1(vector<vector<int> > &grid)
    {
        int result = -1;
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        vector<vector<int> > dp;
        for(int i=0; i<grid.size(); i++)
        {
            dp.push_back(vector<int>(grid[i].size()));
            for(int j=0; j<grid[i].size(); j++)
            {
                dp[i][j] = INF;
            }
        }
        //可以将所有小岛先放到队列中
        for(int i=0; i<grid.size(); i++)
        {
            for(int j=0; j<grid[i].size(); j++)
            {
                if(grid[i][j] == 1)
                {
                    queue<vector<int> > q;
                    set<int> s;
                    q.push(vector<int> ({i, j}));
                    while(!q.empty())
                    {
                        vector<int> top = q.front();
                        q.pop();
                        int distance = abs(top[0] - i) + abs(top[1] - j);
                        if(distance < dp[top[0]][top[1]])
                        {
                            dp[top[0]][top[1]] = distance;
                        }
                        for(int k=0; k<4; k++)
                        {
                            int x = top[0] + dx[k];
                            int y = top[1] + dy[k];
                            if(x >= 0 && x < m && y >= 0 && y < n)
                            {
                                if(grid[x][y] == 1 || s.find(x * n + y) != s.end())
                                {
                                    continue;
                                }
                                s.insert(x * n + y);
                                q.push(vector<int>({x, y}));
                            }
                        }
                    }
                }
            }
        }
        
        for(int i=0; i<dp.size(); i++)
        {
            for(int j=0; j<dp[i].size(); j++)
            {
                if(grid[i][j] == 1 || dp[i][j] == INF)
                {
                    continue;
                }
                result = max(result, dp[i][j]);
            }
        }
        
        return result;
    }
    
    //多起点BFS
    int maxDistance(vector<vector<int> > &grid)
    {
        int m = (int)grid.size();
        int n = (int)grid[0].size();
        queue<vector<int> > q;
        set<int> s;
        //可以将所有小岛先放到队列中
        for(int i=0; i<grid.size(); i++)
        {
            for(int j=0; j<grid[i].size(); j++)
            {
                if(grid[i][j] == 1)
                {
                    q.push(vector<int>({i, j}));
                }
                    
            }
        }
        int dist = -1;
        while(!q.empty())
        {
            dist ++;
            size_t len = q.size();
            for(int i=0; i<len; i++)
            {
                vector<int> top = q.front();
                q.pop();
                for(int k=0; k<4; k++)
                {
                    int x = top[0] + dx[k];
                    int y = top[1] + dy[k];
                    if(x >= 0 && x < m && y >= 0 && y < n)
                    {
                        if(grid[x][y] == 1 || s.find(x * n + y) != s.end())
                        {
                            continue;
                        }
                        s.insert(x * n + y);
                        q.push(vector<int>({x, y}));
                    }
                }
            }
            
        }
        
         return dist == 0 ? -1 : dist;
    }
    
    void run()
    {
        vector<vector<int> > grid({{1,0,1},{0,0,0},{1,0,1}});
        cout<<this->maxDistance(grid)<<endl;
    }
    
};
