$$
\begin{align}
    [\text{Prog}] &\to [\text{Stmt}]^* \\
    [\text{Stmt}] &\to
    \begin{cases}
        \text{exit}([\text{Expr}]); \\
    \end{cases} \\
    [\text{Expr}] &\to 
    \begin{cases}
        \text{int\_lit}
    \end{cases}
\end{align}
$$