# Find Your Way (RG061) &#955;

## About:
**Author:** Stefan Pantic.  
**Contact:** stefanpantic13@gmail.com   
<br>
**TL;DR:** Independent project in Computer Graphics college course using OpenGL/GLUT and some GLM convenience   
classes. Done in C++.  
<br>
**Description:** *Find Your Way* is a platformer styled first person game. The goal is to find a way to the end of each level using several abilities at your disposal that include slowing down time, blinking and super jump. At one point I'm hoping to add mobs that will try to hinder your progess, as well as abilities to fend them off. The project is being written in C++ using older OpenGL/GLUT and some GLM classes for convenience. If time allows it, a port to modern OpenGL is not out of the question. This is my first larger C++ project. Any criticism and/or suggestions are more than welcome. :)  

## Installation:
Just run <code>make</code> from the project directory.
## Requirements:
 * **OpenGL/GLUT and GLM:**  

Arch Linux:
<pre>sudo pacman -S freeglut glm</pre>
Ubuntu:
<pre>sudo apt-get install freeglut3-dev binutils-gold glm</pre>

* **Tested C++ compiler (others may work as well)**:   
    * g++ 7.2.0+,
    * clang++ 5.0.0+.

## Preview:
**Date:** 07-01-2018  

![preview](https://github.com/MATF-RG17/RG061-find-your-way/blob/master/sample/07-01-2018.png) 

## Progress reports and change log:
**TODO:** 
* Update wiki and move progress report there,


### Version 0.1:
**Date:** 30-12-2017  
**Progress made:**
 * Implemented a wrapper around GLUT's window manipulation functions and callback registration (see eRG::Window),
 * Implemented the eRG::View class that is in charge of handling camera related OpenGL functionality,
 * Partialy implemeted a mainframe styled class (see eRG::Hub) that will control my classes an handle OpenGL indirectly through them (the end goal is to remove any direct interaction between eRG::Hub and OpenGL/GLUT),
 * Implemeted several enum classes that emulate OpenGL's GLenum functionality with an aditional layer of type safety and option checking,
 * Wrote a Makefile for convenience.

### Version 0.2:
**Date:** 04-01-2018   
**Progress made:** 
 * Added two forward declarations instead of #includes for better compile times,
 * Implemented camera motion via mouse,
 * Added debugging helper functions,
 * Minor refactoring and reformating,
 * Improved Makefile.
 
 ### Version 0.3:
 **Date:** 05-01-2018  
 **Progress made:**
 * Implemented JUMP ability,
 * Implemented BLINK ability,
 * Improved viewpoint control via mouse (cursor can't accidentally leave the screen),
 * Added another temporary helper function in debug.hpp,
 * Minor refactoring.
 
 ### Version 0.4:
 **Date:** 06-01-2018  
 **Progress made:**  
 * Rewrote JUMP ability,
 * Implemented gravity for player,
 * Replaced several #includes in favour of forward declarations,
 * Cleaned up #includes,
 * Minor bug fixes,
 * Updated Makefile,
 * Added screen capture and screenshot.
 
 ### Version 0.5:
 **Date:** 07-01-2018  
 **Progress made:**
 * Started work on eRG::Scene class. This class will handle all models and render the virtual world,
 * Implemented eRG::Model class to act as a base for all future models,
 * Extended eRG::View class functionality with finer camera controls,
 * Removed unused file,
 * Minor refactoring and code cleanup,
 * Added screen capture and screenshot.

 ### Version 0.5.1:
 **Date:** 08-01-2018  
 **Progress made:**
 * Redesigned and reimplemented eRG::Model,
 * Reworked classes dependent on eRG::Model,
 * Minor tweaks.

 ### Version 0.5.2:
 **Date:** 09-01-2018  
 **Progress made:**
 * Implemented most of eRG::PModel, the class used to represent stationary models,
 * Made minor changes to eRG::Model,
 * Tweaked JUMP ability and gravity for eRG::View.

 ### Version 0.6:
 **Date:** 11-01-2018  
 **Progress made:**
 * Implemented eRG::AModel, the class used to represent moving models,
 * Added storing of translation and scale to eRG::Model,
 * Swithced storage of models in eRG::Scene from std::shared_ptr to std::unique_ptr, 
 * Reimplemented eRG::Scene::model_at method,
 * Added per axis camera movement controls.

 ### Version 0.6.1:
 **Date:** 12-01-2018  
 **Progress made:**
 * Changed get and set methods in eRG::View,
 * Added options for eRG::View get and set methods in opt/ enum classes,



