//
// Created by Vincent Zhu on 2021/7/30.
//

#include <iostream>
#include <vector>
#include "zhu_allocator.h"

using namespace std;

int main(int argc, char *argv[])
{
    int a[5] = {1, 2, 3, 4, 5};
    vector<int, zhustl::ZhuAllocator<int>> v(a, a + 5);
    for(auto t: v) {
        cout << t << endl;
    }
    return 0;
}