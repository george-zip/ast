#include "state_machine.h"

std::shared_ptr<Node> OutsideOfToken::handleCharacter(
        char next,
        std::string &accumulator,
        StateContext &context,
        std::shared_ptr<Node> current_node) const {
    assert(accumulator.empty());
    assert(current_node);
    switch (next) {
        case '(': {
            auto new_node = std::make_shared<Node>();
            new_node->parent = current_node;
            current_node->children.push_back(new_node);
            current_node = new_node;
            break;
        }
        case ')':
            break;
        case ' ':
            // do nothing
            break;
        default:
            auto new_node = std::make_shared<Node>();
            current_node->children.push_back(new_node);
            new_node->parent = current_node;
            current_node = new_node;
            accumulator += next;
            context.setState(new InsideToken);
    }
    return current_node;
}

std::shared_ptr<Node> InsideToken::handleCharacter(
        char next,
        std::string &accumulator,
        StateContext &context,
        std::shared_ptr<Node> current_node) const {
    assert(current_node);
    switch (next) {
        case '(':
            break;
        case ')': {
            current_node->value.swap(accumulator);
            context.setState(new OutsideOfToken);
            auto parent = current_node->parent.lock();
            assert(parent);
            auto grand_parent = parent->parent.lock();
            if(grand_parent) {
                current_node = grand_parent;
            }
            // else parent is root node
            break;
        }
        case ' ': {
            current_node->value.swap(accumulator);
            context.setState(new OutsideOfToken);
            auto parent = current_node->parent.lock();
            assert(parent);
            current_node = parent;
            break;
        }
        default:
            accumulator += next;
    }
    return current_node;
}

std::shared_ptr<Node> InitState::handleCharacter(
        char next,
        std::string &accumulator,
        StateContext &context,
        std::shared_ptr<Node> root_node) const {
    assert(accumulator.empty());
    context.setState(new OutsideOfToken);
    return root_node;
}
