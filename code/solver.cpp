#ifndef SOLVER_INCLUDE
#define SOLVER_INCLUDE

#include "includes.h"
#include "plan.h"
#include "lib.h"
#include "verifier.cpp"

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

vector<plan> solve_tryhard(int nBooks, int nLibs, int nDays, vector<int> &bookScores, vector<lib> &libraries)
{
    vector<plan> best,cur;
    int bestScore = 0;
    for(int i=0;i<nLibs;++i)
    {
        cur.push_back(plan());
        cur.back().id = i;
        cur.back().scannedBooks = libraries[i].booksIds;
        sort(cur.back().scannedBooks.begin(), cur.back().scannedBooks.end(),[&](int a,int b) {return bookScores[a]>bookScores[b];});
    }
    auto start = std::chrono::system_clock::now();

    while( true )
    {
        auto end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end-start;
        //cout << elapsed_seconds.count() << "\n";
        if( (elapsed_seconds).count() > 30) break;
        //cout << "trying after " << (std::chrono::system_clock::now() - start).count() << "\n";
        int score;
        verify(nBooks, nLibs, nDays, bookScores, libraries, cur, &score);

        if(score > bestScore)
        {
            bestScore = score;
            best = cur;
        }

        random_shuffle(cur.begin(),cur.end());
    }

    
    return best;
}

bool bySignupTime(lib a, lib b)
{
    if(a.signupDays != b.signupDays) return a.signupDays < b.signupDays;
    else return a.booksPerDay > b.booksPerDay;
}

vector<plan> solve_B(int nBooks, int nLibs, int nDays, vector<int> &bookScores, vector<lib> &Libraries)
{
    // lebo nemozem sortit referenced vec, kazi to dalej verify
    vector<lib> libraries = Libraries;
    sort(libraries.begin(),libraries.end(),bySignupTime);
    vector<plan> res;
    for(int i=0;i<nLibs;++i)
    {
        res.push_back(plan());
        res.back().id = libraries[i].id;
        res.back().scannedBooks = libraries[i].booksIds;
        sort(res.back().scannedBooks.begin(), res.back().scannedBooks.end(),[&](int a,int b) {return bookScores[a]>bookScores[b];});
    }
    return res;
}

bool bySignupTimeAndMore(lib a, lib b)
{
    if(a.signupDays != b.signupDays) return a.signupDays < b.signupDays;
    else if(a.booksPerDay != b.booksPerDay) return a.booksPerDay > b.booksPerDay;
    else return a.nBooks > b.nBooks;
}

bool isIn(int a,set<int> &s)
{
    return s.find(a)!=s.end();
}

void improveUsedBooks(int nLibs, int nDays, vector<lib> &libraries, vector<plan> &res)
{
    set<int> scanned;
    int day = 0;
    for(int i=0;i<nLibs;++i)
    {
        stable_sort(res[i].scannedBooks.begin(), res[i].scannedBooks.end(),[&](int a,int b) {
                return isIn(a,scanned) < isIn(b,scanned);
        });

        // we figure out what we actually scanned from this library
        day += libraries[i].signupDays;
        int curday = day;
        int scannedToday = 0;
        for(int b : res.back().scannedBooks)
        {
            if(curday >= nDays) break;
            scannedToday++;
            if(scannedToday == libraries[i].booksPerDay)
            {
                scannedToday = 0;
                curday++;
            }

            scanned.insert(b);
        }
    }   
}

vector<plan> solve_E(int nBooks, int nLibs, int nDays, vector<int> &bookScores, vector<lib> &Libraries)
{
    // lebo nemozem sortit referenced vec, kazi to dalej verify
    vector<lib> libraries = Libraries;
    sort(libraries.begin(),libraries.end(),bySignupTimeAndMore);
    vector<plan> res;
    set<int> scanned;
    int day = 0;
    for(int i=0;i<nLibs;++i)
    {
        res.push_back(plan());
        res.back().id = libraries[i].id;
        res.back().scannedBooks = libraries[i].booksIds;
        sort(res.back().scannedBooks.begin(), res.back().scannedBooks.end(),[&](int a,int b) {
            if( isIn(a,scanned) != isIn(b,scanned) )
                return isIn(a,scanned) < isIn(b,scanned);
            return bookScores[a]>bookScores[b];
        });

        // we figure out what we actually scanned from this library
        day += libraries[i].signupDays;
        int curday = day;
        int scannedToday = 0;
        for(int b : res.back().scannedBooks)
        {
            if(curday >= nDays) break;
            scannedToday++;
            if(scannedToday == libraries[i].booksPerDay)
            {
                scannedToday = 0;
                curday++;
            }

            scanned.insert(b);
        }
    }
    return res;
}


int zarobim(set<int> &scanned, int dayStartBuilding, int nDays, vector<int> &bookScores, lib library)
{
    sort(library.booksIds.begin(), library.booksIds.end(),[&](int a,int b) {
            if( isIn(a,scanned) != isIn(b,scanned) )
                return isIn(a,scanned) < isIn(b,scanned);
            return bookScores[a]>bookScores[b];
        });

    int day = dayStartBuilding + library.signupDays;
    int curday = day;
    int score = 0;
    int scannedToday = 0;
    for(int b : library.booksIds)
    {
        if(curday >= nDays) break;
        scannedToday++;
        if(scannedToday == library.booksPerDay)
        {
            scannedToday = 0;
            curday++;
        }

        if(isIn(b,scanned) == false)
            score += bookScores[b];

        //scanned.insert(b);
    }

    return score;
}

vector<plan> solve_F(int nBooks, int nLibs, int nDays, vector<int> &bookScores, vector<lib> &Libraries)
{
    vector<lib> libraries = Libraries;
    int day = 0;
    set<int> scanned;
    vector<plan> res;
    while(day<nDays)
    {
        if(day%100==0) cout << day << "/" << nDays << "\n";
        if(libraries.empty()) break;
        int kto=0;
        double best = -1;

        for(int i=0;i<libraries.size();++i)
        {
            //if(day + libraries[i].signupDays + 1 >= nDays) continue;
            double cur = zarobim(scanned,day,nDays,bookScores,libraries[i]);
            //cout << cur << "?\n";
            double val = cur / libraries[i].signupDays;

            if(val>best)
            {
                best = val;
                kto = i;
            }
        }

        if(best == -1) break;

        //cout << "$ " << zarobim(scanned, day, nDays, bookScores, libraries[kto]) << " in " << libraries[kto].signupDays << "\n";

        res.push_back(plan());
        res.back().id = libraries[kto].id;
        res.back().scannedBooks = libraries[kto].booksIds;

        sort(res.back().scannedBooks.begin(), res.back().scannedBooks.end(),[&](int a,int b) {
            if( isIn(a,scanned) != isIn(b,scanned) )
                return isIn(a,scanned) < isIn(b,scanned);
            return bookScores[a]>bookScores[b];
        });

        // we figure out what we actually scanned from this library
        day += libraries[kto].signupDays;
        int curday = day;
        int scannedToday = 0;
        for(int b : res.back().scannedBooks)
        {
            if(curday >= nDays) break;
            scannedToday++;
            if(scannedToday == libraries[kto].booksPerDay)
            {
                scannedToday = 0;
                curday++;
            }

            scanned.insert(b);
        }

        swap(libraries[kto],libraries.back());
        libraries.pop_back();
    }

    return res;
}


#endif