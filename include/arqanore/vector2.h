#pragma once

namespace arqanore {
    class Vector2 {
    public:
        static const Vector2 ZERO;
        static const Vector2 ONE;

        float x;
        float y;

        Vector2();

        Vector2(float x, float y);

        static float distance(Vector2 v1, Vector2 v2);

        static float angle(Vector2 v1, Vector2 v2);

        static float cross(Vector2 v1, Vector2 v2);

        static float dot(Vector2 v1, Vector2 v2);

        static Vector2 normalized(arqanore::Vector2 v);

        static Vector2 lerp(arqanore::Vector2 v1, arqanore::Vector2 v2, float by);

        Vector2 operator+(const Vector2 &v) const;

        Vector2 operator+(const float f) const;

        Vector2 operator-(const Vector2 &v) const;

        Vector2 operator-(const float f) const;

        Vector2 operator*(const Vector2 &v) const;

        Vector2 operator*(const float f) const;

        Vector2 operator/(const Vector2 &v) const;

        Vector2 operator/(const float f) const;

        bool operator==(const Vector2 &v) const;

        bool operator!=(const Vector2 &v) const;
    };
}
