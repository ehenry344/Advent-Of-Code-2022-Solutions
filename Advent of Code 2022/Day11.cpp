#include "common.h"

typedef long long int ll_i; // my hand hurts from typing long long int 

struct wl_fmt { 
    ll_i v; 
    int dest_index; 
}; 

struct monkey { 
    std::vector<ll_i> items; 

    int operand; 
    int test; 
    int item_delta; 

    int dest[2]; 

    monkey(); 
    wl_fmt worry_level(const ll_i & prev, const int & mod_fact);  
};
// operator overload for monkey parsing 
std::istream & operator >>(std::istream & c_stream, monkey & monke); 

std::vector<monkey> get_monkeys(std::string filename, bool i_f); 
unsigned long long int get_monkey_business(std::string filename, int rounds); 

int main() { 
    std::cout << get_monkey_business("./InputFolder/Day11Input.txt", 20) << std::endl;
    std::cout << get_monkey_business("./InputFolder/Day11Input.txt", 10000); 
    return 0; 
}

monkey::monkey() { 
    operand = 0; 
    item_delta = 0; 
    test = 0; 

    memset(dest, 0, sizeof(dest)); 
}

wl_fmt monkey::worry_level(const ll_i & prev, const int & mod_fact) { 
    wl_fmt to_return; 

    if (operand) { 
        to_return.v = prev * (item_delta == -1 ? prev : item_delta);  
    } else { 
        to_return.v =  prev + (item_delta == -1 ? prev : item_delta);  
    }

    if (mod_fact == 3) { 
        to_return.v /= 3; 
    } else { 
        to_return.v %= mod_fact; 
    }

    to_return.dest_index = dest[to_return.v % test == 0]; 

    return to_return; 
}

std::istream & operator >>(std::istream & c_stream, monkey & monke) { // incredibly inefficient, don't care 
    std::string curr_line; 
    while (std::getline(c_stream, curr_line) && !is_complete_ws(curr_line)) { 
        std::vector<int> nums = scrape_int(curr_line); 

        if (curr_line.find("Starting") != std::string::npos) { 
            std::copy(nums.begin(), nums.end(), std::back_inserter(monke.items)); 
        } else if (curr_line.find("Operation:") != std::string::npos) { 
            monke.item_delta = nums.size() == 0 ? -1 : *nums.begin(); 
            monke.operand = (curr_line.find('*') != std::string::npos); 
        } else if (curr_line.find("Test:") != std::string::npos) { 
            monke.test = *nums.begin(); 
        } else { 
            monke.dest[curr_line.find("true:") != std::string::npos] = *nums.begin(); 
        }
    }
    return c_stream;
}

std::vector<monkey> get_monkeys(std::string filename, bool i_f) { 
    monkey final_monkey; // placeholder monkey to hold the modulous factor 

    final_monkey.test = 1; 

    std::vector<monkey> r; 
    std::ifstream input_stream(filename);

    while (!input_stream.eof()) { 
        monkey new_monkey; 
        input_stream >> new_monkey; 
        r.push_back(new_monkey); 
        final_monkey.test *= new_monkey.test; 
    }

    input_stream.close(); 

    if (i_f) { 
        r.push_back(final_monkey); 
    }

    return r; 
}

 unsigned long long int get_monkey_business(std::string filename, int rounds) { 
    unsigned long long int m_biz = 1; 

    std::vector<monkey> m_list = get_monkeys(filename, rounds > 20); 
    std::vector<int> num_viewed; 

    int iter_control = (rounds > 20) ? m_list.size() - 1 : m_list.size(); 
    int mod_value = (rounds > 20) ? m_list.back().test : 3; 

    num_viewed.resize(iter_control, 0); 


    for (int r_num = 0; r_num < rounds; ++r_num) { 
        for (int pos = 0; pos < iter_control; ++pos) { 
            while (!m_list[pos].items.empty()) { 
                num_viewed[pos]++; 

                std::vector<ll_i>::iterator c_it = m_list[pos].items.begin(); 

                wl_fmt new_val = m_list[pos].worry_level(*c_it, mod_value);  
                m_list[new_val.dest_index].items.push_back(new_val.v); 

                m_list[pos].items.erase(c_it); 
            }
        }
    }

    // get the two greatest elems 

    for (int x = 0; x < 2; x++) { 
        std::vector<int>::iterator max = std::max_element(num_viewed.begin(), num_viewed.end()); 
        m_biz *= *max; 
        num_viewed.erase(max); 
    }

    return m_biz; 
}