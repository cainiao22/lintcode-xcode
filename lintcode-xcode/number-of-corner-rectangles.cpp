/**
 
 853. 转角矩形个数
 中文
 English

 给定一个只含0和1的网格，寻找有多少个转角矩形。

 注意，只有转角处需要为1，并且这四个1的位置互不相同。
 样例

 样例 1:

 输入:
   [
     [1, 0, 0, 1, 0],
     [0, 0, 1, 0, 1],
     [0, 0, 0, 1, 0],
     [1, 0, 1, 0, 1]
   ]
 输出: 1
 解释: 只有一个矩形，由grid[1][2], grid[1][4], grid[3][2], grid[3][4]组成。

 样例 2:

 输入:
   [
     [1, 1, 1],
     [1, 1, 1],
     [1, 1, 1]
   ]
 输出: 9
 解释: 有四个2x2，四个2x3，和一个3x3的矩形。

 样例 3:

 输入: [[1,1,1,1]]
 输出: 0
 解释: 矩形必须有四个不同的角落。

 注意事项

     行列的个数在 [1,200][1, 200][1,200] 的范围内.
     每个方格grid[i][j]只会是 0 或 1.
     网格中1的个数不会超过6000.


 
 
 */

#include "CommonUtils.h"


class numberOfCornerRectangles
{
public:
    
    int countCornerRectangles1(vector<vector<int>> &grid)
    {
        long m = grid.size();
        long n = grid[0].size();
        int count = 0;
        for(int i=0; i<m-1; i++)
        {
            for(int j=0; j<n-1; j++)
            {
                if(grid[i][j] == 1)
                {
                    for(int k=j+1; k< n; k++)
                    {
                        if(grid[i][k] == 1)
                        {
                            for(int l=i+1; l<m; l++)
                            {
                                if(grid[l][j] == 1 && grid[l][k] == 1)
                                {
                                    count ++;
                                }
                            }
                        }
                    }
                }
            }
        }
        
        return count;
    }
    
    
    int countCornerRectangles(vector<vector<int>> &grid)
    {
        long m = grid.size();
        long n = grid[0].size();
        int dp[m][m][n];
        int count[m][m][n];
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
                if(grid[0][i] && grid[0][j])
                {
                    count[0][i][j] = 1;
                }else{
                    count[0][i][j] = 0;
                }
                dp[0][i][j] = 0;
            }
        }
        for(int i=1; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                for(int k=j+1; k<n; k++)
                {
                    if(grid[i][j]  && grid[i][k])
                    {
                        dp[i][j][k] = dp[i-1][j][k] + count[i-1][j][k];
                        count[i][j][k] = count[i-1][j][k] + 1;
                    }
                    else
                    {
                        dp[i][j][k] = dp[i-1][j][k];
                        count[i][j][k] = count[i-1][j][k];
                    }
                }
            }
        }
        int ans = 0;
        for(int i=0; i<n; i++)
        {
            for(int j=i+1; j<n; j++)
            {
               ans += dp[m-1][i][j];
            }
        }
        
        return  ans;
    }
    
    void run()
    {
        vector<vector<int>> grid = {
            {1,0,0,1,0},
            {0,0,1,0,1},
            {0,0,0,1,0},
            {1,0,1,0,1}
        };
        
        cout<<this->countCornerRectangles(grid)<<endl;
    }
};
