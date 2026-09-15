#ifndef CAMARA_H
#define CAMARA_H

#include "Vector3.h"
#include "controlador/input.h"

struct Camara {

    Vector3 eye; 
    Vector3 target;
    Vector3 up;
    
    float anguloH;
    float anguloV;
    float distancia;
    //Velocidad a la que se mueven la cámara, de momento son valores de testeo
    float velocidadMovimiento = 10.0f;

    void update(float dt, const Entrada &entrada);
    // No es necesario, debería ir en update, es por claridad
    // Y poder debuggear más fácil si algo falla
    // Prolly acabará unido en update
    void updateEye();
};

#endif