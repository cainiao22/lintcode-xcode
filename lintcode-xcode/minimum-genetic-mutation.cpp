
/**
 
 1244. 最小基因变化

 描述

 基因序列可以用8个字符的字符串表示，可选择的字符包括 "A", "C", "G", "T"。

 假设我们需要调查基因突变（从“起始点”到“结束点”突变），其中一个突变被定义为基因序列中的单个字符发生突变。

 例如，"AACCGGTT" -> "AACCGGTA"是1个突变。

 此外，还有一个给定的基因“库”，它记录了所有有效的基因突变。 基因必须在基因库中才有效。

 现在，给出3个参数 - 起始点，结束点，基因库，你的任务是确定从“起始点”到“结束点”变异所需的最小突变数。 如果没有这样的突变，则返回-1。

     假设起始点一定是合法的，它不一定在基因库中。
     如果进行了多次突变，那么所有的突变过程中的序列必须是合法的
     假设起始点和终止点的序列字符串不同。

 您在真实的面试中是否遇到过这个题？
 样例

 样例1:

 输入：
 "AACCGGTT"
 "AACCGGTA"
 ["AACCGGTA"]
 输出：1
 解释：
 起始点: "AACCGGTT"
 终止点: "AACCGGTA"
 基因库: ["AACCGGTA"]

 样例2:

 输入：
 "AACCGGTT"
 "AAACGGTA"
 ["AACCGGTA", "AACCGCTA", "AAACGGTA"]
 输出: 2

 样例3:

 输入：
 "AAAAACCC"
 "AACCCCCC"
 ["AAAACCCC", "AAACCCCC", "AACCCCCC"]
 输出: 3

 题解  BFS
 */

#include "CommonUtils.h"


class MinimumGeneticMutation
{
public:
    int minMutation(string &start, string &end, vector<string> &bank)
    {
        vector<bool> flag(bank.size(), false);
        queue<string> q;
        q.push(start);
        int step = 0;
        while(!q.empty())
        {
            size_t len = q.size();
            for(int i=0; i<len; i++)
            {
                string top = q.front();
                if(top == end)
                {
                    return step;
                }
                q.pop();
                for(int j=0; j<bank.size(); j++)
                {
                    if(!flag[j] && canConvert(top, bank[j]))
                    {
                        q.push(bank[j]);
                        flag[j] = true;
                    }
                }
            }
            step ++;
        }
        
        return -1;
    }
    
    bool canConvert(string& from, string& target)
    {
        int cnt = 0;
        for(int i=0; i<from.size(); i++)
        {
            if(from[i] != target[i])
            {
                cnt ++;
            }
        }
        
        return cnt == 1;
    }
    
    void run()
    {
        string start = "AAAAACCC";
        string end = "AACCCCCC";
        vector<string> bank({"AAAACCCC", "AAACCCCC", "AACCCCCC"});
        cout<<this->minMutation(start, end, bank)<<endl;
    }
    
};
