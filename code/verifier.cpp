#ifndef VERIFIER_INCLUDE
#define VERIFIER_INCLUDE
#include "includes.h"
#include "plan.h"

bool verify(int nbooks, int nlibs, int ndays, vector<int> &scores, vector<lib> &libraryData, vector<plan> &result)
{
    set<int> signedUpLibs, scannedBooks;
    int duplicates = 0;

    int day = 0;
    for(plan &library : result)
    {
        if(day >= ndays) continue;

        if(library.id < 0 || library.id >= nlibs)
        {
            cout << "WA library id = " << library.id << ", must be in [0," << nlibs-1 << "]\n";
            return false;
        }

        if(signedUpLibs.find(library.id) != signedUpLibs.end())
        {
            cout << "WA " << library.id << " signed up twice\n";
            return false;
        }

        day += libraryData[library.id].signupDays;
        int curday = day;
        int scannedToday = 0;
        set<int> libraryInventory;
        for(int x : libraryData[library.id].booksIds) libraryInventory.insert(x);
        for(int book : library.scannedBooks)
        {
            if(libraryInventory.find(book) == libraryInventory.end())
            {
                cout << "WA book " << book << " scanned from library " << library.id << " but that library does not have it\n";
                return false;
            }

            if(scannedToday == libraryData[library.id].booksPerDay)
            {
                curday++;
                scannedToday = 0;
            }

            scannedToday++;
            if(curday >= ndays) continue;

            if(scannedBooks.find(book) != scannedBooks.end()) duplicates++;
            else scannedBooks.insert(book);
        }
    }


    long long res = 0;
    for(int x : scannedBooks)
        res += scores[x];

    cout << "OK score = " << res << "\n";
    return true;
}

#endif