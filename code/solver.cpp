#ifndef SOLVER_INCLUDE
#define SOLVER_INCLUDE

#include "includes.h"
#include "plan.h"
#include "lib.h"

vector<plan> solve_bf(int nBooks, int nLibs, int nDays, vector<int> &bookScores, vector<lib> &libraries)
{
    vector<plan> res;
    for(int i=0;i<nLibs;++i)
    {
        res.push_back(plan());
        res.back().id = i;
        res.back().scannedBooks = libraries[i].booksIds;
    }
    return res;
}

#endif