/**
 1037. 全局和局部逆序数
 中文English
 给定一个[0, 1, ...N - 1]的排列A，其中N是A的长度.

 全局逆序数是指满足0 <= i < j < N 且 A[i] > A[j]的数量.

 局部逆序数是指满足0 <= i < N 且 A[i] > A[i+1]的数量.

 如果全局逆序数和局部逆序数相等，返回true，否则返回false.

 样例
 样例 1:

 输入: [0, 1, 2]
 输出: true
 解释: 没有全局逆序, 没有局部逆序.
 样例 2:

 输入: [1, 2, 0]
 输出: false
 解释: 有两个全局逆序, 一个局部逆序.
 注意事项
 A 是[0, 1, ..., A.length - 1]的一个排列.
 A 的长度范围为 [1, 5000].
 该题目时间限制比较严格.
 */


#include "CommonUtils.h"

class GlobalAndLocalInversions
{
public:
    bool isIdealPermutation(vector<int> &A)
    {
        int global[A.size()];
        memset(global, 0, sizeof(global));
        int part[A.size()];
        memset(part, 0, sizeof(part));
        for(int i=0; i<A.size(); i++)
        {
            if(i > 0 && A[i] < A[i-1])
            {
                part[i] = part[i-1] + 1;
            }
            for(int j=i-1; j>=0; j--)
            {
                if(A[i] < A[j])
                {
                    global[i] += global[j] + 1;
                }
            }
        }
        
        int partSum = 0, globalSum = 0;
        for(int i=0; i<A.size(); i++)
        {
            partSum += part[i];
            globalSum += global[i];
        }
        
        for(int i=0; i<A.size(); i++)
        {
            cout<<"part["<<i<<"]="<<part[i]<<endl;
            cout<<"global["<<i<<"]="<<global[i]<<endl;
        }
        
        cout<<partSum<<'\t'<<globalSum<<endl;
        return partSum == globalSum;
    }
    
    /**
     ·一种f更加优化的写法
     这道题目表述明确，问题清晰，其解法也有很多种。这里我们介绍一种在时间和空间上高效，同时便于理解，亦可扩展的方法。
     2. 首先思考全局逆序数和局部逆序数的定义，不管是哪种逆序数，都是这一对元素大小颠倒。而且发现，局部逆序数一定是全局逆序数，而全局逆序数不一定是局部逆序数，当且仅当全局逆序数的i和j相差大于1时，这就只是一组全局逆序数，但不是局部逆序数。
     3. 进而，想返回true，对于任意的i，A[0]到A[i - 2]（如果i >= 2）必须都要小于A[i]，A[i + 2]到A[N - 1]（如果i <= N - 3）都必须要大于A[i]。否则，一定返回false。
     4. 更进一步，我们只用检查所有的i，使得A[0]到A[i - 2]是否都小于A[i]即可。而且A[i]的右侧不用检查。这是因为如果A[i]右侧存在比A[i]小的数，记它为A[k]，则在以后检查A[k]的左侧时，就能检查出A[i]存在问题。
     5. 所以，我们只需要初始化i为2，不断自增i，同时记录A[0]到A[i - 2]的最大值max_value，并保证max_value不大于A[i]，否则直接返回false。在一次遍历完之后，直接返回true即可。
     6. 复杂度分析：
     1. 时间复杂度：O(N)，这里只需要一次遍历数组A。
     2. 空间复杂度：O(1)，只需要max_value，不断更新即可。
     7. 一些扩展：该方法的适用范围其实强于这道题，因为这道题限定了数组元素一定是[0, 1, 2, ... N - 1]。但是如果使用该方法，我们并不需要这种限制。不过这个限制带给我们的额外好处是可以初始化max_value为0，因为不存在比0小的元素。
     */
    bool isIdealPermutation2(vector<int> &A)
    {
        //对于前两个数字而言 局部和全局数量是一样的 所以不需要判断
        int maxValue = 0;
        for(int i=2; i<A.size(); i++)
        {
            maxValue = A[i-2] > maxValue ? A[i-2] : maxValue;
            if(A[i] < maxValue)
            {
                return false;
            }
        }
        
        return true;
    }
    
    void run()
    {
        vector<int> A({0,1,2});
        cout<<this->isIdealPermutation(A)<<endl;
    }
};
