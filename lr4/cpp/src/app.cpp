#include "../include/app.hpp"

#include <filesystem>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "../include/cli.hpp"
#include "../include/demo_helpers.hpp"
#include "../include/read_only_stream.hpp"
#include "../include/sequence.hpp"
#include "../include/sync.hpp"
#include "../include/types.hpp"
#include "../include/vector_sequence.hpp"
#include "../include/write_only_stream.hpp"

namespace lr4 {

namespace {

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

void run_file_demo() {
    auto temp_path = std::filesystem::current_path() / "lr4_stream_demo.csv";
    WriteOnlyStream<std::string> writer(temp_path.string().c_str(), [](const Event<std::string>& e) {
        return std::to_string(e.t) + "," + e.value;
    });
    writer.Open();
    writer.Write({0.0, "hello"});
    writer.Write({1.0, "world"});
    writer.Close();

    ReadOnlyStream<std::string> reader(temp_path.string().c_str(), [](const std::string& line) {
        std::istringstream iss(line);
        std::string t_text;
        std::string value_text;
        if (!std::getline(iss, t_text, ',')) throw std::runtime_error("invalid csv row");
        if (!std::getline(iss, value_text, ',')) throw std::runtime_error("invalid csv row");
        const double t = std::stod(t_text);
        return Event<std::string>{t, value_text};
    });
    reader.Open();
    std::cout << "File demo saved to " << temp_path.string() << ":\n";
    while (!reader.IsEndOfStream()) {
        auto e = reader.Read();
        std::cout << e.t << " -> " << e.value << "\n";
    }
    reader.Close();
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
            case 3:
                run_file_demo();
                break;
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
