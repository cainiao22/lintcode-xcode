/**
 
 1909 · 订单分配


 打车派单场景, 假定有N个订单，待分配给N个司机。每个订单在匹配司机前，会对候选司机进行打分，打分的结果保存在N*N的矩阵score，其中score[i][j]代表订单i派给司机j的分值。
 假定每个订单只能派给一位司机，司机只能分配到一个订单。求最终的派单结果，使得匹配的订单和司机的分值累加起来最大，并且所有订单得到分配。

 1≤N≤81 \le N \le 81≤N≤8
 0≤score[i][j]≤1000 \le score[i][j] \leq 1000≤score[i][j]≤100
 题目保证每组数据的最大分数都是唯一的
 样例

 样例 1

 输入：
 [[1,2,4],[7,11,16],[37,29,22]]
 输出：
 [1,2,0]
 解释：
 标号为0的订单给标号为1的司机，获得 score[0][1] = 2 分，
 标号为1的订单给标号为2的司机，获得 score[1][2] = 16 分，
 标号为2的订单给标号为0的司机，获得 score[2][0] = 37 分，
 所以一共获得了 2 + 16 + 37 = 55 分。
 
 */

#include "CommonUtils.h"


class OrderAllocation
{
public:
    
    int max = 0;
    vector<int> result;
    
    vector<int> orderAllocation(vector<vector<int>> &score)
    {
        vector<int> current;
        vector<bool> assigned(score.size(), false);
        this->dfs(score, current, 0, 0, assigned);
        return result;
    }
    
    
    void dfs(vector<vector<int>> &score, vector<int> current, int cur,
             int idx, vector<bool> &assigned)
    {
        if(idx >= score.size())
        {
            if(cur > max)
            {
                result = current;
                max = cur;
            }
            return;
        }
        for(int i=0; i<assigned.size(); i++)
        {
            if(!assigned[i])
            {
                assigned[i] = true;
                current.push_back(i);
                dfs(score, current, cur + score[idx][i], idx+1, assigned);
                current.pop_back();
                assigned[i] = false;
            }
        }
    }
    
    void run()
    {
        vector<vector<int>> score({{1,2,4},{7,11,16},{37,29,22}});
        vector<int> result = this->orderAllocation(score);
        for(int i=0; i<result.size(); i++)
        {
            cout<<result[i]<<'\t';
        }
        cout<<endl;
    }
};
