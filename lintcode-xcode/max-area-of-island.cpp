/**
 080. 最大的岛
 中文
 English

 给定一个由0和1组成的非空二维数组grid，一个岛由一组四联通（上下左右四方向）的1（表示陆地）组成。假定grid的四周都是水。

 返回最大的岛。（没有岛则返回0）
 样例

 样例 1:

 输入：
 [[0,0,1,0,0,0,0,1,0,0,0,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,1,1,0,1,0,0,0,0,0,0,0,0],
  [0,1,0,0,1,1,0,0,1,0,1,0,0],
  [0,1,0,0,1,1,0,0,1,1,1,0,0],
  [0,0,0,0,0,0,0,0,0,0,1,0,0],
  [0,0,0,0,0,0,0,1,1,1,0,0,0],
  [0,0,0,0,0,0,0,1,1,0,0,0,0]]
 输出：6。
 解释：注意不是11！因为是4方向联通。

 样例 2:

 输入：[[0,0,0,0,0,0,0,0]]
 输出：0

 注意事项

 grid中的每一维度长度都不超过50。

 */

#include "CommonUtils.h"

class MaxAreaOfIsland
{
public:
    
    int dx[4] = {1, 0, -1, 0};
    int dy[4] = {0, -1, 0, 1};
    
    int maxAreaOfIsland(vector<vector<int>> &grid)
    {
        /*
        int m = grid.size();
        int n = grid[0].size();
        int result = 0;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j] == 1)
                {
                    result = max(result, bfs(i, j, grid));
                }
            }
        }
        
        return result;
        */
        
        return union_find(grid);
    }
    
    /**
       深度优先遍历
     */
    int dfs(int i, int j, vector<vector<int>> &grid)
    {
        int result = 1;
        grid[i][j] = 0;
        int m = grid.size();
        int n = grid[0].size();
        for(int k=0; k<4; k++)
        {
            int new_i = i + dy[k];
            int new_j = j + dx[k];
            if(new_i < 0 || new_i >= m
               || new_j < 0 || new_j >= n
               || grid[new_i][new_j] == 0)
            {
                continue;
            }
            
            result += bfs(new_i, new_j, grid);
        }
        
        return result;
    }
    
    /**
            广度优先遍历
     */
    int bfs(int i, int j, vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        queue<int> q;
        q.push(i * n + j);
        int result = 0;
        grid[i][j] = 0;
        while(!q.empty())
        {
            int top = q.front();
            q.pop();
            result ++;
            for(int k=0; k<4; k++)
            {
                int new_i = top / n + dy[k];
                int new_j = top % n + dx[k];
                if(new_i < 0 || new_i >= m
                   || new_j < 0 || new_j >= n
                   || grid[new_i][new_j] == 0)
                {
                    continue;
                }
                //避免重复添加
                grid[new_i][new_j] = 0;
                q.push(new_i * n + new_j);
            }
        }
        
        return result;
    }
    
    
    vector<vector<int>> father;
    vector<int> area;
    /**
            并查集
     */
    int union_find(vector<vector<int>> &grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<int>> father_tmp(m);
        for(int i=0; i<m; i++)
        {
            vector<int> tmp(n);
            father_tmp[i] = tmp;
        }
        vector<int> area_tmp(m * n);
        area = area_tmp;
        father = father_tmp;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                father[i][j] = i * n + j;
                area[i * n + j] = grid[i][j];
            }
        }
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(grid[i][j] == 1)
                {
                    int parent1 = findParent(i, j, n);
                    for(int k=0; k<4; k++)
                    {
                        int new_i = i + dy[k];
                        int new_j = j + dx[k];
                        if(new_i < 0 || new_i >= m
                           || new_j < 0 || new_j >= n
                           || grid[new_i][new_j] == 0)
                        {
                            continue;
                        }
                        int parent2 = findParent(new_i, new_j, n);
                        if(parent1 != parent2)
                        {
                            if(parent1 < parent2)
                            {
                                father[parent2/n][parent2 % n] = parent1;
                                area[parent1] += area[parent2];
                            }
                            else
                            {
                                father[parent1/n][parent1 % n] = parent2;
                                area[parent2] += area[parent1];
                                //此时父节点已经变
                                parent1 = parent2;
                            }
                        }
                    }
                }
            }
        }
        
        int result = 0;
        for(int i=0; i<area.size(); i++)
        {
            result = max(result, area[i]);
        }
        
        return result;
    }
    
    int findParent(int i, int j, int n)
    {
        int flag = i * n + j;
        while(father[i][j] != flag)
        {
            flag = father[i][j];
            i = flag / n;
            j = flag % n;
        }
        
        return flag;
    }
    
    
    void run()
    {
        /*
        vector<vector<int>> grid( {
            {0,0,1,0,0,0,0,1,0,0,0,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,1,1,0,1,0,0,0,0,0,0,0,0},
            {0,1,0,0,1,1,0,0,1,0,1,0,0},
            {0,1,0,0,1,1,0,0,1,1,1,0,0},
            {0,0,0,0,0,0,0,0,0,0,1,0,0},
            {0,0,0,0,0,0,0,1,1,1,0,0,0},
            {0,0,0,0,0,0,0,1,1,0,0,0,0}});
         */
        vector<vector<int>> grid({
            {0,0,1},
            {1,1,1},
            {1,1,1}});
        cout<<this->maxAreaOfIsland(grid)<<endl;
        
        
    }
};
