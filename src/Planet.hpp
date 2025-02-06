#include <SFML/Graphics.hpp>
#include <vector>

class Planet {
    private:
        std::vector<sf::CircleShape> trail;
        sf::CircleShape object;
        float mass;
        sf::Vector2f velocity;
        
public:
    Planet(float x, float y, float radius, float mass, sf::Vector2f velocity, sf::Color color);

    void applyGravity(Planet& other);

    void updatePosition();

    sf::Vector2f getPosition();
    sf::Vector2f getVelocity();
    std::vector<sf::CircleShape> getTrail();
    float getMass();
    sf::CircleShape& getObject();

    void setVelocity(sf::Vector2f newVelocity);
};