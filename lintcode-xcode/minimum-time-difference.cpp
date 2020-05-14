/**
 1184. 最小时间差
 中文
 English

 给出"小时:分钟"格式的24小时时钟点列表，找到列表中任意两个时间点之间的最小分钟差。
 样例

 例1:

 输入:
 ["23:59","00:00"]
 输出:
 1

 例2:

 输入:
 ["01:01","02:01"]
 输出:
 60

 注意事项

 1.给定列表中的时间数至少为2，不超过20000。
 2.输入时间合法，范围从00:00到23:59。

 */

#include "CommonUtils.h"

class MinimumTimeDifference
{
public:
    int findMinDifference(vector<string> &timePoints)
    {
        sort(timePoints.begin(), timePoints.end());
        int min = 0xffffff;
        for(int i=1; i<timePoints.size(); i++)
        {
            int cur = getTimeOfMinutes(timePoints[i]);
            int last = getTimeOfMinutes(timePoints[i-1]);
            int sub = cur - last;
            if(min > sub)
            {
                min = sub;
            }
        }
        
        int last = this->getTimeOfMinutes(timePoints[timePoints.size() - 1]);
        int cur = this->getTimeOfMinutes(timePoints[0]);
        int sub = cur + 24 * 60  - last;
        if(sub < min)
        {
            min = sub;
        }
        return min;
    }
    
    int getTimeOfMinutes(string time)
    {
        int hour = (time[0] - '0') * 10 + (time[1] - '0');
        int minutes = (time[3] - '0') * 10 + time[4] - '0';
        return hour * 60 + minutes;
    }
    
    void run()
    {
        vector<string> timePoints({"05:31","22:08","00:35"});
        int result = this->findMinDifference(timePoints);
        cout<<result<<endl;
    }
};
