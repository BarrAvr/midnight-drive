#include "Trashcan.h"
#include "FileNotFound.h"
#include "Constants.h"

Trashcan::Trashcan(Score& score) : Obstacle(score, 2) 
{
    std::string texturePath = cs::RESOURCE_PATH + cs::OBSTACLE_FILENAMES[0];
    while (!obstacleTexture.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Trashcan Texture"); }
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

    std::string sfxPath = cs::RESOURCE_PATH + cs::BIG_CRASH_SFX;
    while (!crashBuffer.loadFromFile(sfxPath))
    {
        try
        {
            crashSound.setBuffer(crashBuffer);
            throw FileNotFound("Big crash sound");
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

void Trashcan::makeCrashSound() 
{
    if (crashSound.getBuffer() != NULL)
    {
        crashSound.setVolume(50);
        crashSound.setPitch(crashSound.getPitch());
        crashSound.play();
    }
}