#pragma once

#include <SFML/Graphics.hpp>

class Vista
{
    private:
    int ResolucionH;
    int ResolucionV;
    // Ventana pasa como referencia
    // No es valor, porque no es copiable, no es puntero por seguridad, evita nullptr
    sf::RenderWindow& ventana;

    bool modo3d = false;
    int tipoEjes = 0;

    public:
    Vista(int ResolucionH, int ResolucionV, sf::RenderWindow& ventana);
    //Recibe ya el cuerpo limpio, y se llama por frame
    void mostrar(const std::vector<sf::Drawable*> &mostrado);
    void dibujarCuadricula();
    void dibujarEjes();

    void cambioEjes();
    void invertirModo3d() { this->modo3d = !modo3d; }

    bool getModo3d() const { return this->modo3d; }
};