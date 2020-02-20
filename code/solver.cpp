#ifndef SOLVER_INCLUDE
#define SOLVER_INCLUDE

#include "includes.h"

vector<int> solve_sort(int limit, vector<int> &pizza)
{
    vector<int> res;
    vector<pair<int,int> > v;
    for(int i=0;i<pizza.size();++i) v.push_back({pizza[i],i});
    sort(v.begin(),v.end(),greater<pair<int,int>>());
    long long sum = 0;
    for(auto r : v)
    {
        int x = r.first;
        if(sum+x<=limit)
        {
            sum += x;
            res.push_back(r.second);
        }
    }

    cout << "solve_sort: " << sum << "\n";
    return res;
}

#endif