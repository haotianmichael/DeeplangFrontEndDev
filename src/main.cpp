#pragma  once
#include <iostream>
#include <fstream>
#include "parsing/parsing.h"
#include "../third-party/antlr_runtime/antlr4-runtime.h"


using namespace std;

static std::string s_infile;
static std::string s_outfile;
static bool s_interative_mod = false;
static const char s_description[] = R"( Deeplang Compiler)";



static void parseOptions(int argc, char** argv) {


}

int main(int argc, char** argv)
{
    parseOptions(argc, argv);    
    
    if(s_interative_mod) {
        return 0; 
    }
    if(!s_infile.size()) {
        return -1; 
    }


    std::fstream infile(s_infile);
    if(!infile.is_open()) {
        return -1; 
    }



    //backend===========


    return 0;
}
