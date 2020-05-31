#pragma once

#include "Vector2D.hpp"

template <typename T>
class Matrix2D {
 public:
  //! Default constructor
  Matrix2D() : coords{0, 0, 0, 0} {}
  Matrix2D(T a, T b, T c, T d) : coords{a, b, c, d} {}

  //! Copy constructor
  Matrix2D(const Matrix2D<T> &other) : coords(other.coords) {}

  //! Move constructor
  Matrix2D(Matrix2D<T> &&other) noexcept = delete;

  //! Destructor
  virtual ~Matrix2D() noexcept {}

  //! Copy assignment operator
  Matrix2D<T> &operator=(const Matrix2D<T> &other) {
    coords(other.coords);
    return *this;
  }

  //! Move assignment operator
  Matrix2D<T> &operator=(Matrix2D<T> &&other) noexcept {
    coords(other.coords);
    return *this;
  }

  Matrix2D<T> dot(const Matrix2D<T> &m) {
    return Matrix2D<T>(coords[0] * m.coords[0] + coords[1] * m.coords[2],
                       coords[0] * m.coords[1] + coords[1] * m.coords[3],
                       coords[2] * m.coords[0] + coords[3] * m.coords[2],
                       coords[2] * m.coords[1] + coords[3] * m.coords[3]);
  }

  Vector2D<T> dot(const Vector2D<T> &v) {
    return Vector2D<T>(v.getX() * coords[0] + v.getY() * coords[1],
                       v.getX() * coords[2] + v.getY() * coords[3]);
  }

  static Matrix2D<T> dot(const Matrix2D<T> &m1, const Matrix2D<T> &m2) {
    return m1.dot(m2);
  }

  static Matrix2D<T> dot(const Matrix2D<T> &m, const Vector2D<T> &v) {
    return m.dot(v);
  }

  static Matrix2D<T> Identity() { return Matrix2D<T>(1, 0, 0, 1); }

  Matrix2D<T> &operator+=(const Matrix2D<T> &m) {
    coords[0] += m.coords[0];
    coords[1] += m.coords[1];
    coords[2] += m.coords[2];
    coords[3] += m.coords[3];
    return *this;
  }

  Matrix2D<T> &operator-=(const Matrix2D<T> &m) {
    coords[0] -= m.coords[0];
    coords[1] -= m.coords[1];
    coords[2] -= m.coords[2];
    coords[3] -= m.coords[3];
    return *this;
  }

  Matrix2D<T> &operator*=(const Matrix2D<T> &m) {
    coords[0] *= m.coords[0];
    coords[1] *= m.coords[1];
    coords[2] *= m.coords[2];
    coords[3] *= m.coords[3];
    return *this;
  }

  Matrix2D<T> &operator/=(const Matrix2D<T> &m) {
    coords[0] /= m.coords[0];
    coords[1] /= m.coords[1];
    coords[2] /= m.coords[2];
    coords[3] /= m.coords[3];
    return *this;
  }

  Matrix2D<T> &operator+=(T z) {
    coords[0] += z;
    coords[1] += z;
    coords[2] += z;
    coords[3] += z;
    return *this;
  }

  Matrix2D<T> &operator-=(T z) {
    coords[0] -= z;
    coords[1] -= z;
    coords[2] -= z;
    coords[3] -= z;
    return *this;
  }

  Matrix2D<T> &operator*=(T z) {
    coords[0] *= z;
    coords[1] *= z;
    coords[2] *= z;
    coords[3] *= z;
    return *this;
  }

  Matrix2D<T> &operator/=(T z) {
    coords[0] /= z;
    coords[1] /= z;
    coords[2] /= z;
    coords[3] /= z;
    return *this;
  }

  T coords[4];
};

template <typename T>
Matrix2D<T> operator+(const Matrix2D<T> &m1, const Matrix2D<T> &m2) {
  Matrix2D<T> result(m1);
  result += m2;
  return result;
}

template <typename T>
Matrix2D<T> operator-(const Matrix2D<T> &m1, const Matrix2D<T> &m2) {
  Matrix2D<T> result(m1);
  result -= m2;
  return result;
}

template <typename T>
Matrix2D<T> operator*(const Matrix2D<T> &m1, const Matrix2D<T> &m2) {
  Matrix2D<T> result(m1);
  result *= m2;
  return result;
}

template <typename T>
Matrix2D<T> operator/(const Matrix2D<T> &m1, const Matrix2D<T> &m2) {
  Matrix2D<T> result(m1);
  result /= m2;
  return result;
}

template <typename T>
Matrix2D<T> operator+(const Matrix2D<T> &m1, T z) {
  Matrix2D<T> result(m1);
  result += z;
  return result;
}

template <typename T>
Matrix2D<T> operator-(const Matrix2D<T> &m1, T z) {
  Matrix2D<T> result(m1);
  result -= z;
  return result;
}

template <typename T>
Matrix2D<T> operator*(const Matrix2D<T> &m1, T z) {
  Matrix2D<T> result(m1);
  result *= z;
  return result;
}

template <typename T>
Matrix2D<T> operator/(const Matrix2D<T> &m1, T z) {
  Matrix2D<T> result(m1);
  result /= z;
  return result;
}
