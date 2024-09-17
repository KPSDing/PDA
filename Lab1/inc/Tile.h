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
    //
    coordinate(int in_x, int in_y):x(in_x),y(in_y){}

    // Overloading the == operator
    bool operator==(const coordinate& other) const {
        return x == other.x && y == other.y;
    }
};


class Tile{
public:
    //Constructor
    Tile() : type(0), bottom_left(0,0), w(0), h(0) {}
    Tile(bool in_type, coordinate in_coor, int in_w, int in_h) : type(0), bottom_left(0,0), w(0), h(0) {}
    //data member
    bool type; //0:vacant, 1:block
    coordinate bottom_left;
    int w, h;
    string top, down, left, right;

    //member function
    bool point_inside_tile(coordinate);


};


#endif