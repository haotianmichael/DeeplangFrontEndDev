#include <iostream>
#include <vector>
#include "antlr4-runtime/antlr4-runtime.h"
#include "antlr4-runtime/SceneBaseVisitor.h"


class ImageVisitor : public SceneBaseVisitor
{
public:
    ImageVisitor ();

    antlrcpp::Any visitFile(SceneParser::FileContext *ctx) override{

        std::vector<Element>  elements;        
        for(auto element : ctx->elements)  {
            antlrcpp::Any el = visitAction(element); 
            elements.push_back(el);
        } 

        antlrcpp::Any result = Scene(ctx->name()->NAME()->getText(), elements);
        return result;
    }


    antlrcpp::Any visitAction(SceneParser::ActionContext *ctx) override{
        Action action; 
        if(ctx->DRAW()){
            action = Draw();
            Shape shape = visitShape(ctx->shape()); 
            return Element(action, ctx->size()->getText(), ctx->color()->getText(), ctx->position()->x->getText(), 
                    ctx->position()->y->getText(0, shape));
        }else if(ctx->WRITE()) {
            action = Write;
            string text = ctx->STRING()->getText().substr(1, ctx->STRING()->getText().length() - 2);

            return Element(action, ctx->size()->getText(), ctx->color()->getText(), ctx->position()->x->getText(), 
                    ctx->position()->y->getText(), text);
        }else {
            action = NoAction; 
        }

        return Element(action);
    }


    antlrcpp::Any visitShape(SceneParser::ShapeContext *ctx) override{
        return Element::convertShape(ctx->getText()); 
    }
    
};
