#include <iostream>
#include <fstream>
#include "ast/parsing.h"

/*
    invoking LIBS 
 */
#define USE_ANTLR_RUNTIME
#define USE_OPTION_PARSER
#include "ast/include/includeLIB.h"



using namespace std;
using namespace wabt;
using namespace dp::internal;

static std::string s_infile;
static std::string s_outfile;
static bool s_interative_mod = false;
static const char s_description[] = R"( Deeplang Compiler)";



static void parseOptions(int argc, char** argv) {
    
    OptionParser parser("dp", s_description);

    parser.AddOption('v', "version", "current version: ", [](){});
    parser.AddOption(
            'o', "output", "FILENAME",
            "Output file for the compiled wasm file",
            [](const char* arguments){
                s_outfile = arguments;
                ConvertBackslashToSlash(&s_outfile); 
            });
            
    parser.AddOption('i', "interactive", "REPL", 
            []() {s_interative_mod = true;});

    parser.AddArgument("filename", OptionParser::ArgumentCount::One,
            [](const char* arguement){
                s_infile = arguement;
                ConvertBackslashToSlash(&s_infile); 
            });
    parser.Parse(argc, argv);
}

int main(int argc, char** argv)
{

    /*
        @1st features: ./dp --help
        @needed: wabt::OptionParser  antlr4::ConvertBackslashToSlash
    */
    parseOptions(argc, argv);    

    std::ifstream infile(s_infile);
    if(!infile.is_open()) {
        return -1; 
    }

    Parser* parser = new Parser();
    antlr4::ANTLRInputStream input(infile);
    auto module = parser->parseModule(input);






    return 0;
}
