#ifndef VERIFIER_INCLUDE
#define VERIFIER_INCLUDE
#include "includes.h"

bool verify(int limit, vector<int> &pizzas, vector<int> &res)
{
    set<int> used;
    long long sum = 0;
    for(int x : res)
    {
        if(x<0||x>=pizzas.size())
        {
            cout << "WA used pizza " << x << " not in [0" << pizzas.size()-1 << "]\n";
            return false;
        }
        used.insert(x);
        sum += pizzas[x];
    }

    if(used.size() != res.size())
    {
        cout << "WA duplicate pizzas\n";
        return false;
    }

    if(sum > limit)
    {
        cout << "WA bought " << sum << "/" << limit << "\n";
        return false;
    }

    cout << "OK score:" << sum << "\n";
    return true;
}

#endif