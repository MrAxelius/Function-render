#include "Matriz4x4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Utilidades.h"

#include <cmath>
#include <array>
#include <stdexcept>
#include <initializer_list>
#include <optional>

Matriz4x4::Matriz4x4()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (i == j)
            {
                matriz[i][j] = 1.f;
            }
            else
                matriz[i][j] = 0.f;
        }
    }
}

Matriz4x4::Matriz4x4(std::initializer_list<float> valores)
{
    if (valores.size() != 16)
    {
        throw std::invalid_argument("La lista de elementos debe tener 16 elementos");
    }

    int contadorDesdoblado = 0;
    for(auto v : valores)
    {
        // La división literal da la fila, pasa de 1 en 1 cada 4 elementos
        // El modulo(resto) suma 1 por elemento, pero se resetea cada 4 al ser múltiplo
        matriz[contadorDesdoblado / 4][contadorDesdoblado % 4] = v;
        ++contadorDesdoblado;
    }
}

Matriz4x4::Matriz4x4(const std::array<float, 16> &valores)
{
    int contador = 0;
    for (int fila = 0; fila < 4; fila++)
    {
        for (int columna = 0; columna < 4; columna++)
        {
            matriz[fila][columna] = valores[contador];
            contador++;
        }
    }
}

Matriz4x4 Matriz4x4::operator*(const Matriz4x4 &multiplo) const
{
    std::array<float, 16> resultado;
    float au = 0;
    int contador = 0;

    for (int fila = 0; fila < 4; fila++)
    {
        for (int columna_a = 0; columna_a < 4; columna_a++)
        {
            for (int comun = 0; comun < 4; comun++)
            {
                au += this->matriz[fila][comun] * multiplo.matriz[comun][columna_a];
            }
            resultado[contador] = au;
            au = 0;
            contador++;
        }
    }
    return Matriz4x4(resultado);
}

Vector3 Matriz4x4::operator*(const Vector3 &multiplo) const
{

    float r0 = matriz[0][0] * multiplo.get_x() + matriz[0][1] * multiplo.get_y() +
               matriz[0][2] * multiplo.get_z() + matriz[0][3];
    float r1 = matriz[1][0] * multiplo.get_x() + matriz[1][1] * multiplo.get_y() +
               matriz[1][2] * multiplo.get_z() + matriz[1][3];
    float r2 = matriz[2][0] * multiplo.get_x() + matriz[2][1] * multiplo.get_y() +
               matriz[2][2] * multiplo.get_z() + matriz[2][3];
    float r3 = matriz[3][0] * multiplo.get_x() + matriz[3][1] * multiplo.get_y() +
               matriz[3][2] * multiplo.get_z() + matriz[3][3];

    if (Matematicas::floatIguales(r3, 0) || Matematicas::floatIguales(r3, 1))
    {
        return Vector3(r0, r1, r2);
    }
    else
    {
        Vector4 final(r0, r1, r2, r3);
        return final.toVector3();
    }
}

Matriz4x4 Matriz4x4::traslacion(float tx, float ty, float tz)
{

    Matriz4x4 resultado;

    // Sustitucon en el Row-Major
    resultado.matriz[0][3] = tx;
    resultado.matriz[1][3] = ty;
    resultado.matriz[2][3] = tz;
    return resultado;
}

Matriz4x4 Matriz4x4::escalado(float sx, float sy, float sz)
{

    Matriz4x4 resultado;

    // Sustitución de la DP por los valores de escalado
    resultado.matriz[0][0] = sx;
    resultado.matriz[1][1] = sy;
    resultado.matriz[2][2] = sz;
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_x(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje horizontal
    resultado.matriz[1][1] = std::cos(angulo);
    resultado.matriz[1][2] = -(std::sin(angulo));
    resultado.matriz[2][1] = std::sin(angulo);
    resultado.matriz[2][2] = std::cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_y(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje vertical
    resultado.matriz[0][0] = std::cos(angulo);
    resultado.matriz[0][2] = -(std::sin(angulo));
    resultado.matriz[2][0] = std::sin(angulo);
    resultado.matriz[2][2] = std::cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::rotacion_z(float angulo)
{

    Matriz4x4 resultado;

    // Rotación sobre el eje de profundidad
    resultado.matriz[0][0] = std::cos(angulo);
    resultado.matriz[0][1] = -(std::sin(angulo));
    resultado.matriz[1][0] = std::sin(angulo);
    resultado.matriz[1][1] = std::cos(angulo);
    return resultado;
}

Matriz4x4 Matriz4x4::lookAt(const Camara &camara)
{
    Vector3 forward = (camara.target - camara.eye).normalizar();
    Vector3 right = forward.productoVectorial(camara.up).normalizar();
    Vector3 up = right.productoVectorial(forward).normalizar();

    Matriz4x4 resultado;

    // Fila 0: right
    resultado.matriz[0][0] = right.get_x();
    resultado.matriz[0][1] = right.get_y();
    resultado.matriz[0][2] = right.get_z();
    resultado.matriz[0][3] = -right.productoEscalar(camara.eye);

    // Fila 1: up
    resultado.matriz[1][0] = up.get_x();
    resultado.matriz[1][1] = up.get_y();
    resultado.matriz[1][2] = up.get_z();
    resultado.matriz[1][3] = -up.productoEscalar(camara.eye);

    // Fila 2: -forward
    resultado.matriz[2][0] = -forward.get_x();
    resultado.matriz[2][1] = -forward.get_y();
    resultado.matriz[2][2] = -forward.get_z();
    resultado.matriz[2][3] = forward.productoEscalar(camara.eye);

    // Fila 3
    resultado.matriz[3][0] = 0.0f;
    resultado.matriz[3][1] = 0.0f;
    resultado.matriz[3][2] = 0.0f;
    resultado.matriz[3][3] = 1.0f;

    return resultado;
}

float Matriz4x4::getElemento(int fila, int columna) const
{
    return this->matriz[fila][columna];
}

void Matriz4x4::setElemento(int fila, int columna, float elemento)
{
    this->matriz[fila][columna] = elemento;
}

std::optional<Matriz4x4> Matriz4x4::crearOrtografica(const Matematicas::proyeccionOrtografica &proyeccion)
{
    if (Matematicas::floatIguales(proyeccion.derecha, proyeccion.izquierda) ||
        Matematicas::floatIguales(proyeccion.arriba, proyeccion.abajo) ||
        Matematicas::floatIguales(proyeccion.lejos, proyeccion.cerca))
    {
        return std::nullopt;
    }
    Matriz4x4 m;

    // Diagonal principal
    m.matriz[0][0] = 2.0f / (proyeccion.derecha - proyeccion.izquierda);
    m.matriz[1][1] = 2.0f / (proyeccion.arriba - proyeccion.abajo);
    m.matriz[2][2] = - (2.0f / (proyeccion.lejos - proyeccion.cerca));
    // Columna 4
    m.matriz[0][3] = - ((proyeccion.derecha + proyeccion.izquierda) / (proyeccion.derecha - proyeccion.izquierda));
    m.matriz[1][3] = - ((proyeccion.arriba + proyeccion.abajo) / (proyeccion.arriba - proyeccion.abajo));
    m.matriz[2][3] = - ((proyeccion.lejos + proyeccion.cerca) / (proyeccion.lejos - proyeccion.cerca));

    return m;
}