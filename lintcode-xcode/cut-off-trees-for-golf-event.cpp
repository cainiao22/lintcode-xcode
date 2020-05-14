/**
 描述

 为了高尔夫赛事，你被要求修剪森林当中的树。森林被表示为一个非负的2D地图，在这张地图当中：

     0代表不能到达的障碍
     1代表可以通过的地面
     大于1的地方代表可以通过的一棵树，这个整数代表树的高度。
     你被要求去修剪在森林当中的所有树，按照树的高度——总是首先剪掉最小高度的树。在修剪完后，一开始有树的地方变成了草（值为1）。

 你从点(0, 0)开始，然后你应该输出剪掉所有的树你需要走的最小的步数。如果你不能够剪掉所有的树，在这种情况下输出-1。

 数据保证不存在两颗树具有相同的高度，并且至少有一棵需要被砍掉的树。

 给定的矩阵不会超过50 x 50.
 您在真实的面试中是否遇到过这个题？
 样例

 样例 1:

 输入：[[1,2,3],[0,0,4],[7,6,5]]
 输出：6
 解释：(0,0)->(0,1)->(0,2)->(1,2)->(2,2)->(2,1)->(2,0)，然后返回6。

 样例 2:

 输入：[[1,2,3],[0,0,0],[7,6,5]]
 输出：-1
 解释：无法完成。
 */

#include "CommonUtils.h"

class CutOffTreesForGolfEvent
{
private:
    int dt[4][2] = {{-1, 0}, {0, 1}, {1, 0}, {0, -1}};
public:
    
    int cutOffTree(vector<vector<int>> &forest)
    {
        int m = forest.size();
        if(m == 0)
        {
            return 0;
        }
        int n = forest[0].size();
        if(n == 0)
        {
            return 0;
        }
        vector<int> nums;
        map<int, int> positions;
        nums.push_back(1);
        positions.insert(pair<int, int>(1, 0));
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(forest[i][j] > 1)
                {
                    nums.push_back(forest[i][j]);
                    positions.insert(pair<int, int>(forest[i][j], i * n + j));
                }
            }
        }
        nums.push_back(1);
        positions.insert(pair<int, int>(1, 0));
        sort(nums.begin(), nums.end());
        int sum = 0;
        for(int i=0; i<nums.size() - 1; i++)
        {
            int from = positions[nums[i]];
            int to = positions[nums[i+1]];
            int min = shortest_distance_non_iterator(vector<int>({from/n, from % n}), vector<int>({to/n, to%n}), m, n, forest);
            if(min >= MAX_NUM)
            {
                return -1;
            }
            sum += min;
        }
        return sum;
    }
    
    int shotest_distance(vector<int> from, vector<int> to, int m, int n, vector<vector<int>> &forest)
    {
        if(from[0] == to[0] && from[1] == to[1])
        {
            return 0;
        }
        int min = MAX_NUM;
        for(int i=0; i<4; i++)
        {
            vector<int> next = vector<int>({from[0] + dt[i][0], from[1] + dt[i][1]});
            if(validate_position(next, m, n, forest))
            {
                int pre = forest[next[0]][next[1]];
                forest[next[0]][next[1]] = 0;
                int item = shotest_distance(next, to, m, n, forest);
                forest[next[0]][next[1]] = pre;
                if(item != MAX_NUM)
                {
                    item = item + 1;
                    if(item < min)
                    {
                        min = item;
                    }
                    if(min == abs(from[0] - to[0]) + abs(from[1] - to[1]) + 1)
                    {
                        return min;
                    }
                }
            }
        }
        
        return min;
    }
    
    /**
     * bfs搜索
     */
    int shortest_distance_non_iterator(vector<int> from, vector<int> to, int m, int n, vector<vector<int>> &forest)
    {
        int visited[m][n];
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                visited[i][j] = false;
            }
        }
        
        queue<vector<int>> queue;
        queue.push(from);
        int step = 0;
        while(!queue.empty())
        {
            int len = queue.size();
            for(int i=0; i<len; i++)
            {
                vector<int> cur = queue.front();
                if(cur[0] == to[0] && cur[1] == to[1])
                {
                    return step;
                }
                queue.pop();
                for(int j=0; j<4; j++)
                {
                    int x = cur[0] + dt[j][0];
                    int y = cur[1] + dt[j][1];
                    if(x < 0 || y < 0 || x >= m || y >= n)
                    {
                        continue;
                    }
                    if(forest[x][y] == 0 || visited[x][y])
                    {
                        continue;
                    }
                    
                    queue.push(vector<int>({x, y}));
                    visited[x][y] = true;
                }
            }
            step ++;
        }
        
        return MAX_NUM;
    }
    
    bool validate_position(vector<int> pos, int m, int n, vector<vector<int>> &forest)
    {
        if(pos[0] < 0 || pos[0] >= m || pos[1] < 0 || pos[1] >= n || forest[pos[0]][pos[1]] == 0)
        {
            return false;
        }
        return true;
    }
    
    
    
    
    void run()
    {
        vector<vector<int>> forest = vector<vector<int>>({{1,2,3},{0,0,4},{7,6,5}});
        int result = this->cutOffTree(forest);
        cout<<result<<endl;
    }
};
