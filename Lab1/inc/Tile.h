#ifndef TILE_H
#define TILE_H

#include <iostream>
#include <string>

#define VACANT 0
#define BLOCK 1

using namespace std;

struct coordinate {
    int x;
    int y;

    // Overloading the == operator
    bool operator==(const coordinate& other) const {
        return x == other.x && y == other.y;
    }
};


class Tile{
public:
    //Constructor
    Tile();
    Tile(bool in_type, coordinate in_coor, int in_w, int in_h);
    //data member
    bool type; //0:vacant, 1:block
    coordinate bottom_left;
    int w, h;
    int top, down, left, right;

    //member function
    bool point_inside_tile(coordinate);


};


#endif