/**
 458. 目标最后位置
 中文
 English

 给一个升序数组，找到 target 最后一次出现的位置，如果没出现过返回 -1
 样例

 样例 1：

 输入：nums = [1,2,2,4,5,5], target = 2
 输出：2

 样例 2：

 输入：nums = [1,2,2,4,5,5], target = 6
 输出：-1


 */

#include "CommonUtils.h"

class LastPositionOfTarget
{
public:
    int lastPosition(vector<int> &nums, int target)
    {
        if(nums.size() == 0 || nums[0] > target || nums[nums.size() - 1] < target)
        {
            return -1;
        }
        int start = 0, end = nums.size() - 1;
        while(start < end)
        {
            int mid = (start + end) / 2;
            if(nums[mid] > target)
            {
                end = mid - 1;
            }
            else if(nums[mid] <= target)
            {
                start = mid + 1;
            }
        }
        if(nums[start] == target)
        {
            return start;
        }
        if(nums[start - 1] == target)
        {
            return start - 1;
        }
        
        return -1;
    }
    
    void run()
    {
        vector<int> nums({1,2,2,2,2,2});
        int target = 2;
        cout<<this->lastPosition(nums, target)<<endl;
    }
};
