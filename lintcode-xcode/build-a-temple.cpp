
/**
 1669. 建庙

 你是一名建造寺庙的建筑师。
 寺庙的柱子是由木头制成。每根柱子必须是一jie完整的木头而且不能是被连接得到的。
 给出n段具有不同长度的木头。你的寺庙有m根高度严格相同的柱子。那么你寺庙最大高度是多少。(m根柱子的高度)
 样例

 样例 1:

 输入：m = 3, [2, 3, 4]
 输出：2
 解释：选择长度为2的木头并且长度为4的木头被分为两段长度为2的木头。

 样例 2:

 输入：m = 3, [2, 10]
 输出：3
 解释：长度为10的木头分为3段长度为3的木头和一根长度为1的木头。

 注意事项

     1<=n<=100000
     1<=m<=100000


 */

#include "CommonUtils.h"


class buildATemple
{
public:
    
    int buildTemple(int m, vector<int> &woods)
    {
        int ans = 0;
        int mod = 0;
        for(int i=0; i<woods.size(); i++)
        {
            ans += woods[i] / m;
            mod += woods[i] % m;
            ans += mod / m;
            mod = mod % m;
            
        }
    
        int min = 0;
        int n = 0;
        while(min < ans - 1)
        {
            int mid = (ans + min) / 2;
            n = 0;
            for(int i=0; i<woods.size() && n < m; i++)
            {
                n += woods[i] / mid;
            }
            if(n >= m)
            {
                min = mid;
            }
            else
            {
                ans = mid - 1;
            }
        }
        
        n = 0;
        for(int i=0; i<woods.size() && n < m; i++)
        {
            n += woods[i] / ans;
        }
        if(n >= m)
        {
            return ans;
        }
        return min;
    }
    
    void run()
    {
        vector<int> woods({2,10});
        cout<<this->buildTemple(3, woods)<<endl;
    }
};
