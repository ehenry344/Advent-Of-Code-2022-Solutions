#include "common.h"

struct RangedZone { 
    int min, max; 

    RangedZone(int iMn, int iMx) { 
        min = iMn; max = iMx; 
    } 

    bool doesContain(RangedZone other) {
        return ((min >= other.min) && (max <= other.max));  
    }

    bool doesOverlap(RangedZone other) { 
        return (max >= other.max && min <= other.max);
    }
};

int getOverlapCount(std::string, int); 

int main() { 
    std::cout << getOverlapCount("./InputFolder/Day4Input.txt", 1) << " is the number of fully contained regions" << std::endl;
    std::cout << getOverlapCount("./InputFolder/Day4Input.txt", 2) << " is the number of overlapping regions"; 
    return 0; 
}

int getOverlapCount(std::string filePath, int partNum) { 
    int sum = 0; 

    std::ifstream inputReader(filePath); 
    std::string currentLine; 

    while (std::getline(inputReader, currentLine)) { 
        std::vector<int> lineData = scrapeIntegers(currentLine); 

        RangedZone r1(lineData[0], lineData[1]); 
        RangedZone r2(lineData[2], lineData[3]); 

        switch(partNum) { 
            case 1: 
                if (r1.doesContain(r2) || r2.doesContain(r1)) { 
                    sum++; 
                }
                break; 
            case 2: 
                if (r1.doesOverlap(r2) || r2.doesOverlap(r1)) { 
                    sum++; 
                }
                break; 
            }
    }

    inputReader.close(); 

    return sum; 
}