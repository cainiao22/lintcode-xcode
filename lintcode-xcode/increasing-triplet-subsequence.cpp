/**

 1287. 递增的三元子序列
 中文
 English

 给定未排序的数组，返回是否在数组中存在递增的长度为3的子序列。

 完整的功能应为：
 如果存在i, j, k，使得arr[i] < arr[j] < arr[k]，且0 ≤ i < j < k ≤ n-1，则返回true，否则返回false。
 您的算法应该以O(n)时间复杂度和O(1)空间复杂度运行。
 样例

 样例1

 输入： [3, 2, 1, 4, 5]
 输出： true

 样例2

 输入： [5, 4, 3, 2, 1]
 输出： false

 */

#include "CommonUtils.h"


class increasing_triplet_subsequence
{
public:
    int INF = 0xfffffff;
    
    //到第i个元素的最长序列 dp[i] = max(dp[j] + 1) 相对通用
    bool increasingTripletDP(vector<int> &nums)
    {
        vector<int> dp(nums.size(), 1);
        int maxLen = 3;
        for(int i=1; i<nums.size(); i++)
        {
            for(int j=0; j<i; j++)
            {
                if(nums[i] > nums[j])
                {
                    dp[i] = max(dp[i], dp[j] + 1);
                }
                if(dp[i] >= maxLen)
                {
                    return true;
                }
            }
        }
        return false;
    }
    
    bool increasingTriplet2(vector<int> &nums)
    {
        vector<int> result(2, INF);
        for(int i=0; i<nums.size(); i++)
        {
           
            if(nums[i] <=result[0])
            {
                result[0] = nums[i];
            }
            else if(nums[i] < result[1])
            {
                result[1] = nums[i];
            }
            else{
                return true;
            }
            
        }
        
        return false;
    }
    
    bool increasingTriplet(vector<int> &nums)
    {
        vector<int> result(3, INF);
        for(int i=0; i<nums.size(); i++)
        {
            for(int j=0; j<result.size(); j++)
            {
                if(nums[i] <result[j])
                {
                    result[j] = nums[i];
                    break;
                }
                else if(nums[i] == result[j])
                {
                    break;
                }
            }
        }
        for(int i=0; i<result.size(); i++)
        {
            if(result[i] == INF)
            {
                return false;
            }
        }
        return true;
    }
    //{1,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100000000}
    //无法覆盖上面的case
    bool increasingTriplet_bug(vector<int> &nums)
    {
        stack<int> s;
        for(int i=0; i<nums.size(); i++)
        {
            if(s.empty())
            {
                s.push(nums[i]);
                continue;
            }
            while(!s.empty())
            {
                int top = s.top();
                //如果相等，不算升序
                if(top >= nums[i])
                {
                    s.pop();
                }
                else
                {
                    s.push(nums[i]);
                    break;
                }
            }
            if(s.size() >= 3)
            {
                return true;
            }
            if(s.empty())
            {
                s.push(nums[i]);
            }
        }
        while(!s.empty())
        {
            cout<<s.top()<<'\t';
            s.pop();
        }
        cout<<endl;
        return false;
    }
    
    void run()
    {
        vector<int> nums({1,0,0,0,0,0,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,100000000});
        cout<<this->increasingTriplet(nums)<<endl;
    }
};
