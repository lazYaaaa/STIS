#include "../include/app.hpp"

#include <chrono>
#include <cstdlib>
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/cli.hpp"
#include "../include/demo_helpers.hpp"
#include "../include/sequence.hpp"
#include "../include/sync.hpp"
#include "../include/types.hpp"
#include "../include/vector_sequence.hpp"
#include "../include/stress.hpp"

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

void run_example_sync_demo() {
    auto a_events = std::vector<Event<std::string>>{{0.0, "alpha"}, {1.0, "beta"}, {2.0, "gamma"}};
    auto b_events = std::vector<Event<std::string>>{{0.1, "red"}, {1.5, "blue"}};
    auto a = std::make_shared<VectorSequence<Event<std::string>>>(a_events);
    auto b = std::make_shared<VectorSequence<Event<std::string>>>(b_events);
    std::vector<std::shared_ptr<Sequence<Event<std::string>>>> streams{a, b};
    double tau = 0.5;

    print_events("Stream A before synchronization:", a_events);
    print_events("Stream B before synchronization:", b_events);
    auto synced = SynchronizeStreams<std::string>(streams, tau);
    std::cout << "Synchronization result (tau=" << tau << "):\n";
    print_synced_result(synced);
}

void run_manual_sync_demo() {
    std::cout << "Enter the first stream as 't:value' pairs separated by spaces (value is string, example: 0.0:alpha 1.0:beta):\n";
    std::string line1;
    std::getline(std::cin, line1);
    auto events1 = parse_events(line1);

    std::cout << "Enter the second stream similarly (strings only):\n";
    std::string line2;
    std::getline(std::cin, line2);
    auto events2 = parse_events(line2);

    if (events1.empty() || events2.empty()) {
        std::cout << "No valid string events were parsed. Use input like 0.0:alpha 1.0:beta.\n";
        return;
    }

    auto a = std::make_shared<VectorSequence<Event<std::string>>>(events1);
    auto b = std::make_shared<VectorSequence<Event<std::string>>>(events2);
    std::vector<std::shared_ptr<Sequence<Event<std::string>>>> streams{a, b};
    std::cout << "Enter tau (window) as a number (e.g. 0.5): ";

    std::string rest;
    double tau = 0.5;
    std::cin >> tau;
    std::getline(std::cin, rest);

    print_events("Stream A before synchronization:", events1);
    print_events("Stream B before synchronization:", events2);
    auto synced = SynchronizeStreams<std::string>(streams, tau);
    std::cout << "Synchronization result:\n";
    print_synced_result(synced);
}

} 

int run_cli() {
    while (true) {
        print_menu();
        int choice = 0;
        if (!(std::cin >> choice)) {
            break;
        }

        std::string rest;
        std::getline(std::cin, rest);

        switch (choice) {
            case 1:
                run_example_sync_demo();
                break;
            case 2:
                run_manual_sync_demo();
                break;
            case 3: {
                // Interactive stress test runner
                std::cout << "Stress test runner\n";
                size_t env_n = read_env_size("LR4_STRESS", 10000);
                int env_runs = read_env_int("LR4_STRESS_RUNS", 1);
                int env_pause = read_env_int("LR4_STRESS_PAUSE_MS", 0);
                std::string env_measure = read_env_str("LR4_STRESS_MEASURE", "time");
                std::string env_outdir = read_env_str("LR4_STRESS_OUTDIR", "results");

                std::cout << "Enter events count [default " << env_n << "]: ";
                size_t n = env_n;
                std::string n_line;
                std::getline(std::cin, n_line);
                std::getline(std::cin, n_line);
                if (!n_line.empty()) {
                    try {
                        n = static_cast<size_t>(std::stoul(n_line));
                    } catch (...) {
                        n = env_n;
                    }
                }
                std::cout << "Number of runs (repeat measurements) [default " << env_runs << "]: ";
                int runs = env_runs; std::cin >> runs;

                std::cout << "Pause between runs in ms [default " << env_pause << "]: ";
                int pauseMs = env_pause;
                std::string pause_line;
                std::getline(std::cin, pause_line);
                std::getline(std::cin, pause_line);
                if (!pause_line.empty()) {
                    try {
                        pauseMs = std::stoi(pause_line);
                    } catch (...) {
                        pauseMs = env_pause;
                    }
                }

                std::string run_ts = timestamp_string();
                std::string outdir;
                std::cout << "Output directory [default " << env_outdir << "/run_<timestamp>]: ";
                std::string tmp;
                std::getline(std::cin, tmp);
                std::getline(std::cin, tmp);
                if (!tmp.empty()) {
                    outdir = tmp;
                } else {
                    outdir = (std::filesystem::path(env_outdir) / ("run_" + run_ts)).string();
                }

                std::cout << "Measure to plot (time | throughput) [default " << env_measure << "]: ";
                std::string measure; std::getline(std::cin, measure);
                if (measure.empty()) measure = env_measure;

                std::cout << "Running stress: n=" << n << ", runs=" << runs << ", pause_ms=" << pauseMs << ", out=" << outdir << ", measure=" << measure << "\n";
                RunStress(n, runs, outdir, measure, pauseMs);
                // try to call Python plot script if available
                // try several relative locations for the plotting script
                std::vector<std::string> candidates = {"scripts\\plot_results.py", "..\\scripts\\plot_results.py", "..\\..\\scripts\\plot_results.py", "..\\..\\..\\scripts\\plot_results.py", "..\\..\\..\\..\\scripts\\plot_results.py"};
                std::string script_path;
                for (auto &c : candidates) {
                    if (std::filesystem::exists(c)) { script_path = c; break; }
                }
                std::string csv_path = (std::filesystem::path(outdir) / (std::to_string(n) + "_stress.csv")).string();
                std::string png_path = (std::filesystem::path(outdir) / (std::to_string(n) + "_stress.png")).string();
                if (!script_path.empty()) {
                    std::string cmd = "python " + script_path + " " + outdir + " " + std::to_string(n) + " " + measure;
                    std::cout << "Attempting to create plot with: " << cmd << "\n";
                    int r = std::system(cmd.c_str());
                    if (r != 0) std::cout << "Plotting failed or python not available. CSV written to " << outdir << "\n";
                } else {
                    std::cout << "Plot script not found in expected locations. CSV written to " << outdir << "\n";
                }
                const auto report_path = std::filesystem::path(outdir) / ("report_" + run_ts + ".md");
                std::ofstream report(report_path);
                if (report) {
                    report << "# Stress run report\n\n";
                    report << "- timestamp: " << run_ts << "\n";
                    report << "- n: " << n << "\n";
                    report << "- runs: " << runs << "\n";
                    report << "- pause_ms: " << pauseMs << "\n";
                    report << "- measure: " << measure << "\n\n";
                    report << "## Files\n";
                    report << "- CSV: " << csv_path << "\n";
                    report << "- Plot: " << png_path << "\n";
                }
                std::cout << "Report saved to " << report_path.string() << "\n";
                break;
            }
            case 4:
                return 0;
            default:
                std::cout << "Unknown option\n";
                break;
        }
    }

    std::cout << "Exit.\n";
    return 0;
}

}
