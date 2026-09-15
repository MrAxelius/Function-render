#pragma once

#include <cmath>
#include <vector>
#include <utility>

#include "modelo/Vector3.h"
#include "modelo/Vector4.h"

namespace Matematicas
{
    // Estructuras para escribir
    struct funcionParametrica
    {
        int xRangoInferior = -5;
        int xRangoSuperior = 5;
        int yRangoInferior = -5;
        int yRangoSuperior = 5;
        int xPuntos = 50;
        int yPuntos = 50;
    };
    struct proyeccionOrtografica
    {
        float derecha = 8.0f;
        float izquierda = -8.0f;
        float arriba = 8.0f;
        float abajo = -8.0f;
        float cerca = 0.1;
        float lejos = 100;
    };
    // El inline resuelve el problema del linker, si no se pone, el código se duplica y el linker da error
    // En clases, structs y templates las funciones son implicitamente inline
    inline bool floatIguales(float i, float j)
    {
        return (std::abs(i - j) < 1e-6f);
    }

    inline std::vector<std::pair<float, float>> calcularFuncion(int limite)
    {
        std::vector<std::pair<float, float>> funcion;
        funcion.resize(limite / 10);
        float x = 0;
        float y;

        // / 10 para no hacer una burrada de puntos, pero hacer una curva suave
        for (int i = 0; i < limite / 10; i++)
        {
            x = i * 10;
            y = i * (-i);
            funcion[i] = {x, y};
        }
        return funcion;
    }

    inline std::vector<Vector3> calcularSuperficie(funcionParametrica &funcion)
    {
        /*
            Es ligeramente más optimo devolver Vector4
            Pero entonces el código no es reutilizable
        */
        std::vector<Vector3> resultado;
        resultado.reserve(funcion.xPuntos * funcion.yPuntos);

        float pasoX = (float)(funcion.xRangoSuperior - funcion.xRangoInferior) / (funcion.xPuntos - 1);
        float pasoY = (float)(funcion.yRangoSuperior - funcion.yRangoInferior) / (funcion.yPuntos - 1);

        for (int i = 0; i < funcion.xPuntos; i++)
        {
            float x = funcion.xRangoInferior + i * pasoX;
            for (int j = 0; j < funcion.yPuntos; j++)
            {
                float y = funcion.yRangoInferior + j * pasoY;
                float z = sin(x) * cos(y);
                resultado.push_back(Vector3(x, y, z));
            }
        }

        return resultado;
    }

}
namespace Controlador
{
    struct configuracionPantalla
    {
        int ancho_Pantalla = 800;
        int alto_Pantalla = 600;
    };
}