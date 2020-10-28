#include "../../include/common.h"
#include "type.h"

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

        //Statement
        enum class StatementKind{
            VariableDeclaration,
            FunctionDeclaration,
            Expression 
        };

        class Statement : public ASTNode
        {
            public:
                Statement () = delete;
                virtual ~Statement () = default;

                StatementKind kind() const {
                    return _kind;
                }

                std::string toString() const {
                    return "Statement"; 
                }
            protected:
                explicit Statement(StatementKind kind, const Location& loc = Location()) 
                    : ASTNode(loc), _kind(kind){

                    }

            private:
                StatementKind _kind; 
        };
        typedef std::unique_ptr<Statement> StatementPtr;
        typedef std::vector<StatementPtr> StatementVector;


        template<StatementKind Kind>
            class StatementMixin : public Statement{
                public:
                    static bool classof(const Statement* expr) {
                        return expr->kind() == Kind; 
                    }

                    explicit StatementMixin(const Location& loc = Location())
                        : Statement(Kind, loc){

                        }

            };


        class Expression;
        typedef  std::unique_ptr<Expression> ExpressionPtr;
        typedef std::vector<ExpressionPtr> ExpressionVector;


        class ExpressionStatement : public StatementMixin<StatementKind::Expression> {
            public:
                ExpressionStatement(const Location& loc = Location()) 
                    : StatementMixin<StatementKind::Expression>(loc){

                    } 

                std::string toString() const {
                    return "ExpressionStatement"; 
                }

                ExpressionPtr expr;
        };


        class VariableDeclaration : public StatementMixin<StatementKind::VariableDeclaration>
        {
            public:
                VariableDeclaration (std::string name, const Location& loc = Location()) 
                    : StatementMixin<StatementKind::VariableDeclaration>(loc), id(name) {

                    }
                virtual ~VariableDeclaration ();

                std::string toString() const{
                    return "VariableDeclaration"; 
                }
            private:
                Identifier id;
                std::unique_ptr<Type> vartype;
                std::unique_ptr<Expression> init;
        };


        class Param{
            public:
                Param(Identifier id) : id(id){

                } 
            private:
                Identifier id;
                std::unique_ptr<Type>  typ;
        };

        typedef std::unique_ptr<Param> ParamPtr;
        typedef std::vector<ParamPtr> ParamPtrVector;

        class FunctionDeclaration : public StatementMixin<StatementKind::FunctionDeclaration> {
            public:
                FunctionDeclaration(std::string name, const Location& loc = Location()):
                    StatementMixin<StatementKind::FunctionDeclaration>(loc), id(name), isPublic(true){

                    }        

                Identifier id;
                std::unique_ptr<FunctionType> signature;
                std::unique_ptr<ExpressionStatement> body;
                ParamPtrVector params;
                bool isPublic;
        };


        enum class ExpressionKind{
            Array,
            Binary,
            Block,
            Call,
            Literal,
            New,
            Path,
            Unary,            
            Update, 
        };



        class Expression : public ASTNode{
            public:
                Expression() = delete; 
                virtual ~Expression() = default; 

                ExpressionKind kind() const {
                    return _kind; 
                }

            protected:
                explicit Expression(ExpressionKind kind, const Location& loc = Location()) 
                    : ASTNode(loc), _kind(kind){

                    }

                ExpressionKind _kind;
        };


        template<ExpressionKind Kind>
            class ExpressionMixin : public Expression{
                public:
                    static bool classof(const Expression* expr) {
                        return expr->kind()==Kind;
                    }    

                    explicit ExpressionMixin(const Location& loc = Location()) : Expression(kind, loc){

                    }

                    std::string toString()const{
                        return "ExpressionMixin";
                    }
            };


        enum class BinaryOperator{
            Plus,
            Minus,
            Mult,
            Div,
            BitwiseAnd,
            BitwiseOr,
        };


        class BinaryExpression : public ExpressionMixin<ExpressionKind::Binary> {
            public:
                BinaryExpression (BinaryOperator op, const Location& loc = Location())
                    : ExpressionMixin<ExpressionKind::Binary>(loc), op(op){

                    }
                virtual ~BinaryExpression ();

                std::string toString() const {
                    return "BinaryExpression"; 
                }

            private:
                /* data */
                BinaryOperator op;
                ExpressionPtr left;
                ExpressionPtr right;
        };


        class BlockExpression : public ExpressionMixin<ExpressionKind::Binary> {
            public:
                BlockExpression(BinaryOperator op, const Location& loc = Location()) 
                    : ExpressionMixin<ExpressionKind::Binary>(loc), op(op){

                    }        

                std::string toString() const {
                    return "BlockExpression"; 
                }

                BinaryOperator op;
                ExpressionPtr left;
                ExpressionPtr right;
        };


        class CallExpression : public ExpressionMixin<ExpressionKind::Call>{
            public:
                CallExpression(const Location& loc = Location()) :
                    ExpressionMixin<ExpressionKind::Call>(loc){

                    } 

                ExpressionPtr receiver;
                ExpressionPtr methor;
                ExpressionVector params;
        };


        class LiteralExpression : public ExpressionMixin<ExpressionKind::Literal> {
        public:
            LiteralExpression (int32_t value, const Location& loc = Location())
                : ExpressionMixin<ExpressionKind::Literal>(loc), i32val(value), typ(LiteralExpression::Typ::I32) {
                }
            virtual ~LiteralExpression ();
        
        private:
            enum Typ{
                I32,
                I64,
                F32,
                F64,
                String 
            };
            Typ typ;

            union{
                int32_t i32val;
                int64_t i64val;
                float f32val;
                float f64val;
                std::string strval;
            };
        };


        //Module
        class Module : public ASTNode {
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

    }

}
