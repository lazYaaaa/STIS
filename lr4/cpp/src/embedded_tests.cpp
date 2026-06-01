#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

#include "../tests/test_lazy.cpp"
#include "../tests/test_streams.cpp"
#include "../tests/test_stress.cpp"

int RunCatchTests(int argc, char* argv[]) {
    Catch::Session session;
    return session.run(argc, argv);
}
