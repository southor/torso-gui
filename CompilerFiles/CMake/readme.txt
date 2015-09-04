In order to compile "Test" you must make sure that CMake can find SDL2.
If SDL2 includes a CMake module then it might work to "Test" without doing anything.
Last time I checked there was no such module, and then you haveto download a "FindSDL2.cmake" file from
the internet, check this link:
https://github.com/Twinklebear/TwinklebearDev-Lessons/blob/master/cmake/FindSDL2.cmake
Next, place this file in Test/cmake/Modules.
Now it should be possible to compile "Test".