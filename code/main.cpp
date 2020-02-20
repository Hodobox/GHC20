#include "includes.h"

const string INPUTDIR = "inputs/";
const string OUTPUTDIR = "outputs/";
const vector<string> fnames = {"a_example","b_small","c_medium","d_quite_big","e_also_big"};

int main()
{
    for(const string file : fnames)
    {
        cout << "solving " << file << "\n";
        string input = INPUTDIR + file + ".in";
        string output = OUTPUTDIR + file + ".out";

        int limit;
        vector<int> pizza = read(input, limit);

        vector<int> sol = solve_sort(limit, pizza);

        if( verify(limit, pizza, sol) )
            print(output, sol);
    }
    return 0;
}