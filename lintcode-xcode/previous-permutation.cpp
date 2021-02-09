/**
 
 51. 上一个排列

 给定一个整数数组来表示排列，找出其上一个排列。
 样例

 Example 1:

 Input:[1]
 Output:[1]

 Example 2:

 Input:[1,3,2,3]
 Output:[1,2,3,3]

 Example 3:

 Input:[1,2,3,4]
 Output:[4,3,2,1]

 注意事项

 排列中可能包含重复的整数

 
 */

#include "CommonUtils.h"


class PreviousPremutation
{
public:
    
    /**
     从排列的最末尾开始，找到第一个下降点，下降点的意义为这个点之前的序列无需改动。 然后,将后面的序列变为降序。 从下降点开始扫描，找到第一个比她小的数字，交换即可
     */
    vector<int> previousPermuation(vector<int> &nums)
    {
        //找第一个逆序的
        for(int i=nums.size() - 1; i>0; i--)
        {
            if(nums[i] < nums[i-1])
            {
                for(int j=i, k=nums.size()-1; j<k; j++,k--)
                {
                    nums[j] = nums[j] ^ nums[k];
                    nums[k] = nums[j] ^ nums[k];
                    nums[j] = nums[j] ^ nums[k];
                }
                int j = i;
                while(j < nums.size() && nums[j] >= nums[i-1])
                {
                    j++;
                }
                if(j < nums.size())
                {
                    nums[j] = nums[j] ^ nums[i-1];
                    nums[i-1] = nums[j] ^ nums[i-1];
                    nums[j] = nums[j] ^ nums[i-1];
                }
                return nums;
            }
        }
        
        for(int i=0, j=nums.size()-1; i<j; i++, j--)
        {
            int temp = nums[i];
            nums[i] = nums[j];
            nums[j] = temp;
        }
        
        return nums;
    }
    
    void run()
    {
        vector<int> nums({3,1,2});
        vector<int> result = this->previousPermuation(nums);
        for (int i=0; i<result.size(); i++) {
            cout<<result[i]<<'\t';
        }
        cout<<endl;
    }
    
};
