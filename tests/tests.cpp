#include <catch2/catch_test_macros.hpp>
// #include <catch2/benchmark/catch_benchmark.hpp>
#include <vector.hpp>

TEST_CASE("test Vector", "[VECTOR]") {
    krain::Vector<double, 1, 2> myvect{};
    REQUIRE(myvect.rows == 1);
    REQUIRE(myvect.columns == 2);
    REQUIRE(myvect.size == 2);
    REQUIRE(myvect.get(0, 0) == 0);
    REQUIRE(myvect.get(0, 0) == 0);
    REQUIRE(myvect.get(0, 1) == 0);
    krain::Vector<double, 1, 2> myvect2{{1, 2}};
    REQUIRE(myvect2.get(0, 0) == 1.0);
    REQUIRE(myvect2.get(0, 1) == 2.0);

    REQUIRE(myvect2.sum() == 3.0);
}

TEST_CASE("TEST VECTOR ON VECTOR", "[VECTOR ON VECTOR]")
{
    krain::Vector<double, 2, 2> myvect{};
    krain::Vector<double, 2, 2> myvect2{{1, 2, 3, 4}};
    auto myvect3 = myvect+myvect2;
    REQUIRE(myvect3 == myvect2);
    REQUIRE(myvect3 != myvect);
    REQUIRE((myvect3-myvect2) == myvect);
    REQUIRE((myvect3*myvect) == myvect);
    auto myvect4 = myvect2+myvect;
    REQUIRE(myvect4 == myvect3);
    //------------------------------------
    REQUIRE((myvect3-=myvect2) == myvect);
    REQUIRE((myvect3+=myvect2) == myvect2);
    REQUIRE((myvect3*=myvect) == myvect);

}

TEST_CASE("TEST VECTOR ON SCALAR", "[VECTOR ON SCALAR]")
{
    krain::Vector<double, 2, 2> myvect{};
    krain::Vector<double, 2, 2> myvectTarget{};
    REQUIRE(5*myvect == myvect*5);
    REQUIRE(5-myvect == myvect-5);
    REQUIRE(5+myvect == myvect+5);
    REQUIRE((myvect+=5) == (myvectTarget+5));
    REQUIRE((myvect-=5) == (myvectTarget));
    REQUIRE((myvect*=5) == (myvectTarget));
    krain::Vector<double, 2, 2> myvect2{{1,1,1,1}};
    myvectTarget = krain::Vector<double, 2, 2>{{5, 5, 5, 5}};
    REQUIRE(5/myvect2 == myvectTarget);
    myvectTarget = krain::Vector<double, 2, 2>{{1/5.0, 1/5.0, 1/5.0, 1/5.0}};
    REQUIRE(myvect2/5 == myvectTarget);
    REQUIRE((myvect2^3) == myvect2);

    REQUIRE((1.23 + 3.75*myvect2) == (myvect2*3.75 + 1.23));
}



