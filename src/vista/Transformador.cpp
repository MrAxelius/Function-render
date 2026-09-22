#include "vista/Transformador.h"
#include <FunctionParser/FunctionParser.h>

PuntoPantalla Transformador::Transformar(const FunctionParser::Punto& puntoMundo) const
{
    PuntoPantalla resultado;
    resultado.x = static_cast<float>((puntoMundo.x - rango.xMin) * pixelPorUnidad);
    resultado.y = static_cast<float>(configuracion.altoPantalla - ((puntoMundo.y - yMin) * pixelPorUnidad));
    return resultado;
}