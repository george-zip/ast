#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <vector>

struct Node {
    std::string value;
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
};

#endif //AST_NODE_H
