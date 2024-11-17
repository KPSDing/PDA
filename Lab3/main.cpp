#include "Legalizer.h"

int main(int argc, char* argv[]){
    Legalizer legalizer;
    legalizer.parser_info(argv[1]);
    legalizer.parser_opt(argv[2]);
    legalizer.check_input();
    legalizer.output_draw(argv[3]);
    return 0;
}
