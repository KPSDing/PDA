#include "Corner_Stitching.h"

void Corner_Stitching::parse_input(string input_file){
    ifstream get_input_file(input_file , ios::in);
    if(!get_input_file) cout << "cannot get input file";

    get_input_file >> outline_width >> outline_height;

    //initialize the outline tile
    coordinate outline_bottom_left = {0, 0};
    tile[-1] = Tile(VACANT, outline_bottom_left, outline_width, outline_height, OUTOFBOUNDARY, OUTOFBOUNDARY, OUTOFBOUNDARY, OUTOFBOUNDARY);

    string command;
    while (get_input_file >> command) {
        if (command == "P") {
            coordinate target;
            get_input_file >> target.x >> target.y;
            auto result = point_finding(bottom_right_tile, target); // Assuming 0 is the starting tile
            point_finding_result.push_back(tile[result.second].bottom_left);
        } else {
            int block_index, x, y, width, height;
            block_index = stoi(command);
            block_tile_sort.insert(block_index);
            get_input_file >> x >> y >> width >> height;
            tile_creation(block_index, x, y, width, height);
        }
    }
    return ;
}

void Corner_Stitching::parser_output(string output_file){
    ofstream output(output_file, ios::out);
    if(!output) cout << "cannot output file";

    //total tile number
    output << tile.size() << endl;

    //block tile neighbor
    for(auto it : block_tile_sort){
        auto result = neighbor_finding(it);
        output << it << " " << result.first << " " << result.second << endl;
    }

    for(auto it : point_finding_result){
        output << it.x << " " << it.y << endl;
    }
    return ;
}

pair<bool, int> Corner_Stitching::point_finding(int tile_name, coordinate target){
    //cout << "Finding the target in tile " << tile_name << endl;
    pair<bool, int> result = {false, -1};
    //found the tile
    if(tile[tile_name].point_inside_tile(target) == true){
        //cout << "   1. The target is in tile " << tile_name << " at coordinate (" << target.x << ", " << target.y << ")" << endl;
        result = {true, tile_name};
        return result;
    }

    //not found the tile
    if(tile[tile_name].bottom_left.y > target.y){
        return result;
    }

    if(tile[tile_name].top != 0){
        //cout << "   2. Find the target in tile " << tile[tile_name].top << endl;
        int top_tile = tile[tile_name].top;
        result = point_finding(top_tile, target);
        if(result.first == true){
            return result;
        }
    }

    if(tile[tile_name].left != 0){
        //cout << "   3. Find the target in tile " << tile[tile_name].left << endl;
        int left_tile = tile[tile_name].left;
        result = point_finding(left_tile, target);
        if(result.first == true){
            return result;
        }
    }
    return result;

}

pair<int, int> Corner_Stitching::neighbor_finding(int tile_name){
    int vacant_neighbor = 0;
    int block_neighbor = 0;
    bool flag = false;
    
    //top
    // cout << "============ top ===============" << endl;
    int top_tile = 0;
    if(tile[tile_name].top != 0){
        top_tile = tile[tile_name].top;
        // cout << "top_tile: " << top_tile << endl;

        do{
            if(tile[top_tile].bottom_left.x < tile[tile_name].bottom_left.x){
                if(flag == false){
                    if(tile[top_tile].type == BLOCK){
                        // cout << "add block_neighbor: " << top_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                else if(tile[top_tile].bottom_left.x + tile[top_tile].w > tile[tile_name].bottom_left.x){
                    if(tile[top_tile].type == BLOCK){
                        // cout << "add block_neighbor: " << top_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                // cout << "no add top_tile: " << top_tile << " break" << endl;
                break;
            }

            if(tile[top_tile].type == BLOCK){
                // cout << "add block_neighbor: " << top_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            if(tile[top_tile].bottom_left.x == tile[tile_name].bottom_left.x){
                // cout << "add top_tile: " << top_tile << " break" << endl;
                break;
            }

            top_tile = tile[top_tile].left;
            flag = true;
        } while (top_tile != 0);
    }
    
    //down
    // cout << block_neighbor <<" " << vacant_neighbor <<endl;
    // cout << "============ down ===============" << endl;
    int down_tile = 0;
    flag = false;
    if(tile[tile_name].down != 0){
        down_tile = tile[tile_name].down;

        do{
            // cout << "down_tile: " << down_tile << endl;
            if(tile[down_tile].bottom_left.x >= tile[tile_name].bottom_left.x + tile[tile_name].w){
                if(flag == false){
                    if(tile[down_tile].type == BLOCK){
                        // cout << "add block_neighbor: " << down_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                // cout << "no add down_tile: " << down_tile << " break" << endl;
                break;
            }

            if(tile[down_tile].type == BLOCK){
                // cout << "add block_neighbor: " << down_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            down_tile = tile[down_tile].right;
            flag = true;
        } while (down_tile != 0);
    }

    //left
    // cout << block_neighbor <<" " << vacant_neighbor <<endl;
    // cout << "============ left ===============" << endl;
    int left_tile = 0;
    flag = false;
    if(tile[tile_name].left != 0){
        left_tile = tile[tile_name].left;
        // cout << "left_tile: " << left_tile << endl;

        do{
            if(tile[left_tile].bottom_left.y >= tile[tile_name].bottom_left.y + tile[tile_name].h){
                if (flag == false){
                    if(tile[left_tile].type == BLOCK){
                        // cout << "add block_neighbor: " << left_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                
                // cout << "no add left_tile: " << left_tile << " break" << endl;
                break;
            }

            if(tile[left_tile].type == BLOCK){
                // cout << "add block_neighbor: " << left_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            left_tile = tile[left_tile].top;
            flag = true;
        } while (left_tile != 0);
    }

    //right
    // cout << block_neighbor <<" " << vacant_neighbor <<endl;
    // cout << "============ right ===============" << endl;
    int right_tile = 0;
    flag = false;
    if(tile[tile_name].right != 0){
        right_tile = tile[tile_name].right;
        // cout << "right_tile: " << right_tile << endl;        

        do{
            if(tile[right_tile].bottom_left.y < tile[tile_name].bottom_left.y){
                if(flag == false){
                    if(tile[right_tile].type == BLOCK){
                        // cout << "add block_neighbor: " << right_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                // cout << "no add right_tile: " << right_tile << " break" << endl;
                break;
            }

            if(tile[right_tile].type == BLOCK){
                // cout << "add block_neighbor: " << right_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            if(tile[right_tile].bottom_left.y == tile[tile_name].bottom_left.y){
                // cout << "add right_tile: " << right_tile << " break" << endl;
                break;
            }

            right_tile = tile[right_tile].down;
            flag = true;
        } while (right_tile != 0);
    }
    return make_pair(block_neighbor, vacant_neighbor);
}

void Corner_Stitching::tile_creation(int block_index, int x, int y, int width, int height){
    
}

int Corner_Stitching::horizontal_split(int tile_name, int y){
    Tile new_tile = tile[tile_name];
    new_tile.h = y - tile[tile_name].bottom_left.y;

    int new_tile_name = vacant_tile_counter--;
    tile[new_tile_name] = new_tile;
    tile[new_tile_name].top = tile_name;

    tile[tile_name].bottom_left.y = y;
    tile[tile_name].h = tile[tile_name].h - new_tile.h;
    tile[tile_name].down = new_tile_name;

    return new_tile_name;
}

int Corner_Stitching::vertical_split(int tile_name, int x){
    Tile new_tile = tile[tile_name];
    new_tile.w = x - tile[tile_name].bottom_left.x;

    int new_tile_name = vacant_tile_counter--;
    tile[new_tile_name] = new_tile;
    tile[new_tile_name].right = tile_name;

    tile[tile_name].bottom_left.x = x;
    tile[tile_name].w = tile[tile_name].w - new_tile.w;
    tile[tile_name].left = new_tile_name;

    return new_tile_name;
}
