#pragma once
#include <FunctionParser/FunctionParser.h>
#include "Utilidades.h"

struct PuntoPantalla
{
    float x = 0.0f;
    float y = 0.0f;
};

class Transformador
{
private:
    Controlador::configuracionPantalla configuracion;
    Controlador::rango rango;
    double yMin;
    double yMax;
    double pixelPorUnidad;

public:

    Transformador(const Controlador::configuracionPantalla& configuracion,const Controlador::rango& rango)
        : configuracion(configuracion), rango(rango)
        {
            double relacion = static_cast<double>(configuracion.altoPantalla) / static_cast<double>(configuracion.anchoPantalla);
            double anchoMundo = rango.xMax - rango.xMin;
            pixelPorUnidad = static_cast<double>(configuracion.anchoPantalla) / anchoMundo;
            double alturaMundo = relacion * anchoMundo;
            yMax = alturaMundo / 2;
            yMin = - alturaMundo / 2;
        }
    
    PuntoPantalla Transformar(const FunctionParser::Punto& puntoMundo) const;
};

