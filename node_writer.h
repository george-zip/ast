#ifndef AST_NODE_WRITER_H
#define AST_NODE_WRITER_H

#include "node.h"
#include <memory.h>
#include <cassert>
#include <iostream>
#include <queue>

using namespace std;

template<typename Output>
class NodeWriter {
public:
    explicit NodeWriter (Output &o) : output (o) {}

    void writeNode (const std::shared_ptr<Node> current_node) const {
        if (!current_node)
            return;
        std::queue<std::shared_ptr<Node>> traversal_queue;
        traversal_queue.push (current_node);
        while (!traversal_queue.empty ()) {
            auto node = traversal_queue.front ();
            traversal_queue.pop ();
            if (node->children.empty ()) {
                output << "\"" << node->value << "\" ";
            } else {
                output << "[";
                for (auto &sub_node : node->children) {
                    writeNode (sub_node);
                }
                output << "]";
            }
        }
    }

private:
    Output &output;
};

#endif //AST_NODE_WRITER_H
