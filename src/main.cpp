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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
        {
            if (posicion.y > 40)
            {
                jugador.move({0, -velocidad});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
        {
            if (posicion.y < 520)
            {
                jugador.move({0, velocidad});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
        {
            if (posicion.x > 40)
            {
                jugador.move({-velocidad, 0});
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
        {
            if (posicion.x < 720)
            {
                jugador.move({velocidad, 0});
            }
        }

        window.clear();

        for (int i = 0; i < 20; i++)
        {
            pared.setPosition({i * 40.f, 0.f});
            window.draw(pared);

            pared.setPosition({i * 40.f, 560.f});
            window.draw(pared);
        }

        for (int i = 0; i < 15; i++)
        {
            pared.setPosition({0.f, i * 40.f});
            window.draw(pared);

            pared.setPosition({760.f, i * 40.f});
            window.draw(pared);
        }

        window.draw(jugador);
        window.display();
    }

    return 0;
}