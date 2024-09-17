#include "Corner_Stitching.h"

pair<bool, coordinate> Corner_Stitching::point_finding(int tile_name, coordinate target){
    pair<bool, coordinate> result = {false, {0, 0}};
    //found the tile
    if(tile[tile_name].point_inside_tile(target) == true){
        result = {true, tile[tile_name].bottom_left};
        return result;
    }

    //not found the tile
    if(tile[tile_name].top != -1 && tile[tile[tile_name].top].bottom_left.y <= target.y){
        int top_tile = tile[tile_name].top;
        result = point_finding(top_tile, target);
        if(result.first == true){
            return result;
        }
    }

    if(tile[tile_name].left != -1 && tile[tile[tile_name].left].bottom_left.x <= target.x){
        int left_tile = tile[tile_name].left;
        result = point_finding(left_tile, target);
        if(result.first == true){
            return result;
        }
    }


}

vector<int> Corner_Stitching::neighbor_finding(){

}

void Corner_Stitching::insert_tile(Tile){

}
