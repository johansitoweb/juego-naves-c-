#include <SFML/Graphics.hpp>  
#include <vector>  

class Projectile {  
public:  
    sf::CircleShape shape;  
    float speed;  

    Projectile(float x, float y) : speed(10.f) {  
        shape.setRadius(5.f);  
        shape.setFillColor(sf::Color::Red);  
        shape.setPosition(x, y);  
    }  

    void update() {  
        shape.move(0, -speed); // Mover el proyectil hacia arriba  
    }  
};  

class Player {  
public:  
    sf::RectangleShape shape;  
    float speed;  

    Player() : speed(5.f) {  
        shape.setSize(sf::Vector2f(50, 50));  
        shape.setFillColor(sf::Color::Blue);  
        shape.setPosition(400, 500); // Posición inicial  
    }  

    void moveLeft() {  
        if (shape.getPosition().x > 0)  
            shape.move(-speed, 0);  
    }  

    void moveRight() {  
        if (shape.getPosition().x < 750) // Ancho de la ventana - ancho de la nave  
            shape.move(speed, 0);  
    }  
};  

int main() {  
    // Crear la ventana  
    sf::RenderWindow window(sf::VideoMode(800, 600), "Juego de Naves");  

    Player player;  
    std::vector<Projectile> projectiles;  

    while (window.isOpen()) {  
        sf::Event event;  
        while (window.pollEvent(event)) {  
            if (event.type == sf::Event::Closed)  
                window.close();  
        }  

        // Movimiento del jugador  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {  
            player.moveLeft();  
        }  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {  
            player.moveRight();  
        }  
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {  
            projectiles.emplace_back(player.shape.getPosition().x + 22.5f, player.shape.getPosition().y); // Lanzar un proyectil desde el centro de la nave  
        }  

        // Actualizar proyectiles  
        for (size_t i = 0; i < projectiles.size(); ++i) {  
            projectiles[i].update();  
            if (projectiles[i].shape.getPosition().y < 0) {  
                projectiles.erase(projectiles.begin() + i);  
                --i; // Ajustar el índice después de eliminar un proyectil  
            }  
        }  

        // Limpiar la ventana  
        window.clear(sf::Color::Black);  

        // Dibujar el jugador y los proyectiles  
        window.draw(player.shape);  
        for (const auto& projectile : projectiles) {  
            window.draw(projectile.shape);  
        }  

        // Mostrar la ventana  
        window.display();  
    }  

    return 0;  
}