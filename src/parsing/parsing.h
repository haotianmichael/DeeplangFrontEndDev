#pragma  once
#include "ast/ast.h"
#include "../../third_party/antlr_runtime/antlr4-runtime.h"

namespace dp{
    namespace  internal{
        class Parser : public DLParserVisitor
        {
        public:
            Module* parseModule(antlr4::ANTLRInputStream);
        
        private:

            std::string prettyPrint(std::string);
            antlrcpp::Any visitAryOp(DLParser::AryOpContext* context); 
        };


    
    
    
    }
}
