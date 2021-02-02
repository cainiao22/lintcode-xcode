/**
 
 高点击诱导区域
 
 描述

 在一个二维矩阵上，每一个点都是一个 000 到 101010 之间的像素值，像素值都是整数。
 我们将大于像素阈值 pixelThresholdpixelThresholdpixelThreshold 的点称为高点击诱导点。
 由相连的高点击诱导点组成的区域的面积大于面积阈值 areaThresholdareaThresholdareaThreshold 的区域称为高点击诱导区域。
 如果两个点上下或左右相邻，则认为这两个点是相连的。
 请统计这个二维矩阵中高点击诱导区域的个数。

 矩阵的长 nnn，宽 mmm 满足 1≤n,m≤3001 \le n, m \le 3001≤n,m≤300.
 矩阵中的值 0≤matrix[x][y]≤100 \le matrix[x][y] \le 100≤matrix[x][y]≤10
 0≤pixelThreshold≤100 \le pixelThreshold \le 100≤pixelThreshold≤10
 0≤areaThreshold≤n∗m0 \le areaThreshold \le n * m0≤areaThreshold≤n∗m
 您在真实的面试中是否遇到过这个题？
 说明

 样例中有三个由高点击诱导点组成的区域：

     [(0, 0)]
     [(0, 2), (1, 2)]
     [(2, 0), (2, 1)]

 其中有两个区域的面积大于 111。
 样例

 样例

 输入：
 matrix = [[6,2,8],[1,3,7],[6,9,5]]
 pixedThreshold = 5
 areaThreshold = 1

 输出：
 2
 
 */

#include "CommonUtils.h"


class HighClickInductionArea
{
public:
    
    long m, n;
    
    int direction[2][2]{{-1, 0}/*,{-1, -1}*/, {0,-1}/*, {-1,1}*/};
    
    //又是并查集
    int highClickAreaCount(vector<vector<int>> &matrix, int pixelThreshold, int areaThreshold)
    {
        this->m = matrix.size();
        this->n = matrix[0].size();
        vector<vector<long>> parent(m);
        vector<vector<long>> count(m);
        for(int i=0; i<m; i++)
        {
            parent[i] = vector<long>(n);
            count[i] = vector<long>(n);
        }
        
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                parent[i][j] = getIndex(i, j);
                count[i][j] = 0;
            }
        }
        
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(matrix[i][j] > pixelThreshold)
                {
                    count[i][j] = 1;
                    for(int k=0; k<2; k++)
                    {
                        int x = i + direction[k][0];
                        int y = j + direction[k][1];
                        if(x >= 0 && x < m && y >= 0 && y <n && matrix[x][y] > pixelThreshold)
                        {
                            join(getParent(i, j, parent), getParent(x, y, parent), parent, count);
                        }
                    }
                }
            }
            
        }
        
        int result = 0;
        for(int i=0; i<m; i++)
        {
            for(int j=0; j<n; j++)
            {
                if(matrix[i][j] > pixelThreshold && count[i][j] >= areaThreshold && getIndex(i, j) == getParent(i, j, parent))
                {
                    result ++;
                }
            }
        }
        return result;
    }
    
    long getIndex(int i, int j)
    {
        return this->n * i + j;
    }
    
    void join(long x, long y, vector<vector<long>> &parent, vector<vector<long>> &count)
    {
        if(x < y)
        {
            parent[y / n][y % n] = x;
            count[x / n][x % n] += count[y / n][y % n];
        }
        else if(x > y)
        {
            parent[x / n][x % n] = y;
            count[y / n][y % n] += count[x / n][x % n];
        }
    }
    
    
    long getParent(int i, int j, vector<vector<long>> &parent)
    {
        if(parent[i][j] == getIndex(i, j))
        {
            return parent[i][j];
        }
        int x = parent[i][j] / n;
        int y = parent[i][j] % n;
        long parentId = getIndex(x, y);
        parent[i][j] = parentId;
        return parentId;
    }
    
    void run()
    {
        vector<vector<int>> matrix( {{6,2,8},
                                    {1,3,7},
                                    {6,9,5}});
        cout<<this->highClickAreaCount(matrix, 5, 1)<<endl;
    }
};
