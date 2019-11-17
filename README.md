# &#955;: Find Your Way

*Find Your Way* is a platformer styled first person game. The goal is to find a way to the end of each level using several abilities at your disposal that include slowing down time, blinking and super jump. At one point I'm hoping to add mobs that will try to hinder your progess, as well as abilities to fend them off. The project is being written in C++ using older OpenGL/GLUT and some GLM classes for convenience. If time allows it, a port to modern OpenGL is not out of the question. This is my first larger C++ project. Any criticism and/or suggestions are more than welcome. :)  

## :movie_camera: Preview:
**Date:** 01-02-2018  

![preview](https://github.com/stefanpantic/find-your-way/blob/master/sample/01-02-2018.gif) 

## :computer: Installation:
Just run <code>./start.sh</code> from the project directory. This will compile the project if needed and then start it with the default map/textures.   
Alternatively you can run <code>make -j</code> and run with your own map/textures.   
## :computer: Requirements:
 * **OpenGL/GLUT, GLM:**  

Arch Linux:
<pre>sudo pacman -S freeglut glm</pre>
Ubuntu:
<pre>sudo apt-get install freeglut3-dev binutils-gold libglm-dev</pre>

* **Tested C++ compiler (others may work as well)**:   
    * g++ 7.2.0+,
    * clang++ 5.0.0+.
 
 
## :video_game: Instructions:
| Key | Action |
|-----|:------:|
| :arrow_up: | Move forward |
| :arrow_down: | Move backward |
| :arrow_left: | Strafe left |
| :arrow_right: | Strafe right |
| `space` | Jump |
| `b` | Blink/dash |
| :mouse2: or `wasd` | Look around |
| `r` | Reset |
| `Esc` | Exit |


## :clock1030: Progress reports and change log:
**NOTE:** This section has been moved to the [wiki page](https://github.com/stefanpantic/find-your-way/wiki/Progress-reports-and-change-logs).


## :information_source: About me:
**Author:** Stefan Pantic.  
**Contact:** stefanpantic13@gmail.com   
