/**
 1710. 漂亮数组
 中文
 English

 对于某些固定的 N，如果数组 A 是整数 1, 2, ..., N 组成的排列，使得：

 对于每个 i < j，都不存在 k 满足 i < k < j 使得 A[k] * 2 = A[i] + A[j]。

 那么数组 A 是漂亮数组。

 给定 N，返回任意漂亮数组 A（保证存在一个）。
 样例

 样例 1:

 输入: N = 4
 输出:[1,3,2,4]

 样例 2:

 输入: N = 5
 输出: [1,5,3,2,4]

 注意事项

 1 <= N <= 1000

 
 很巧妙的递归解法
  符合条件的奇数组和和符合条件的偶数组 组合之后肯定满足条件(1,3,2,4)
  同时数组肯定也满足如果全部元素同时加减乘某个相同的数之后，也满足条件
  所以对该数组扩容的方式是：
        数组A 各元素x2  得到一组偶数组合
        数组A 各元素x2 - 1 得到一组奇数组合
  两个数组拼接到一起 原来数组会扩大二倍 去除大于N的就是我们要的结果
 */



#include "CommonUtils.h"



class BeautifulArray
{
public:
    
    /**
       递归方式解决
     */
    vector<int> beautifulArray(int N)
    {
        vector<int> result;
        if(N == 0)
        {
            return result;
        }
        
        result.push_back(1);
        vector<int> even = beautifulArray(N / 2);
        //这里不能加1 因为当N=1时候会造成死循环
        vector<int> odd = beautifulArray((N - 1)/ 2);
        //因为odd生成方式，出现的数字是从0开始的，所以生成奇数需要变成+1
        for(int i=0; i<odd.size(); i++)
        {
            result.push_back(odd[i] * 2 + 1);
        }
        for(int i=0; i<even.size(); i++)
        {
            result.push_back(even[i] * 2);
        }
        
        return result;
    }
    
    vector<int> beautifulArray1(int N)
    {
        vector<int> result;
        if(N == 0)
        {
            return result;
        }
        result.push_back(1);
        while(result.size() < N)
        {
            //构建奇数数组 偶数数组
            vector<int> odd, even;
            for(int i=0; i<result.size(); i++)
            {
                int seed = result[i];
                //奇数数组
                if(seed * 2 - 1 <= N)
                {
                    odd.push_back(seed * 2 - 1);
                }
                //偶数数组
                if(seed * 2 <= N)
                {
                    even.push_back(seed * 2);
                }
            }
            //将两个数组组合
            result.clear();
            for(int j=0; j<odd.size(); j++)
            {
                result.push_back(odd[j]);
            }
            for(int j=0; j<even.size(); j++)
            {
                result.push_back(even[j]);
            }
        }
        
        
        return result;
    }
    
    void run()
    {
        vector<int> result = this->beautifulArray(4);
        for(int i=0; i<result.size(); i++)
        {
            cout<<result[i]<<'\t';
        }
        
        cout<<endl;
    }
};
