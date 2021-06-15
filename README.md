# Midnight Drive: A Real-time Arcade Driving Game

Midnight Drive puts you in the shoes of a Mystery Driver trying to survive a gauntlet of obstacles for as long as possible.

See if you can beat your high score!

![Title Screen](https://i.imgur.com/5roMR8j.png)

## Dependencies/References

* [SFML](https://www.sfml-dev.org/)

## Development

If you're using Ubuntu 18.04+, please install these dependencies first:

    $ sudo apt install libsfml-dev libsfml-audio2.5 cmake build-essential
    
Then build the project:

    $ mkdir build
    $ cd build
    $ cmake ..
    $ make -j4
    $ ./MidnightDrive

You may have to edit the Constants.h file, locate RESOURCE_PATH and change the path to where the resources are located.

![Controls](https://i.imgur.com/RaykCt8.png)
![Instructions](https://i.imgur.com/NZMEKwi.png) 
![Play Screen](https://i.imgur.com/EuMNUoW.png) 
![Game Over](https://i.imgur.com/bpDY2v5.png) 

## License 

This project is licensed under the MIT License 
