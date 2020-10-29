#include <fstream>
#include <iostream>

/*
 *   front-end invoking-LIBS 
 * */
#define LIB_ANTLR_RUNTIME
#define LIB_OPTION_PARSER
#define AST_PARSING_H
#include "astIncludeBy.h"
#include "astIncludeFrom.h"

/*
 *   back-end invoking-LIBS
 * */
using namespace dp;
using namespace dp::internal;
using namespace wabt;

static std::string s_infile;
static std::string s_outfile;
static bool        s_interactive_mode = false;
static const char s_description[] =
		R"(  Deeplang compiler)";






/*
 *  @features: ./dp --help
 *  @dependencies: wabt::OptionParser  antlr4::ConvertBackslashToSlash
 */
static void parseOptions(int argc, char** argv) {
	OptionParser parser("dp", s_description);

	parser.AddOption('v', "version", "current version: ", []() {
	});
	parser.AddOption(
			'o', "output", "FILENAME",
			"Output file for the compiled wasm file",
			[](const char* argument) {
				s_outfile = argument;
				ConvertBackslashToSlash(&s_outfile);
			});
	parser.AddOption('i', "interactive", "REPL",
									 []() { s_interactive_mode = true; });
	parser.AddArgument("filename", OptionParser::ArgumentCount::One,
										 [](const char* argument) {
											 s_infile = argument;
											 ConvertBackslashToSlash(&s_infile);
										 });
	parser.Parse(argc, argv);
}

int main(int argc, char** argv) {

	parseOptions(argc, argv);

	if (s_interactive_mode) {
		// repl
		return 0;
	}

	if (!s_infile.size()) {
		return -1;
	}

	std::ifstream infile(s_infile);
	if (!infile.is_open()) {
		return -1;
	}

	Parser* parser = new Parser();
	antlr4::ANTLRInputStream input(infile);

	auto module = parser->parseModule(input);

}
