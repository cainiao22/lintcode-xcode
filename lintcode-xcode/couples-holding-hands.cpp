/**
 1043. 夫妻手牵手
 中文English
 N对夫妇坐在2N个排成一排的座位上. 现求最小的交换数量，使每对夫妇并坐一起，他们可以手牵着手。

 一次交换可选择任何两个人交换座位。

 人和座位由从0到2N-1的整数表示，夫妻按顺序编号，第一对是(0,1)，第二对是(2,3)，以此类推，最后一对是(2N-2,2N-1)。

 初始座位由row [i]给出，表示坐在第i座位的人的编号。

 样例
 样例 1:

 输入: row = [0, 2, 1, 3]
 输出: 1

 解释: 只需交换row[1]的人和row[2]的人即可.
 样例 2:

 输入: row = [3, 2, 0, 1]
 输出: 0

 解释: 每一对夫妇已经并坐一起.
 注意事项
 1.len(row) 是偶数且范围为 [4, 60].
 2.row 一定是[0, 1...len(row)-1]的一个排列.
 */

#include "CommonUtils.h"

class CouplesHoldingHands
{
public:
    /**
        贪心算法，如果发现当前不匹配，去找和他匹配的然后两个交换，直到最后
     */
    int minSwapsCouples(vector<int> &row)
    {
        int result = 0;
        for(int i=0; i<row.size(); i+= 2)
        {
            if(isCouple(row[i], row[i+1]))
            {
                continue;
            }
            result ++;
            for(int j=i+2; j<row.size(); j++)
            {
                if(isCouple(row[i], row[j]))
                {
                    row[j] = row[i+1];
                    row[i+1] = row[i] ^ 1;
                    break;
                }
            }
        }
               
        return result;
    }
    bool isCouple(int a1, int a2)
    {
        //如果是偶数，w异或相当于加了1，如果是奇数，异或相当于减了1
        return (a1 ^ 1) == a2;
    }
    
    //并查集
    int minSwapsCouples2(vector<int> &row)
    {
        int N = row.size() / 2;
        int cnt = 0;
        int root[N];
        for(int i=0; i<N; i++)
        {
            root[i] = -1;
        }
        for(int i=0; i<row.size(); i+=2)
        {
            int p1 = find(root, row[i]);
            int p2 = find(root, row[i+1]);
            if(p1 != p2)
            {
                if(p1 < p2)
                {
                    root[p2] = p1;
                }
                else
                {
                    root[p1] = p2;
                }
                cnt ++;
            }
        }
        
        return cnt;
    }
    
    int find(int* root, int target)
    {
        int parent = target / 2;
        while(root[parent] != -1)
        {
            parent = root[parent];
        }
        
        return parent;
    }
                        
    
    void run()
    {
        vector<int> row({0, 2, 1, 3});
        cout<<this->minSwapsCouples2(row)<<endl;
    }
};
