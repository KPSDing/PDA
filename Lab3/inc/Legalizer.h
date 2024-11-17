#ifndef LEGALIZER_H
#define LEGALIZER_H

using namespace std;

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <iomanip>

#define PSEUDO -1
#define FF 0
#define GATE 1
#define INSERTFF 2
#define ILLEGAL_FF 3

struct Point{
    double x, y;
};

class Block{
    public:
        string name;
        Point BL;
        Point original;
        double width, height;
        int type; // 0 for FFs, 1 for Gates, 2 for Inserted FFs
    private:    
};

class CompareByDifference {
    int target;

public:
    explicit CompareByDifference(int t) : target(t) {}

    bool operator()(const int& a, const int& b) const {
        int diff_a = std::abs(a - target);
        int diff_b = std::abs(b - target);

        if (diff_a == diff_b) {
            return a < b;
        }

        return diff_a < diff_b;
    }
};

using Map_x_block = map<double, Block*>;

class Legalizer {
    public:
        // member functions
        Legalizer();
        void parser_info(string filename);
        void parser_opt(string filename);
        // void output_file(string filename);
        void output_draw(string filename);
        //void block_legalize(string blockname);

        void check_input();

        //data member
        unordered_map<string, Block> all_blocks;
        vector<Map_x_block> PlacementRow;

    private:
        bool window_search(Block* tempblock);
        

        // for block
        bool check_overlap(Block block);
        bool check_inside_boundary(Block block);
        bool check_legal(Block block);
        void Make_onsite(Block* block);
        int Get_PLR_index(Block block);


        double alpha, beta;
        double die_x, die_y, die_width, die_height;
        double cost;
        double max_width, max_height;

        // for placementrow
        double Placementrow_startX, Placementrow_startY, Placementrow_siteWidth, Placementrow_siteHeight, Placementrow_totalNumOfSites, Placementrow_rightmost;
        void insert_block(Block* new_block);
        void remove_block(string blockname);
        
        // for test legal
        double total_success;
};

#endif
