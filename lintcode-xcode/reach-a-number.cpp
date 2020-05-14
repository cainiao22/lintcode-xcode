/**
 797. 到达一个数字
 中文English
 你站在一个无穷数轴上的 0 位置。在位置目标上有一个目标。
 在每一个动作中，你可以向左或向右。在第n次移动中(从1开始)，你行走n步。
 返回到达目的地所需的最小步骤数。

 样例
 样例1

 输入: target = 3
 输出: 2
 解释:
 在第一步，我们从0到1。
 在第二步，我们从1到3。
 样例2

 输入: target = 2
 输出: 3
 解释:
 在第一步，我们从0到1。
 在第二个步骤中，我们从1到-1。
 在第三步，从-1到2。
 注意事项
 目标将是一个非零的整数范围[-10^9, 10^9]。
 
 */



#include "CommonUtils.h"


class ReachANumber
{
public:
    //TODO bug未考虑周全
    int reachNumber(int target)
    {
        int sum = 0;
        int current = 1;
        while(sum < target)
        {
            sum += current;
            current ++;
        }
        
        int dValue = target - sum + current - 1;
        if(dValue == 0)
        {
            return current;
        }
        int dValue2 = sum - target;
        if(dValue2 < dValue)
        {
            return current - 1 + dValue2 * 2;
        }
        return current + dValue * 2 - 2;
    }
    
    int reachNumber2(int target)
    {
        //有可能传负数，但是没关系，转换为正数就好了，正负是对称的
        target = abs(target);
        int sum = 0;
        int current = 0;
        while(sum < target)
        {
            current ++;
            sum += current;
        }
    //如果刚好达到target肯定可以，同时，如果sum和target的差值为偶数d,我们只需要让第d/2个数取反就可以达到要求
        if(sum == target || (sum - target) & 1 == 0)
        {
            return current;
        }
        
        //如果我们的和与target的差为奇数，那么我们需要揍那个偶数，然后返回第d/2个取反
        while((sum - target) & 1 == 1)
        {
            current ++;
            sum += current;
        }
        
        return current;
    }
    
    void run()
    {
        for(int i=2; i<=4; i++)
        {
            cout<<reachNumber2(i)<<endl;
        }
    }
};
