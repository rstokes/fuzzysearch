#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "FuzzySearchService.h"

using namespace std;

int main(int argc, const char * argv[])
{

    vector<string> inputs;
    ifstream infile("movies.txt");
    string line;
    for(string line; getline(infile, line); )
    {
        inputs.push_back(line);
    }
    
    
    clock_t startTime = clock();
    FuzzySearchService *service = new FuzzySearchService(inputs);
    cout << "Indexed data in: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC << "s" << endl;
    
    
    while (1) {
        string input;
        cin >> input;
        clock_t startTime = clock();
        set<Result> results = service->search(input);
        cout << "Search took: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC << "s" << endl;
        for(set <Result>::iterator resultsIterator = results.begin(); resultsIterator != results.end(); resultsIterator++){
            string  outVal = resultsIterator->toString();
            cout << outVal << endl;
        }
    }
    return 0;
}

