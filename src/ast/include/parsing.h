#pragma  once
#include "ast.h"
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

            antlrcpp::Any visitParam(DLParser::ParamContext* context);

            antlrcpp::Any visitParamList(DLParser::ParamListContext* context);

            antlrcpp::Any visitExpressionStatement();



        };
    }
}
