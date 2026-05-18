#include <optional>
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Dungeon Game");
    sf::RectangleShape jugador({40, 40});
    jugador.setFillColor(sf::Color::Green);
    jugador.setPosition({100, 100});

    sf::RectangleShape pared({40, 40});
    pared.setFillColor(sf::Color::Blue);

    static const int mapa[15][20] =
    {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
    };

    while (window.isOpen())
    {
        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        float velocidad = 0.2f;
        sf::Vector2f posicion = jugador.getPosition();

        auto puedeMoverse = [&](const sf::Vector2f &destino)
        {
            int fila = static_cast<int>(destino.y) / 40;
            int columna = static_cast<int>(destino.x) / 40;
            return fila >= 0 && fila < 15 && columna >= 0 && columna < 20 && mapa[fila][columna] == 0;
        };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            sf::Vector2f siguientePos = posicion + sf::Vector2f{0, -velocidad};
            if (posicion.y > 40 && puedeMoverse(siguientePos))
            {
                jugador.move({0, -velocidad});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            sf::Vector2f siguientePos = posicion + sf::Vector2f{0, velocidad};
            if (posicion.y < 520 && puedeMoverse(siguientePos))
            {
                jugador.move({0, velocidad});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            sf::Vector2f siguientePos = posicion + sf::Vector2f{-velocidad, 0};
            if (posicion.x > 40 && puedeMoverse(siguientePos))
            {
                jugador.move({-velocidad, 0});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            sf::Vector2f siguientePos = posicion + sf::Vector2f{velocidad, 0};
            if (posicion.x < 720 && puedeMoverse(siguientePos))
            {
                jugador.move({velocidad, 0});
            }
        }

        window.clear();

        for (int fila = 0; fila < 15; fila++)
        {
            for (int columna = 0; columna < 20; columna++)
            {
                if (mapa[fila][columna] == 1)
                {
                    pared.setPosition({columna * 40.f, fila * 40.f});
                    window.draw(pared);
                }
            }
        }

        window.draw(jugador);
        window.display();
    }

    return 0;
}