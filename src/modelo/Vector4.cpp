#include "Vector4.h"
#include "Vector3.h"
#include "Utilidades.h"

#include <array>

Vector4::Vector4(float x, float y, float z, float w)
    : x(x), y(y), z(z), w(w) {}

Vector4::Vector4(const Vector3 &vector)
{
    this->x = vector.get_x();
    this->y = vector.get_y();
    this->z = vector.get_z();
}

Vector4::Vector4(const std::array<float, 4> &array)
{
    this->x = array[0];
    this->y = array[1];
    this->z = array[2];
    this->w = array[3];
}

Vector3 Vector4::toVector3() const
{
    if (Matematicas::floatIguales(w, 1.0f) || Matematicas::floatIguales(w, 0.0f))
    {
        return Vector3(this->x, this->y, this->z);
    }
    return Vector3(this->x / this->w, this->y / this->w, this->z / this->w);
}

Vector4 Vector4::operator*(float multiplo)
{
    Vector4 solucion({0, 0, 0, 0});
    solucion.set_x(this->x *= multiplo);
    solucion.set_y(this->y *= multiplo);
    solucion.set_z(this->z *= multiplo);
    solucion.set_w(this->w *= multiplo);
    return solucion;
}

std::array<float, 4> Vector4::toArray() const
{
    std::array<float, 4> convertido;
    convertido[0] = this->x;
    convertido[1] = this->y;
    convertido[2] = this->z;
    convertido[3] = this->w;
    return convertido;
}

float Vector4::productoEscalar(float multiplo) const
{

    float au1 = this->x * multiplo;
    float au2 = this->y * multiplo;
    float au3 = this->z * multiplo;
    float au4 = this->w * multiplo;
    return (au1 + au2 + au3 + au4);
}
