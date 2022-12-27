#include "common.h"

// - Evan (12 / 26 / 2022) 
// This solution has an off by done error (Pathology is likely faulty handling of diagonal cases) 
// My brain fought against this code and it won today, will come back another day 


struct position_2D { 
    int x; 
    int y; 

    position_2D() { 
        this->x = 0; 
        this->y = 0; 
    }

    position_2D(int ix, int iy) { 
        this->x = ix; 
        this->y = iy; 
    }

    position_2D nonscalar_add(char direction, int magnitude) const { 
        switch(direction) { 
            case 'U': 
                return position_2D(this->x, this->y + magnitude); 
            case 'D': 
                return position_2D(this->x, this->y - magnitude); 
            case 'L': 
                return position_2D(this->x - magnitude, this->y); 
            case 'R':
                return position_2D(this->x + magnitude, this->y); 
        }
        return position_2D(0, 0); 
    }

    int get_dx(position_2D  other) { 
        if (other.x == this->x) { 
            return 0; 
        }
        return (this->x < other.x) ? 1 : -1; 
    }

    int get_dy(position_2D other) { 
        if (other.y == this->y) { 
            return 0; 
        }
        return (this->y < other.y) ? 1 : -1; 
    }


    // overloads 

    void operator = (const position_2D & v) { 
        this->x = v.x; 
        this->y = v.y; 
    }

    bool operator == (const position_2D & v) const { 
        return v.x == this->x && v.y == this->y; 
    }

    // hashing overloads 
   
    std::size_t operator()(const position_2D & th) const { // cantor pairing hash 
        return ((th.x + th.y) * (th.x + th.y + 1)) / (2 + th.y); 
    }

    bool operator()(const position_2D & v1, const position_2D & v2) const { 
        return v1 == v2; 
    }
}; 

struct position_map { // manages tail positions 
    std::unordered_set<position_2D, position_2D, position_2D> pos_set; 

    void insert(const position_2D & v) { 
        pos_set.insert(v); 
    }

    std::size_t size() { 
        return pos_set.size(); 
    }
}; 

std::size_t num_unique_pos(std::string path, int length); 

int main() { 
    std::cout << num_unique_pos("./InputFolder/Day9Input.txt", 2) << std::endl;
    std::cout << num_unique_pos("./InputFolder/Day9Input.txt", 10); 
    return 0; 
}


std::size_t num_unique_pos(std::string path, int length) {         
    std::vector<position_2D> knot_grp; 
    knot_grp.resize(length, position_2D(0, 0)); 

    position_map solve_data; 
    solve_data.insert(position_2D(0, 0)); 

    { 
        std::ifstream stream(path); 

        char dir; 
        int magnitude; 

        while (stream >> dir >> magnitude) {           
            knot_grp[0] = knot_grp[0].nonscalar_add(dir, magnitude); 

            for (int i = 1; i < knot_grp.size(); i++) { 
                while (abs(knot_grp[i].x - knot_grp[i - 1].x) >= 2 || abs(knot_grp[i].y - knot_grp[i - 1].y) >= 2) { 
                    knot_grp[i].x += knot_grp[i].get_dx(knot_grp[i - 1]);
                    knot_grp[i].y += knot_grp[i].get_dy(knot_grp[i - 1]); 

                    solve_data.insert(knot_grp[length - 1]);
                }
            }

        }
    }

    return solve_data.size(); 
}
