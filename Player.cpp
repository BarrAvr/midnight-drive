#include "Constants.h"
#include "Player.h"

Player::Player(HealthScore& healthScore) : healthScore_(healthScore)
{
    //TODO: Add file check
    textureBlue_.loadFromFile(constants::ResourcePath + constants::carTexture);
    textureRed_.loadFromFile(constants::ResourcePath + constants::carHitTexture);

    player_.setScale(sf::Vector2f(constants::playerSize, constants::playerSize));

    player_.setTexture(textureBlue_);

    player_.setPosition(sf::Vector2f(constants::playerStartingPosX, constants::playerStartingPosY));
}

void Player::changeLane(Player::Movement playerDirection)
{
    if (movingToLane_ != Player::Movement::NONE)
    {
        return;
    }

    // Move right
    if (playerDirection == Player::Movement::RIGHT && currentLane < 4)
    {
        currentLane++;
        movingToLane_ = Player::Movement::RIGHT;
    }
        // Move left
    else if (playerDirection == Player::Movement::LEFT && currentLane > 1)
    {
        currentLane--;
        movingToLane_ = Player::Movement::LEFT;
    }
}

void Player::movePlayer()
{
    if (movingToLane_ != Player::Movement::NONE)
    {
        if (movingToLane_ == Player::Movement::LEFT)
        {
            player_.move(sf::Vector2f(-10, 0));
        } else
        {
            player_.move(sf::Vector2f(10, 0));
        }

        int targetPos = constants::targetX_[currentLane - 1];    // lane x-pos
        int playerPos = player_.getPosition().x;

        // stop moving if car is in the correct lane
        if (playerPos >= (targetPos - 5) && playerPos <= (targetPos + 5))
        {
            movingToLane_ = Player::Movement::NONE;
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

void Player::getHit(Damage dmg)
{
    if (dmg == Damage::NOT_HIT)
    {
        if (hitTimer_.getElapsedTime().asMilliseconds() > constants::hitDelay)
        {
            player_.setTexture(textureBlue_);
            gettingHit_ = Damage::NOT_HIT;
        }
    } else
    {
        if (gettingHit_ == Damage::NOT_HIT)
        {
            healthScore_.deductHealth();
            player_.setTexture(textureRed_);
            hitTimer_.restart();
            gettingHit_ = Damage::HIT;
        }
    }
}
