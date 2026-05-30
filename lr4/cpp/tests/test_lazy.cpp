#include <iostream>
#include <catch2/catch.hpp>
#include "lazy.hpp"

using namespace lr4;

TEST_CASE("LazySequence basic generation and memoization") {
    auto squareGen = [](size_t i) { return uint64_t(i * i); };
    LazySequence<uint64_t> seq(squareGen);
    REQUIRE(seq.Get(0) == 0);
    REQUIRE(seq.Get(1) == 1);
    REQUIRE(seq.Get(2) == 4);
    REQUIRE(seq.Get(10) == 100);
}

TEST_CASE("Map and Zip and Subsequence") {
    auto gen = [](size_t i) { return uint64_t(i + 1); };
    LazySequence<uint64_t> s(gen);
    auto mapped = s.Map<int>([](uint64_t x){ return int(x * 2); });
    REQUIRE(mapped.Get(0) == 2);
    REQUIRE(mapped.Get(4) == 10);

    auto other = std::make_shared<MaterializedSequence<uint64_t>>(std::vector<uint64_t>{10,20,30,40,50});
    auto zipped = s.Zip(std::static_pointer_cast<Sequence<uint64_t>>(other));
    auto p = zipped.Get(2);
    REQUIRE(p.first == 3);
    REQUIRE(p.second == 30);

    auto sub = s.GetSubsequence(1,4);
    REQUIRE(sub->Get(0) == 2);
    REQUIRE(sub->Get(2) == 4);
}

TEST_CASE("Append concatenation") {
    auto a = std::make_shared<MaterializedSequence<int>>(std::vector<int>{1,2,3});
    auto b = std::make_shared<MaterializedSequence<int>>(std::vector<int>{4,5});
    LazySequence<int> la([a](size_t i){ return a->Get(i); });
    auto appended = la.Append(b);
    REQUIRE(appended->Get(0) == 1);
    REQUIRE(appended->Get(3) == 4);
    REQUIRE(appended->Get(4) == 5);
}
