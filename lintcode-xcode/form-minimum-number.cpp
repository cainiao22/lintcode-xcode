/**
 给定一个仅包含I和D的模式串str。 I代表相邻项增加，D代表相邻项减少。 设计一种算法，返回符合该模式且字典序最小的字符串。字符串只包含1到9且不能重复
 
 样例

 例1:

 输入:
 "D"
 输出:
 "21"
 解释:
 2>1

 例2:

 输入:
 "II"
 输出:
 "123"
 解释:
 1<2<3

 例3:

 输入:
 "DIDI"
 输出:
 "21435"

 例4:

 输入:
 "DDIDDIID"
 输出:
 "321654798"
 */

#include "CommonUtils.h"


class FormMinimNumber
{
public:
    string formMinimumNumber(string &str)
    {
        vector<int> nums(str.size() + 1);
        string ans;
        nums[0] = 1;
        int minNum = 1;
        for(int i=0; i<str.size(); i++)
        {
            if(str[i] == 'I')
            {
                nums[i+1] = nums[i] + 1;
            }
            else
            {
                nums[i+1] = nums[i] - 1;
                minNum = min(minNum, nums[i+1]);
            }
        }
        int deta = 1 - minNum;
        for(int i=0; i<nums.size(); i++)
        {
            ans.append(nums[i] + deta);
        }
        
        return  ans;
    }
    
    
    void run()
    {
        
    }
};
