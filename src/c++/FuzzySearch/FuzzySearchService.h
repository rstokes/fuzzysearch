//
//  FuzzySearch.h
//  FuzzySearch
//
//  Created by Rob Stokes on 2/21/13.
//  Copyright (c) 2013 Rob Stokes. All rights reserved.
//
#include <vector>
#include <string>
#include <map>
#include <iterator>
#include <set>
#include <algorithm>
#include <sstream>
#include <functional>
#include <cctype>
#include <locale>

using namespace std;

#ifndef FuzzySearch_FuzzySearch_h
#define FuzzySearch_FuzzySearch_h

// trim from start
static inline std::string &ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
static inline std::string &rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
static inline std::string &trim(std::string &s) {
    return ltrim(rtrim(s));
}


class Result{
private:
    float _score;
    string _searched;
    string _result;
public:
    float getScore() const { return _score; }
    string getScoreString() const {
        ostringstream stringStream;
        stringStream << _score;
        string scoreString(stringStream.str());
        return scoreString;
    }
    string getSearched() const { return _searched; }
    string getResult() const { return _result; }
    string toString() const {
        ostringstream stringStream;
        stringStream << _score;
        string scoreString(stringStream.str());
        return "Searched: " + _searched + " Result: " + _result + " Score: " + scoreString;
    }
    Result(float score, string searched, string result){
        _score = score;
        _searched = searched;
        _result = result;
    }
    bool operator <(const Result & s1) const { return s1._result < _result; }
    bool operator ==(const Result & s1) const { return s1._result == _result; }

};


class FuzzySearchService{
public:
    FuzzySearchService(vector<string> inputs){
        index = init(inputs);
    }
    
    set<Result> search(string value){
        set<Result> results;
        vector<string> valuesToSearch = splitStringToWords(value);
        for(int i = 0; i < valuesToSearch.size(); i++){
            string word = valuesToSearch[i];
            string hash = soundex(word);
            //cout << hash << " " << word << endl;
            vector<string> valuesFromIndex = index[hash];
            for (int j = 0; j < valuesFromIndex.size(); j++) {
                results.insert(*new Result(score(value, valuesFromIndex[j]), value, valuesFromIndex[j]));
            }
        }
        return results;
    }
    
private:
    map<string, vector<string> > index;
    
    string encodeChar(char c)
    {
        switch (tolower(c))
        {
            case 'b':
            case 'f':
            case 'p':
            case 'v':
                return "1";
            case 'c':
            case 'g':
            case 'j':
            case 'k':
            case 'q':
            case 's':
            case 'x':
            case 'z':
                return "2";
            case 'd':
            case 't':
                return "3";
            case 'l':
                return "4";
            case 'm':
            case 'n':
                return "5";
            case 'r':
                return "6";
            default:
                return "";
        }
    }
    
    string soundex(string data)
    {
        string result = "";
        
        if (!data.empty())
        {
            string previousCode, currentCode;
            result = toupper(data[0]);
            previousCode = "";
            
            for (int i = 1; i < data.size(); i++)
            {
                currentCode = encodeChar(data[i]);
                
                if (currentCode != previousCode)
                    result += currentCode;
                
                if (result.size() == 4) break;
                
                if (!currentCode.empty())
                    previousCode = currentCode;
            }
        }
        
        if (result.size() < 4)
            result = padSoundex(result);
        
        return result;
    }
    
    string padSoundex(string value){
        if(value.size() == 1)
            return value += "000";
        else if (value.size() == 2)
            return value + "00";
        else if (value.size() == 3)
            return value + "0";
        else
            return value;
    }
    
    string removeNonAlphaNumerics(string value){
        string result = value;
        for (size_t i = 0; i < result.length(); ++i)
            if (!isalnum(result[i]) || result[i] != ' ' || result[i] == '(' || result[i] == ')')
                result.erase(i, 1);
        
        return result;
    }

    map<string, vector<string> > init(vector<string> inputs){
        map<string, vector<string> > indexToBuild;
        
        for (int i = 0; i < inputs.size(); i++) {
            string currentInput = inputs[i];
            //make everything lowercase
            transform(inputs[i].begin(), inputs[i].end(), inputs[i].begin(), ::tolower);
            
            
            //split into words
            vector<string> words = splitStringToWords(removeNonAlphaNumerics(inputs[i]));
            for (int x = 0; x < words.size(); x++) {
                string word = trim(words[x]);
                string hash = soundex(word);
                if(indexToBuild.count(hash) == 0){
                    cout << "new " << hash << ": " << word << endl;
                    vector<string> value;
                    value.push_back(currentInput);
                    indexToBuild[hash] = value;
                }
                else{
                    cout << "old " << hash << ": " << word << endl;
                    map<string, vector<string> >::iterator vals;   
                    vals = indexToBuild.find(hash);
                    vals->second.push_back(currentInput);
                }
            }
        }
        return indexToBuild;
    }
    
    vector<string> splitStringToWords(string value){
        stringstream ss(value);
        istream_iterator<string> begin(ss);
        istream_iterator<string> end;
        vector<string> vstrings(begin, end);
        return vstrings;
    }
    
    float score(string val1, string val2){
        transform(val1.begin(), val1.end(), val1.begin(), ::tolower);
        transform(val2.begin(), val2.end(), val2.begin(), ::tolower);
        if (val1 == val2) return 100;
        return diceCoefficient(val1, val2)*100;
    }
    
    /**************** Scoring ******************/
    float diceCoefficient(string string1, string string2)
    {
        
        set<string> string1_bigrams;
        set<string> string2_bigrams;
        
        //base case
        if(string1.length() == 0 || string2.length() == 0)
        {
            return 0;
        }
        
        for(unsigned int i = 0; i < (string1.length() - 1); i++) {      // extract character bigrams from string1
            string1_bigrams.insert(string1.substr(i, 2));
        }
        for(unsigned int i = 0; i < (string2.length() - 1); i++) {      // extract character bigrams from string2
            string2_bigrams.insert(string2.substr(i, 2));
        }
        
        int intersection = 0;
        
        // find the intersection between the two sets
        
        for(set<string>::iterator IT = string2_bigrams.begin();
            IT != string2_bigrams.end();
            IT++)
        {
            intersection += string1_bigrams.count((*IT));
        }
        
        // calculate dice coefficient
        int total = string1_bigrams.size() + string2_bigrams.size();
        float dice = (float)(intersection * 2) / (float)total;
        
        return dice;
    }
};


#endif
