#include "Camara.h"

#include <cmath>

void Camara::update(float dt, const Entrada &entrada)
{
    if (entrada.getVertical() == 1)
    {
        anguloV += dt * velocidadMovimiento;
        if (anguloV >= 1.57f)
        {
            anguloV = 1.57f;
        }
    }
    if (entrada.getVertical() == -1)
    {
        if (anguloV <= -1.57f)
        {
            anguloV = -1.57f;
        }
        anguloV -= dt * velocidadMovimiento;
    }
    if (entrada.getHorizontal() == 1)
    {
        anguloH += dt * velocidadMovimiento;
    }
    if (entrada.getHorizontal() == -1)
    {
        anguloH -= dt * velocidadMovimiento;
    }
    // No funciona bien
    // Tests TODO
    if (entrada.getZoom() == 1)
    {
        distancia += dt * velocidadMovimiento;
    }
    if (entrada.getZoom() == -1)
    {
        if (distancia > 0.5f)
        {
            distancia -= dt * velocidadMovimiento;
        }
    }
    updateEye();
}

void Camara::updateEye()
{
    // Coordenadas esféricas: ánguloH desde el eje Z (no desde el eje X)
    this->eye.set_x(distancia * std::cos(anguloV) * std::sin(anguloH));
    this->eye.set_y(distancia * std::sin(anguloV));
    this->eye.set_z(distancia * std::cos(anguloV) * std::cos(anguloH));
}
