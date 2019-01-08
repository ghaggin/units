#ifndef __UNITS__
#define __UNITS__

#include <chrono>
#include <ostream>
#include <ratio>
#include <type_traits>

namespace units
{
template <typename T_Rep, typename T_Ratio = std::ratio<1L, 1L>>
struct Unit_Base;

/*
 *  Casting
 */
template <typename T_To_Unit_Base, typename _CF, typename _CR>
struct Unit_Base_cast_impl
{
    template <typename T_Rep, typename T_Ratio>
    static constexpr T_To_Unit_Base cast(const Unit_Base<T_Rep, T_Ratio>& unit_base)
    {
        typedef typename T_To_Unit_Base::rep __to_rep;
        return T_To_Unit_Base(
            static_cast<__to_rep>(static_cast<_CR>(unit_base.count()) * static_cast<_CR>(_CF::num) /
                                  static_cast<_CR>(_CF::den)));
    }
};

template <typename Type>
struct Is_Unit_Base : std::false_type
{
};

template <typename T_Rep, typename T_Ratio>
struct Is_Unit_Base<Unit_Base<T_Rep, T_Ratio>> : std::true_type
{
};

template <typename T_To_Unit_Base, typename T_Rep, typename T_Ratio>
constexpr typename std::enable_if<Is_Unit_Base<T_To_Unit_Base>::value, T_To_Unit_Base>::type
Unit_Base_cast(const Unit_Base<T_Rep, T_Ratio>& unit_base)
{
    typedef typename T_To_Unit_Base::ratio __to_ratio;
    typedef typename T_To_Unit_Base::rep __to_rep;
    typedef std::ratio_divide<T_Ratio, __to_ratio> __cf;
    typedef typename std::common_type<__to_rep, T_Rep, intmax_t>::type __cr;
    typedef Unit_Base_cast_impl<T_To_Unit_Base, __cf, __cr> unit_base_cast_impl;
    return unit_base_cast_impl::cast(unit_base);
}

/*
 *  Unit_Base
 *  TODO:   Add squared,cubed,etc.. units
 *          implement casts
 *          zero offset (deg / C)
 */
template <typename T_Rep, typename T_Ratio>
struct Unit_Base
{
    typedef T_Rep rep;
    typedef T_Ratio ratio;

    constexpr Unit_Base() = default;
    constexpr Unit_Base(const Unit_Base&) = default;
    constexpr explicit Unit_Base(const T_Rep& value) : value_(value) {}
    ~Unit_Base() = default;
    Unit_Base& operator=(const Unit_Base&) = default;

    T_Rep count() const { return value_; }

private:
    T_Rep value_;

};  // Unit_Base

/*
 *  Distance
 */
template <typename T_Rep, typename T_Ratio = std::ratio<1L, 1L>>
class Distance : public Unit_Base<T_Rep, T_Ratio>
{
public:
    constexpr explicit Distance(const T_Rep& value) : Unit_Base<T_Rep, T_Ratio>(value) {}
};  // Distance

// template <typename T_To_Distance, typename T_Distance>
// constexpr T_To_Distance Distance_cast(const T_Distance& dist)
// {
//     return Unit_Base_cast<T_To_Distance>(dist);
// }

/*
 *  Operators
 */
template <typename T_Unit_Base>
T_Unit_Base operator+(const T_Unit_Base& lhs, const T_Unit_Base rhs)
{
    return T_Unit_Base(lhs.count() + rhs.count());
}

template <typename T_Unit_Base>
T_Unit_Base operator-(const T_Unit_Base& lhs, const T_Unit_Base rhs)
{
    return T_Unit_Base(lhs.count() - rhs.count());
}

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