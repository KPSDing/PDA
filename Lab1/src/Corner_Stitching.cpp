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
            //tile_creation(block_index, x, y, width, height);
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

pair<int, int> Corner_Stitching::find_top_neighbor(int tile_name) {
    int block_neighbor = 0;
    int vacant_neighbor = 0;
    bool flag = false;
    int top_tile = 0;

    if (tile[tile_name].top != 0) {
        top_tile = tile[tile_name].top;

        do {
            if (tile[top_tile].bottom_left.x < tile[tile_name].bottom_left.x) {
                if (!flag) {
                    if (tile[top_tile].type == BLOCK) {
                        block_neighbor++;
                    } else {
                        vacant_neighbor++;
                    }
                } else if (tile[top_tile].bottom_left.x + tile[top_tile].w > tile[tile_name].bottom_left.x) {
                    if (tile[top_tile].type == BLOCK) {
                        block_neighbor++;
                    } else {
                        vacant_neighbor++;
                    }
                }
                break;
            }

            if (tile[top_tile].type == BLOCK) {
                block_neighbor++;
            } else {
                vacant_neighbor++;
            }

            if (tile[top_tile].bottom_left.x == tile[tile_name].bottom_left.x) {
                break;
            }

            top_tile = tile[top_tile].left;
            flag = true;
        } while (top_tile != 0);
    }

    return make_pair(block_neighbor, vacant_neighbor);
}

pair<int, int> Corner_Stitching::find_down_neighbor(int tile_name) {
    int block_neighbor = 0;
    int vacant_neighbor = 0;
    bool flag = false;
    int down_tile = 0;

    if (tile[tile_name].down != 0) {
        down_tile = tile[tile_name].down;

        do {
            if (tile[down_tile].bottom_left.x >= tile[tile_name].bottom_left.x + tile[tile_name].w) {
                if (!flag) {
                    if (tile[down_tile].type == BLOCK) {
                        block_neighbor++;
                    } else {
                        vacant_neighbor++;
                    }
                }
                break;
            }

            if (tile[down_tile].type == BLOCK) {
                block_neighbor++;
            } else {
                vacant_neighbor++;
            }

            down_tile = tile[down_tile].right;
            flag = true;
        } while (down_tile != 0);
    }

    return make_pair(block_neighbor, vacant_neighbor);
}

pair<int, int> Corner_Stitching::find_left_neighbor(int tile_name) {
    int block_neighbor = 0;
    int vacant_neighbor = 0;
    bool flag = false;
    int left_tile = 0;

    if (tile[tile_name].left != 0) {
        left_tile = tile[tile_name].left;

        do {
            if (tile[left_tile].bottom_left.y >= tile[tile_name].bottom_left.y + tile[tile_name].h) {
                if (!flag) {
                    if (tile[left_tile].type == BLOCK) {
                        block_neighbor++;
                    } else {
                        vacant_neighbor++;
                    }
                }
                break;
            }

            if (tile[left_tile].type == BLOCK) {
                block_neighbor++;
            } else {
                vacant_neighbor++;
            }

            left_tile = tile[left_tile].top;
            flag = true;
        } while (left_tile != 0);
    }

    return make_pair(block_neighbor, vacant_neighbor);
}

pair<int, int> Corner_Stitching::find_right_neighbor(int tile_name) {
    int block_neighbor = 0;
    int vacant_neighbor = 0;
    bool flag = false;
    int right_tile = 0;

    if (tile[tile_name].right != 0) {
        right_tile = tile[tile_name].right;

        do {
            if (tile[right_tile].bottom_left.y < tile[tile_name].bottom_left.y) {
                if (!flag) {
                    if (tile[right_tile].type == BLOCK) {
                        block_neighbor++;
                    } else {
                        vacant_neighbor++;
                    }
                }
                break;
            }

            if (tile[right_tile].type == BLOCK) {
                block_neighbor++;
            } else {
                vacant_neighbor++;
            }

            if (tile[right_tile].bottom_left.y == tile[tile_name].bottom_left.y) {
                break;
            }

            right_tile = tile[right_tile].down;
            flag = true;
        } while (right_tile != 0);
    }

    return make_pair(block_neighbor, vacant_neighbor);
}

pair<int, int> Corner_Stitching::neighbor_finding(int tile_name){
    int vacant_neighbor = 0;
    int block_neighbor = 0;
    
    auto top_neighbor = find_top_neighbor(tile_name);
    block_neighbor += top_neighbor.first;
    vacant_neighbor += top_neighbor.second;

    auto down_neighbor = find_down_neighbor(tile_name);
    block_neighbor += down_neighbor.first;
    vacant_neighbor += down_neighbor.second;

    auto left_neighbor = find_left_neighbor(tile_name);
    block_neighbor += left_neighbor.first;
    vacant_neighbor += left_neighbor.second;

    auto right_neighbor = find_right_neighbor(tile_name);
    block_neighbor += right_neighbor.first;
    vacant_neighbor += right_neighbor.second;

    return make_pair(block_neighbor, vacant_neighbor);
}

void Corner_Stitching::tile_creation(int block_index, int x, int y, int width, int height) {
    // 左上角點
    coordinate left_top = {x, y + height};
    auto top_left_point_result = point_finding(bottom_right_tile, left_top);
    int top_left_tile_name = top_left_point_result.second;
    vector <int> top_edge_tile = find_tile_contain_horizontal_edge(top_left_tile_name, x, x + width, y + height);

    vector <int> left_edge_tile = find_tile_contain_vertical_edge(top_left_tile_name, y, y + height, x);
    
    vector <int> right_edge_tile = find_tile_contain_vertical_edge(top_edge_tile[top_edge_tile.size()-1], y, y + height, x);

    coordinate left_bottom = {x, y};
    auto bottom_left_point_result = point_finding(bottom_right_tile, left_bottom);
    int bottom_left_tile_name = bottom_left_point_result.second;
    vector <int> bottom_edge_tile = find_tile_contain_horizontal_edge(bottom_left_tile_name, x, x + width, y);

    cout << "Top edge tile: ";
    for(auto it : top_edge_tile){
        cout << it << " ";
    }
    cout << endl;

    cout << "Left edge tile: ";
    for(auto it : left_edge_tile){
        cout << it << " ";
    }
    cout << endl;

    cout << "Bottom edge tile: ";
    for(auto it : bottom_edge_tile){
        cout << it << " ";
    }
    cout << endl;

    cout << "Right edge tile: ";
    for(auto it : right_edge_tile){
        cout << it << " ";
    }
    cout << endl;
    
    return;
}

vector <int> Corner_Stitching::find_tile_contain_horizontal_edge(int tile_name, int x_min, int x_max, int target_y){
    
    Tile target_tile = tile[tile_name];
    vector <int> result;
    
    while(target_tile.bottom_left.x < x_max){
        if(target_tile.bottom_left.x + target_tile.w > x_min && target_tile.bottom_left.y <= target_y && target_tile.bottom_left.y + target_tile.h > target_y){
            result.push_back(tile_name);
            tile_name = tile[tile_name].right;
            if(tile_name == 0){
                break;
            }
            target_tile = tile[tile_name];
        }
        else{
            tile_name = tile[tile_name].down;
            if(tile_name == 0){
                break;
            }
            target_tile = tile[tile_name];
        }
    }

    return result;
}

vector <int> Corner_Stitching::find_tile_contain_vertical_edge(int tile_name, int y_min, int y_max, int target_x){

    vector<int> result;
    
    while (tile_name != 0) {
        Tile& target_tile = tile[tile_name];
        std::cout << "Tile name: " << tile_name << std::endl;
        
        if (target_tile.bottom_left.y + target_tile.h > y_min && target_tile.bottom_left.y < y_max &&
            target_tile.bottom_left.x <= target_x && target_tile.bottom_left.x + target_tile.w > target_x) {
            result.push_back(tile_name);
            tile_name = target_tile.down;
        } else {
            tile_name = target_tile.right;
        }
    }

    return result;
}