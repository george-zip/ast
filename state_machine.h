#ifndef AST_STATE_MACHINE_H
#define AST_STATE_MACHINE_H

#include <string>
#include <cassert>
#include "node.h"

struct StateContext;

struct State {
    virtual void handleCharacter(
            char next,
            std::string& accumulator,
            StateContext& context,
            std::shared_ptr<Node> current_node) const = 0;
};

struct OutsideOfExpressionState : public State {
    virtual void handleCharacter(
            char next,
            std::string &accumulator,
            StateContext& context,
            std::shared_ptr<Node> current_node) const override {
        assert(accumulator.empty());
        switch(next) {
            case '(':
                if (current_node) {
                    
                } else {

                }
                break;
            case ')':
                break;
            case ' ':
                // ignore
                break;
            default:
                accumulator += next;
                context.setState(InsideOfExpressionState{});
        }

        }
        if(next == '(' || c == ')') {
            tokens.push_back(string(1, c));
        } else {
            current_token += c;
            stream_state = InsideOfToken;
        }


    }
};

struct InsideOfExpressionState : public State {
    virtual void handleCharacter(
            char next,
            std::string &accumulator,
            StateContext& context,
            std::shared_ptr<Node> current_node) const override;
};

#endif //AST_STATE_MACHINE_H
