#ifndef PARSER_INCLUDE
#define PARSER_INCLUDE

#include "includes.h"

void read(string fname, int &nBooks, int &nLibs, int &nDays, vector<int> &bookScores, vector<lib> &libs)
{
    ifstream in(fname);
    in >> nBooks >> nLibs >> nDays;
    for (int i = 0; i < nBooks; i++)
        cin >> bookScores[i];
    for (int i = 0; i < nLibs; i++) {
        lib l = lib();
        cin >> l.nBooks >> l.signupDays >> l.booksPerDay;
        for (int j = 0; j < l.nBooks; j++) {
            int x;
            cin >> x;
            l.booksIds.push_back(x);
        }
    }
    in.close();
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