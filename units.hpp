#ifndef __UNITS__
#define __UNITS__

#include <chrono>
#include <ostream>
#include <ratio>

namespace units
{
/*
 *  Unit_Base
 */
template <typename T_Rep, typename T_Ratio = std::ratio<1L, 1L>>
class Unit_Base
{
private:
    T_Rep value_;

public:
    constexpr Unit_Base() = default;
    constexpr Unit_Base(const Unit_Base&) = default;
    constexpr explicit Unit_Base(const T_Rep& value) : value_(value) {}
    ~Unit_Base() = default;
    Unit_Base& operator=(const Unit_Base&) = default;

    T_Rep count() const { return value_; }
};  // Unit_Base

template <typename T_Rep, typename T_Ratio = std::ratio<1L, 1L>>
class Distance : public Unit_Base<T_Rep, T_Ratio>
{
public:
    constexpr explicit Distance(const T_Rep& value) : Unit_Base<T_Rep, T_Ratio>(value) {}
};

/*
 *  Functions
 */
template <typename T_Unit_Base, typename T_Rep, typename T_Ratio>
T_Unit_Base Unit_Base_cast(const Unit_Base<T_Rep, T_Ratio>& measurement)
{
    return T_Unit_Base();
}

/*
 *  Operators
 */

/*
 *  Literal unit operators
 */

constexpr Distance<long double> operator"" _m(long double meters)
{
    return Distance<long double>{static_cast<long double>(meters)};
}

constexpr Distance<long double, std::kilo> operator"" _km(long double kilometers)
{
    return Distance<long double, std::kilo>{static_cast<long double>(kilometers)};
}

constexpr Distance<long double, std::milli> operator"" _mm(long double millimeters)
{
    return Distance<long double, std::milli>{static_cast<long double>(millimeters)};
}

}  // units

#endif /* __UNITS__ */