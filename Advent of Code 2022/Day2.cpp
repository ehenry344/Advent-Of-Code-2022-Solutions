#include "common.h"

struct ScoreData { int alg1; int alg2; }; 

int moveToInt(char); 
ScoreData getScores(std::string); 

int main() { 
    ScoreData fetched = getScores("./InputFolder/Day2Input.txt"); 

    std::cout << fetched.alg1 << " is the part 1 algorithm score" << std::endl;
    std::cout << fetched.alg2 << " is the part 2 algoritm score"; 

    return 0; 
}

int moveToInt(char move) { 
    switch(move) { 
        case 'A': return 1; case 'B': return 2; case 'C': return 3; 
        case 'X': return 1; case 'Y': return 2; case 'Z': return 3; 
    }
    return 0; 
}

ScoreData getScores(std::string fPath) { 
    ScoreData scores; 

    std::ifstream roundCharStream(fPath); 
    std::string cLine; 

    while (std::getline(roundCharStream, cLine)) { 
        int m1 = moveToInt(cLine.c_str()[0]); 
        int m2 = moveToInt(cLine.c_str()[2]); 
        int dM = m2 - m1; 

        // the partial algorithm for part 1 
        scores.alg1 += m2;

        if (dM == 0) { 
            scores.alg1 += 3; 
        } else if ((m1 > 2 && dM == -2) || (m1 <= 2 && dM == 1)) {
            scores.alg1 += 6; 
        }
        // algorithm that the elf gave us upon returning in part 2
        switch(m2) { 
            case 1: 
                scores.alg2 += (m1 == 1) ? 3 : (m1 - 1); 
                break; 
            case 2: 
                scores.alg2 += (3 + m1); 
                break; 
            case 3:  
                scores.alg2 += 6 + ((m1 == 3) ? 1 : (m1 + 1)); 
                break; 
        }
    }

    return scores; 
}
