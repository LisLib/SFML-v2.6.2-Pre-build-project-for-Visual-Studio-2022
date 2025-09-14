#include <SFML/Graphics.hpp>
#include <thread>
#include <optional>

void renderingThread(sf::RenderWindow* windowPtr)
{
    sf::RenderWindow& window = *windowPtr;
    window.setActive(true);

    sf::CircleShape shape;
    shape.setFillColor(sf::Color::Red);
    shape.setRadius(100.f);

    while (window.isOpen())
    {
        window.draw(shape);
        window.display();
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML Window");

    std::thread thread(&renderingThread, &window);

    window.setActive(false);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                thread.detach();
                window.close();
                break;
            case sf::Event::KeyPressed:
                switch (event.key.code)
                {
                case sf::Keyboard::Escape:
                    thread.detach();
                    window.close();
                    break;
                }
                break;
            }
        }
    }

    if(thread.joinable())
        thread.join();
}