#include "units.hpp"

#define BOOST_TEST_MODULE MyTest
#include <boost/test/unit_test.hpp>

using namespace units;

BOOST_AUTO_TEST_CASE(unit_base_constructor_test)
{
    double x = 3.2;

    Unit_Base<double> ub1(x);
    BOOST_CHECK_EQUAL(ub1.count(), x);

    Unit_Base<double> ub2 = ub1;
    BOOST_CHECK_EQUAL(ub2.count(), x);

    Unit_Base<double> ub3(1.2);
    ub3 = ub1;
    BOOST_CHECK_EQUAL(ub3.count(), x);

    Unit_Base<double, std::ratio<1, 100>> ub4(x);
    BOOST_CHECK_EQUAL(ub4.count(), x);
}

BOOST_AUTO_TEST_CASE(distance_constructor_test)
{
    double x = 2.3;

    Distance<double> d1(x);
    BOOST_CHECK_EQUAL(d1.count(), x);

    Distance<double> d2 = d1;
    BOOST_CHECK_EQUAL(d2.count(), x);

    Distance<double> d3(7.6);
    d3 = d1;
    BOOST_CHECK_EQUAL(d3.count(), x);

    Distance<double, std::ratio<1000, 1>> d4(x);
    BOOST_CHECK_EQUAL(d4.count(), x);
}

BOOST_AUTO_TEST_CASE(operator_tests)
{
    double x = 2.3;
    double y = 5.7;

    Unit_Base<double> ub1(x);
    Unit_Base<double> ub2(y);
    BOOST_CHECK_EQUAL((ub1 + ub2).count(), x + y);
    BOOST_CHECK_EQUAL((ub1 - ub2).count(), x - y);

    Distance<double> d1(x);
    Distance<double> d2(y);
    BOOST_CHECK_EQUAL((d1 + d2).count(), x + y);
    BOOST_CHECK_EQUAL((d1 - d2).count(), x - y);
}

BOOST_AUTO_TEST_CASE(casting_test)
{
    double x = 2.3;

    Unit_Base<double> ub1(x);
    auto ub2 = Unit_Base_cast<Unit_Base<double, std::ratio<100, 1>>>(ub1);
    auto ub3 = Unit_Base_cast<Unit_Base<double, std::ratio<1, 100>>>(ub1);

    BOOST_CHECK_EQUAL(ub2.count(), 2.3 / 100.);
    BOOST_CHECK_EQUAL(ub3.count(), 2.3 * 100.);
}