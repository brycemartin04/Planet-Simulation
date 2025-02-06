#include <SFML/Graphics.hpp>
#include <optional>
#include "Planet.hpp"
#include <vector>

const float SCALE_DISTANCE = 1e-9f; // Reduced scale for distance
const float SCALE_VELOCITY = 1e-4f;    // Scale for velocity (e.g., in m/s to pixels/frame)
const float SCALE_MASS = 1e-28f;            // Scale for mass (e.g., in kg to scaled units)

int main() {
    const int width = 720;
    const int height = 720;

    std::vector<Planet> planets;

    Planet sun(width / 2.0f, height / 2.0f, 50.0f, 1.989e30f * SCALE_MASS, { 0.0f, 0.0f }, sf::Color::Yellow);
    Planet earth(width / 2.0f + (1.496e11f * SCALE_DISTANCE), height / 2.0f, 10.0f, 5.972e24f * SCALE_MASS, { 0.0f, 29.783f * SCALE_VELOCITY }, sf::Color::Blue);
    Planet moon(width / 2.0f + (3.844e8f * SCALE_DISTANCE), height / 2.0f, 1.0f, 7.34767309e22f * SCALE_MASS, { 0.0f, 1.022f * SCALE_VELOCITY }, sf::Color::White);

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
            for (auto& trailDot : planet.getTrail()) {
                window->draw(trailDot);  // Draw the trail
            }
            window -> draw(planet.getObject());
            planet.updatePosition();
        }

        window -> display();
    }
    
    
    return 0;
}
