#include "../../util/utils.h"

namespace dp {

    namespace  internal{
        class ASTNode
        {
            public:
                ASTNode(const Location& _loc = Location())
                    : loc(_loc){

                    }
                ~ASTNode() {
                }
                std::string toString() const;
            private:
                Location loc;
        }; 

        class Identifier
        {
            public:
                Identifier(const std::string& name) : 
                    _name(name){

                    }
                virtual ~Identifier () {}
            private:
                std::string _name; 
        };

        class Statement;
        typedef std::unique_ptr<Statement> StatementPtr;
        typedef std::vector<StatementPtr> StatementVector;



        //Module
        class Module : ASTNode
        {
            public:
                Module (std::string name, const Location& loc = Location()) 
                    : ASTNode(loc), id(name){

                    }
                virtual ~Module ();

            private:
                std::string id;
                StatementVector stmts;
        };

        typedef std::unique_ptr<Module> ModulePtr;


        //Statement
        enum class StatementKind{
            VariableDeclaration,
            FunctionDeclaration,
            Expression 
        };















    }

}
