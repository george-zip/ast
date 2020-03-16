#ifndef AST_NODE_H
#define AST_NODE_H

#include <memory>
#include <string>
#include <vector>

// A Node can be a leaf containing a single element or an array of nodes
// This could be a variant of different possible types or that could be
// overkill
struct Node {
    std::string value;
    std::weak_ptr<Node> parent;
    std::vector<std::shared_ptr<Node>> children;
};

#endif //AST_NODE_H
