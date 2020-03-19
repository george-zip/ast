#include <iostream>

#include "state_machine.h"
#include "node_writer.h"

int main() {
    std::cout << "Type your LISP to be interpreted:\n";
    string response;
    getline(std::cin, response);
    std::cout << response << std::endl;
    StateContext state_context;
    std::string accumulator;
    auto root_node = std::make_shared<Node> ();

    auto current_node = state_context.handleCharacter
            (response.at (0), accumulator, root_node);
    for (int i = 1; i < response.size (); ++i) {
        current_node = state_context.handleCharacter
                (response.at (i), accumulator, current_node);
    }

    std::cout << "Done parsing\n";

    NodeWriter<std::ostream> writer (std::cout);
    writer.writeNode (root_node);
    std::cout << std::endl;

    return 0;
}

