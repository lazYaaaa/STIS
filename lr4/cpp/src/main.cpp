#include <string>
#include "../include/app.hpp"

using namespace lr4;

extern int RunCatchTests(int argc, char* argv[]);

int main(int argc, char** argv) {
    enum class Mode { RunTests, RunCli };

    Mode mode = Mode::RunCli;
    if (argc > 1) {
        std::string arg1(argv[1]);
        if (arg1 == "--run-tests" || arg1 == "test") {
            mode = Mode::RunTests;
        }
    }

    switch (mode) {
        case Mode::RunTests: {
            char* new_argv[1];
            new_argv[0] = argv[0];
            return RunCatchTests(1, new_argv);
        }
        case Mode::RunCli:
            return run_cli();
    }

    return 0;
}
