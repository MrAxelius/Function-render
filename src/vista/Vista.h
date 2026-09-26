#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include <FunctionParser/FunctionParser.h>

#include "Utilidades.h"
#include "vista/Transformador.h"

class Vista
{
private:
    Controlador::configuracionPantalla configuracion;
    sf::RenderWindow &ventana;
    Transformador transformador;
    std::vector<sf::VertexArray> tramosFuncion; 
    sf::VertexArray superficie;

    bool modo3d = false;
    int tipoEjes = 0;

public:
    Vista(Controlador::rango &rango, sf::RenderWindow &ventana);
    // Recibe ya el cuerpo limpio, y se llama por frame
    void mostrar();
    void dibujarCuadricula();
    void dibujarEjes();

    void construirFuncion (const std::vector<FunctionParser::Punto>& puntos);
    void construirSuperficie (const std::vector<FunctionParser::Punto>& puntos);

    void cambioEjes();
    void invertirModo3d() { this->modo3d = !modo3d; }

    bool getModo3d() const { return this->modo3d; }
    
    int getAltoPantalla() const { return this->configuracion.altoPantalla;}
    int getAnchoPantalla() const { return this->configuracion.anchoPantalla;}

    void setSuperficie(const sf::VertexArray& superficie){ this->superficie = superficie; }
};