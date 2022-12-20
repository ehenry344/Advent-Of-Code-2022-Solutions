#include "common.h"

struct DirNode { 
    std::string name;
    int size; // name of the file is irrelevant therefore we just need to store this value 

    DirNode * parent; 
    std::vector<DirNode *> children;

    int cumulativeSize(); 
    void log(int tabWidth); 
};

DirNode * findChild(DirNode * inputNode, std::string childName);
DirNode * getRoot(DirNode * inputNode); 
DirNode * parseInput(std::string filePath);

void updateSizeVector(std::vector<int> & sizeVector, DirNode * inputNode, int requiredSpace, bool option); 

int main() { 
    DirNode * parsed = parseInput("./InputFolder/Day7Input.txt"); 
    parsed = getRoot(parsed); 

    std::vector<int> p1; 
    std::vector<int> p2; 

    updateSizeVector(p1, parsed, 100000, false); 
    updateSizeVector(p2, parsed, 30000000 - (70000000 - (parsed->cumulativeSize())), true); 

    std::cout << std::accumulate(p1.begin(), p1.end(), 0) << " is the total size of the directories under 100000" << std::endl;
    std::cout << *std::min_element(p2.begin(), p2.end()) << " is the size of the file that should be deleted to do the update"; 

    return 0; 
}

void updateSizeVector(std::vector<int> & sizeVector, DirNode * inputNode, int requiredSpace, bool option) { 
    int cSize = inputNode->cumulativeSize(); 

    if (option) { 
        if (cSize >= requiredSpace) { 
            sizeVector.push_back(cSize); 

            if (!inputNode->children.empty()) { 
                for (int i = 0; i < inputNode->children.size(); i++) { 
                    updateSizeVector(sizeVector, inputNode->children[i], requiredSpace, option); 
                }
            } 
        }
    } else { 
        if (cSize <= requiredSpace) { 
            sizeVector.push_back(cSize); 
        } 

        for (int i = 0; i < inputNode->children.size(); i++) {
            updateSizeVector(sizeVector, inputNode->children[i], requiredSpace, option); 
        } 
    }
}
// DirectoryNode member / utility function defs  

int DirNode::cumulativeSize() { 
    int contentSize = size; // c(init) = size of the content in the file 

    for (int i = 0; i < children.size(); ++i) { 
        int cNodeSize = children[i]->cumulativeSize(); 

        contentSize += cNodeSize; 
    }

    return contentSize; 
}

DirNode * findChild(DirNode * inputNode, std::string childName) { 
    if (!inputNode->children.empty()) { 
        for (int i = 0; i < inputNode->children.size(); ++i) { 
            if (inputNode->children[i]->name == childName) { 
                return inputNode->children[i]; 
            }
        }
    }
    return inputNode; 
}

DirNode * getRoot(DirNode * inputNode) {
    if (inputNode->parent != nullptr) { 
        return getRoot(inputNode->parent); 
    }
    return inputNode;
}

DirNode * parseInput(std::string filePath) { 
    DirNode * rNode = new DirNode(); 

    rNode->parent = nullptr; 
    rNode->name = "/";

    // handle input parsing in separate scope 
    {
        std::ifstream inputStream (filePath); 
        std::string s[3]; 

        while (inputStream >> s[0] >> s[1]) { 
            if (s[1] == "ls") { continue; }

            if (s[1] == "cd") { 
                inputStream >> s[2]; // grab the 3rd argument 

                if (s[2] == "/") { 
                    rNode = getRoot(rNode); 
                } else if (s[2] == "..") { 
                    if (rNode->parent != nullptr) { 
                        rNode = rNode->parent; 
                    }
                } else { 
                    rNode = findChild(rNode, s[2]); 
                }
            } else if (s[0] == "dir") { 
                DirNode * newDirectory = new DirNode(); 

                newDirectory->parent = rNode; 
                newDirectory->name = s[1]; 

                rNode->children.push_back(newDirectory); 
            } else { 
                rNode->size += std::stoi(s[0]);  
            }
        }
    }
    return rNode; 
}