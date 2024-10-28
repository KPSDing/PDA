#include <bits/stdc++.h>
#include "Tile.h"
#include "Corner_Stitching.h"

using namespace std;

int main(int argc, char *argv[]){
    Corner_Stitching corner_stitching;
    corner_stitching.tile[-1] = Tile(0, {0, 0}, 100, 5, -3, 0, 0, 0);
    corner_stitching.tile[-2] = Tile(0, {0, 5}, 65, 10, 4, -1, 0, 3);
    corner_stitching.tile[-3] = Tile(0, {85, 5}, 15, 60, -6, -1, 3, 0);
    corner_stitching.tile[-4] = Tile(0, {0, 15}, 5, 20, -5, -2, 0, 4);
    corner_stitching.tile[4] = Tile(1, {5, 15}, 60, 20, 1, -2, -4, 3);
    corner_stitching.tile[3] = Tile(1, {65, 5}, 20, 60, 2, -1, -2, -3);
    corner_stitching.tile[-5] = Tile(0, {0, 35}, 15, 60, -8, -4, 0, 5);
    corner_stitching.tile[5] = Tile(1, {15, 35}, 20, 60, -8, 4, -5, -7);
    corner_stitching.tile[1] = Tile(1, {35, 35}, 30, 30, 2, 4, 5, 3);
    corner_stitching.tile[2] = Tile(1, {35, 65}, 60, 20, -7, 1, 5, -6);
    corner_stitching.tile[-6] = Tile(0, {95, 65}, 5, 20, -7, -3, 2, 0);
    corner_stitching.tile[-7] = Tile(0, {35, 85}, 65, 10, -8, 2, 5, 0);
    corner_stitching.tile[-8] = Tile(0, {0, 95}, 100, 5, 0, -5, 0, 0);

    cout << corner_stitching.tile.size() << endl;

    vector <coordinate> point_result;

    // Test point_finding
    coordinate target = {15, 35};
    pair<bool, int> result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // Test point_finding
    target = {10, 10};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);
    
    // Test point_finding
    target = {50, 50};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // Test point_finding
    target = {70, 70};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // Test point_finding
    target = {90, 10};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // Test point_finding
    target = {5, 95};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // Test point_finding
    target = {10, 85};
    result = corner_stitching.point_finding(-1, target);
    point_result.push_back(corner_stitching.tile[result.second].bottom_left);

    // print point_result
    for(auto it : point_result){
        cout << it.x << " " << it.y << endl;
    }

    return 0;
}