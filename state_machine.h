#ifndef AST_STATE_MACHINE_H
#define AST_STATE_MACHINE_H

#include <string>
#include <cassert>
#include "node.h"

struct StateContext;

struct State {
    // return shared_ptr to current Node
    virtual std::shared_ptr<Node> handleCharacter(
            char next,
            std::string &accumulator,
            StateContext &context,
            std::shared_ptr<Node> current_node) const = 0;
};

struct InitState : public State {
    virtual std::shared_ptr<Node> handleCharacter(
            char next,
            std::string &accumulator,
            StateContext &context,
            std::shared_ptr<Node> current_node) const override {
        assert(accumulator.empty());
        assert(current_node == nullptr);
        //context.setState(new OutsideOfExpressionState);
        return std::make_shared<Node>();
    }
};

struct OutsideOfExpressionState : public State {
    virtual std::shared_ptr<Node> handleCharacter(
            char next,
            std::string &accumulator,
            StateContext &context,
            std::shared_ptr<Node> current_node) const override {
        assert(accumulator.empty());
//        switch (next) {
//            case '(':
//                if (current_node) {
//
//                } else {
//                    current_node = std::make_shared<Node>();
//                }
//                break;
//            case ')':
//                break;
//            case ' ':
//                // ignore
//                break;
//            default:
//                accumulator += next;
//                //context.setState(InsideOfExpressionState{});
//        }
        return current_node;
    }
};

struct StateContext {

    StateContext() {
        state = std::make_unique<OutsideOfExpressionState>();
    }

    void setState(State *new_state) {
        state.reset(new_state);
    }

    std::shared_ptr<Node> handleCharacter(
            char next,
            std::string &accumulator,
            std::shared_ptr<Node> current_node) {
        return state->handleCharacter(next, accumulator, *this, current_node);
    }

private:
    std::unique_ptr<State> state;
};

//struct InsideOfExpressionState : public State {
//    virtual void handleCharacter(
//            char next,
//            std::string &accumulator,
//            StateContext& context,
//            std::shared_ptr<Node> current_node) const override;
//};

#endif //AST_STATE_MACHINE_H
