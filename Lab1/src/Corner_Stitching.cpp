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

vector<int> Corner_Stitching::neighbor_finding(){
    return {};
}

void Corner_Stitching::insert_tile(Tile){
    return ;
}
