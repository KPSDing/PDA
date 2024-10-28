#include <bits/stdc++.h>
#include "Tile.h"
#include "Corner_Stitching.h"

using namespace std;

int main(int argc, char *argv[]){
    
    Corner_Stitching corner_stitching;
    corner_stitching.parse_input(argv[1]);
    corner_stitching.parser_output(argv[2]);
    
    return 0;
}