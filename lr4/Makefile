.PHONY: all build test run

all: build

build:
	cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
	cmake --build build --config Release

test: build
	ctest --test-dir build -C Release --output-on-failure

run: build
	build/cpp/src/Release/lr4.exe
