/***
 我们把数组 A 中符合下列属性的任意连续子数组 B 称为 “山脉”：

     B.length >= 3
     存在 0 < i < B.length - 1 使得 B[0] < B[1] < ... B[i-1] < B[i] > B[i+1] > ... > B[B.length - 1]
     （注意：B 可以是 A 的任意子数组，包括整个数组 A。）

 给出一个整数数组 A，返回最长 “山脉” 的长度。

 如果不含有 “山脉” 则返回 0。
 样例

 示例 1:

 输入: [2,1,4,7,3,2,5]
 输出: 5
 解释: 最长的 “山脉” 是 [1,4,7,3,2]，长度为 5。

 示例 2:

 输入: [2,2,2]
 输出: 0
 解释: 不含 “山脉”。

 挑战

     可以只通过一次遍历完成吗？
     可以使用O(1)的空间吗？

 注意事项

     0 <= A.length <= 10000
     0 <= A[i] <= 10000

 */

#include "CommonUtils.h"

class LongestMountainInArray
{
public:
    int longestMountain1(vector<int> &A) {
        if(A.size() <= 1)
        {
            return 0;
        }
        int maxLength = 0;
        int curLength = 0;
        bool up = false;
        bool pre = false;
        for(int i=0; i<A.size(); i++)
        {
            if(i == 0)
            {
                up = A[i+1] > A[i];
                curLength ++;
                continue;
            }
            if(up)
            {
                if(A[i] > A[i-1])
                {
                    curLength ++;
                    continue;
                }
                if(A[i] == A[i-1])
                {
                    //maxLength = curLength > maxLength ? curLength : maxLength;
                    curLength = 1;
                    continue;
                }
                if(A[i] < A[i-1])
                {
                    pre = up;
                    up = !up;
                    curLength ++;
                    continue;
                }
            }
            
            if(!up)
            {
                if(A[i] < A[i-1])
                {
                    curLength ++;
                    continue;
                }
                if(A[i] == A[i-1])
                {
                    maxLength = curLength > maxLength ? curLength : maxLength;
                    curLength = 1;
                    continue;
                }
                if(A[i] > A[i-1])
                {
                    up = !up;
                    if(pre)
                    {
                        maxLength = curLength > maxLength ? curLength : maxLength;
                    }
                    curLength = 2;
                }
            }
            
        }
        if(!up && pre)
        {
            maxLength = curLength > maxLength ? curLength : maxLength;
        }
        return maxLength;
    }
    
    /**
     这个要比上面那个巧妙的多
     */
    int longestMountain(vector<int> A)
    {
        int up = 0, down = 0, result = 0;
        //从后往前比较，比较优雅
        for(int i=1; i<A.size(); i++)
        {
            if((down > 0 && A[i] > A[i-1]) || A[i] == A[i-1])
            {
                up = down = 0;
            }
            if(A[i] > A[i-1])
            {
                up ++;
            }
            if(A[i] < A[i-1])
            {
                down ++;
            }
            
            if(up && down && up + down + 1> result)
            {
                result = up + down + 1;
            }
        }
        
        return result;
    }
    
    void run()
    {
        vector<int> A ({2,1,4,7,3,2,5});
        int longest = this->longestMountain(A);
        cout<<longest<<endl;
    }
};
