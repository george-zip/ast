#ifndef AST_NODE_WRITER_H
#define AST_NODE_WRITER_H

#include "node.h"

template<typename Output>
class NodeWriter {
public:
    NodeWriter(Output&);
    void writeNode(const Node&) const;
private:
    Output output;
};

#endif //AST_NODE_WRITER_H
