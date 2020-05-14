/**
 一个神奇字符串S仅包含'1'和'2'，并遵守以下规则：

 字符串S是神奇的，因为连接字符'1'和'2'的连续出现次数会产生字符串S本身。

 字符串S的前几个元素如下：S = “1221121221221121122 ......”

 如果我们将S中的连续'1'和'2'分组，它将是：

 1 22 11 2 1 22 1 22 11 2 11 22 ......

 并且每组中出现'1'或'2'的情况是：

 1 2 2 1 1 2 1 2 2 1 2 2 ......

 您可以看到上面的出现序列是S本身。

 给定一个整数N作为输入，返回神奇字符串S中前N个数字中的'1'的个数。

 N不会超过100,000。
 您在真实的面试中是否遇到过这个题？
 样例

 例1:

 输入: 6
 输出: 3
 说明：神奇字符串S的前6个元素是“12211”，它包含3个1，所以返回3。

 例2:

 输入: 3
 输出: 1
 说明：神奇字符串S的前3个元素是“122”，它包含1个1，所以返回1。


 */


#include "CommonUtils.h"

class MagicalString
{
public:
    //双指针 + 归纳法
    int magicalString(int n)
    {
        if(n == 0)
        {
            return 0;
        }
        if(n <= 3)
        {
            return 1;
        }
        int result = 1;
        int a[n];
        a[0] = 1;
        a[1] = 2;
        a[2] = 2;
        //下一个需要设置的值
        int next = 1;
        //连续出现次数那条数组的位置
        int head = 2;
        //S本身下一个的位置
        int tail = 3;
        while(tail < n)
        {
            for(int i=0; i<a[head]; i++)
            {
                a[tail] = next;
                if(next == 1)
                {
                    result ++;
                }
                tail ++;
            }
            next = next ^ 3;
            head ++;
        }
        
        return result;
    }
    
    void run()
    {
        for(int i=1; i<20; i++)
        {
            cout<<i<<':'<<this->magicalString(i)<<endl;
        }
    }
};
