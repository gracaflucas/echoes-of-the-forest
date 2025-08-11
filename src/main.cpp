#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Monkey.hpp"
#include "MonkeyNPC.hpp"
#include "Poacher.hpp"
#include "AMonkey.hpp"
#include "utils.hpp"

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
        if (!line.empty() && line.back() == '\r') {
            line.pop_back();
        }
        mapLines.push_back(line);
    }
    return mapLines;
}

int main() {
    const int tileSize = 32;
    bool playerWasOnExit = false;
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    std::vector<std::string> map = loadMap("maps/mapsample.txt");
    if (map.empty()) {
        std::cerr << "Failed to load map." << std::endl;
        return 1;
    }
    sf::RenderWindow window(sf::VideoMode(tileSize * map[0].size(), tileSize * map.size()), "Echoes of the Forest");

    Monkey player;
    std::vector<MonkeyNPC> monkeyNPCs;
    std::vector<Poacher> poachers;
    std::vector<std::pair<int,int>> bananas;
    std::vector<std::pair<int,int>> fires;
    int exitX = -1, exitY = -1;

    // Struct to hold tile info (position + char)
    struct TileInfo {
        unsigned int x, y;
        char tileChar;
    };
    // Prepare tile info vector for your map
    std::vector<TileInfo> tileInfos;
    for (unsigned int y = 0; y < map.size(); ++y) {
        for (unsigned int x = 0; x < map[y].size(); ++x) {
            tileInfos.push_back(TileInfo{x, y, map[y][x]});
        }
    }

    // Scan map to initialize player, NPCs, bananas, exit, poacher, and fires
    for (unsigned int y = 0; y < map.size(); ++y) {
        for (unsigned int x = 0; x < map[y].size(); ++x) {
            char c = map[y][x];
            switch (c) {
                case 'P':
                    player.setX(x);
                    player.setY(y);
                    map[y][x] = '0';
                    break;
                case 'N':
                    monkeyNPCs.emplace_back(x, y);
                    map[y][x] = '0';
                    break;
                case 'B':
                    bananas.emplace_back(x, y);
                    map[y][x] = '0';
                    break;
                case 'L':
                    exitX = x;
                    exitY = y;
                    map[y][x] = '0';
                    break;
                case 'E':
                    poachers.emplace_back(x, y);
                    map[y][x] = '0';
                    break;
                case 'F':
                    fires.emplace_back(x, y);
                    map[y][x] = '0';
                    break;
            }
        }
    }
    sf::Clock poacherClock;
    const float poacherMoveInterval = 1.5f;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                player.handleInput(event.key.code, map);
            }
        }
        // Build AMonkey pointer list for AI hunt
        std::vector<AMonkey*> allMonkeys;
        allMonkeys.push_back(&player);
        for (MonkeyNPC& npc : monkeyNPCs)
            allMonkeys.push_back(&npc);
        // Update poacher AI with current map and monkeys
        if (poacherClock.getElapsedTime().asSeconds() >= poacherMoveInterval) {
            for (auto& poacher : poachers) {
                poacher.updateIA(2, map, allMonkeys); // switch to current phase
                for (MonkeyNPC& npc : monkeyNPCs) {
                    npc.wanderRandomly(map);
                }
            }
            poacherClock.restart();
        }
        window.clear();
        sf::Texture wallTexture, floorTexture, exitTexture, bananaTexture, monkeyTexture;

        auto loadTexture = [](sf::Texture& tex, const std::string& file) {
            if (!tex.loadFromFile(file)) {
                std::cerr << "Error loading texture: " << file << "\n";
            }
        };

        loadTexture(wallTexture,   "textures/bush.png");
        loadTexture(floorTexture,  "textures/grass.png");
        loadTexture(exitTexture,   "textures/dekutree.png");
        loadTexture(bananaTexture, "textures/banana.png");
        loadTexture(monkeyTexture, "textures/still.png");
        // Draw the map base
        drawSprites(window, tileInfos, tileSize, [&](sf::Sprite& sprite, const TileInfo& tile) {
            switch (tile.tileChar) {
                case '1': sprite.setTexture(wallTexture); break;
                case '0': sprite.setTexture(floorTexture); break;
                case 'L': sprite.setTexture(exitTexture); break;
                case 'F': sprite.setTexture(floorTexture); sprite.setColor(sf::Color::Red); break; // fire fallback
                case 'E': sprite.setTexture(floorTexture); break; // poacher tile base
                case 'B': sprite.setTexture(floorTexture); break; // banana base tile
                case 'P': sprite.setTexture(floorTexture); break; // player base tile
                case 'N': sprite.setTexture(floorTexture); break; // monkeyNPC base tile
                default:  sprite.setTexture(floorTexture); break;
            }
            sprite.setPosition(tile.x * tileSize, tile.y * tileSize);
        });

        // Bananas
        drawSprites(window, bananas, tileSize, [&](sf::Sprite& sprite, const std::pair<int,int>& b) {
            sprite.setTexture(bananaTexture);
            sprite.setPosition(b.first * tileSize, b.second * tileSize);
        });

        // Player
        drawSprite(window, player, tileSize, [&](sf::Sprite& sprite, const auto& p) {
            sprite.setTexture(monkeyTexture);
            sprite.setPosition(p.getX() * tileSize, p.getY() * tileSize);
        });

        // Monkey NPCs
        drawSprites(window, monkeyNPCs, tileSize, [&](sf::Sprite& sprite, const auto& npc) {
            sprite.setTexture(monkeyTexture);
            sprite.setPosition(npc.getX() * tileSize, npc.getY() * tileSize);
        });

        // Poachers (colored rectangle fallback)
        for (const auto& poacher : poachers) {
            sf::RectangleShape poacherRect(sf::Vector2f(tileSize, tileSize));
            poacherRect.setPosition(poacher.getX() * tileSize, poacher.getY() * tileSize);
            poacherRect.setFillColor(sf::Color::White);
            window.draw(poacherRect);
        }

        // Fires (colored rectangle fallback)
        for (const auto& fire : fires) {
            sf::RectangleShape fireRect(sf::Vector2f(tileSize, tileSize));
            fireRect.setPosition(fire.first * tileSize, fire.second * tileSize);
            fireRect.setFillColor(sf::Color::Red);
            window.draw(fireRect);
        }
        // Banana colision loop
        for (auto it = bananas.begin(); it != bananas.end(); ) {
            if (player.getX() == it->first && player.getY() == it->second) {
                std::cout << "Player collected a banana!" << std::endl;
                it = bananas.erase(it);
            } else {
                ++it;
            }
        }
        // Exit colision
        bool playerOnExit = (player.getX() == exitX && player.getY() == exitY);
        if (playerOnExit && !playerWasOnExit) {
            if (bananas.empty()) {
                std::cout << "Player reached the exit! You win!" << std::endl;
                window.close();
            } else {
                std::cout << "You need to collect all bananas before exiting!" << std::endl;
            }
        }
        playerWasOnExit = playerOnExit;
        // poacher colision with monkey
        for (const Poacher& poacher : poachers) {
            if (player.getX() == poacher.getX() && player.getY() == poacher.getY()) {
                std::cout << "Player has been caught by a poacher!" << std::endl;
                window.close();
                break;
            }
        }
        window.display();
    }
    return 0;
}