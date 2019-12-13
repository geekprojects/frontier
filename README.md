Frontier [![Build Status](https://travis-ci.org/geekprojects/frontier.svg?branch=develop)](https://travis-ci.org/geekprojects/frontier) [![Quality Gate](https://sonarcloud.io/api/project_badges/measure?project=geekprojects_frontier&metric=alert_status)](https://sonarcloud.io/dashboard?id=geekprojects_frontier) [![Codacy Badge](https://api.codacy.com/project/badge/Grade/fd89c5a557c24f3eb9a17565cb6e9dfb)](https://www.codacy.com/gh/geekprojects/frontier?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=geekprojects/frontier&amp;utm_campaign=Badge_Grade)

--------


**Frontier** is a toolkit for creating simple OS-independent user interfaces.


#### Features
* Very simple to use
* Small
* Styling and customisation using CSS
* SDL, native MacOS (Cocoa) and OpenGL engines
* sigc++ event handlers
* High DPI support
* Embeddable in to other applications (Games etc)


##### Requirements
* [libgeek](https://github.com/geekprojects/libgeek)
* Antlr4 C++ runtime (For CSS parsing)
* freetype 2
* libsigc++ 2.0
* SDL (For the SDL engine)
* OpenGL (For OpenGL embedding)

##### Ubuntu
* libxml2-dev libpng-dev libjpeg-dev libjpeg-turbo8 libsdl2-dev libfreetype6-dev libsigc++-2.0-dev uuid-dev
* Optional: freeglut3-dev

##### MacOS
* homebrew: freetype libsigc++@2 libtool antlr@4 antlr4-cpp-runtime


Documentation
-------------

Soon! If anybody expresses any interest in Frontier, I'll get on to it more quickly!


Installation
------------

```
mkdir build
cd build
cmake ..
make
sudo make install
```


License
-------

These libraries are available under the LGPL v3 license. You can use them
in any open or closed source projects, but if you make changes to any of
my code, you have to make those changes available.

libgeek is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

libgeek is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.


