#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "state_machine.h"

TEST_CASE("State Machine Parsing", "[state_machine]") {
    StateContext state_context;
    std::string input = "(first (list 1 (+ 2 3) 9))";
    std::string accumulator;
    auto root_node = std::make_shared<Node>();

    std::shared_ptr<Node> current_node = state_context.handleCharacter
            (input.at(0), accumulator, root_node);
    // "("
    REQUIRE(accumulator.empty());
    REQUIRE(current_node);
    REQUIRE(current_node->value.empty());
    REQUIRE(current_node->children.empty());

    current_node = state_context.handleCharacter(input.at(1), accumulator, current_node);
    // "(f"
    REQUIRE(accumulator.size() == 1);
    REQUIRE(current_node->value.empty());
    REQUIRE(current_node->children.empty());
    REQUIRE_FALSE(current_node->parent.expired());
    REQUIRE(root_node->children.size() == 1);

    for(int i = 2; i < 7; ++i) {
        current_node = state_context.handleCharacter(input.at(i), accumulator, current_node);
    }
    // "(first "
    REQUIRE(accumulator.empty());
    REQUIRE(current_node->children.size() == 1);
    REQUIRE(current_node->children.at(0)->value == "first");

    current_node = state_context.handleCharacter(input.at(7), accumulator, current_node);
    // "(first ("
    REQUIRE(accumulator.empty());
    REQUIRE(current_node->value.empty());
    REQUIRE(current_node->children.empty());
    REQUIRE_FALSE(current_node->parent.expired());
    REQUIRE(root_node->children.size() == 2);

    for(int i = 8; i < 15; ++i) {
        current_node = state_context.handleCharacter(input.at(i), accumulator, current_node);
    }
    // "(first (list 1 "
    REQUIRE(accumulator.empty());
    REQUIRE(current_node->value.empty());
    REQUIRE(current_node->children.size() == 2);
    REQUIRE(current_node->children.at(0)->value == "list");
    REQUIRE(current_node->children.at(1)->value == "1");

    for(int i = 15; i <= 21; ++i) {
        current_node = state_context.handleCharacter(input.at(i), accumulator, current_node);
    }
    // "(first (list 1 (+ 2 3)"
    REQUIRE(accumulator.empty());
    REQUIRE(current_node->children.size() == 3);
    auto nested_list = current_node->children.at(2);
    REQUIRE(nested_list->children.size() == 3);

    for(int i = 21; i <= 25; ++i) {
        current_node = state_context.handleCharacter(input.at(i), accumulator, current_node);
    }
    // "(first (list 1 (+ 2 3) 9))"
    REQUIRE(accumulator.empty());
    REQUIRE(current_node->children.size() == 2);
    REQUIRE(current_node->children.at(0)->value == "first");
    REQUIRE(current_node->children.at(1)->children.size() == 4);
}