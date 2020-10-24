#include <iostream>
#include <fstream>
#include "../third_party/wabt/src/option-parser.h"
#include "../third_party/antlr_runtime/antlr4-runtime.h"

using namespace std;
using namespace wabt;

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


    return 0;
}
