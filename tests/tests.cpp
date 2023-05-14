#include <catch2/catch_test_macros.hpp>
// #include <catch2/benchmark/catch_benchmark.hpp>
#include <vector.hpp>



TEST_CASE("test Vector", "[VECTOR]") {
    krain::Vector<double, 1, 2> myvect{};
    REQUIRE(myvect.get(0, 0) == 0);
    REQUIRE(myvect.get(0, 1) == 0);
    krain::Vector<double, 1, 2> myvect2{{1, 2}};
    REQUIRE(myvect.get(0, 0) == 1.0);
    REQUIRE(myvect.get(0, 1) == 2.0);

}