#include "Tile.h"

Tile::Tile(){
    type = VACANT;
    bottom_left.x = 0;
    bottom_left.y = 0;
    w = 0;
    h = 0;
    top = down = left = right = -1;
}

Tile::Tile(bool in_type, coordinate in_coor, int in_w, int in_h){
    type = in_type;
    bottom_left = in_coor;
    w = in_w;
    h = in_h;
    top = down = left = right = -1;
}

bool Tile::point_inside_tile(coordinate target){
    if(bottom_left.x <= target.x && target.x < bottom_left.x + w && bottom_left.y <= target.y && target.y < bottom_left.y + h){
        return true;
    }else{
        return false;
    }
}