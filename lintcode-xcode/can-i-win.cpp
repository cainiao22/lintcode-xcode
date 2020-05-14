/**
 985. 我能赢吗
 中文
 English

 在 "100 game" 中, 两位玩家交替使用 1 到 10 的任意一个整数加到一个和中, 谁加完之后, 和达到或者超过了 100 就获胜.

 如果我们改变规则, 玩家不能重复使用已经使用过的整数呢？

 举个例子, 两个玩家可以轮流从一个共同的数字池 (里面的整数为 1 到 15) 中拿出整数, 拿出之后不放回, 直到某个玩家拿出一个数字之后, 已经拿出的数字之和达到或者超过了 100, 该玩家获胜.

 给定两个整数 maxChoosableInteger 和 desiredTotal, 表示刚开始数字池中有 1, 2, 3, ..., maxChoosableInteger 这些数字, 获胜的目标和是 desiredTotal.

 判断先手玩家是否必胜, 假设两个玩家都用了最佳策略.
 样例

 样例 1:

 输入: maxChoosableInteger = 10, desiredTotal = 11
 输出: false
 解释:
     无论第一个玩家怎么选都会输.
     如果他没选 10, 那么第二个玩家选择 10 就可以取得胜利.
     如果他选了 10, 那么第二个玩家可以选择任意一个数取得胜利.

 样例 2:

 输入: maxChoosableInteger = 10, desiredTotal = 10
 输出: true
 解释: 第一个玩家直接选择 10 就可以取得胜利.

 注意事项

     maxChoosableInteger <= 20
     desiredTotal <= 300


 */

#include "CommonUtils.h"


class CanIWin
{
public:
    bool pool[20];
    //超时了 需要做优化 一般使用map存储状态，但是当前的pool状态不太好存储，
    //可以考虑将pool数组换成二进制
    bool canIWin(int maxChoosableInteger, int desiredTotal)
    {
        if(desiredTotal <= 0)
        {
            return false;
        }
        for(int i=maxChoosableInteger - 1; i>=0; i--)
        {
            if(!pool[i])
            {
                pool[i] = true;
                if(!canYouWin(maxChoosableInteger, desiredTotal - i - 1))
                {
                    pool[i] = false;
                    return true;
                }
                pool[i] = false;
            }
        }
        
        return false;
    }
                        
    bool canYouWin(int maxChoosableInteger, int desiredTotal)
    {
        if(desiredTotal <= 0)
        {
            return false;
        }
        for(int i=maxChoosableInteger - 1; i>=0; i--)
        {
            if(!pool[i])
            {
                pool[i] = true;
                if(!canIWin(maxChoosableInteger, desiredTotal - i - 1))
                {
                    pool[i] = false;
                    return true;
                }
                pool[i] = false;
            }
        }
        
        return false;
    }
    
    bool canIWin2(int maxChoosableInteger, int desiredTotal)
    {
        map<int, bool> memory;
        if((maxChoosableInteger + 1) * maxChoosableInteger / 2 < desiredTotal)
        {
            return false;
        }
        if(maxChoosableInteger >= desiredTotal)
        {
            return true;
        }
        return canWin(maxChoosableInteger, desiredTotal, 0, memory);
    }
    //数位压缩
    bool canWin(int maxChoosableInteger, int desiredTotal,
                int used, map<int, bool>& memory)
    {
        if(memory.count(used)) return memory[used];
        for(int i=1; i<=maxChoosableInteger; i++)
        {
            int current = 1 << (i - 1);
            if((used & current) == 0)
            {
                if(i >= desiredTotal)
                {
                    return true;
                }
                //如果我想赢，必须让对方返回false
                if(!canWin(maxChoosableInteger, desiredTotal - i, used | current, memory))
                {
                    memory[used] = true;
                    return true;
                }
            }
        }
        
        memory[used] = false;
        return false;
    }
    
    
    void run()
    {
        int maxChoosableInteger = 20;
        int desiredTotal = 300;
        cout<<this->canIWin2(maxChoosableInteger, desiredTotal)<<endl;
    }
};
