/**
 
 
 给定两段基因片段 Gene1 和 Gene2 ,基因片段中由数字和"ACGT"四种字符组成。
 每一个字符前都会有相应的数字，这个数字是描述该字符连续出现的数量，例如："1A2C2G1T" 表示 "ACCGGT"。
 返回一个表示这两个基因片段的相似度的字符串，相似度字符串的定义是："相同位置上的字符相同个数" + "/" + "总字符个数"。

     Gene1 和 Gene2 仅仅包含数字和["A", "C", "G", "T"]这四种字母
     Gene1 以及 Gene2 的长度范围是: [1, 100000]
     基因片段中字符数量的范围是: [1, 10000000]
     保证扩充之后的 Gene1 以及 Gene2 的长度相同

 样例

 示例 1:
 输入:
 Gene1: "2T3G"
 Gene2: "3T2G"
 输出:
 "4/5"
 解释:
 "TTTGG" 和 "TTGGG" 有 4 处位置上的基因片段相同，所以 "4/5"

 示例 2:
 输入:
 Gene1 = "3T2G4A1C"
 Gene2 = "6T1A2C1G"
 输出:
 "4/10"
 解释：
 "TTTGGAAAAC" 和 "TTTTTTACCG" 有 4 个位置具有相同的基因片段, 所以 "4/10"


 
 */

#include "CommonUtils.h"


class GeneSimilarity
{
public:
    
    char c1, c2;
    int idx1, idx2;
    
    /**
       这种是区间版本，还有一种是迭代器版本，将当前字符和个数存放一起，遍历两个字符串，相同的加一起，这个方式相比下面这个效率低一些，但是更简单，相比于解析全部字符串再去遍历要节省空间，因为只会存放一个个数和当前字符串，不会存放全量
     */
    string geneSimilarity(string &Gene1, string &Gene2)
    {
        int total = 0;
        vector<int> g1(2), g2(2);
        g1[0] = g2[0] = 0;
        g1[1] = g2[1] = -1;
        idx1 = idx2 = 0;
        this->setPosition(Gene1, g1, &c1, &idx1);
        this->setPosition(Gene2, g2, &c2, &idx2);
        int len = getLen(Gene1);
        while(g1[1] != -1 || g2[1] != -1)
        {
            if(c1 == c2)
            {
                if(g1[0] <= g2[1] || g2[0] <= g1[1])
                {
                    total += (min(g1[1], g2[1]) - max(g1[0], g2[0])) + 1;
                }
            }
            if(g1[1] < g2[1])
            {
                this->setPosition(Gene1, g1, &c1, &idx1);
            }
            else if(g1[1] == g2[1])
            {
                this->setPosition(Gene1, g1, &c1, &idx1);
                this->setPosition(Gene2, g2, &c2, &idx2);
            }
            else
            {
                this->setPosition(Gene2, g2, &c2, &idx2);
            }
        }
        return to_string(total) + "/" + to_string(len);
    }
    
    int getLen(string &s)
    {
        int len = 0;
        int count = 0;
        for(int i=0; i<s.size(); i++)
        {
            if(s[i] >= '0' && s[i] <= '9')
            {
                count = count * 10 + (s[i] - '0');
            }
            else
            {
                len += count;
                count = 0;
            }
        }
        return len;
    }
    
    void setPosition(string &s, vector<int> &g, char * c, int * idx)
    {
        if(*idx >= s.size())
        {
            g[1] = -1;
            return;
        }
        int count = 0;
        for(int i=*idx; i<s.size(); i++)
        {
          cout<<"s[i] is "<< s[i]<<endl;
            if(s[i] >= '0' && s[i] <= '9')
            {
                count = count * 10 + (s[i] - '0');
            }
            else
            {
                *c = s[i];
                g[0] = g[1] + 1;
                g[1] = g[0] + count - 1;
                cout<<"g[0] is "<<g[0] << " g[1] is " << g[1]<<endl;
                *idx = i + 1;
                break;
            }
            
        }
    }
    
    
    void run()
    {
        
    }
};
