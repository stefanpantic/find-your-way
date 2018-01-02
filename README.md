# RG061-find-your-way
**Author:** Stefan Pantic.  
**Contact:** stefanpantic13@gmail.com  
**TL;DR:** Independent project in Computer Graphics college course done using OpenGL/GLUT and some GLM convenience 
classes. Done in C++.  
**Description:** *Find Your Way* is a platformer styled first person game. The goal is to find a way to the end of each level using several abilities at your disposal that include slowing down time, blinking and super jump. At one point I'm hoping to add mobs that will try to hinder your progess, as well as abilities to fend them off. The project is being written in C++ using older OpenGL/GLUT and some GLM classes for convenience. If time allows it, a port to modern OpenGL is not out of the question. This is my first larger C++ project. Any criticism and/or suggestions are more than welcome. :)

## Version 0.1:
**Date:** 30-12-2017  
**TODO:** Update wiki and move progress report there.  
**Progress:**
 * Implemented a wrapper around GLUT's window manupulation functions and callback registration (see eRG::Window),
 * Implemented the eRG::View class that is in charge of handling camera related OpenGL functionality,
 * Partialy implemeted a mainframe styled class (see eRG::Hub) that will control my classes an handle OpenGL indirectly through them (the end goal is to remove any direct interaction between eRG::Hub and OpenGL/GLUT),
 * Implemeted several enum classes that emulate OpenGL's GLenum functionality with an aditional layer of type safety and option checking,
 * Wrote a Makefile for convenience.


 
