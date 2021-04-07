/**
 
 切割剩余金属
 
 
 金属棒工厂的厂长拥有 n 根多余的金属棒。当地的一个承包商提出，只要所有的棒材具有相同的长度（用 saleLength 表示棒材的长度），就将金属棒工厂的剩余棒材全部购买。厂长可以通过将每根棒材切割零次或多次来增加可销售的棒材数量，但是每次切割都会产生一定的成本（用 costPerCut 表示每次切割的成本）。等所有的切割完成以后，多余的棒材将被丢弃，没有利润。金属棒工厂的厂长获得的销售总利润计算公式如下：

 totalProfit = totalUniformRods * saleLength * salePrice - totalCuts * costPerCut

 其中 totalUniformRods 是可销售的金属棒数量，salePrice 是承包商同意支付的每单位长度价格，totalCuts是需要切割棒材的次数。

 1≤n≤501 \le n \le 501≤n≤50
 1≤lengths[i]≤1041 \le lengths[i] \le 10^41≤lengths[i]≤104
 1≤salePrice,costPerCut≤1031 \le salePrice, costPerCut \le 10^31≤salePrice,costPerCut≤103
 样例

 样例 1

 输入：
 1
 10
 [30,59,110]
 输出：
 1913


 */

#include "CommonUtils.h"



class CuttingMetalSurplus
{
public:
    int maxProfit(int costPerCut, int salePrice, vector<int> &lengths)
    {
        int profit = 0;
        int maxLen = 0;
        for(int length : lengths)
        {
            maxLen = max(maxLen, length);
        }
        for(int i=1; i<=maxLen; i++)
        {
            int cut = 0, pieces = 0;
            for(int length: lengths)
            {
                int curCuts = (length - 1) / i;
                int curPiece = length / i;
                if(curCuts * salePrice * i - curPiece * costPerCut > 0)
                {
                    cut += curCuts;
                    pieces += curPiece;
                }
            }
            profit = max(profit, pieces * i * salePrice - cut * costPerCut);
        }
        return profit;
    }
    
    void run()
    {
        
    }
};
