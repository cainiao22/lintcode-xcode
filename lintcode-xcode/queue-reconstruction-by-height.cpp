/**
 1252. 根据身高重排队列
 中文
 English

 假设你有一个顺序被随机打乱的列表，代表了站成一列的人群。每个人被表示成一个二元组(h, k)，其中h表示他的身高，k表示站在他之前的身高高于或等于h的人数。你需要将这个队列重新排列以恢复其原有的顺序。
 样例

 样例1

 输入：
 [[7,0], [4,4], [7,1], [5,0], [6,1], [5,2]]
 输出：
 [[5,0], [7,0], [5,2], [6,1], [4,4], [7,1]]

 样例2

 输入：
 [[2,0],[1,1]]
 输出：
 [[2,0],[1,1]]

 注意事项

 总人数小于1,100。

 */


#include "CommonUtils.h"

class QueueReconstructionByHeight
{
public:
    vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
    {
        vector<vector<int>> result;
        //排序是先按大小个从高往低排，再按顺序从低往高排
        sort(people.begin(), people.end(), cmp);
        //从最高的开始，从最前的开始，排完之后cur增加
        for(int i=0; i<people.size(); i++)
        {
            cout<<people[i][0]<<'\t'<<people[i][1]<<endl;
            //插入的话是原来位置的元素向后移，当前元素插进去，原来这个位置的元素向后移
            //因为原来顺序是从高往低排的，所以插入当前元素的时候，当前元素位置前面有几个人就是它的位置
            //然后比他高的往后挪，不影响他后面那个元素。
            result.insert(result.begin() + people[i][1], people[i]);
        }
        cout<<"***************"<<endl;
        for(vector<int> item : result)
        {
            cout<<item[0]<<'\t'<<item[1]<<endl;
        }
        return result;
    }
    
    static bool cmp(vector<int> v1, vector<int> v2)
    {
        return (v1[0] > v2[0]) || (v1[0] == v2[0] && v1[1] < v2[1]);
    }
    
    void run()
    {
        vector<vector<int>> people({{7,0}, {4,4}, {7,1}, {5,0}, {6,1}, {5,2}});
        this->reconstructQueue(people);
    }
};
