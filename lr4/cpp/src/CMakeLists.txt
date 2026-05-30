## Single combined executable containing CLI and test runner
add_executable(lr4 main.cpp cli.cpp embedded_tests.cpp)
target_include_directories(lr4 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include ${CMAKE_CURRENT_SOURCE_DIR}/../tests)
target_link_libraries(lr4 PRIVATE Catch2::Catch2)
