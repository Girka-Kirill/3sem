// Girka_Vector.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>

struct Vector2{
    float x;
    float y;

    Vector2(float x_ = 0, float y_ = 0) {
        x = x_;
        y = y_;
    };
    ~Vector2() {
    }

    friend std::ostream& operator<< (std::ostream& stream, const Vector2& v);
    friend std::istream& operator>> (std::istream& stream, Vector2& v);
    Vector2 operator+ (const Vector2& other) const {
        struct Vector2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
    Vector2& operator+ (const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }
    Vector2 operator+= (const Vector2& other) const {
        struct Vector2 result;
        result.x = x + other.x;
        result.y = y + other.y;
        return result;
    }
    Vector2& operator- (const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this;
    }
    Vector2 operator-= (const Vector2& other) const {
        struct Vector2 result;
        result.x = x - other.x;
        result.y = y - other.y;
        return result;
    }
    float operator* (const Vector2& other) const {
        return x * other.x + y * other.y;
    }
    float operator^ (const Vector2& other) const {
        return x * other.x - y * other.y;
    }
    Vector2 scalarMul (const float& a) {
        Vector2 result(x*a, y*a);
        return result;
    }
    Vector2 scalarDiv(const float& a) {
        Vector2 result(x/a, y/a);
        return result;
    }
    Vector2 perpend() {
        Vector2 result(y, -x);
        return result;
    }
    float len() {
        return sqrt(x * x + y * y);
    }
    float squareLen() {
        return x * x + y * y;
    }
    Vector2 norm() {
        Vector2 result(x / sqrt(x * x + y * y), y / sqrt(x * x + y * y));
        return result;
    }

    Vector2 operatorUnarMinus () const {
        Vector2 result(-x,-y);
        return result;
    }
    Vector2& rotate (const char& angle) {
        float tempx = x, tempy = y;
        x = x * cos(angle) - y * sin(angle);
        y = x * sin(angle) + y * cos(angle);
        return *this;
    }
    Vector2 getRotated(const char& angle) {
        Vector2 result(x * cos(angle) - y * sin(angle), x * sin(angle) + y * cos(angle));
        return result;
    }
};

std::ostream& operator<< (std::ostream& stream, const Vector2& v) {
    stream << v.x << " " << v.y;
    return stream;
}

std::istream& operator>> (std::istream& stream, Vector2& v) {
    stream >> v.x >> v.y;
    return stream;
}

int main()
{
    float a = 3.2, b = 5.6;
    Vector2 vect1(a,b);
    Vector2 vect2;
    std::cin >> vect2;

    std::cout << vect1 << std::endl;
    std::cout << vect2 << std::endl;

    vect1.operator+(vect2);
    std::cout << "operator+ " << vect1 << std::endl;
    std::cout << "operator+= " << vect1.operator+=(vect2) << std::endl;

    vect1.operator-(vect2);
    std::cout << "operator- " << vect1 << std::endl;
    std::cout << "operator-= " << vect1.operator-=(vect2) << std::endl;

    std::cout << "operator* " << vect1.operator*(vect2) << std::endl;

    std::cout << "operator^ " << vect1.operator^(vect2) << std::endl;

    std::cout << "scalarMul " << vect1.scalarMul(1.5) << std::endl;

    std::cout << "scalarDiv " << vect1.scalarDiv(1.5) << std::endl;

    std::cout << "norm " << vect1.norm() << std::endl;

    std::cout << "perpend " << vect1.perpend() << std::endl;

    std::cout << "len " << vect1.len() << std::endl;
    std::cout << "squareLen " << vect1.squareLen() << std::endl;

    std::cout << "operatorUnarMinus " << vect1.operatorUnarMinus() << std::endl;

    vect1.rotate(30);
    std::cout << "rotate " << vect1 << std::endl;
    std::cout << "getRotated " << vect2.getRotated(48) << std::endl;
}
