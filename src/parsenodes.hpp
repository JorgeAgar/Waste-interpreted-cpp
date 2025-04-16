#ifndef PARSENODES_HPP
#define PARSENODES_HPP

#include "tokens.hpp"
#include "types.hpp"
#include <variant>

struct NodeIdent {
    Token ident;
};

struct NodeTermIntLit {
    Token intLit;
};

struct NodeTerm {
    std::variant<NodeIdent, NodeTermIntLit> term;
};

struct NodeExpr;

struct NodeDecl {
    NodeIdent ndId;
    Type type;
    NodeExpr* expr;
};

struct NodeAssig {
    NodeIdent ndId;
    NodeExpr* expr;
};

struct NodeBinExprAdd {
    NodeExpr* left;
    NodeExpr* right;
};

struct NodeBinExprSub {
    NodeExpr* left;
    NodeExpr* right;
};

struct NodeBinExprMul {
    NodeExpr* left;
    NodeExpr* right;
};

struct NodeBinExprDiv {
    NodeExpr* left;
    NodeExpr* right;
};

struct NodeBinExprMod {
    NodeExpr* left;
    NodeExpr* right;
};

struct NodeBinExpr {
    std::variant<NodeBinExprAdd, NodeBinExprSub, NodeBinExprMul, NodeBinExprDiv, NodeBinExprMod> binExpr;
};

struct NodeExpr {
    std::variant<NodeDecl, NodeBinExpr> expr;
};

struct NodeStmtExit {
    NodeExpr exitCode;
};

struct NodeStmt {
    std::variant<NodeStmtExit> var;
};


#endif //PARSENODES_HPP
