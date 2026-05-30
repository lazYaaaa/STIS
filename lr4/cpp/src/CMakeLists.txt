## Single combined executable containing CLI and test runner
add_executable(lr4 main.cpp app.cpp cli.cpp demo_helpers.cpp embedded_tests.cpp read_only_stream.cpp write_only_stream.cpp)
target_include_directories(lr4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../tests)
target_link_libraries(lr4 PRIVATE Catch2::Catch2)

enable_testing()
add_test(NAME lr4_run_tests COMMAND $<TARGET_FILE:lr4> --run-tests)
