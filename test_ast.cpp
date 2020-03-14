#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "state_machine.h"

TEST_CASE("State Machine Parsing", "[state_machine]") {
    StateContext state_context;
    std::string input = "(first (list 1 (+ 2 3) 9))";
    std::string accumulator;
    std::shared_ptr<Node> current_node;

    SECTION("0") {
        current_node = state_context.handleCharacter(input.at(0), accumulator, current_node);
        REQUIRE(accumulator.empty());
        REQUIRE(current_node);
    }
}