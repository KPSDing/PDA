#ifndef _LEGALIZER_H
#define _LEGALIZER_H

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <unordered_set>

#define FF 0
#define GATE 1

struct coor{
    int x, y;
};

class Block{
    public:
        int x, y;
        int width, height;
        bool type; // 0 for FFs, 1 for Gates
        Block(int x, int y, int width, int height, bool type);
    private:    

};

class Placementrow{
    public:
        int startX, startY;
        int siteWidth, siteHeight;
        int totalNumOfSites;
    private:
}

class Legalizer {
    public:
        // member functions
        Legalizer();
        void parser_info(string filename);
        void parser_opt(string filename);
        void output_file(string filename);
        void output_draw(string filename);
        void block_legalize(string blockname);

        //data member
        unordered_map<string, Block> all_blocks;
        unordered_map<string, Placementrow> all_rows;

        multimap<int, string> x_sorted_blocks;
        multimap<int, string> y_sorted_blocks;
    private:
        coor findnearestsite(coor target_xy);
        coor spiral_search(coor target_xy);

        double alpha, beta;
        int die_x, die_y, die_width, die_height;
        double cost;
};