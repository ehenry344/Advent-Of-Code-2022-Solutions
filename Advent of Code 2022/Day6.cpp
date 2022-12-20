#include "common.h"

int getRelevantIndex(std::string input, int numDistinct) { 
    for (int i = 0; i < input.length(); ++i) {
        std::string buffer;

        buffer += input[i];

        for (int j = 1; j < numDistinct; ++j) { 
            if (buffer.find(input[i + j]) != std::string::npos) { 
                break;
            }
            buffer += input[i + j]; 
        }

        if (buffer.length() == numDistinct) { 
            return i + numDistinct; 
        }
    }
    return -1; 
}

int main() { 
    std::ifstream inputStream("./InputFolder/Day6Input.txt");
    std::string data;

    std::getline(inputStream, data);
    inputStream.close();

    std::cout << getRelevantIndex(data, 4) << " is the index of the start of packet marker" << std::endl;
    std::cout << getRelevantIndex(data, 14) << " is the index of the start of message marker"; 

    return 0; 
}