#pragma once
#include "ast.h"

#define LIB_ANTLR_RUNTIME 
#define LIB_DLPARSER_VISITOR_H
#include "astIncludeFrom.h"


namespace dp {
    namespace internal {

        class Parser : public DLParserBaseVisitor{
            public:
                Module* parseModule(antlr4::ANTLRInputStream);

            private:
                std::string prettyPrint(std::string);

        };
    }
} 
