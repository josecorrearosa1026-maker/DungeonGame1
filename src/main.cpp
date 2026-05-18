#include <optional>
#include <SFML/Graphics.hpp>

const int FILAS = 15;
const int COLUMNAS = 20;
const int TAM = 40;
const int NUM_HABITACIONES = 6;

bool hayPared(const int mapas[NUM_HABITACIONES][FILAS][COLUMNAS], int habitacion, float x, float y)
{
    int columna = static_cast<int>(x) / TAM;
    int fila = static_cast<int>(y) / TAM;

    if (fila < 0 || fila >= FILAS || columna < 0 || columna >= COLUMNAS)
    {
        return true;
    }

    return mapas[habitacion][fila][columna] == 1;
}

bool puedeMoverse(const int mapas[NUM_HABITACIONES][FILAS][COLUMNAS], int habitacion, sf::Vector2f pos)
{
    return !hayPared(mapas, habitacion, pos.x, pos.y) &&
           !hayPared(mapas, habitacion, pos.x + 39, pos.y) &&
           !hayPared(mapas, habitacion, pos.x, pos.y + 39) &&
           !hayPared(mapas, habitacion, pos.x + 39, pos.y + 39);
}

void revisarCambioHabitacion(sf::RectangleShape& jugador, int& habitacionActual)
{
    sf::Vector2f pos = jugador.getPosition();
    int columnaCentro = static_cast<int>(pos.x + 20) / TAM;
    int filaCentro = static_cast<int>(pos.y + 20) / TAM;

    if (columnaCentro >= 19 && habitacionActual < NUM_HABITACIONES - 1)
    {
        habitacionActual++;
        jugador.setPosition(sf::Vector2f(40.f, filaCentro * 40.f));
    }

    if (columnaCentro <= 0 && habitacionActual > 0)
    {
        habitacionActual--;
        jugador.setPosition(sf::Vector2f(720.f, filaCentro * 40.f));
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Dungeon Game");

    sf::RectangleShape jugador(sf::Vector2f(40.f, 40.f));
    jugador.setFillColor(sf::Color::Green);
    jugador.setPosition(sf::Vector2f(100.f, 100.f));

    sf::RectangleShape pared(sf::Vector2f(40.f, 40.f));
    pared.setFillColor(sf::Color::Blue);

    sf::RectangleShape salida(sf::Vector2f(40.f, 40.f));
    salida.setFillColor(sf::Color::Yellow);

    static const int mapas[NUM_HABITACIONES][FILAS][COLUMNAS] =
    {
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,0,1,0,0,0,0,0,1,1,1,1,0,0,0,0,1,0,0,1},
            {1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,1},
            {1,0,1,1,1,1,0,0,0,0,0,0,0,1,1,1,1,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,2},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        },
        {
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,1,1,1,1,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0,0,0,1},
            {1,0,0,0,1,1,1,0,0,0,0,0,1,1,1,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
            {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
        }
    };

    int habitacionActual = 0;
    float velocidad = 0.2f;

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> evento = window.pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        sf::Vector2f posicion = jugador.getPosition();
        sf::Vector2f nuevaPosicion = posicion;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            nuevaPosicion.y -= velocidad;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            nuevaPosicion.y += velocidad;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            nuevaPosicion.x -= velocidad;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            nuevaPosicion.x += velocidad;
        }

        if (puedeMoverse(mapas, habitacionActual, nuevaPosicion))
        {
            jugador.setPosition(nuevaPosicion);
        }

        revisarCambioHabitacion(jugador, habitacionActual);

        window.clear();

        for (int fila = 0; fila < FILAS; fila++)
        {
            for (int columna = 0; columna < COLUMNAS; columna++)
            {
                if (mapas[habitacionActual][fila][columna] == 1)
                {
                    pared.setPosition(sf::Vector2f(columna * 40.f, fila * 40.f));
                    window.draw(pared);
                }
                else if (mapas[habitacionActual][fila][columna] == 2)
                {
                    salida.setPosition(sf::Vector2f(columna * 40.f, fila * 40.f));
                    window.draw(salida);
                }
            }
        }

        window.draw(jugador);
        window.display();
    }

    return 0;
}