#pragma once

#include <iostream>

class Vector2D {
 private:
  float m_x;
  float m_y;
  float m_length;

 public:
  Vector2D();
  Vector2D(float x, float y);
  Vector2D(const Vector2D &v);
  ~Vector2D();

  float x() const;
  float y() const;
  float length();

  void setX(float x);
  void setY(float y);
  void set(float x, float y);
  void set(Vector2D v);

  bool equals(const Vector2D &v) const;

  float dot(const Vector2D &v) const;
  static float dot(const Vector2D &v1, const Vector2D &v2);

  float angle(const Vector2D &v) const;
  static float angle(const Vector2D &v1, const Vector2D &v2);

  static Vector2D normalize(const Vector2D &v);

  Vector2D &operator+=(const Vector2D &v);
  Vector2D &operator-=(const Vector2D &v);
  Vector2D &operator*=(const Vector2D &v);
  Vector2D &operator/=(const Vector2D &v);

  Vector2D &operator+=(float x);
  Vector2D &operator-=(float x);
  Vector2D &operator*=(float x);
  Vector2D &operator/=(float x);

  void write(std::ostream &stream) const;
};

bool operator==(const Vector2D &v1, const Vector2D &v2);

Vector2D operator+ (const Vector2D &v1, const Vector2D &v2);
Vector2D operator- (const Vector2D &v1, const Vector2D &v2);
Vector2D operator* (const Vector2D &v1, const Vector2D &v2);
Vector2D operator/ (const Vector2D &v1, const Vector2D &v2);

Vector2D operator+ (const Vector2D &v, float x);
Vector2D operator- (const Vector2D &v, float x);
Vector2D operator* (const Vector2D &v, float x);
Vector2D operator/ (const Vector2D &v, float x);

std::ostream &operator<<(std::ostream &stream, const Vector2D &v);
