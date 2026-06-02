#include <catch2/catch.hpp>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "../include/sequence.hpp"
#include "../include/vector_sequence.hpp"
#include "../include/sync.hpp"
#include "../include/types.hpp"

using namespace lr4;

TEST_CASE("Stress: SynchronizeStreams large", "[stress]") {
    const char* env = std::getenv("LR4_STRESS");
    size_t n = env ? static_cast<size_t>(std::stoul(env)) : 10000;
    std::vector<Event<int>> a;
    a.reserve(n);
    std::vector<Event<int>> b;
    b.reserve(n);
    for (size_t i = 0; i < n; ++i) {
        a.push_back(Event<int>{double(i), int(i)});
        b.push_back(Event<int>{double(i) + 0.1, int(i*10)});
    }

    auto sa = std::make_shared<VectorSequence<Event<int>>>(a);
    auto sb = std::make_shared<VectorSequence<Event<int>>>(b);
    std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{sa, sb};

    double tau = 0.5;
    auto t0 = std::chrono::steady_clock::now();
    auto synced = SynchronizeStreams<int>(streams, tau);
    auto t1 = std::chrono::steady_clock::now();
    std::chrono::duration<double> dur = t1 - t0;

    REQUIRE(synced->GetSize() == n);
    if (n >= 3) {
        auto r0 = synced->Get(0);
        REQUIRE(r0.first == Approx(0.0));
        REQUIRE(r0.second.size() == 2);
    }

    std::cout << "SynchronizeStreams computed " << synced->GetSize() << " rows in " << dur.count() << "s\n";
}
