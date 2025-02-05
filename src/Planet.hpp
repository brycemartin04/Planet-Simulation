#include <SFML/Graphics.hpp>

class Planet {
    private:
        sf::CircleShape object;
        float mass;
        sf::Vector2f velocity;
        
public:
    Planet(float x, float y, float radius, float mass, sf::Vector2f velocity, sf::Color color);

    void applyGravity(Planet& other);

    void updatePosition();

    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    float getMass();
    sf::CircleShape& getObject();

    void setVelocity(sf::Vector2f newVelocity);
};