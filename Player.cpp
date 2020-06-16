#include "Player.h"
#include "Constants.h"
#include "FileNotFound.h"

namespace cs = constants;

Player::Player(HealthScore& healthScore) : healthScore(healthScore)
{
    std::string texturePath = cs::RESOURCE_PATH + cs::CAR_TEXTURE;
    while (!textureBlue.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Car Texture"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }

    texturePath = cs::RESOURCE_PATH + cs::CAR_HIT_TEXTURE;
    while (!textureRed.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Car Hit Texture"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }

    player_.setScale(sf::Vector2f(cs::PLAYER_SIZE, cs::PLAYER_SIZE));
    player_.setTexture(textureBlue);
    player_.setPosition(sf::Vector2f(cs::PLAYER_STARTING_POS_X, cs::PLAYER_STARTING_POS_Y));
}

void Player::changeLane(Player::Movement playerDirection)
{
    if (movingToLane != Player::Movement::NONE)
        return;

    if (playerDirection == Player::Movement::RIGHT && currentLane < 4)      // Move right
    {
        currentLane++;
        movingToLane = Player::Movement::RIGHT;
    }

    else if (playerDirection == Player::Movement::LEFT && currentLane > 1)  // Move left
    {
        currentLane--;
        movingToLane = Player::Movement::LEFT;
    }
}

void Player::movePlayer(float speedMultiplier)
{
    if (movingToLane != Player::Movement::NONE)
    {
        if (movingToLane == Player::Movement::LEFT)
        {
            player_.move(sf::Vector2f(-cs::BASE_PLAYER_MOVE_SPEED, 0));
        }
        else
        {
            player_.move(sf::Vector2f(cs::BASE_PLAYER_MOVE_SPEED, 0));
        }

        int targetPos = cs::TARGET_X[currentLane - 1];    // lane x-pos
        int playerPos = player_.getPosition().x;

        // stop moving if car is in the correct lane
        if (playerPos >= (targetPos - 5) && playerPos <= (targetPos + 5))
        {
            movingToLane = Player::Movement::NONE;
        }
    }
}

void Player::draw(sf::RenderWindow& window)
{
    window.draw(player_);
}

sf::Sprite Player::getPlayer()
{
    return player_;
}

void Player::getHit(Damage dmg, int damage_level)
{
    if (dmg == Damage::NOT_HIT)
    {
        if (hitTimer.getElapsedTime().asMilliseconds() > cs::HIT_DELAY)
        {
            player_.setTexture(textureBlue);
            gettingHit = Damage::NOT_HIT;
        }
    }
    else
    {
        if (gettingHit == Damage::NOT_HIT)
        {
            healthScore.deductHealth(damage_level);
            player_.setTexture(textureRed);
            hitTimer.restart();
            gettingHit = Damage::HIT;
        }
    }
}
