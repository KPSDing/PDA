#include "Legalizer.h"

Legalizer :: Legalizer(){
    all_blocks.clear();
    PlacementRow.clear();
    cost = 0;
    total_success = 0;
}

void Legalizer::parser_info(string filename){
    ifstream file(filename);

    if(!file.is_open()){
        cout << "Error: File not found" << endl;
        return;
    }

    string ffname;
    double number;

    file >> ffname; // "ALPHA"
    file >> alpha;

    file >> ffname; // "BETA"
    file >> beta;

    file >> ffname; // "DieSize" 
    file >> die_x >> die_y >> die_width >> die_height;

    Block new_block;
    string garbage;
    int placementrow_count = 0;

    // read until file ends
    while(file >> ffname){
        if(ffname.substr(0,2) == "FF" || ffname.substr(0,1) == "C"){
            new_block.name = ffname;
            file >> new_block.BL.x >> new_block.BL.y >> new_block.width >> new_block.height;
            file >> garbage;

            new_block.original.x = new_block.BL.x;
            new_block.original.y = new_block.BL.y;

            if(ffname.substr(0,1) == "C"){
                new_block.type = GATE;
            }
            else{
                new_block.type = FF;
            }

            if(new_block.width > max_width){
                max_width = new_block.width;
            }
            if(new_block.height > max_height){
                max_height = new_block.height;
            }

            all_blocks[ffname] = new_block;
        }  
        else { // "PlacementRows"
            if(placementrow_count == 0){
                file >> Placementrow_startX; // Startx
                file >> Placementrow_startY; // Starty
                file >> Placementrow_siteWidth; // SiteWidth
                file >> Placementrow_siteHeight; // SiteHeight
                file >> Placementrow_totalNumOfSites; // TotalNumSites
                Placementrow_rightmost = Placementrow_startX + Placementrow_siteWidth * (Placementrow_totalNumOfSites-1);
            }
            else {
                double row_info;
                file >> row_info; // Startx
                file >> row_info; // Starty
                file >> row_info; // SiteWidth
                file >> row_info; // SiteHeight
                file >> row_info; // TotalNumSites
            }
            placementrow_count++; 
        }
    }
    
    PlacementRow.resize(placementrow_count); //0-> Placementrow_startY 1-> Placementrow_startY+Placementrow_siteHeight 2-> Placementrow_startY+2*Placementrow_siteHeight...
    Block *pseudoblock = new Block();
    pseudoblock->name = "PseudoBlock";
    pseudoblock->type = PSEUDO;
    pseudoblock->BL.x = Placementrow_startX - 1;
    pseudoblock->BL.y = Placementrow_startY;
    pseudoblock->width = 1;
    pseudoblock->height = Placementrow_siteHeight;
    for(int i=0;i<PlacementRow.size();i++){
        PlacementRow[i].clear();
        PlacementRow[i][Placementrow_startX-1] = pseudoblock;
        PlacementRow[i][Placementrow_rightmost+2] = pseudoblock;
    }

    
    //initialize all_rows occupied_sites
    for(auto it = all_blocks.begin(); it != all_blocks.end(); it++){
        int this_row_height = it->second.height / Placementrow_siteHeight;
        //find index of the row in PlacementRow
        int row_index = (it->second.BL.y - Placementrow_startY) / Placementrow_siteHeight;
        for(int i=0;i<this_row_height && row_index < PlacementRow.size() ;i++,row_index++){
            PlacementRow[row_index][it->second.BL.x] = (&it->second);
        }
    }

    // cout << "PlacementRow size: " << PlacementRow.size() << endl;

    // ofstream file2("output.txt");
    // for(int i=0;i<PlacementRow.size();i++){
    //     cout << "Row " << i << ": " << PlacementRow[i].size() << endl;
    //     file2 << fixed << "     Row index: " << i << " Size: " << PlacementRow[i].size() << endl;
    //     for(auto it = PlacementRow[i].begin(); it != PlacementRow[i].end(); it++){
    //         file2 << fixed << "             map key x: " << it->first << endl;
    //         file2 << fixed << "             Block x: " << it->second->BL.x << " Block y: " << it->second->BL.y << " Block width: " << it->second->width << " Block height: " << it->second->height << " Block type: " << it->second->type << " Block name: " << it->second->name << " Block original x: " << it->second->original.x << " Block original y: " << it->second->original.y << endl;
    //     }
    // }
    // file2.close();
    file.close();
}

void Legalizer::check_input(){
    cout << "ALPHA: " << alpha << endl;
    cout << "BETA: " << beta << endl;
    cout << "DieSize: " << die_x << " " << die_y << " " << die_width << " " << die_height << endl;

    cout << "Blocks: " << all_blocks.size() << endl;
    // for(auto it = all_blocks.begin(); it != all_blocks.end(); it++){
    //     cout << it->first << " " << it->second.BL.x << " " << it->second.BL.y << " " << it->second.width << " " << it->second.height << " " << it->second.type << endl;
    // }

    cout << "PlacementRows: " << PlacementRow.size() << endl;
    for(int i=0;i<PlacementRow.size();i++){
        cout << "Row " << i << ": " << PlacementRow[i].size() << endl;
        // for(auto it = PlacementRow[i].begin(); it != PlacementRow[i].end(); it++){
        //     cout << (*it)->BL.x << " " << (*it)->BL.y << " " << (*it)->width << " " << (*it)->height << " " << (*it)->type << endl;
        // }
    }

}

void Legalizer::parser_opt(string filename){
    ifstream file(filename);

    if(!file.is_open()){
        cout << "Error: File not found" << endl;
        return;
    }

    string line;

    int i = 0;
    ofstream file2("output_illegal.txt", ios::out);

    while (std::getline(file, line)) {
        //cout << "Line " <<  << ": " << line << endl;
        istringstream lineStream(line);
        string part;

        // Part 1: Read "Banking_Cell:"
        lineStream >> part;
        //cout << "   Part 1: " << endl;
        // Part 2: Collect FFs to be removed until " --> "
        while (lineStream >> part) {
            if (part == "-->") {
                break;
            }
            remove_block(part);
        }
        //cout << "   Part 2: " << endl;

        // Part 3: Read the merged FF name and coordinates after " --> "
        Block new_block;
        lineStream >> new_block.name >> new_block.original.x >> new_block.original.y >> new_block.width >> new_block.height;
        new_block.BL.x = new_block.original.x;
        new_block.BL.y = new_block.original.y;
        Make_onsite(&new_block);

        

        //cout << "   Part 3: " << endl;
        bool find_insert = window_search(&new_block);
        if(find_insert){
            //cout << "       Success: " << new_block.name << " " << new_block.BL.x << " " << new_block.BL.y << " " << new_block.width << " " << new_block.height << endl;
            total_success ++;
            new_block.type = INSERTFF;
            insert_block(&new_block);
        }
        else{
            //cout << "Error: Cannot legalize the merged block" << endl;
            file2 << "i: " << i << " " << new_block.name << " " << new_block.BL.x << " " << new_block.BL.y << " " << new_block.width << " " << new_block.height << endl;
            new_block.type = ILLEGAL_FF;
            insert_block(&new_block);
        }
        i++;
    }
    file.close();
    file2.close();
    cout << "Total success: " << total_success << endl;
}

void Legalizer::output_draw(string filename){
    ofstream file(filename, ios::out);
    file << std::fixed << "die " << die_x << " " << die_y << " " << die_width << " " << die_height <<endl;
    for(int i=0;i<PlacementRow.size();i++){
        file << std::fixed << "4 " << Placementrow_startX << " " << Placementrow_startY + i*Placementrow_siteHeight << " " << Placementrow_rightmost - Placementrow_startX + Placementrow_siteWidth << " " << Placementrow_siteHeight << endl;
    }
 
    for(auto it = all_blocks.begin(); it != all_blocks.end(); it++){
        if(it->second.type == FF){
            file << std::fixed << "2 " << it->second.BL.x << " " << it->second.BL.y << " " << it->second.width << " " << it->second.height << endl;
        }
        else if(it->second.type == GATE){
            file << std::fixed << "1 " << it->second.BL.x << " " << it->second.BL.y << " " << it->second.width << " " << it->second.height << endl;
        }
        else if(it->second.type == ILLEGAL_FF){
            file << std::fixed << "0 " << it->second.BL.x << " " << it->second.BL.y << " " << it->second.width << " " << it->second.height << endl;
        }
        else {
            file << std::fixed << "3 " << it->second.BL.x << " " << it->second.BL.y << " " << it->second.width << " " << it->second.height << endl;
        } 
    }
    file.close();
}

void Legalizer::Make_onsite(Block* block) {
    int row_index = Get_PLR_index(*block);
    double site_y = Placementrow_startY + row_index * Placementrow_siteHeight;
    double site_y_upper = site_y + Placementrow_siteHeight;
    if (abs(block->BL.y - site_y) < abs(block->BL.y - site_y_upper)) {
        block->BL.y = site_y;
    }
    else {
        block->BL.y = site_y_upper;
    }
}

int Legalizer::Get_PLR_index(Block block){
    int row_index = (block.BL.y - Placementrow_startY) / Placementrow_siteHeight;
    if (row_index < 0 ) {
        row_index = 0;
    }
    else if (row_index >= PlacementRow.size()) {
        row_index = PlacementRow.size() - 1;
    }
    return row_index;
}

bool Legalizer::check_overlap(Block block) {
    int this_row_height = block.height / Placementrow_siteHeight;
    int row_index = Get_PLR_index(block);
    bool overlap = false;

    // cout << "Check overlap: " << block.name << endl;
    // cout << "Row index: " << row_index << " Height: " << this_row_height << endl;
    
    for(int i=0;i<this_row_height;i++, row_index++){
        if(row_index == PlacementRow.size()){
            // cout << "Error: Block is out of top boundary" << endl;
            break;
        }
        // cout <<" i: " << i << " row_index: " << row_index << endl;
        auto& current_row = PlacementRow[row_index];
        if(current_row.empty()) continue;
        if(block.BL.x > PlacementRow[row_index].rbegin()->first){
            // cout << "Error: Block is out of right boundary" << endl;
            overlap = true;
            break;
        }
        else if(block.BL.x < PlacementRow[row_index].begin()->first){
            // cout << "Error: Block is out of left boundary" << endl;
            overlap = true;
            break;
        }
        else{
            auto block_it = current_row.lower_bound(block.BL.x);
            if(block_it->second->type != PSEUDO){
                // cout << " Block x: " << block.BL.x << " Block width: " << block.width << " block_it->first: " << block_it->first << endl;
                if(block.BL.x+block.width > block_it->first){
                    // cout << "Overlap 1" << endl;
                    overlap = true;
                    break;
                }
            }            
            
            if(block_it != PlacementRow[i].begin()){
                block_it = prev(block_it);
                if(block_it->second->type == PSEUDO){
                    continue;
                }
                if(block_it->second->BL.x + block_it->second->width > block.BL.x){
                    // cout << "Overlap 2" << endl;
                    overlap = true;
                    break;
                }
            }
        }
    }
    return overlap;
}

bool Legalizer::check_inside_boundary(Block block) {
    return (block.BL.x >= die_x) && (block.BL.x <= (Placementrow_rightmost + Placementrow_siteWidth)) && (block.BL.x >= Placementrow_startX) && (block.BL.y >= die_y) && ((block.BL.x + block.width) <= (die_x + die_width)) && ((block.BL.y + block.height) <= (die_y + die_height));
}
                    
bool Legalizer::check_legal(Block block) {
    if(!check_inside_boundary(block)){
        //cout << "Error: Block is out of boundary" << endl;
        return false;
    }
    if(check_overlap(block)){
        //cout << "Error: Block is overlapping" << endl;
        return false;
    }
    return true;
}

void Legalizer::insert_block(Block* new_block){
    string blockname = new_block->name;
    all_blocks[blockname] = *new_block;
    Block* stored_block = &all_blocks[blockname];

    int this_row_height = new_block->height / Placementrow_siteHeight;
    int row_index = Get_PLR_index(*new_block);
    for(int i=0;i<this_row_height && row_index < PlacementRow.size();i++, row_index++){
        PlacementRow[row_index][new_block->BL.x] = stored_block;
    }
}

void Legalizer::remove_block(string blockname){
    auto it = all_blocks.find(blockname);
    if(it == all_blocks.end()){
        cout << "Error: Block not found" << endl;
        return;
    }
    Block& block = it->second;

    // remove the block from the PlacementRow
    int this_row_height = block.height / Placementrow_siteHeight;
    int row_index = Get_PLR_index(block);
    for(int i=0;i<this_row_height && row_index < PlacementRow.size();i++, row_index++){
        // cout << "Row index: " << row_index << " Height: " << this_row_height << endl;
        // cout << "Block name: " << block.name << endl;
        PlacementRow[row_index].erase(block.BL.x);
        if( PlacementRow[row_index].find(block.BL.x) != PlacementRow[row_index].end() ){
            cout << "Error: Block is not removed from PlacementRow" << endl;
        }
    }
    all_blocks.erase(block.name);
}


bool Legalizer::window_search(Block* tempblock) {
    // cout << "       window_search: " << endl;
    Block* testblock = new Block();
    testblock->BL = tempblock->BL;
    testblock->width = tempblock->width;
    testblock->height = tempblock->height;

    // cout << "           Part a: " << endl;
    int row_index = Get_PLR_index(*tempblock);
    int this_row_height = tempblock->height / Placementrow_siteHeight;

    // Initialize set with custom comparator
    set<double, CompareByDifference> need_to_judge(CompareByDifference(tempblock->BL.x));

    // Initialize iterators for current rows
    vector<decltype(PlacementRow[0].begin())> current_row_r(this_row_height);
    vector<decltype(PlacementRow[0].begin())> current_row_l(this_row_height);

    for (int i = 0; i < this_row_height && row_index < PlacementRow.size(); i++, row_index++) {
        if(PlacementRow[row_index].empty()) continue;
        current_row_r[i] = PlacementRow[row_index].upper_bound(tempblock->BL.x);

        if (current_row_r[i] != PlacementRow[row_index].begin()) {
            current_row_l[i] = prev(current_row_r[i]);
        } else {
            current_row_l[i] = current_row_r[i];
        }

        if (current_row_r[i] != PlacementRow[row_index].end() && current_row_r[i]->first <= Placementrow_rightmost) {
            // cout << "Current row r: " << current_row_r[i]->first << " " << current_row_r[i]->second->name  << " width: " << current_row_r[i]->second->width << endl;
            need_to_judge.insert(current_row_r[i]->first - tempblock->width);
            // need_to_judge.insert(current_row_r[i]->first + current_row_r[i]->second->width);
        }
        if (current_row_l[i] != PlacementRow[row_index].end() && current_row_l[i]->first >= Placementrow_startX) {
            // cout << "Current row l: " << current_row_l[i]->first << " " << current_row_l[i]->second->name << " width: " << current_row_l[i]->second->width << endl;
            need_to_judge.insert(current_row_l[i]->first + current_row_l[i]->second->width);
        }
    }
    // cout << "           Part c: " << endl;
    // cout << " X: " << tempblock->BL.x << " Y: " << tempblock->BL.y << " W: " << tempblock->width << " H: " << tempblock->height << endl;
    // cout << " Need to judge: " << need_to_judge.size() << endl;
    for (int i = 0; i < this_row_height && row_index < PlacementRow.size(); i++, row_index++) {

        if(PlacementRow[row_index].empty()) continue;
        while (current_row_r[i]->second->type != PSEUDO) {
            // cout << "Current row r: " << current_row_r[i]->first << " " << current_row_r[i]->second->name << " width: " << current_row_r[i]->second->width << endl;
            need_to_judge.insert(current_row_r[i]->first + current_row_r[i]->second->width);
            // cout << "           qqqq" << endl;
            current_row_r[i] = next(current_row_r[i]);
        }
        // cout <<" i: " << i << " row_index: " << row_index << endl;
        while (current_row_l[i]->second->type != PSEUDO) {
            // cout << "Current row l: " << current_row_l[i]->first << " " << current_row_l[i]->second->name << " width: " << current_row_l[i]->second->width << endl;
            need_to_judge.insert(current_row_l[i]->first - tempblock->width);
            current_row_l[i] = prev(current_row_l[i]);
        }
    }
    // Start window search
    while (!need_to_judge.empty()) {
        double judge_x = *need_to_judge.begin();
        // cout << "           Judge X: " << judge_x << endl;
        need_to_judge.erase(need_to_judge.begin());
        testblock->BL.x = judge_x;
        // cout << "           Test X: " << testblock->BL.x << " Y: " << testblock->BL.y << " W: " << testblock->width << " H: " << testblock->height << endl;
        if (check_legal(*testblock)) {
            tempblock->BL.x = judge_x;
            delete testblock;
            return true;
        }
    }
    // cout << "           Part d: " << endl;

    tempblock->BL.x = testblock->BL.x;
    delete testblock;
    return false;
}
