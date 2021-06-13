#include <cstring> 
#include <iostream>
#include <exception>
#include <fstream>
#include "FileNotFound.h"

const char* FileNotFound::what() const noexcept
{
    static char temp[200];
    strcpy(temp, "Could not find ");
    strcat(temp, std::runtime_error::what());
    return temp;
}

std::string FileNotFound::resolve()
{
    std::cout << "... What would you like to do?" << std::endl;

    bool needValidInput = true;
    while (needValidInput)
    {
        std::cout << "Ignore the problem (I), Provide a path (P), Terminate Program (Q):  ";

        std::string choice;
        getline(std::cin, choice);
        switch (toupper(choice[0]))
        {
        case 'I':      // Ignore the problem, potentially leading to further problems
            std::cout << std::endl;
            return "";
        case 'P':      // Get a new path from user
            return resolvePath();
        case 'Q':       // Quit the game
            exit();
        default:        // Invalid choice
            std::cout << "Please choose a valid option:" << std::endl;
        }
    }

    return "";
}


std::string FileNotFound::resolvePath()
{
    std::string path;
    bool needValidPath = true;
    while (needValidPath)
    {
        std::cout << "Please enter a full valid path for the file" << std::endl;
        std::cout << "Path: ";
        std::getline(std::cin, path);
        std::ifstream test(path.c_str());
        if (test.good())
            break;
    }
    return path;
}

void FileNotFound::exit()
{
    std::cout << "Terminating program..." << std::endl;
    std::exit(-1);
}


/*
How to use:


    while (!texture_.loadFromFile(texturePath))
    {
        try { throw FileNotFound("Barricade Texture\n"); }
        catch (FileNotFound e)
        {
            std::cout << e.what();
            texturePath = e.resolve(cs::ResourcePath + cs::background_);
            if (texturePath == "")
                break;
        }
    }


*/
