/**

 给定一个整数 n, 返回从 1 到 n 的字典顺序。
 样例

 样例1:

 输入: 13
 输出 : [1,10,11,12,13,2,3,4,5,6,7,8,9]

 样例2:

 输入: 10
 输出 : [1,10,2,3,4,5,6,7,8,9]

 注意事项

 请尽可能的优化算法的时间复杂度和空间复杂度。 输入的数据 n 小于等于 5,000,000。
 */



#include "CommonUtils.h"


class LexicographicalNumbers
{
    int TEN = 10;
public:
    vector<int> lexicalOrder(int n)
    {
        vector<int> result;
        for(int i=1; i<TEN; i++)
        {
            if(i > n)
            {
                break;
            }
            lexicalOrder(i, n, result);
        }
        return result;
    }
    
    void lexicalOrder(int start, int max, vector<int> &result)
    {
        if(start > max)
        {
            return;
        }
        result.push_back(start);
        for(int i=0; i<TEN; i++)
        {
            int newStart = start * 10+i;
            if(newStart > max)
            {
                break;
            }
            lexicalOrder(newStart, max, result);
        }
    }
    
    
    vector<int> lexicalOrder_better(int n)
    {
        int curr = 1;
        vector<int> result;
        //限制总数
        for(int i=1; i<=n; i++)
        {
            result.push_back(curr);
            if(curr * 10 <= n)
            {
                curr *= 10;
            }
            else if(curr % 10 < 9 && curr + 1 <= n)
            {
                curr ++;
            }
            else
            {
                /**
                 while ((curr / 10) % 10 == 9)
                 {
                    curr /= 10;
                 }
                 curr = curr / 10 + 1;
                 */
                curr /= 10;
                //TODO 有问题和上面那段代码有点差别，测试不通过
                while(curr > i && curr % 10 == 9)
                {
                    curr /= 10;
                }
                curr ++;
            }
        }
        
        return result;
    }
    
    
    void run()
    {
        vector<int> result = this->lexicalOrder_better(20);
        for(int i=0; i<result.size(); i++)
        {
            cout<<result[i]<<'\t';
        }
        
        cout<<endl;
    }
};
