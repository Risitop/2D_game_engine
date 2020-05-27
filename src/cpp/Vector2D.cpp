#include "../inc/Vector2D.hpp"

#include <math.h>
#include <string>

Vector2D::Vector2D(): m_x(0), m_y(0), m_length(-1.0)
{

}

Vector2D::Vector2D(float x, float y): m_x(x), m_y(y), m_length(-1.0)
{

}

Vector2D::Vector2D(const Vector2D &v): m_x(v.m_x), m_y(v.m_y), m_length(v.m_length)
{

}

Vector2D::~Vector2D() {

}

float Vector2D::x() const { return m_x; }

float Vector2D::y() const { return m_y; }

float Vector2D::length() {
  if (m_length < 0) {
    const float x = this->x();
    const float y = this->y();
    m_length = sqrt(x * x + y * y);
  }

  return m_length;
}

void Vector2D::setX(float x) { m_x = x; }

void Vector2D::setY(float y) { m_y = y; }

void Vector2D::set(float x, float y) {
  this->setX(x);
  this->setY(y);
  m_length = -1.0;
}

void Vector2D::set(Vector2D v) { this->set(v.m_x, v.m_y); }

bool Vector2D::equals(const Vector2D &v) const {
  return (m_x == v.m_x && m_y == v.m_y);
}

float Vector2D::dot(const Vector2D &v) const {

    return m_x * v.m_x + m_y * v.m_y;

}

float Vector2D::dot(const Vector2D &v1, const Vector2D &v2) {

    return v1.dot(v2);

}

float Vector2D::angle(const Vector2D &v) const {

    float angle = atan2(v.m_y, v.m_x) - atan2(m_y, m_x);

    if (angle < 0) {
        angle += 2*M_PI;
    }

    return angle;

}

float Vector2D::angle(const Vector2D &v1, const Vector2D &v2) {

    return v1.angle(v2);

}

Vector2D Vector2D::normalize(const Vector2D &v) {

    if (v.m_length == 0.0) {
        throw std::string("Invalid normalization of 0-length vector.");
        return Vector2D(0.0, 0.0);
    }

    return Vector2D(v.m_x / v.m_length, v.m_y / v.m_length);

}

Vector2D& Vector2D::operator+=(const Vector2D &v) {

    m_x += v.m_x;
    m_y += v.m_y;
    return *this;

}

Vector2D& Vector2D::operator-=(const Vector2D &v) {

    m_x -= v.m_x;
    m_y -= v.m_y;
    return *this;

}

Vector2D& Vector2D::operator*=(const Vector2D &v) {

    m_x *= v.m_x;
    m_y *= v.m_y;
    return *this;

}

Vector2D& Vector2D::operator/=(const Vector2D &v) {

    if (v.m_x == 0.0) {
        throw std::string("Division by 0.");
    }
    if (v.m_y == 0.0) {
        throw std::string("Division by 0.");
    }
    m_x /= v.m_x;
    m_y /= v.m_y;
    return *this;

}

Vector2D& Vector2D::operator+=(float x) {

    m_x += x;
    m_y += x;
    return *this;

}

Vector2D& Vector2D::operator-=(float x) {

    m_x -= x;
    m_y -= x;
    return *this;

}

Vector2D& Vector2D::operator*=(float x) {

    m_x *= x;
    m_y *= x;
    return *this;

}

Vector2D& Vector2D::operator/=(float x) {

    if (x == 0.0) {
        throw std::string("Division by 0.");
    }

    m_x /= x;
    m_y /= x;
    return *this;

}

void Vector2D::write(std::ostream &stream) const {

    stream << "Vector2D[" << m_x << ", " << m_y << "]";

}

bool operator==(const Vector2D &v1, const Vector2D &v2) {

    return v1.equals(v2);

}

Vector2D operator+(const Vector2D &v1, const Vector2D &v2) {

    Vector2D result(v1);
    result += v2;
    return result;

}

Vector2D operator-(const Vector2D &v1, const Vector2D &v2) {

    Vector2D result(v1);
    result -= v2;
    return result;

}

Vector2D operator*(const Vector2D &v1, const Vector2D &v2) {

    Vector2D result(v1);
    result *= v2;
    return result;

}

Vector2D operator/(const Vector2D &v1, const Vector2D &v2) {

    Vector2D result(v1);
    result /= v2;
    return result;

}

Vector2D operator+(const Vector2D &v1, float x) {

    Vector2D result(v1);
    result += x;
    return result;

}

Vector2D operator-(const Vector2D &v1, float x) {

    Vector2D result(v1);
    result -= x;
    return result;

}

Vector2D operator*(const Vector2D &v1, float x) {

    Vector2D result(v1);
    result *= x;
    return result;

}

Vector2D operator/(const Vector2D &v1, float x) {

    Vector2D result(v1);
    result /= x;
    return result;

}

std::ostream &operator<<(std::ostream &stream, const Vector2D &v) {

    v.write(stream);
    return stream;
}
