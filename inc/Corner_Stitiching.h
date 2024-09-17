#ifndef CORNER_STITCHING_H
#define CORNER_STITCHING_H

#include "Tile.h"
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>

class Corner_Stitching{
public: 

    //data member
    unordered_map <int, Tile> tile;
    set <int> block_tile_sort;
    vector <pair <int, coordinate>> point_finding_result;
    string bottom_right_tile;

    //member function
    coordinate point_finding(int tile_name, coordinate target);
    vector<int> neighbor_finding();
    void insert_tile(Tile);

}


#endif