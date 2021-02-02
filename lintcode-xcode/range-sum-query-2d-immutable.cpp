/**

 665. 平面范围求和 -不可变矩阵

 给一 二维矩阵,计算由左上角 (row1, col1) 和右下角 (row2, col2) 划定的矩形内元素和.
 样例

 样例1

 输入：
 [[3,0,1,4,2],[5,6,3,2,1],[1,2,0,1,5],[4,1,0,1,7],[1,0,3,0,5]]
 sumRegion(2, 1, 4, 3)
 sumRegion(1, 1, 2, 2)
 sumRegion(1, 2, 2, 4)
 输出：
 8
 11
 12
 解释：
 给出矩阵
 [
   [3, 0, 1, 4, 2],
   [5, 6, 3, 2, 1],
   [1, 2, 0, 1, 5],
   [4, 1, 0, 1, 7],
   [1, 0, 3, 0, 5]
 ]
 sumRegion(2, 1, 4, 3) = 2 + 0 + 1 + 1 + 0 + 1 + 0 + 3 + 0 = 8
 sumRegion(1, 1, 2, 2) = 6 + 3 + 2 + 0 = 11
 sumRegion(1, 2, 2, 4) = 3 + 2 + 1 + 0 + 1 + 5 = 12

 样例2

 输入：
 [[3,0],[5,6]]
 sumRegion(0, 0, 0, 1)
 sumRegion(0, 0, 1, 1)
 输出：
 3
 14
 解释：
 给出矩阵
 [
   [3, 0],
   [5, 6]
 ]
 sumRegion(0, 0, 0, 1) = 3 + 0 = 3
 sumRegion(0, 0, 1, 1) = 3 + 0 + 5 + 6 = 14

 注意事项

     你可以假设矩阵不变
     对函数 sumRegion 的调用次数有很多次
     你可以假设 row1 ≤ row2 并且 col1 ≤ col2


 
 */

#include "CommonUtils.h"

//前缀和解法
class NumMatrix {
public:
    vector<vector<int>> sum;
    NumMatrix(vector<vector<int>> matrix)
    {
        for(int i=0; i<matrix.size(); i++)
        {
            vector<int> item;
            item.push_back(0);
            for(int j=0; j<matrix[0].size(); j++)
            {
                int front = item.at(item.size() - 1);
                item.push_back(front + matrix[i][j]);
            }
            sum.push_back(item);
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        int result = 0;
        for(int i=row1; i<=row2; i++)
        {
            result += sum[i][col2+1] - sum[i][col1];
        }
        
        return result;
    }
};

//dp解法
class NumMatrixDP {
public:
    vector<vector<int>> sum;
    NumMatrixDP(vector<vector<int>> matrix)
    {
        vector<int> zero(matrix[0].size() + 1);
        sum.push_back(zero);
        for(int i=0; i<matrix.size(); i++)
        {
            vector<int> item(matrix[0].size() + 1);
            item.push_back(0);
            sum.push_back(item);
            for(int j=0; j<matrix[0].size(); j++)
            {
                sum[i+1][j+1] = sum[i+1][j] + sum[i][j+1] - sum[i][j] + matrix[i][j];
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) {
        return sum[row2 + 1][col2 + 1] - sum[row2+1][col1] - sum[row1][col2+1] + sum[row1][col1];
    }
};


//二维树状数组解法
class NumMatrixTreeArray {
public:
    vector<vector<int>> sum;
    long hegiht;
    long width;
    NumMatrixTreeArray(vector<vector<int>> matrix)
    {
        this->hegiht = matrix.size() + 1;
        this->width = matrix[0].size() + 1;
        vector<int> zero(matrix[0].size() + 1);
        sum.push_back(zero);
        for(int i=1; i<hegiht; i++)
        {
            vector<int> item(matrix[0].size() + 1);
            item.push_back(0);
            sum.push_back(item);
        }
        for(int i=0; i<matrix.size(); i++)
        {
            for(int j=0; j<matrix[0].size(); j++)
            {
                add(i, j, matrix[i][j]);
            }
        }
    }
    
    void add(int x, int y, int value)
    {
        for(int i=x+1; i< hegiht; i=i+lowbit(i))
        {
            for(int j=y+1; j<width; j= j+lowbit(j))
            {
                sum[i][j] += value;
            }
        }
    }
    
    int query(int x, int y)
    {
        int result = 0;
        for(int i=x; i>0; i=i-lowbit(i))
        {
            for(int j=y; j>0; j=j-lowbit(j))
            {
                result += sum[i][j];
            }
        }
        
        return result;
    }
    
    int lowbit(int x)
    {
        return x & -x;
    }
    
    int sumRegion(int row1, int col1, int row2, int col2)
    {
       return query(row2+1, col2+1) - query(row2+1, col1)
            - query(row1, col2+1) + query(row1, col1);
    }
};


class RangeSumQuery2dImmutable
{
public:
    
    
    void run()
    {
        vector<vector<int>> matrix({{3,0},{5,6}});
        NumMatrixTreeArray ma(matrix);
        cout<<ma.sumRegion(0, 0, 0, 1)<<endl;
        cout<<ma.sumRegion(0, 0, 1, 1)<<endl;
    }
};


