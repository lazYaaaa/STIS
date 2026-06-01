#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <thread>
#include <ctime>

#include "../include/vector_sequence.hpp"
#include "../include/sync.hpp"
#include "../include/types.hpp"

using namespace lr4;

namespace lr4 {

namespace {
size_t read_env_size(const char* key, size_t fallback) {
    const char* env = std::getenv(key);
    if (!env || !*env) return fallback;
    try {
        return static_cast<size_t>(std::stoul(env));
    } catch (...) {
        return fallback;
    }
}

int read_env_int(const char* key, int fallback) {
    const char* env = std::getenv(key);
    if (!env || !*env) return fallback;
    try {
        return std::stoi(env);
    } catch (...) {
        return fallback;
    }
}

std::string read_env_str(const char* key, const std::string& fallback) {
    const char* env = std::getenv(key);
    if (!env || !*env) return fallback;
    return std::string(env);
}

std::string timestamp_string() {
    auto now = std::chrono::system_clock::now();
    std::time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm tm{};
#if defined(_WIN32)
    localtime_s(&tm, &tt);
#else
    localtime_r(&tt, &tm);
#endif
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return oss.str();
}
}

int RunStress(size_t n, int runs, const std::string& outDir, const std::string& measure, int pauseMs) {
    std::vector<Event<int>> a; a.reserve(n);
    std::vector<Event<int>> b; b.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        a.push_back(Event<int>{double(i), int(i)});
        b.push_back(Event<int>{double(i) + 0.1, int(i*10)});
    }

    auto sa = std::make_shared<VectorSequence<Event<int>>>(a);
    auto sb = std::make_shared<VectorSequence<Event<int>>>(b);
    std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{sa, sb};

    double tau = 0.5;

    std::filesystem::create_directories(outDir);
    const auto filename = std::filesystem::path(outDir) / (std::to_string(n) + "_stress.csv");
    std::ofstream csv(filename);
    if (!csv) {
        std::cerr << "cannot open output file " << filename.string() << "\n";
        return 2;
    }
    csv << "n,run,time_s,rows,throughput_rows_s\n";

    for (int r = 0; r < runs; ++r) {
        auto t0 = std::chrono::steady_clock::now();
        auto synced = SynchronizeStreams<int>(streams, tau);
        auto t1 = std::chrono::steady_clock::now();
        std::chrono::duration<double> dur = t1 - t0;
        double seconds = dur.count();
        double throughput = seconds > 0.0 ? (double) synced->GetSize() / seconds : 0.0;
        csv << n << "," << r << "," << std::fixed << std::setprecision(6) << seconds << "," << synced->GetSize() << "," << throughput << "\n";
        std::cout << "run=" << r << ", time_s=" << seconds << ", throughput_rows_s=" << throughput << "\n";
        if (pauseMs > 0 && r + 1 < runs) {
            std::this_thread::sleep_for(std::chrono::milliseconds(pauseMs));
        }
    }

    std::cout << "Wrote results to " << filename.string() << "\n";
    return 0;
}

int RunStressFromEnv() {
    size_t n = read_env_size("LR4_STRESS", 10000);
    int runs = read_env_int("LR4_STRESS_RUNS", 1);
    int pauseMs = read_env_int("LR4_STRESS_PAUSE_MS", 0);
    std::string measure = read_env_str("LR4_STRESS_MEASURE", "time");
    std::string outdir = read_env_str("LR4_STRESS_OUTDIR", "results");
    if (outdir == "results") {
        outdir = (std::filesystem::path(outdir) / ("run_" + timestamp_string())).string();
    }
    return RunStress(n, runs, outdir, measure, pauseMs);
}

} 

