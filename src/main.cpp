#include <SFML/Graphics.hpp>
#include <optional>
#include "Planet.hpp"
#include <vector>

const float TIME_STEP = 1.0f; // Time step for prediction (in seconds)
const int NUM_POINTS = 200;   // Number of points to predict in the orbit

int main() {
    const int width = 720;
    const int height = 720;

    std::vector<Planet> planets;

    Planet sun(width / 2.0f, height / 2.0f, 100.0f, 5000.0f, { 0.0f, 0.0f }, sf::Color::Yellow);
    Planet earth(width / 2.0f + 200.f, height / 2.0f + 0.f, 10.0f, 15.0f, { 0.0f, 33.0f }, sf::Color::Blue);
    Planet moon(width / 2.0f + 215.f, height / 2.0f + 0.f, 1.0f, 5.0f, { 0.0f, 41.0f }, sf::Color::White);

    planets.push_back(sun);
    planets.push_back(earth);
    planets.push_back(moon);


    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({width,height}),"Planet Simulation");
    window -> setFramerateLimit(60);


    
    while (window -> isOpen()){
        while (const std::optional event = window -> pollEvent()){
            if (event->is<sf::Event::Closed>()){
                window->close();
            }
        }


        window -> clear();

        for (size_t i = 0; i < planets.size(); ++i) {
            for (size_t j = i + 1; j < planets.size(); ++j) {
                planets[i].applyGravity(planets[j]);
                planets[j].applyGravity(planets[i]);
            }
        }

        for (auto& planet : planets){
            window -> draw(planet.getObject());
            planet.updatePosition();
        }

        window -> display();
    }
    
    
    return 0;
}
