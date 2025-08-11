#ifndef UTILS_HPP
# define UTILS_HPP

#include <SFML/Graphics.hpp>
#include <vector>

// Template functions to draw sprites with texture and position
template<typename Collection, typename Setter>
void drawSprites(sf::RenderWindow& window, const Collection& items, float tileSize, Setter setSprite) {
    for (const auto& item : items) {
        sf::Sprite sprite;
        setSprite(sprite, item);
        // Scale sprite to tile size after texture is set
        if (sprite.getTexture()) {
            sf::IntRect texRect = sprite.getTextureRect();
            sprite.setScale(tileSize / texRect.width, tileSize / texRect.height);
        }
        window.draw(sprite);
    }
}

template<typename Item, typename Setter>
void drawSprite(sf::RenderWindow& window, const Item& item, float tileSize, Setter setSprite) {
    sf::Sprite sprite;
    setSprite(sprite, item);
    if (sprite.getTexture()) {
        sf::IntRect texRect = sprite.getTextureRect();
        sprite.setScale(tileSize / texRect.width, tileSize / texRect.height);
    }
    window.draw(sprite);
}

#endif