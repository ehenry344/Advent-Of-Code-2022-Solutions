#include "common.h" 

// brute force solution : I just wanted it to work 

// type declarators 

typedef std::vector< std::vector<int> > height_matrix; 

struct point_2D { 
    int x; 
    int y; 

    point_2D(int ix, int iy) { 
        this->x = ix; 
        this->y = iy; 
    }
}; 

// of course... 

height_matrix con_height_mat(std::string path); 

point_2D score_horiz(height_matrix mat, point_2D to_score); 
point_2D score_vert(height_matrix mat, point_2D to_score); 

std::vector<int> get_solve_info(std::string path); 

int main() { 
    std::vector<int> solve_values = get_solve_info("./InputFolder/Day8Input.txt"); 

    std::cout << "Number of visible trees from outside the grid " << solve_values[0] << std::endl;
    std::cout << "The highest possible scenic score is " << solve_values[1]; 

    return 0; 
}

height_matrix con_height_mat(std::string path) { 
    height_matrix new_matrix; 

    std::ifstream stream(path); 
    std::string str; 

    while (std::getline(stream, str)) { 
        std::vector<int> buffer; 

        for (int i = 0; i < str.length(); i++) { 
            buffer.push_back((int) str[i] - '0'); 
        }

        new_matrix.push_back(buffer); 
    }

    return new_matrix; 
}

point_2D score_horiz(height_matrix mat, point_2D to_score) { 
    point_2D h_score(0, 0); 

    if (to_score.x <= 0 || to_score.x >= mat.size() - 1) { 
        return h_score; 
    }

    for (int i = to_score.x - 1; i >= 0; i--) { 
        h_score.x++; 
        if (mat[i][to_score.y] >= mat[to_score.x][to_score.y]) { 
            break; 
        }
    }

    for (int i = to_score.x + 1; i < mat.size(); i++) { 
        h_score.y++; 
        if (mat[i][to_score.y] >= mat[to_score.x][to_score.y]) { 
            break; 
        }
    }

    return h_score; 
}

point_2D score_vert(height_matrix mat, point_2D to_score) { 
    point_2D v_score(0, 0); 

    if (to_score.y <= 0 || to_score.y >= mat[to_score.x].size() - 1) { 
        return v_score; 
    }

    for (int i = to_score.y - 1; i >= 0; i--) { 
        v_score.x++; 
        if (mat[to_score.x][i] >= mat[to_score.x][to_score.y]) { 
            break; 
        }
    }

    for (int i = to_score.y + 1; i < mat[to_score.x].size(); i++) { 
        v_score.y++; 
        if (mat[to_score.x][i] >= mat[to_score.x][to_score.y]) { 
            break; 
        }
    }

    return v_score; 
}

std::vector<int> get_solve_info(std::string path) { 
    std::vector<int> r_values; 

    height_matrix h_mat = con_height_mat(path); 

    int max = 0; 
    int num_vis = (2 * h_mat.size()) + (2 * (h_mat[0].size() - 2)); 

    for (int i = 1; i < h_mat.size() - 1; i++) { 
        for (int j = 1; j < h_mat[i].size() - 1; j++) { 
            point_2D score_h = score_horiz(h_mat, point_2D(i, j)); 
            point_2D score_v = score_vert(h_mat, point_2D(i, j)); 

            
            max = std::max(
                max, 
                (score_h.x * score_h.y * score_v.x * score_v.y)
            ); 
        }
    }

    r_values.push_back(num_vis); 
    r_values.push_back(max); 

    return r_values; 
}