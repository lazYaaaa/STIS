#include <catch2/catch.hpp>
#include "stream.hpp"
#include "types.hpp"
#include "sequence.hpp"
#include "sync.hpp"

using namespace lr4;

TEST_CASE("Stream basic read and write") {
    // create materialized sequence of events
    auto seq = std::make_shared<VectorSequence<Event<int>>>(std::vector<Event<int>>{{0.1,1},{0.5,2},{1.2,3}});
    ReadOnlyStream<int> rs(seq);
    REQUIRE(!rs.IsEndOfStream());
    auto e = rs.Read();
    REQUIRE(e.value == 1);
    REQUIRE(rs.GetPosition() == 1);

    WriteOnlyStream<int> ws;
    ws.Write({2.0, 42});
    REQUIRE(ws.Buffer().size() == 1);
    REQUIRE(ws.Buffer()[0].value == 42);
}

TEST_CASE("Synchronize two streams") {
    auto a = std::make_shared<VectorSequence<Event<int>>>(std::vector<Event<int>>{{0.0,10},{1.0,20},{2.0,30}});
    auto b = std::make_shared<VectorSequence<Event<int>>>(std::vector<Event<int>>{{0.1,100},{1.5,200}});
    std::vector<std::shared_ptr<Sequence<Event<int>>>> streams{a,b};
    auto synced = SynchronizeStreams<int>(streams, 0.5);
    // synced should have one row per event in reference a
    REQUIRE(synced->GetMaterializedCount() == 3);
    auto row0 = synced->Get(0);
    REQUIRE(row0.first == Approx(0.0));
    REQUIRE(row0.second.size() == 2);
    // reference value
    REQUIRE(row0.second[0].has_value());
    REQUIRE(row0.second[0].value() == 10);
    // matched b within 0.5 window -> b has event at 0.1
    REQUIRE(row0.second[1].has_value());
    REQUIRE(row0.second[1].value() == 100);
    // second row: a at 1.0, b has event at 1.5 outside window 1.0..1.5 (inclusive) -> within
    auto row1 = synced->Get(1);
    REQUIRE(row1.second[1].has_value());
    REQUIRE(row1.second[1].value() == 200);
}
