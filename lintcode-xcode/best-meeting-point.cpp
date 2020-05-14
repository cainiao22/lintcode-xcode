/**

 912. 最佳见面地点
 中文
 English

 有一群住在不同地方的朋友（两个或以上）想要在某地见面，要求他们去往目的地的路程和最短。现在给一个0、1组成的二维数组，1表示此地有一个人居住。使用曼哈顿距离作为计算总距离，公式为：(p1, p2) = |p2.x - p1.x| + |p2.y - p1.y|
 样例

 样例 1:

 输入:
 [[1,0,0,0,1],[0,0,0,0,0],[0,0,1,0,0]]
 输出:
 6

 解释:
 点(0, 2)是最佳见面地点，最小的路程总和为2+2+2=6，返回6。

 样例 2:

 输入:
 [[1,1,0,0,1],[1,0,1,0,0],[0,0,1,0,1]]
 输出:
 14

  竟然是求中位数，我去

 */

#include "CommonUtils.h"

class BestMeetingPoint
{
public:
    int minTotalDistance(vector<vector<int>> &grid)
    {
        vector<int> locationX, locationY;
        for(int i=0; i<grid.size(); i++)
        {
            for(int j=0; j<grid[0].size(); j++)
            {
                if(grid[i][j] == 1)
                {
                    locationX.push_back(i);
                    locationY.push_back(j);
                }
            }
        }
        
        sort(locationX.begin(), locationX.end());
        sort(locationY.begin(), locationY.end());
        
        int x = locationX[locationX.size() / 2];
        int y = locationY[locationY.size() / 2];
        
        int sum = 0;
        for(int i=0; i<locationX.size(); i++)
        {
            sum += abs(locationX[i] - x);
            sum += abs(locationY[i] - y);
        }
        return sum;
    }
    
    void run()
    {
        vector<vector<int>> grid({{1,0,0,0,1},{0,0,0,0,0},{0,0,1,0,0}});
        int result = this->minTotalDistance(grid);
        cout<<result<<endl;
    }
};
