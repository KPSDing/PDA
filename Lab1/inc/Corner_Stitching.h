#ifndef CORNER_STITCHING_H
#define CORNER_STITCHING_H

#include "Tile.h"
#include <vector>
#include <unordered_map>
#include <fstream>
#include <set>
#include <utility>

class Corner_Stitching{
public: 

    //data member
    unordered_map <int, Tile> tile;
    set <int> block_tile_sort;
    vector <coordinate> point_finding_result;

    //member function
    void parse_input(string input_file);
    void parser_output(string output_file);
    pair<bool, int> point_finding(int tile_name, coordinate target);
    pair<int, int>  neighbor_finding(int tile_name);
    vector <int> area_searching(coordinate target, int w, int h);
    vector <int> enumerate_all_tiles(coordinate top_left_point, int w, int h); 
    void tile_creation(int block_index, int x, int y, int width, int height);

private:
    //data member
    int outline_width;
    int outline_height;
    int vacant_tile_counter = -1;
    int bottom_right_tile = -1;

    //member function
    int vertical_split(int tile_name, int x);
    int horizontal_split(int tile_name, int y);
    void vertical_merge();
    void horizontal_merge();

};


#endif