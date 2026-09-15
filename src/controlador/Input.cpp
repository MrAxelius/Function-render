#include "input.h"

#include <SFML/Window/Keyboard.hpp>

Entrada leerEntrada()
{
    Entrada e;
    // Con acumulación y no asignación para evitar pisadas, así se anulan
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        e.vertical += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        e.vertical -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        e.horizontal += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        e.horizontal -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        e.zoom += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        e.zoom -= 1.f;
    return e;
}