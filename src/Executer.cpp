#include "parsenodes.hpp"

class Executer {
public:
    Executer() = default;

    void exit_(const NodeStmtExit &nodeExit) {
        if (auto sexitCode = nodeExit.exitCode.nodeIntLit.intLit.value) {
            const int exitCode = std::stoi(sexitCode.value());
            exit(exitCode);
        }
        assert(false);
    }
};
