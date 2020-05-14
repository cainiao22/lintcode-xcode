/**
 360. 滑动窗口的中位数

 给定一个包含 n 个整数的数组，和一个大小为 k 的滑动窗口,从左到右在数组中滑动这个窗口，找到数组中每个窗口内的中位数。(如果数组个数是偶数，则在该窗口排序数字后，返回第 N/2 个数字。)
 样例

 样例 1:

 输入:
 [1,2,7,8,5]
 3
 输出:
 [2,7,7]

 解释:
 最初，窗口的数组是这样的：`[ | 1,2,7 | ,8,5]` , 返回中位数 `2`;
 接着，窗口继续向前滑动一次。`[1, | 2,7,8 | ,5]`, 返回中位数 `7`;
 接着，窗口继续向前滑动一次。`[1,2, | 7,8,5 | ]`, 返回中位数 `7`;

 样例 2:

 输入:
 [1,2,3,4,5,6,7]
 4
 输出:
 [2,3,4,5]

 解释:
 最初，窗口数组是这样的：`[ | 1,2,3,4, | 5,6,7]` , 返回中位数 `2`;
 接着，窗口向前滑动一次.`[1,| 2,3,4,5 | 6,7]`,返回中位数 `3`;
 接着，窗口向前滑动一次.`[1,2, | 3,4,5,6 | 7 ]`, 返回中位数 `4`;
 接着，窗口向前滑动一次`[1,2,3,| 4,5,6,7 ]`, 返回中位数 `5`;

 挑战

 时间复杂度为 O(nlog(n))
 
 使用两个优先队列，一个大顶堆，一个小顶堆，将k个数据分两部分分别g放到两个队列中，每个队列放置一半数据
 两个队列顶部的数就是中位数，移除时候，从两个队列中移除数据，再加入新数据，然后重新平衡两个队列中的数据

 */

#include "CommonUtils.h"

class SlidingWindowMedian
{
    /**
            这两个做不到随机删除，没办法用
     */
    //大顶堆
    //priority_queue<int, vector<int>, less<int>> maxQueue;
    //小顶堆
    //priority_queue<int, vector<int>, greater<int>> minQueue;
    
    //两个列表都是从小到大排列的集合，max存放后面那一半，min存放前面那一半
    multiset<int> max, min;
public:
    vector<int> medianSlidingWindow(vector<int> &nums, int k)
    {
        vector<int> result;
        if(k == 0 || nums.size() < k)
        {
            return result;
        }
        
        for(int i=0; i<k; i++)
        {
            min.insert(nums[i]);
        }
        for(int i=0; i<k/2; i++)
        {
            max.insert(*min.rbegin());
            min.erase(min.lower_bound(*min.rbegin()));
        }
        
        for(int i=k; i<nums.size(); i++)
        {
            result.push_back(*min.rbegin());
            if(!max.empty() && max.find(nums[i-k]) != max.end())
            {
                max.erase(max.find(nums[i-k]));
                max.insert(nums[i]);
            }
            else
            {
                min.erase(min.find(nums[i-k]));
                min.insert(nums[i]);
            }
            //k等于1的时候 有一个肯定是空，做指针操作时候会找不到边界
            if(!max.empty() && !min.empty() && *max.begin() < *min.rbegin())
            {
                int temp = *max.begin();
                max.erase(max.begin());
                max.insert(*min.rbegin());
                min.erase(min.lower_bound(*min.rbegin()));
                min.insert(temp);
            }
            
        }
        result.push_back(*min.rbegin());
        return result;
    }
    
    void run()
    {
        vector<int> nums({1,2,3,4,5,6,7});
        int k = 1;
        vector<int> result = this->medianSlidingWindow(nums, k);
        cout<<result.size()<<endl;
    }
};
