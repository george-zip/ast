#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <vector>

// TODO: Node should be variant of atom, operator or list
struct Node {
    std::string value;
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
};

#endif //AST_NODE_H
