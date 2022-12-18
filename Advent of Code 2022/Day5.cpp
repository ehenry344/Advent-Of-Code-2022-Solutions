#include "common.h"

// Lowkey ugly solution 

struct CrateManager { 
    std::vector< std::vector<char> > crates9000; // Pt.  1
    std::vector< std::vector<char> > crates9001; // Pt. 2 

    std::queue< std::vector<int> > steps; 

    void parse(std::string filePath) { 
        std::ifstream inputStream(filePath); 
        std::string currentLine; 

        while (std::getline(inputStream, currentLine)) {
            if (*(currentLine.c_str()) == 'm') {
                steps.push(scrapeIntegers(currentLine)); 
            } else if (currentLine.find("[") != std::string::npos) { 
                int rowSize = std::floor(currentLine.length() / 4) + 1; 

                crates9000.resize(rowSize); 

                for (int i = 0; i < rowSize; ++i) { 
                    char crateCode = currentLine[1 + (4 * i)]; 
                    if (!std::isspace(crateCode)) {
                        crates9000.at(i).push_back(crateCode); 
                    }
                }
            }
        }

        for (int i = 0; i < crates9000.size(); ++i) { 
            std::reverse(crates9000[i].begin(), crates9000[i].end()); 
        }
        crates9001.assign(crates9000.begin(), crates9000.end()); 
    }

    void crateMover9000() { 
        std::vector<int> task = steps.front();

        for (int i = 0; i < task[0]; ++i) {             
            if (crates9000.at(task[1] - 1).size() > 0) { 
                crates9000.at(task[2] - 1).push_back(
                    crates9000.at(task[1] - 1).back()
                ); 
                crates9000.at(task[1] -1).pop_back(); 
            }
        }
    }

    void crateMover9001() { 
        std::vector<int> task = steps.front(); 
        std::copy(
            crates9001[task[1] - 1].end() - task[0], 
            crates9001[task[1] - 1].end(), 
            std::back_inserter(crates9001[task[2] - 1])
        ); 
        crates9001[task[1] - 1].resize(crates9001[task[1] - 1].size() - task[0]); 
    }

    std::string getTopCrates(int craneCode) { 
        std::string topRow; 
        std::vector<std::vector<char>> data = craneCode == 9000 ? crates9000 : crates9001; 
        
        for (int i = 0; i < data.size(); ++i) { 
            if (data.at(i).size() > 0) { 
                topRow += data.at(i).back(); 
            }
        }
        return topRow; 
    }
}; 

int main() { 
    CrateManager manager; 
    
    manager.parse("./InputFolder/Day5Input.txt"); 

    while (!manager.steps.empty()) { 
        manager.crateMover9000(); 
        manager.crateMover9001(); 

        manager.steps.pop(); 
    }

    std::cout << manager.getTopCrates(9000) << " is the top row of crates at the end of the steps 1" << std::endl;
    std::cout << manager.getTopCrates(9001) << " is the top row of crates at the end of the steps 2"; 

    return 0; 
}