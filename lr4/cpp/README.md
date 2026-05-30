Lab 4 C++ implementation notes

Structure:
- `include/` — public headers (`lazy`, `stream`)
- `src/` — implementation sources
- `tests/` — unit tests (use Catch2 or GoogleTest)
- `cmd/` — CLI demo (if needed)
- `CMakeLists.txt` — project build

Quick start (once implemented):

```bash
mkdir build && cd build
cmake ..
cmake --build .
ctest --output-on-failure
```