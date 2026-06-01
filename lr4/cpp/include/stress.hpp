#pragma once

#include <cstddef>
#include <string>

namespace lr4 {

// Run stress test programmatically: n = events, runs = number of repeats,
// outDir = directory to write CSV, measure = metric for plotting ("time" or "throughput"),
// pauseMs = delay between runs in milliseconds.
int RunStress(size_t n, int runs, const std::string& outDir, const std::string& measure, int pauseMs);

// Read env wrapper for existing --run-stress path
int RunStressFromEnv();

} 