//
//  main.cpp
//  FuzzySearch
//
//  Created by Rob Stokes on 2/21/13.
//  Copyright (c) 2013 Rob Stokes. All rights reserved.
//

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
    
    vector<string> its;
    its.push_back("Ethiocn");
    its.push_back("Ethiocn Inc.");
    its.push_back("Ethiocn Health");
    its.push_back("Cardinal Health");
    its.push_back("Fart Health");
    
    FuzzySearchService *service = new FuzzySearchService(its);
    set<Result> results = service->search("helth");
    
    for(set <Result>::iterator resultsIterator = results.begin(); resultsIterator != results.end(); resultsIterator++){
        string  outVal = resultsIterator->toString();
        cout << outVal << endl;
    }

    cout<<endl;
    return 0;
}

