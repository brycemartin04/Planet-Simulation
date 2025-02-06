#include "Planet.hpp"
#include <SFML/Graphics.hpp>

const float G = 1e-5f;  // Gravitational constant (scaled for simulation)
const float TIME_STEP = 1000.f;  // Simulation time step

Planet::Planet(float x, float y, float radius, float initialMass, sf::Vector2f initialVelocity, sf::Color color){
    velocity = initialVelocity;
    mass = initialMass;
    object.setRadius(radius);
    object.setOrigin(object.getGeometricCenter());
    object.setPosition({x,y}); 
    object.setFillColor(color);  //Change to use sprite later  
}


void Planet::applyGravity(Planet& other) {
    // Get the difference vector between planets
    sf::Vector2f diff = other.getPosition() - object.getPosition();
    float distance = std::sqrt(diff.x * diff.x + diff.y * diff.y);
    
    //if (distance < 10.f) return;

    float force = G * (mass * other.mass) / (distance * distance);
    
    sf::Vector2f direction = diff / distance;

    sf::Vector2f acceleration = direction * (force / mass); 

    velocity += acceleration * TIME_STEP; 
}

void Planet::updatePosition(){
    sf::CircleShape t(1); // Trail dot
    t.setPosition(object.getPosition());
    t.setPointCount(4);
    t.setFillColor(sf::Color(255, 255, 255, 100)); // Semi-transparent white
    trail.push_back(t);

    // Remove old trail points to keep the trail length manageable
    if (trail.size() > 200) {
        trail.erase(trail.begin());
    }
    object.move(velocity * TIME_STEP);
}

sf::Vector2f Planet::getPosition(){ 
    return object.getPosition();
    }
sf::Vector2f Planet::getVelocity(){ 
    return velocity; 
    }
float Planet::getMass(){
     return mass; 
     }

sf::CircleShape& Planet::getObject(){
    return object;
}

std::vector<sf::CircleShape> Planet::getTrail(){
     return trail; 
     }