#include "Gasoline.h"
#include "FileNotFound.h"
#include "Constants.h"

Gasoline::Gasoline(Score& score) : Obstacle(score, -1) 
{
    std::string texturePath = cs::RESOURCE_PATH + cs::OBSTACLE_FILENAMES[3];
    while (!obstacleTexture.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Gasoline Texture"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve();
            if (texturePath == "")
                break;
        }
    }
    obstacle.setScale(sf::Vector2f(cs::OBSTACLE_SIZE, cs::OBSTACLE_SIZE));
    obstacle.setTexture(obstacleTexture);

    std::string sfxPath = cs::RESOURCE_PATH + cs::GAS_CRASH_SOUND;
    while (!crashBuffer.loadFromFile(sfxPath))
    {
        try
        {
            crashSound.setBuffer(crashBuffer);
            throw FileNotFound("Gas crash sound");
        }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            sfxPath = e.resolve();
            if (sfxPath == "")
                break;
        }
    }
    crashSound.setBuffer(crashBuffer);
}

void Gasoline::makeCrashSound()
{
    crashSound.play();
}