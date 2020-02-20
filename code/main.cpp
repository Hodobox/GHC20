#include "includes.h"

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

        int limit;
        vector<int> pizza = read(input, limit);

        vector<int> sol = solve_sort(limit, pizza);

        if( verify(limit, pizza, sol) )
            print(output, sol);
    }
    return 0;
}