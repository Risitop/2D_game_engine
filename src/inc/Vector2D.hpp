#pragma once

#include <math.h>

#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <string>

template <typename T>
class Vector2D : public sf::Vector2<T> {
 public:
  Vector2D() : sf::Vector2<T>(0, 0) {}
  Vector2D(T x, T y) : sf::Vector2<T>(x, y) {}
  Vector2D(const sf::Vector2<T> &v) : sf::Vector2<T>(v.x, v.y) {}
  ~Vector2D() {}

  T getX() const { return this->x; }
  T getY() const { return this->y; }
  float length() {
    if (m_length < 0) {
      const float xtmp = getX();
      const float ytmp = getY();
      m_length = sqrt(xtmp * xtmp + ytmp * ytmp);
    }
    return m_length;
  }

  void setX(T new_x) {
    this->x = new_x;
    m_length = -1;
  }
  void setY(T new_y) {
    this->y = new_y;
    m_length = -1;
  }
  void set(T new_x, T new_y) {
    setX(new_x);
    setY(new_y);
  }
  void set(const Vector2D<T> &v) { set(v.getX(), v.getY()); }

  bool equals(const Vector2D<T> &v) const {
    return getX() == v.getX() && getY() == v.getY();
  }

  float dot(const Vector2D<T> &v) const {
    return getX() * v.getX() + getY() * v.getY();
  }
  static float dot(const Vector2D<T> &v1, const Vector2D<T> &v2) {
    return v1.dot(v2);
  }

  float angle(const Vector2D<T> &v) const {
    float angle = atan2(v.getY(), v.getX()) - atan2(getY(), getX());

    if (angle < 0) {
      angle += 2 * M_PI;
    }

    return angle;
  }
  static float angle(const Vector2D<T> &v1, const Vector2D<T> &v2) {
    return v1.angle(v2);
  }

  static Vector2D<T> normalize(Vector2D<T> &v) {
    assert(v.length() > 0);
    return Vector2D<T>(v.getX(), v.getY()) / v.length();
  }

  Vector2D<T> &operator+=(const Vector2D<T> &v) {
    setX(getX() + v.getX());
    setY(getY() + v.getY());
    return *this;
  }
  Vector2D<T> &operator-=(const Vector2D<T> &v) {
    setX(getX() - v.getX());
    setY(getY() - v.getY());
    return *this;
  }
  Vector2D<T> &operator*=(const Vector2D<T> &v) {
    setX(getX() * v.getX());
    setY(getY() * v.getY());
    return *this;
  }
  Vector2D<T> &operator/=(const Vector2D<T> &v) {
    setX(getX() / v.getX());
    setY(getY() / v.getY());
    return *this;
  }

  Vector2D<T> &operator+=(T z) {
    setX(getX() + z);
    setY(getY() + z);
    return *this;
  }
  Vector2D<T> &operator-=(T z) {
    setX(getX() - z);
    setY(getY() - z);
    return *this;
  }
  Vector2D<T> &operator*=(T z) {
    setX(getX() * z);
    setY(getY() * z);
    return *this;
  }
  Vector2D<T> &operator/=(T z) {
    setX(getX() / z);
    setY(getY() / z);
    return *this;
  }

  void write(std::ostream &stream) const {
    stream << "Vector2D[" << getX() << "/" << getY() << "]";
  }

 private:
  float m_length;
};

template <typename T>
bool operator==(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  return v1.equals(v2);
}

template <typename T>
Vector2D<T> operator+(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  Vector2D<T> result(v1);
  result += v2;
  return result;
}
template <typename T>
Vector2D<T> operator-(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  Vector2D<T> result(v1);
  result -= v2;
  return result;
}
template <typename T>
Vector2D<T> operator*(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  Vector2D<T> result(v1);
  result *= v2;
  return result;
}
template <typename T>
Vector2D<T> operator/(const Vector2D<T> &v1, const Vector2D<T> &v2) {
  Vector2D<T> result(v1);
  result /= v2;
  return result;
}

template <typename T>
Vector2D<T> operator+(const Vector2D<T> &v1, float z) {
  Vector2D<T> result(v1);
  result += z;
  return result;
}
template <typename T>
Vector2D<T> operator-(const Vector2D<T> &v1, float z) {
  Vector2D<T> result(v1);
  result -= z;
  return result;
}
template <typename T>
Vector2D<T> operator*(const Vector2D<T> &v1, float z) {
  Vector2D<T> result(v1);
  result *= z;
  return result;
}
template <typename T>
Vector2D<T> operator/(const Vector2D<T> &v1, float z) {
  Vector2D<T> result(v1);
  result /= z;
  return result;
}

template <typename T>
std::ostream &operator<<(std::ostream &stream, const Vector2D<T> &v) {
  v.write(stream);
  return stream;
}
