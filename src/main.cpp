#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>
#include "Monkey.hpp"
#include "MonkeyNPC.hpp"
#include "Poacher.hpp"
#include "AMonkey.hpp"

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
        // Update all NPCs and player // doing nothing for now
        // player.update(map);
        // for (MonkeyNPC& npc : monkeyNPCs) {
        //     npc.update(map);
        // }
        // Build AMonkey pointer list for AI hunt
        std::vector<AMonkey*> allMonkeys;
        allMonkeys.push_back(&player);
        for (MonkeyNPC& npc : monkeyNPCs)
            allMonkeys.push_back(&npc);
        // Update poacher AI with current map and monkeys
        if (poacherClock.getElapsedTime().asSeconds() >= poacherMoveInterval) {
            for (auto& poacher : poachers) {
                poacher.updateIA(2, map, allMonkeys); // switch to current phase
            }
            poacherClock.restart();
        }
        window.clear();
        // Draw map tiles
        for (unsigned int y = 0; y < map.size(); ++y) {
            for (unsigned int x = 0; x < map[y].size(); ++x) {
                sf::RectangleShape tile(sf::Vector2f(tileSize, tileSize));
                tile.setPosition(x * tileSize, y * tileSize);
                switch (map[y][x]) {
                    case '1':   tile.setFillColor(sf::Color(139, 69, 19));
                                break;
                    case '0':   tile.setFillColor(sf::Color::Green);
                                break;
                    case 'E':   tile.setFillColor(sf::Color(255, 165, 0));
                                break;
                    case 'F':   tile.setFillColor(sf::Color::Red);
                                break;
                    default:    tile.setFillColor(sf::Color::Black);
                                break;
                }
                window.draw(tile);
            }
        }
        // Drawing loop for bananas
        for (auto& b : bananas) {
            sf::RectangleShape bananaRect(sf::Vector2f(tileSize, tileSize));
            bananaRect.setPosition(b.first * tileSize, b.second * tileSize);
            bananaRect.setFillColor(sf::Color::Yellow);
            window.draw(bananaRect);
        }
        // Draw exit
        if (exitX != -1 && exitY != -1) {
            sf::RectangleShape exitRect(sf::Vector2f(tileSize, tileSize));
            exitRect.setPosition(exitX * tileSize, exitY * tileSize);
            exitRect.setFillColor(sf::Color::Cyan);
            window.draw(exitRect);
        }
        // Draw player
        sf::RectangleShape playerRect(sf::Vector2f(tileSize, tileSize));
        playerRect.setPosition(player.getX() * tileSize, player.getY() * tileSize);
        playerRect.setFillColor(sf::Color::Blue);
        window.draw(playerRect);
        // Drawing loop for NPCs
        for (MonkeyNPC& npc : monkeyNPCs) {
            sf::RectangleShape npcRect(sf::Vector2f(tileSize, tileSize));
            npcRect.setPosition(npc.getX() * tileSize, npc.getY() * tileSize);
            npcRect.setFillColor(sf::Color::Magenta);
            window.draw(npcRect);
        }
        // Drawing loop for poachers
        for (const Poacher& poacher : poachers) {
            sf::RectangleShape poacherRect(sf::Vector2f(tileSize, tileSize));
            poacherRect.setPosition(poacher.getX() * tileSize, poacher.getY() * tileSize);
            poacherRect.setFillColor(sf::Color::White);
            window.draw(poacherRect);
        }
        // Drawing loop for fire
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