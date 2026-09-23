#include "Vista.h"

#include "vista/Transformador.h"

namespace
{
    Controlador::configuracionPantalla obtenerTamañoPantalla(const sf::RenderWindow &ventana)
    {
        Controlador::configuracionPantalla configuracion;
        configuracion.altoPantalla = static_cast<int>(ventana.getSize().y);
        configuracion.anchoPantalla = static_cast<int>(ventana.getSize().x);
        return configuracion;
    }
}

Vista::Vista(Controlador::rango &rango, sf::RenderWindow &ventana)
    : configuracion(obtenerTamañoPantalla(ventana)), ventana(ventana), transformador(configuracion, rango)
{
}

void Vista::mostrar(const std::vector<sf::Drawable *> &mostrado, const std::vector<FunctionParser::Punto> &puntos)
{
    ventana.clear();
    if (!modo3d)
    {
        if (tipoEjes < 0 || tipoEjes > 2)
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
    for (const sf::Drawable *item : mostrado)
    {
        this->ventana.draw(*item);
    }
    funcion2d(puntos);
    ventana.display();
}
void Vista::dibujarCuadricula()
{
    size_t mayorValorPantalla = std::max(configuracion.altoPantalla, configuracion.anchoPantalla);
    size_t espacioEntreCasillas = 10;
    // Ejes
    static sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 1.f));
    static sf::RectangleShape Eje_y(sf::Vector2f(1.f, 10000.f));

    // Color
    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Blue);

    // Dibujar la cuadrícula
    for (float i = 0; i < mayorValorPantalla; i += espacioEntreCasillas)
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
    static sf::RectangleShape Eje_x(sf::Vector2f(10000.f, 1.f));
    static sf::RectangleShape Eje_y(sf::Vector2f(1.f, 10000.f));

    PuntoPantalla origen = transformador.Transformar(FunctionParser::Punto{0.0, 0.0});

    Eje_x.setFillColor(sf::Color::Blue);
    Eje_y.setFillColor(sf::Color::Blue);

    Eje_x.setPosition(sf::Vector2f(0.f, origen.y));
    Eje_y.setPosition(sf::Vector2f(origen.x, 0.f));

    ventana.draw(Eje_x);
    ventana.draw(Eje_y);
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

void Vista::funcion2d(const std::vector<FunctionParser::Punto> &puntos)
{
    sf::VertexArray funcion (sf::PrimitiveType::LineStrip);
    for (const auto& punto : puntos)
    {
        if(std::isfinite(punto.y))
        {
            auto puntoPantalla = transformador.Transformar(punto);
            funcion.append(sf::Vector2f(puntoPantalla.x, puntoPantalla.y));
        }else{
            ventana.draw(funcion);
            funcion.clear();
        }
    }
    ventana.draw(funcion);
}