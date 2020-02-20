#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include "includes.h"

vector<int> read(string fname, int &m)
{
    ifstream in(fname);
    int n;
    vector<int> res;
    in >> m >> n;
    while(n--)
    {
        int x;
        in >> x;
        res.push_back(x);
    }
    return res;
}

void print(string fname, vector<int> res)
{
    ofstream out(fname);
    out << res.size() << "\n";
    for(int i=0;i<res.size();++i)
    {
        if(i) out << " ";
        out << res[i];
    } out << "\n";
}

#endif