#ifndef PARSENODES_HPP
#define PARSENODES_HPP

#include "tokens.hpp"
#include <variant>

struct NodeIntLit {
    Token intLit;
};

struct NodeExpr {
    NodeIntLit nodeIntLit;
};

struct NodeStmtExit {
    NodeExpr exitCode;
};

struct NodeStmt {
    std::variant<NodeStmtExit> var;
};


#endif //PARSENODES_HPP
