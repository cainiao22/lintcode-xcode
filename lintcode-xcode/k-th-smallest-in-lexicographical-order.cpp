/**
 
 239. 字典序的第K小数字

 给定整数n和k，找到按字典序排序的第k个最小整数，范围从1到n。
 样例

 样例 1:

 输入：200,18
 输出：114
 解释：1,10,100,101,102,103,104,105,106,107,108,109,11,110,111,112,113,114，第十八个是114。

 样例 2:

 输入：13，2
 输出：10
 解释：按字典序排列顺序为 [1, 10, 11, 12, 13, 2, 3, 4, 5, 6, 7, 8, 9], 所以第二小的数字为10。

 注意事项

 1 ≤ k ≤ n ≤ 1e9.

 我们可以从1到100，慢慢地将数字一个一个地插入到它们该插入的地方，以此来查找其规律之所在。
 从1开始，1，2，3，4，5，6，7，8，9
 从10开始，1，10…19，2，3，4，5，6，7，8，9
 从20开始，1，10…19，2，20…29，3，4，5，6，7，8，9
 以此类推，所有的两位数，都插入了到与他们10位数相等的个位数后面。

 再让我们来看看百位数如何插入
 从100开始，1，10,100-109,11,110-119,12,120-129…2，21-29…
 从200开始，1，10,100-109…2,20,200-209，21,210-219…3，31-39…
 以此类推，所有的三位数，都插入了到与他们百位至十位数相等的十位数后面。

 这里我们就已经能得到整个数组的排列规律了：整个数组可以构成一棵树，树的先序遍历结果就是数组字典序排列顺序。
 (下面只以1为例)

             1-9
            / \
           10-19
          / \
        100-109
        /  \
      1000-1009
 .....................

 可以发现，每个个位数都分别对应一棵“十叉树”，并且随着n的增大，树的深度是越来越深的。我们想要有规律地找到第k个数字，就要先确定下来树的深度deep，deep确定下来，每一棵树的元素总数目就确定了下来，这样我们就可以根据除法及取余操作，确定下来第k个数在哪棵树下面，以及该数是这棵树的第几个元素（余数p)。

 剩下的问题就是在这颗树中找到它的第p个数。这个问题也要用数学的方法去解决，不能暴力遍历。我的方法是不断地对p进行除法及取余操作，确定它归属的第二层结点，第三层结点…最终确定下来它的位置。以上面的图为例，从上至下每一层中的节点所附庸的节点数目（包括自己）分别是：1111，111，11，1。那么p/111的商result就是它归属于第二层节点的位置，余数p就代表它在该子树中是第几个元素，然后递归计算查找即可
 
 ————————————————
 版权声明：本文为CSDN博主「LNGOD」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
 原文链接：https://blog.csdn.net/qq_36946274/article/details/81638367
 
 */

#include "CommonUtils.h"


class KThSmallestInLexicographicalOrder
{
public:
    long findKthNumber(int n, int k)
    {
        long curr = 1;
        k --;
        while(k > 0)
        {
            int steps = findSteps(n, curr, curr + 1);
            if(steps <= k)
            {
                curr ++;
                k -= steps;
            }
            else
            {
                curr *= 10;
                //因为curr已经乘了10 对于curr来说已经算进去了，
                //好比 （1， 10),1变成10的时候，1已经算进了k里面
                k -= 1;
            }
        }
        
        return curr;
    }
    
    int findSteps(int n, long n1, long n2)
    {
        int steps = 0;
        while(n1 <= n)
        {
            long step = ( n2 < n+1 ? n2 : n+1 ) - n1;
            steps += step;
            n1 *= 10;
            n2 *= 10;
        }
        return steps;
    }
    
    //原理和上面那个差不多 只是换了一种写法
    int findKthNumber2(int n, int k)
    {
        string prefix = "";
        while(k > 0)
        {
            for(int i=0; i<=9; i++)
            {
                string a = prefix + to_string(i);
                int steps = findSteps(n, stoi(a));
                if(steps >= k)
                {
                    prefix = a;
                    break;
                }
                else
                {
                    k -= steps;
                }
            }
            k -= 1;
        }
        
        return stoi(prefix);
    }
    
    int findSteps(int n, long a)
    {
        if(a == 0)
        {
            return 0;
        }
        int steps = 0;
        long b = a + 1;
        while(a <= n)
        {
            steps += (n+1 < b ? n + 1 : b) - a;
            a *= 10;
            b *= 10;
        }
        
        return steps;
    }
    
    //常规dfs
    
    int current = 0;
    int result = 0;
    int k;
    int max;
    int findKthNumber3(int n, int k)
    {
        this->k = k;
        this->max = n;
        dfs(0);
        
        return result;
    }
    
    void dfs(int currNum)
    {
        if(current == k)
        {
            this->result = currNum;
            return;
        }
        int i = currNum == 0 ? 1 : 0;
        
        for( ; i<=9; i++)
        {
            if(current == k)
            {
                break;
            }
            int newNum = currNum * 10 + i;
            if(newNum <= max)
            {
                current ++;
                dfs(newNum);
            }
        }
        
    }
    
    void run()
    {
        int n = 20;
        int k = 20;
        cout<<this->findKthNumber3(n, k)<<endl;
    }
};
