/**
 
 旅行计划 · Travel Plan

 描述

 有n个城市，给出邻接矩阵arr代表任意两个城市的距离。arr[i][j]代表从城市i到城市j的距离。Alice在周末制定了一个游玩计划，她从所在的0号城市开始，游玩其他的1 ~ n-1个城市，最后回到0号。Alice想知道她能完成游玩计划需要行走的最小距离。返回这个最小距离。除了城市0之外每个城市都只能经过一次，且城市0只能是起点和终点，Alice中途不可经过城市0。

 n<=10
 arr[i][j]<=10000
 样例

 例1:

 输入:
 [[0,1,2],[1,0,2],[2,1,0]]
 输出:
 4
 解释:
 [[0,1,2],
  [1,0,2],
  [2,1,0]]
 有两种可能的方案。
 第一种，城市0->城市1->城市2->城市0，cost=5。
 第二种，城市0->城市2->城市1->城市0，cost=4。
 返回4

 例2:

 输入:
 [[0,10000,2],[5,0,10000],[10000,4,0]]
 输出:
 11


 
 */

#include "CommonUtils.h"


class TravelPlan
{
public:
    int result = 0xfffffff;
    
    int travelPlan(vector<vector<int>> &arr)
    {
        vector<bool> visited(arr.size(), false);
        visited[0] = true;
        dfs(arr, visited, 1, 0, 0);
        return result;
    }
    
    void dfs(vector<vector<int>> &arr, vector<bool> &visited, int count, int idx, int sum)
    {
        if(count >= visited.size())
        {
            sum += arr[idx][0];
            if(sum < result)
            {
                result = sum;
            }
            return;
        }
        
        for(int i=1; i<visited.size(); i++)
        {
            if(!visited[i])
            {
                visited[i] = true;
                dfs(arr, visited, count+1, i, sum + arr[idx][i]);
                visited[i] = false;
            }
        }
    }
    
    
    void run()
    {
        
    }
};
