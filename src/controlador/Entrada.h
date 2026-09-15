#pragma once

struct Entrada
{
    float vertical = 0.f;
    float horizontal = 0.f;
    float zoom = 0.f;

    Entrada()
    {
        vertical = 0.f;
        horizontal = 0.f;
        zoom = 0.f;
    }
    Entrada(float vertical, float horizontal, float zoom)
        : vertical(vertical), horizontal(horizontal), zoom(zoom) {}

    float getVertical() const { return vertical; }
    float getHorizontal() const { return horizontal; }
    float getZoom() const { return zoom; }
};