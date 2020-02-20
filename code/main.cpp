#include "includes.h"
#include "lib.h"
#include "plan.h"

const string INPUTDIR = "inputs/";
const string OUTPUTDIR = "outputs/";
const vector<string> fnames = {"a_example","b_read_on","c_incunabula","d_tough_choices","e_so_many_books","f_libraries_of_the_world"};

int main()
{
    for(const string file : fnames)
    {
        cout << "solving " << file << "\n";
        string input = INPUTDIR + file + ".txt";
        string output = OUTPUTDIR + file + ".out";

        int nBooks, nLibs, nDays;
        vector<int> bookScores;
        vector<lib> libs;
        read(input, nBooks, nLibs, nDays, bookScores, libs);
        
        vector<plan> result = solve_bf(nBooks, nLibs, nDays, bookScores, libs);

        if( verify(nBooks, nLibs, nDays, bookScores, libs, result)  )
        {
            print(output, result);
        }

    }
    return 0;
}