$$
\begin{align}
    [\text{Prog}] &\to [\text{Stmt}]^* \\
    [\text{Stmt}] &\to
    \begin{cases}
        \text{exit}([\text{Expr}]); \\
        [\text{Type}] \text{ \{ident\}}; \\
        [\text{Type}] \text{ \{ident\} = } [\text{Expr}]; \\
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
    [\text{Type}] &\to
    \begin{cases}
        \text{boolean} \\
        \text{char} \\
        \text{int} \\
        \text{float} \\
    \end{cases}
\end{align}
$$
