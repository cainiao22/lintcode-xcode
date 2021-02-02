
/**
 
 1711. 下降路径最小和
 中文
 English

 给定一个方形整数数组 A，我们想要得到通过 A 的下降路径的最小和。

 下降路径可以从第一行中的任何元素开始，并从每一行中选择一个元素。在下一行选择的元素和当前行所选元素最多相隔一列。
 样例

 样例：

 输入：[[1,2,3],[4,5,6],[7,8,9]]
 输出：12
 解释：
 可能的下降路径有：
 [1,4,7], [1,4,8], [1,5,7], [1,5,8], [1,5,9]

 [2,4,7], [2,4,8], [2,5,7], [2,5,8], [2,5,9], [2,6,8], [2,6,9]

 [3,5,7], [3,5,8], [3,5,9], [3,6,8], [3,6,9]

 和最小的下降路径是 [1,4,7]，所以答案是 12。

 注意事项

 1 <= A.length == A[0].length <= 100
 -100 <= A[i][j] <= 100

 
 
 */

#include "CommonUtils.h"

class MinimumFallingPathSum
{
public:
    int INF = 0xfffffff;
    int minFallingPathSum3(vector<vector<int>> &A)
    {
        vector<vector<int>> memory(A.size());
        for(int i=0; i<A.size(); i++)
        {
            vector<int> a(A.size(), INF);
            memory[i] = a;
        }
        int result = 0xfffffff;
        for(int i=0; i<A.size(); i++)
        {
            int temp = dfs(A, 0, i, memory);
            if(temp < result)
            {
                result = temp;
            }
        }
        return result;
    }
    
    int dfs(vector<vector<int>> &A, int index,int col, vector<vector<int>> &memory)
    {
        if(index >= A.size())
        {
            return 0;
        }
        if(memory[index][col] != INF)
        {
            return memory[index][col];
        }
        int result = 0xfffffff;
        for(int i=-1; i<=1; i++)
        {
            col += i;
            if(col < 0 || col >= A[0].size())
            {
                col -= i;
                continue;
            }
            int cur = dfs(A, index + 1, col, memory);
            if(cur < result)
            {
                result = cur;
            }
            col -= i;
        }
        memory[index][col] = result + A[index][col];
        return memory[index][col];
    }
    
    int minFallingPathSum2(vector<vector<int>> &A)
    {
        if(A.size() == 0 || A[0].size() == 0)
        {
            return 0;
        }
        int result = 0xfffffff;
        for(int i=0; i<A[0].size(); i++)
        {
            int cur = helper(A, 0, i, 0);
            if(cur < result)
            {
                result = cur;
            }
        }
        
        return result;
    }
    
    //Time Limit Exceeded
    int helper(vector<vector<int>> &A, int index,int col, int sum)
    {
        if(index >= A.size())
        {
            return sum;
        }
        sum += A[index][col];
        int result = 0xfffffff;
        for(int i=-1; i<=1; i++)
        {
            col += i;
            if(col < 0 || col >= A[0].size())
            {
                col -= i;
                continue;
            }
            int cur = helper(A, index + 1, col, sum);
            if(cur < result)
            {
                result = cur;
            }
            col -= i;
        }
        
        return result;
    }
    
    //dp
    int minFallingPathSum1(vector<vector<int>> &A)
    {
        if(A.size() == 0 || A[0].size() == 0)
        {
            return 0;
        }

        for(int i=1; i<A.size(); i++)
        {
            for(int j=0; j<A[i].size(); j++)
            {
                int left = A[i-1][max(j-1, 0)];
                int right = A[i-1][min(j+1, (int)A[i].size() - 1)];
                A[i][j] += min(A[i-1][j], min(left, right));
            }
        }
        int result = INF;
        for(int i=0; i<A[0].size(); i++)
        {
            result = min(result, A[A.size()-1][i]);
        }
        return result;
    }
    
    
   //dp 复用
   int minFallingPathSum(vector<vector<int>> &A)
   {
       if(A.size() == 0 || A[0].size() == 0)
       {
           return 0;
       }
       int n = A.size(), m = A[0].size();
       int dp[2][A.size()];
       for (int i = 0; i < m; i++) {
           dp[0][i] = A[0][i];
       }
       
       // function: dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j], dp[i - 1][j + 1]) + A[i][j]
       for (int i = 1; i < n; i++) {
           for (int j = 0; j < m; j++) {
               dp[i % 2][j] = dp[(i - 1) % 2][j] + A[i][j];
               if (j - 1 >= 0) {
                   dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j - 1] + A[i][j]);
               }
                   
               if (j + 1 < A[0].size()) {
                   dp[i % 2][j] = min(dp[i % 2][j], dp[(i - 1) % 2][j + 1] + A[i][j]);
               }
           }
       }
       // answer
       int answer = INF;
       for (int i = 0; i < m; i++) {
           answer = min(answer, dp[(n - 1) % 2][i]);
       }
       return answer;
   }
    
    
    void run()
    {
        vector<vector<int>> A({{1,2,3},{4,5,6},{7,8,9}});
        cout<<this->minFallingPathSum1(A)<<endl;
    }
    
};
