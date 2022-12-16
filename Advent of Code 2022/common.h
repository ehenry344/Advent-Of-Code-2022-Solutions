#ifndef _Advent2022_EvanHenry 
#define _Advent2022_EvanHenry

// Common Include Paths 

#include <iostream> 
#include <fstream> 
#include <string> 
#include <vector> 
#include <algorithm> 
#include <numeric> 
#include <regex> 
#include <map> 
#include <exception> 

// .h c style libraries 

#include <math.h>  

// various util functions 
const std::vector<int> scrapeIntegers(const std::string toScrape) { 
    std::vector<int> returnList; 

    std::regex numericMatch("\\d+"); 
    std::sregex_iterator numIterator(
        toScrape.begin(), toScrape.end(), numericMatch
    ); 

    std::sregex_iterator end; 

    while (numIterator != end) { 
        std::smatch num = *numIterator; 
        returnList.push_back(stoi(num.str())); 
        numIterator++; 
    }

    return returnList;
} 

template <typename it, short int> 
void logIntVector(const std::vector<it> toLog, short int logType) { 
    std::cout << std::endl; // create separation 

    for (int i = 0; i < toLog.size(); ++i) { 
        switch (logType) { 
            case 1 :   
                std::cout << toLog.at(i) << std::endl;
                break; 
            case 2 : 
                if (i != 0) { 
                    std::cout << ","; 
                } 
                std::cout << toLog.at(i); 
                break;
            default: 
                std::cout << toLog.at(i) << std::endl;
                break; 
        }
    }
} 

#endif