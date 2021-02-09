
/**
 下一个排列 · Next Permutation
 
 给定一个整数数组来表示排列，找出其之后的一个排列
 
 样例

 Example 1:

 Input:[1]
 Output:[1]

 Example 2:

 Input:[1,3,2,3]
 Output:[1,3,3,2]

 Example 3:

 Input:[4,3,2,1]
 Output:[1,2,3,4]


 */

#include "CommonUtils.h"


class NextPermutation
{
public:
    
    //从最后一个位置开始，找到一个上升点，上升点之前的无需改动。 然后，翻转上升点之后的降序。 在降序里，找到第一个比上升点大的，交换位置
    vector<int> nextPermutation(vector<int> &nums)
    {
        for(int i=nums.size()-1; i>=1; i--)
        {
            if(nums[i] > nums[i-1])
            {
                for(int j=i, k=nums.size()-1; j<k; j++,k--)
                {
                    nums[j] = nums[j] ^ nums[k];
                    nums[k] = nums[j] ^ nums[k];
                    nums[j] = nums[j] ^ nums[k];
                }
                
                for(int j=i; j<nums.size(); j++)
                {
                    if(nums[i-1] < nums[j])
                    {
                        nums[j] = nums[j] ^ nums[i-1];
                        nums[i-1] = nums[j] ^ nums[i-1];
                        nums[j] = nums[j] ^ nums[i-1];
                        break;
                    }
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
        vector<int> nums({1,3,2});
        vector<int> result = this->nextPermutation(nums);
        for (int i=0; i<result.size(); i++) {
            cout<<result[i]<<'\t';
        }
        cout<<endl;
    }
};
