#include "common.h"

struct cpu_simulator { 
    int total_cycles; 
    int x_value; 

    std::vector<int> internal_queue; // holds the value, allows for more control than a typical queue 

    cpu_simulator() { 
        total_cycles = 0; 
        x_value = 1;

    }
    
    void push_raw_instruction(std::string instruction) { 
        int magnitude = (instruction == "noop") ? 0 : *scrape_integers(instruction).begin(); 
        internal_queue.push_back(magnitude); 
    }

    std::vector<int> get_signal_strengths(std::vector<int> intervals) { 
        std::vector<int> signal_strengths; 

        std::vector<int>::iterator int_it = intervals.begin(); 

        while (internal_queue.size() > 0 && *int_it != *intervals.end()) { 
            std::vector<int>::iterator prev_it = internal_queue.begin(); 
            total_cycles += (*internal_queue.begin() == 0 ? 1 : 2); 
    
            if (total_cycles == *int_it) { 
                signal_strengths.push_back(x_value * total_cycles); 
                int_it++; 
            } else if ((total_cycles - 1) == *int_it && *(int_it+1) != 0) { 
                signal_strengths.push_back(x_value * (total_cycles - 1)); 
                int_it++; 
            } 
            x_value += *prev_it; 
            internal_queue.erase(prev_it); 
        }

        return signal_strengths; 
    }
}; 

int total_signal_strength(std::string path); 

int main() {
    std::cout << total_signal_strength("./InputFolder/Day10Input.txt"); 
    return 0; 
}

int total_signal_strength(std::string path) { 
    std::ifstream input_stream(path); 
    std::string str; 

    cpu_simulator sim_handler; 

    while (std::getline(input_stream, str)) { 
        sim_handler.push_raw_instruction(str); 
    }

    std::vector<int> strengths = sim_handler.get_signal_strengths(std::vector<int>{20, 60, 100, 140, 180, 220}); 

    return std::accumulate(strengths.begin(), strengths.end(), 0); 
}
