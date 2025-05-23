$$
\begin{align}
    [\text{Prog}] &\to [\text{Stmt}]^* \\
    [\text{Stmt}] &\to
    \begin{cases}
        \text{exit}([\text{Expr}]); \\
        [\text{Decl}] \\
        [\text{Assig}]
    \end{cases} \\
    [\text{Expr}] &\to
    \begin{cases}
        [\text{Term}] \\
        [\text{BinExpr}] \\
    \end{cases} \\
    [\text{Term}] &\to
    \begin{cases}
        \text{\{int\_lit\}} \\
        \text{\{ident\}}
    \end{cases} \\
    [\text{BinExpr}] &\to
    \begin{cases}
        [\text{Expr}] * [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] / [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] \% [\text{Expr}] & \text{prec} = 1 \\
        [\text{Expr}] + [\text{Expr}] & \text{prec} = 0 \\
        [\text{Expr}] - [\text{Expr}] & \text{prec} = 0 \\
    \end{cases} \\
    [\text{Decl}] &\to
    \begin{cases}
        (\text{Type}) \text{ \{ident\}}; \\
        (\text{Type}) \text{ \{ident\} = } [\text{Expr}]; \\
    \end{cases} \\
    [\text{Assig}] &\to
    \begin{cases}
        \text{\{ident\}} = [\text{Expr}]
    \end{cases}
\end{align}
$$
