#include <catch2/catch_test_macros.hpp>
// #include <catch2/benchmark/catch_benchmark.hpp>
#include <vector.hpp>
#include <linear.hpp>

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
    // std::array<double, 2> target{0};
    // REQUIRE(myvect.get(0) == target);

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
    //-------------------------------------
    krain::Vector<double, 3, 2> inputTrans{{1, 2, 
                                            3, 4, 
                                            5, 6}};
    krain::Vector<double, 2, 3> resultTrans{{1, 3, 5,
                                             2, 4, 6}};
    REQUIRE(inputTrans.Tr() == resultTrans);
    //----------------dot product---------------
    auto input = krain::Vector<double, 2, 2> {{1, 2, 
                                               3, 4}};
    auto input2 = krain::Vector<double, 2, 2> {{5, 6, 
                                                7, 8}};
    auto result = krain::Vector<double, 2, 2> {{7, 10, 
                                                15, 22}};
    REQUIRE((input.dot(input)) == result);
    REQUIRE((input.dot(input2).Tr()) == input2.Tr().dot(input.Tr()));
    REQUIRE((input.Tr().dot(input2).Tr()) == input2.Tr().dot(input));
    //----------------Norm product---------------
    auto norm_result = std::sqrt(1 + 4 + 9 + 16);
    REQUIRE(input.norm() == norm_result);
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
    myvect2 = krain::Vector<double, 2, 2>{{2, 2, 2, 2}};
    myvectTarget = krain::Vector<double, 2, 2>{{8, 8, 8, 8}};
    REQUIRE((myvect2^3) == myvectTarget);
    myvect2 = krain::Vector<double, 2, 2>{{4, 4, 4, 4}};
    myvectTarget = krain::Vector<double, 2, 2>{{2, 2, 2, 2}};
    REQUIRE(myvect2.sqrt() == myvectTarget);

    REQUIRE((1.23 + 3.75*myvect2) == (myvect2*3.75 + 1.23));
}


TEST_CASE("TEST Linear Algebra", "[LINEAR ALGEBRA]")
{

}

