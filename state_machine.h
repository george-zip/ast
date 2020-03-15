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
            std::shared_ptr<Node> current_node) const override;
};

struct OutsideOfToken : public State {
    std::shared_ptr<Node> handleCharacter(
            char next,
            std::string &accumulator,
            StateContext &context,
            std::shared_ptr<Node> current_node) const override;
};

struct InsideToken : public State {
    std::shared_ptr<Node> handleCharacter(char next, std::string &accumulator, StateContext &context,
                                          std::shared_ptr<Node> current_node) const override;
};

struct StateContext {

    StateContext() {
        state = std::make_unique<InitState>();
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

//struct InsideToken : public State {
//    virtual void handleCharacter(
//            char next,
//            std::string &accumulator,
//            StateContext& context,
//            std::shared_ptr<Node> current_node) const override;
//};

#endif //AST_STATE_MACHINE_H
