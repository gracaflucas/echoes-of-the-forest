#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include "Monkey.hpp"
#include "MonkeyNPC.hpp"
#include "Poacher.hpp"

// Function to load map lines from file
std::vector<std::string> loadMap(const std::string& filename) {
    std::vector<std::string> mapLines;
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Failed to open map file: " << filename << std::endl;
        return mapLines;
    }
    std::string line;
    while (std::getline(file, line)) {
        mapLines.push_back(line);
    }
    return mapLines;
}

int main() {
    const int tileSize = 32;

    std::vector<std::string> map = loadMap("maps/mapsample.txt");
    if (map.empty()) {
        std::cerr << "Failed to load map." << std::endl;
        return 1;
    }

    // Create window
    sf::RenderWindow window(sf::VideoMode(tileSize * map[0].size(), tileSize * map.size()), "Echoes of the Forest");

    // Create player monkey
    Monkey player;

    // Initialize player position by scanning map for 'P'
    for (unsigned int y = 0; y < map.size(); ++y) {
        for (unsigned int x = 0; x < map[y].size(); ++x) {
            if (map[y][x] == 'P') {
                player.setX(x);
                player.setY(y);
                // Replace 'P' with floor '0' so map rendering is consistent
                map[y][x] = '0';
            }
        }
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Close window event
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            // Key pressed event
            if (event.type == sf::Event::KeyPressed) {
                player.handleInput(event.key.code, map);
            }
        }
        player.update();

        // Draw everything
        window.clear();
        for (unsigned int y = 0; y < map.size(); ++y) {
            for (unsigned int x = 0; x < map[y].size(); ++x) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(x * tileSize, y * tileSize);

                switch (map[y][x]) {
                    case '1': tile.setFillColor(sf::Color(139, 69, 19)); break; // Brown - Wall
                    case '0': tile.setFillColor(sf::Color::Green); break;      // Green - Floor
                    case 'E': tile.setFillColor(sf::Color::Yellow); break;     // Yellow - Enemy
                    case 'F': tile.setFillColor(sf::Color::Red); break;        // Red - Fire
                    default: tile.setFillColor(sf::Color::Black); break;       // Unknown
                }
                window.draw(tile);
            }
        }

        // Draw player as Blue square
        sf::RectangleShape playerRect(sf::Vector2f(tileSize, tileSize));
        playerRect.setPosition(player.getX() * tileSize, player.getY() * tileSize);
        playerRect.setFillColor(sf::Color::Blue);
        window.draw(playerRect);

        window.display();
    }

    return 0;
}
