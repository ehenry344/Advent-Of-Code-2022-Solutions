#include "common.h"

std::vector<int> parseElfData(std::string); 
std::vector<int> maxElfEntries(std::vector<int>, short int); 

int main() { 
    short int setSize = 3; 

    std::vector<int> maximums = maxElfEntries(
        parseElfData("./InputFolder/Day1Input.txt"), 
        setSize
    ); 

    std::cout << *(maximums.begin()) << " is the elf with the maximum number of calories" << std::endl;
    std::cout << std::accumulate(maximums.begin(), maximums.end(), 0) << " is sum of the elves with the highest 3 calorie values"; 

    return 0; 
}

std::vector<int> parseElfData(std::string fName) { 
    std::vector<int> calories; 
    calories.push_back(0); // prevent add'l logic

    std::ifstream iStream(fName); 
    std::string currentLine;

    while (std::getline(iStream, currentLine)) { 
        if (currentLine.empty()) { 
            calories.push_back(0); 
        } else { 
            calories.back() += std::stoi(currentLine); 
        } 
    }
    return calories;
}

std::vector<int> maxElfEntries(std::vector<int> elfData, short int n) {
    std::vector<int> maxElements; 

    for (int i = 0; i < n; ++i) { 
        std::vector<int>::iterator maxIter = std::max_element(elfData.begin(), elfData.end()); 

        if (maxIter != elfData.end()) { 
            maxElements.push_back(*(maxIter)); 
            elfData.erase(maxIter); 
        }
    }

    return maxElements; 
} 