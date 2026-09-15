#include "Vector3.h"
#include "Vector4.h"

#include <stdexcept>
#include <math.h>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{
    // Inicializar en la lista de elementos
}

// Obtenemos el módulo
float Vector3::magnitud() const
{
    return (sqrt((x * x) + (y * y) + (z * z)));
}

// Dividimos todo por el módulo
void Vector3::normalizado()
{

    const float modulo = this->magnitud();
    if (modulo == 0)
    {
        throw std::invalid_argument("El modulo del vector es 0");
    }
    this->set_x(x / modulo);
    this->set_y(y / modulo);
    this->set_z(z / modulo);
}

// Dividimos por el módulo, creamos otro vector
Vector3 Vector3::normalizar() const
{ 
    const float modulo = this->magnitud();
    if (modulo == 0)
    {
        throw std::invalid_argument("El modulo del vector es 0");
    }
    float au1 = this->x / modulo;
    float au2 = this->y / modulo;
    float au3 = this->z / modulo;
    return Vector3(au1, au2, au3);
}

Vector3 Vector3::operator+(const Vector3 &sumando) const
{

    float x_1 = this->x + sumando.x;
    float y_1 = this->y + sumando.y;
    float z_1 = this->z + sumando.z;
    return Vector3(x_1, y_1, z_1);
}

Vector3 Vector3::operator-(const Vector3 &sustraendo) const
{

    float x_1 = this->x - sustraendo.x;
    float y_1 = this->y - sustraendo.y;
    float z_1 = this->z - sustraendo.z;
    return Vector3(x_1, y_1, z_1);
}

Vector3 Vector3::productoVectorial(const Vector3 &multiplicando) const
{

    // Por claridad, no hacemos el proceso completo, sino que directamente pasamos a la formula

    float au1 = (this->y * multiplicando.z) - (this->z * multiplicando.y);
    float au2 = (this->z * multiplicando.x) - (this->x * multiplicando.z);
    float au3 = (this->x * multiplicando.y) - (this->y * multiplicando.x);
    return Vector3(au1, au2, au3);
}

float Vector3::productoEscalar(const Vector3 &multiplicando) const
{

    float au1 = this->x * multiplicando.x;
    float au2 = this->y * multiplicando.y;
    float au3 = this->z * multiplicando.z;
    return (au1 + au2 + au3);
}

Vector3 Vector3::operator*(float multiplo) const
{

    float au1 = this->x * multiplo;
    float au2 = this->y * multiplo;
    float au3 = this->z * multiplo;
    return Vector3(au1, au2, au3);
}

Vector3 Vector3::operator/(float divisor) const
{
    if (divisor == 0)
    {
        throw std::invalid_argument("El divisor del vector es 0");
    }
    float au1 = this->x / divisor;
    float au2 = this->y / divisor;
    float au3 = this->z / divisor;
    return Vector3(au1, au2, au3);
}

// Operadores de acumulación
void Vector3::operator*=(float multiplo)
{

    this->x *= multiplo;
    this->y *= multiplo;
    this->z *= multiplo;
}

void Vector3::operator/=(float divisor)
{
    if (divisor == 0)
    {
        throw std::invalid_argument("El divisor del vector es 0");
    }
    this->x /= divisor;
    this->y /= divisor;
    this->z /= divisor;
}

void Vector3::operator+=(const Vector3 sumando)
{

    this->x += sumando.x;
    this->y += sumando.y;
    this->z += sumando.z;
}

void Vector3::operator-=(const Vector3 sustraendo)
{

    this->x -= sustraendo.x;
    this->y -= sustraendo.y;
    this->z -= sustraendo.z;
}

Vector4 Vector3::homogeneizar() const
{
    return Vector4(*this);
}