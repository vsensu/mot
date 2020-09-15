//
// Created by vsensu.
//

#ifndef MOT_MATH3D_H
#define MOT_MATH3D_H

#include <array>

template <typename T, std::size_t n>
struct Vector
{
    // We don't define any constructors but use aggregate initialization.
    // https://en.cppreference.com/w/cpp/language/aggregate_initialization
    std::array<T, n> elems;
};

template <typename T>
struct Vector3 : public Vector<T, 3>
{
    Vector3(T x, T y, T z)
    {
        this->elems[0] = x;
        this->elems[1] = y;
        this->elems[2] = z;
    }

    [[nodiscard]] inline const T& X() const { return this->elems_.at(0); }
    [[nodiscard]] inline const T& Y() const { return this->elems_.at(1); }
    [[nodiscard]] inline const T& Z() const { return this->elems_.at(2); }
};

using Vector3F = Vector3<float>;
using Vector3I = Vector3<int>;

#endif //MOT_MATH3D_H
