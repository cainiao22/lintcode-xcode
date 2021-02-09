/**
 
 84. 落单的数 III
 
 给出2*n + 2个的数字，除其中两个数字之外其他每个数字均出现两次，找到这两个数字。
 样例

 Example 1:
     Input:  [1,2,2,3,4,4,5,3]
     Output:  [1,5]

 Example 2:
     Input: [1,1,2,3,4,4]
     Output:  [2,3]
     

 挑战

 O(n)时间复杂度，O(1)的额外空间复杂度
 
 
 利用异或运算。 假设两个落单数字是 A、B 2∗n+2

 个数字异或，会得到两个仅出现一次的数字的异或结果：xor = A^B。

 其中我们取出xor中任何一位1，这里取最低位的1。 这个1一定是A和B中对应位上一个是1一个是0。 所以可以将所有数字分成两类，一类是该位是1的，一类是该位是0的。 分别异或起来就得到A和B了。两类数一定都是奇数个，多出来的一个分别就是A、B
 */

#include "CommonUtils.h"


class SingleNumberIII
{
public:
    
    vector<int> singleNumberIII(vector<int> &A)
    {
        int x = 0,  y = 0;
        for(int i=0; i<A.size(); i++)
        {
            x = x ^ A[i];
        }
        long a = ((x ^ (x - 1)) + 1) >> 1;
        x = 0;
        for(int i=0; i<A.size(); i++)
        {
            if((A[i] & a) != 0)
            {
                x = x ^ A[i];
            }
            else
            {
                y = y ^ A[i];
            }
        }
        
        return vector<int>({x, y});
    }
    
    void run()
    {
        vector<int> A({1,1,2,3,4,4});
        
    }
};
