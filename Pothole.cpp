#include "Pothole.h"
#include "FileNotFound.h"
#include "Constants.h"

Pothole::Pothole(Score& score) : Obstacle(score, 1) 
{
    std::string texturePath = cs::RESOURCE_PATH + cs::OBSTACLE_FILENAMES[4];
    while (!obstacleTexture.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Pothole Texture"); }
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

    std::string sfxPath = cs::RESOURCE_PATH + cs::SMALL_CRASH_SFX;
    while (!crashBuffer.loadFromFile(sfxPath))
    {
        try
        {
            crashSound.setBuffer(crashBuffer);
            throw FileNotFound("Small crash sound");
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

void Pothole::makeCrashSound() 
{
    if (crashSound.getBuffer() != NULL)
    {
        crashSound.setVolume(50);
        crashSound.play();
    }
}