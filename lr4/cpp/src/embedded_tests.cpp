#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

// Include test translation units so we can embed tests into a single executable.
#include "../tests/test_lazy.cpp"
#include "../tests/test_streams.cpp"

int RunCatchTests(int argc, char* argv[]) {
    Catch::Session session;
    return session.run(argc, argv);
}
