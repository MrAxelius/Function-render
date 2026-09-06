#include "Vista.h"

Vista::Vista(int ResolucionH, int ResolucionV, sf::RenderWindow &ventana)
    : ResolucionH(ResolucionH), ResolucionV(ResolucionV), ventana(ventana) {}

void Vista::mostrar(const std::vector<sf::Drawable*> &mostrado)
{
    ventana.clear();
    if (!modo3d)
    {
        if(tipoEjes < 0 || tipoEjes > 2)
            tipoEjes = 0;
        switch (tipoEjes)
        {
        case 0:
            break;
        case 1:
            dibujarEjes();
            break;
        case 2:
            dibujarCuadricula();
            break;
        }
    }
    else
    {
        // Añadir la lógica de proyección
    }
    for(const sf::Drawable* item : mostrado){
        this->ventana.draw(*item);
    }
    ventana.display();
}
void Vista::dibujarCuadricula()
{
    int menorValorPantalla = std::min(ResolucionH, ResolucionV);
    int espacioEntreCasillas = 10;
    // Ejes
    static sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 1.f));
    static sf::RectangleShape Eje_y(sf::Vector2f(1.f, 10000.f));

    // Color
    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Blue);

    // Dibujar la cuadrícula
    for (size_t i = 0.f; i < menorValorPantalla; i += espacioEntreCasillas)
    {
        // Espaciamos los ejes 10 px, para poder hacer un análisis de los resultados
        Eje_x.setPosition(sf::Vector2f(0, i));
        Eje_y.setPosition(sf::Vector2f(i, 0));

        ventana.draw(Eje_x);
        ventana.draw(Eje_y);
    }
}

void Vista::dibujarEjes()
{
    int menorValorPantalla = std::min(ResolucionH, ResolucionV);
    static sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 1.f));
    static sf::RectangleShape Eje_y(sf::Vector2f(1.f, 10000.f));

    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Blue);

    Eje_x.setPosition(sf::Vector2f(menorValorPantalla / 2, 0));
    Eje_y.setPosition(sf::Vector2f(0, menorValorPantalla / 2));
}

void Vista::cambioEjes()
{
    if (tipoEjes == 2)
    {
        tipoEjes = 0;
    }
    else
    {
        tipoEjes++;
    }
}