#include "Corner_Stitching.h"

pair<bool, coordinate> Corner_Stitching::point_finding(int tile_name, coordinate target){
    //cout << "Finding the target in tile " << tile_name << endl;
    pair<bool, coordinate> result = {false, {0, 0}};
    //found the tile
    if(tile[tile_name].point_inside_tile(target) == true){
        //cout << "   1. The target is in tile " << tile_name << " at coordinate (" << target.x << ", " << target.y << ")" << endl;
        result = {true, tile[tile_name].bottom_left};
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
    cout << "============ top ===============" << endl;
    int top_tile = 0;
    if(tile[tile_name].top != 0){
        top_tile = tile[tile_name].top;
        cout << "top_tile: " << top_tile << endl;

        do{
            if(tile[top_tile].bottom_left.x < tile[tile_name].bottom_left.x){
                if(flag == false){
                    if(tile[top_tile].type == BLOCK){
                        cout << "add block_neighbor: " << top_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                else if(tile[top_tile].bottom_left.x + tile[top_tile].w > tile[tile_name].bottom_left.x){
                    if(tile[top_tile].type == BLOCK){
                        cout << "add block_neighbor: " << top_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                cout << "no add top_tile: " << top_tile << " break" << endl;
                break;
            }

            if(tile[top_tile].type == BLOCK){
                cout << "add block_neighbor: " << top_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            if(tile[top_tile].bottom_left.x == tile[tile_name].bottom_left.x){
                cout << "add top_tile: " << top_tile << " break" << endl;
                break;
            }

            top_tile = tile[top_tile].left;
            flag = true;
        } while (top_tile != 0);
    }
    
    //down
    cout << block_neighbor <<" " << vacant_neighbor <<endl;
    cout << "============ down ===============" << endl;
    int down_tile = 0;
    flag = false;
    if(tile[tile_name].down != 0){
        down_tile = tile[tile_name].down;

        do{
            cout << "down_tile: " << down_tile << endl;
            if(tile[down_tile].bottom_left.x >= tile[tile_name].bottom_left.x + tile[tile_name].w){
                if(flag == false){
                    if(tile[down_tile].type == BLOCK){
                        cout << "add block_neighbor: " << down_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                cout << "no add down_tile: " << down_tile << " break" << endl;
                break;
            }

            if(tile[down_tile].type == BLOCK){
                cout << "add block_neighbor: " << down_tile << endl;
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
    cout << block_neighbor <<" " << vacant_neighbor <<endl;
    cout << "============ left ===============" << endl;
    int left_tile = 0;
    flag = false;
    if(tile[tile_name].left != 0){
        left_tile = tile[tile_name].left;
        cout << "left_tile: " << left_tile << endl;

        do{
            if(tile[left_tile].bottom_left.y >= tile[tile_name].bottom_left.y + tile[tile_name].h){
                if (flag == false){
                    if(tile[left_tile].type == BLOCK){
                        cout << "add block_neighbor: " << left_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                
                cout << "no add left_tile: " << left_tile << " break" << endl;
                break;
            }

            if(tile[left_tile].type == BLOCK){
                cout << "add block_neighbor: " << left_tile << endl;
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
    cout << block_neighbor <<" " << vacant_neighbor <<endl;
    cout << "============ right ===============" << endl;
    int right_tile = 0;
    flag = false;
    if(tile[tile_name].right != 0){
        right_tile = tile[tile_name].right;
        cout << "right_tile: " << right_tile << endl;        

        do{
            if(tile[right_tile].bottom_left.y < tile[tile_name].bottom_left.y){
                if(flag == false){
                    if(tile[right_tile].type == BLOCK){
                        cout << "add block_neighbor: " << right_tile << endl;
                        block_neighbor ++;
                    }
                    else{
                        vacant_neighbor ++;
                    }
                }
                cout << "no add right_tile: " << right_tile << " break" << endl;
                break;
            }

            if(tile[right_tile].type == BLOCK){
                cout << "add block_neighbor: " << right_tile << endl;
                block_neighbor ++;
            }
            else{
                vacant_neighbor ++;
            }

            if(tile[right_tile].bottom_left.y == tile[tile_name].bottom_left.y){
                cout << "add right_tile: " << right_tile << " break" << endl;
                break;
            }

            right_tile = tile[right_tile].down;
            flag = true;
        } while (right_tile != 0);
    }
    return make_pair(block_neighbor, vacant_neighbor);
}

void Corner_Stitching::insert_tile(Tile){
    return ;
}
