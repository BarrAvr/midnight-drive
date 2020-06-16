#include "Cone.h"
#include "FileNotFound.h"
#include "Constants.h"

Cone::Cone(Score& score) : Obstacle(score, 1) 
{
    std::string texturePath = cs::RESOURCE_PATH + cs::OBSTACLE_FILENAMES[1];
    while (!obstacleTexture.loadFromFile(texturePath))
    {
        try
        {
            throw FileNotFound("Cone Texture");
        }
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

void Cone::makeCrashSound() 
{
    if (crashSound.getBuffer() != NULL)
    {
        crashSound.setVolume(50);
        crashSound.play();
    }
}