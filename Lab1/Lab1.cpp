#include <bits/stdc++.h>
#include "Tile.h"
#include "Corner_Stitching.h"

using namespace std;

int main(){
    Tile tile1 = Tile(1, {0, 0}, 1, 1);
    Tile tile2 = Tile(1, {1, 0}, 1, 1);
    Tile tile3 = Tile(1, {0, 1}, 1, 1);
    Tile tile4 = Tile(1, {1, 1}, 1, 1);
    coordinate target = {0, 0};
    Corner_Stitching corner_stitching;
    corner_stitching.point_finding(1, {0, 0});
    
    return 0;
}