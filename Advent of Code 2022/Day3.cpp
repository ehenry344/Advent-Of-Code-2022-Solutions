#include "common.h"

int getPriorityLevel(char);
int reoccurenceSum(std::string);
int badgeSum(std::string); 

char getCommonCharacter(std::string[]); 

int main() { 
    std::cout << reoccurenceSum("./InputFolder/Day3Input.txt") << std::endl;
    std::cout << badgeSum("./InputFolder/Day3Input.txt"); 

    return 0; 
}

int getPriorityLevel(char itemType) {
    int aV = (int)itemType; 
    return aV > 90 ? (aV - (int)'a') + 1 : (aV - (int)'A') + 27; 
}

int reoccurenceSum(std::string fPath) { 
    int rSum = 0; 

    std::ifstream inputStream(fPath); 
    std::string currentLine; 

    while (std::getline(inputStream, currentLine)) { 
        std::string s1, s2; 

        s1 = currentLine.substr(0, (currentLine.length() / 2));
        s2 = currentLine.substr((currentLine.length() / 2), currentLine.length()); 

        std::size_t foundPos = s2.find_first_of(s1); 

        if (foundPos != std::string::npos) { 
            rSum += getPriorityLevel(s2.at(foundPos)); 
        }
    }

    return rSum; 
}

int badgeSum(std::string fPath) { 
    int rSum = 0; 

    std::ifstream inputStream(fPath); 
    std::string badgeGroup[3]; 

    while (inputStream >> badgeGroup[0]) { 
        inputStream >> badgeGroup[1]; 
        inputStream >> badgeGroup[2]; 

        rSum += getPriorityLevel(getCommonCharacter(badgeGroup)); 
    }

    return rSum; 
} 

char getCommonCharacter(std::string group[]) { 
    for (char cChar : group[0]) { 
        if (group[1].find(cChar) != std::string::npos && group[2].find(cChar) != std::string::npos) { 
            return cChar; 
        } 
    }
    return 'X'; 
}