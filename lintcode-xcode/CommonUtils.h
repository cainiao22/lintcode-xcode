//
//  CommonUtils.h
//  lintcode-xcode
//
//  Created by bjhl on 2019/11/7.
//  Copyright © 2019 free. All rights reserved.
//

#ifndef CommonUtils_h
#define CommonUtils_h

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <set>
#include <cmath>
#include <unordered_set>
#include <unordered_map>

using namespace std;

// class TreeNode;

#define MAX_NUM 0xfffffff

class TreeNode
{
public:
    int val;
    //重复次数
    int sub;
    int sum;
    TreeNode* left, *right;
    TreeNode(int val)
    {
        this->val = val;
        this->left = NULL;
        this->right = NULL;
    }
};

#endif /* CommonUtils_h */
