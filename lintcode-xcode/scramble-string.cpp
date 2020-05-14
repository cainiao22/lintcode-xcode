
/**
 430. 攀爬字符串
 给定一个字符串 s1, 将其递归地分割成两个非空子字符串, 然后可以得到一棵二叉树.

 下面是 s1 = "great" 可能得到的一棵二叉树:

       great
      /    \
     gr    eat
    / \    /  \
   g   r  e   at
         / \
         a   t

 在攀爬字符串的过程中, 我们可以选择其中任意一个非叶节点, 交换该节点的两个子节点.

 例如，我们选择了 "gr" 节点, 并将该节点的两个子节点进行交换, 并且将祖先节点对应的子串部分也交换, 最终得到了 "rgeat". 我们认为 "rgeat" 是 "great" 的一个攀爬字符串.

       rgeat
      /    \
     rg    eat
    / \    /  \
   r   g  e   at
         / \
         a   t

 类似地, 如果我们继续将其节点 "eat" 和 "at" 的子节点交换, 又可以得到 "great" 的一个攀爬字符串 "rgtae".

      rgtae
      /    \
     rg    tae
    / \    /  \
   r   g  ta   e
          / \
         t   a

 给定两个相同长度的字符串 s1 和 s2，判断 s2 是否为 s1 的攀爬字符串.
 样例

 样例 1:

 输入: s1 = "great", s2 = "rgeat"
 输出: true
 解释: 如同上面描述的.

 样例 2:

 输入: s1 = "a", s2 = "b"
 输出: false

 注意事项

 你可以从任何一棵 s1 可以构造出的二叉树开始攀爬, 但是在攀爬得到 s2 的过程中不能重新构造二叉树.

 
 
 */

#include "CommonUtils.h"



class ScrambleString
{
public:
    
    //dp[i][j][k] 以字符串s1的i为开头的长度为k的和以字符串j开头的长度为k的是否可以组成攀爬字符串
    //最终结果dp[0][0][n];
    vector<vector<vector<bool>>> dp;
    
    //递归
    bool isScramble1(string &s1, string &s2)
    {
        if(s1.size() != s2.size())
        {
            return false;
        }
        if(s1.size() == 1){
            return s1 == s2;
        }
        if(s1.size() == 2){
            return s1 == s2 || (s1[0] == s2[1] && s1[1] == s2[0]);
        }
        long len = s1.size();
        for(int i=1; i<len; i++)
        {
            string s1_sub1 = s1.substr(0, i);
            string s1_sub2 = s1.substr(i, len - i);
            
            string s2_sub1 = s2.substr(0, i);
            string s2_sub2 = s2.substr(i, len - i);
            //要保证长度一样  正着比一次 倒着比一次
            string revl_s2 = s2.substr(len - i, i);
            string revr_s2 = s2.substr(0, len - i);
            
            if(isScramble1(s1_sub1, s2_sub1) && isScramble1(s1_sub2, s2_sub2))
            {
                return true;
            }
               
            if(isScramble1(s1_sub1, revl_s2) && isScramble1(s1_sub2, revr_s2))
            {
                return true;
            }
        }
        
        return false;
        
    }
    
    bool sameCharset(string &s1, string &s2)
    {
        if(s1.size() != s2.size())
        {
            return false;
        }
        
        auto size = s1.size();
        unordered_map<char, int> count;
        for(int i=0; i<size; i++)
        {
            if(count.find(s1[i]) == count.end())
            {
                count[s1[i]] = 1;
            }
            else
            {
                count[s1[i]] ++;
            }
            
            if(count.find(s2[i]) == count.end())
            {
                count[s2[i]] = -1;
            }
            else
            {
                count[s2[i]] --;
            }
        }
        for(unordered_map<char, int>::iterator iter=count.begin(); iter!=count.end(); iter++)
        {
            if(iter->second != 0)
            {
                return false;
            }
        }
        return true;
    }
    
    //记忆化搜索
    bool isScrambleMemory(string &s1, string &s2, unordered_map<string, bool> &hash)
    {
        string s3 = s1 + " " + s2;
        if(hash.find(s3) != hash.end())
        {
            return hash[s3];
        }
        if(!sameCharset(s1, s2))
        {
            hash[s3] = false;
            return false;
        }
        if(s1 == s2)
        {
            hash[s3] = true;
            return true;
        }
        long len = s1.size();
        for(int i=1; i< len; i++)
        {
            string s1_sub1 = s1.substr(0, i);
            string s1_sub2 = s1.substr(i, len - i);
            
            string s2_sub1 = s2.substr(0, i);
            string s2_sub2 = s2.substr(i, len - i);
            //要保证长度一样  正着比一次 倒着比一次
            string revl_s2 = s2.substr(len - i, i);
            string revr_s2 = s2.substr(0, len - i);
            
            if(isScrambleMemory(s1_sub1, s2_sub1, hash)
               && isScrambleMemory(s1_sub2, s2_sub2, hash))
            {
                hash[s3] = true;
                return true;
            }
            
            if(isScrambleMemory(s1_sub1, revl_s2, hash)
               && isScrambleMemory(s1_sub2, revr_s2, hash))
            {
                hash[s3] = true;
                return true;
            }
        }
        hash[s3] = false;
        return false;
    }
    
    bool isScramble(string &s1, string &s2)
    {
        //unordered_map<string, bool> hash;
        //return isScrambleMemory(s1, s2, hash);
        return isScrambleDP(s1, s2);
    }
    
    bool isScrambleDP(string &s1, string &s2)
    {
        if(s1.size() != s2.size())
        {
            return false;
        }
        long len = s1.size();
        int dp[len][len][len+1];
        for(int i=0; i<len; i++)
        {
            for(int j=0; j<len; j++)
            {
                dp[i][j][1] = (s1[i] == s2[j]);
            }
        }
    
        for(int n = 2; n<=len; n++)
        {
            //必须小于等于
            for(int i=0; i<=len - n; i++)
            {
                for(int j=0; j<=len - n; j++)
                {
                    dp[i][j][n] = 0;
                    for(int k=1; k<n; k++)
                    {
                        if(dp[i][j][k] && dp[i+k][j+k][n-k])
                        {
                            dp[i][j][n] = 1;
                            break;
                        }
                        
                        if(dp[i][j+k][k] && dp[i+k][j][n-k])
                        {
                            dp[i][j][n] = 1;
                            break;
                        }
                    }
                }
            }
            ;
        }
        
        return dp[0][0][len];
    }
    
    void run()
    {
        string s1 = "vsgqrxvxyojzuznigvosftggtjjcefwnnxsrrdnjntyadhkflthltidpwpnwxmgmgfnwftvdyonozuvdtbuuxzcwnmvkpqqggrxn";
        string s2 = "svqgxrxvoyzjzuinvgsotfggjtcjfenwxnrsdrjntnayhdfktllhitpdpwwnmxmgfgwntfdvoyonuzdvbtuuzxwcmnkvqpgqrgnx";
        
    
        cout<<this->isScramble(s1, s2)<<endl;
    }
};
