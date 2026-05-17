#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Dungeon Game");
sf::RectangleShape jugador({40, 40});
jugador.setFillColor(sf::Color::Green);
jugador.setPosition({100, 100});
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
{
    jugador.move({0, -0.2f});
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
{
    jugador.move({0, 0.2f});
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
{
    jugador.move({-0.2f, 0});
}

if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
{
    jugador.move({0.2f, 0});
}
        window.clear();

        window.draw(jugador);

        window.display();
    }

    return 0;
}