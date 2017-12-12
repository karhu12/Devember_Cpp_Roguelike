# Devember C++ Roguelike
This is a repository for a project where we aim to create a roguelike using c++.
We will be using PDCurses library to work with command prompt as our program display.

Solemn Swear
------------
We will participate to the next Devember. 
Our Devember will be creating a roguelike on C++.
I promise I will program for my Devember for at least an hour, every day of the next December.
I will also write a daily public devlog and will make the produced code publicly available on the internet.
No matter what, I will keep my promise. 

* We will try to create roguelike console game using C++
* Should have procedually generated maps
* RPG elements (npcs, overworld, etc.)
* 

1.12.2017
---------
This day was spent mostly on getting started. We were checking out a few libraries we could use in this project.
Initially i got PDCurses library working even before this project started but we wanted to try out other librarys with more functionality.
We tried to get libtcod working on windows but it ended up wasting many hours of our time and we decided to just keep on using PDCurses.
Rest of the night i just researched what kind of functions does PDcurse have and tried some of them out.

2.12.2017
---------
This day got a little bit more productive. 
I started to get some foundation for functions and classes done. I improved the UI to actually look like game.
I created test player with some really simple movement and tried drawing game window with it successfully.
I need to implement better functions to do some repeating stuff.
I learned how to split classes and functions into headers and other source files. 

3.12.2017
---------
Today i was able to create different kind of game functionality which should be used later on the code.
I created struct with games tileset. It includes tile names, types, colors and etc.
I also created a function that is able to determine which color pairs to apply when drawing game screen.
Also i divided the classes and functions yet more clearly to subfiles.
In general really productive and teaching day! :)

4.12.2017
---------
Day spent mostly on cleaning the code to however clean state i can currently get.
I also did some research on how to start making new zones.

5.12.2017
---------
Really unproductive day. I was not able to really do any real coding except a few lines. I was having really hard time figuring how to proceed from here on out.
Figured i should use pointers on map objects to create more dynamic maps but have no clue how to store them.

6.12.2017
---------
I got a whiff. I heard there is things called "maps" which can store different data. Tried implementing maps in my work. It seemed to be considerably harder than what i imagined.
But its okay because i know somewhat what i am aiming for here!

7.12.2017
---------
Finally the breakthrough. It took considerable amount of time today to finally figure what i wanted to do with the zones.
I implemented system which used map ID's to locate different map pointers. and exits which have links to different ID's.
Quite proud of this to be honest even tho its nothing amazing. Finally time to start doing some of the game logic!

8.12.2017
---------
Made the new area system work so that i changes player position 1 out of the exits position. Started working on random encounters.
Player has a chance to enter encounter during movement (currently planning 10% chance). In the encounter there will be combat in menu fashion.

9.12.2017
---------
Started thinking about how to implement the random encounters during movement. Just playing around with ideas.

10.12.2017
----------
Base for the encounter programmed but it was kinda lack luster so it will probably be rewritten.

11.12.2017
----------
Rewritten the encounter base to be alot clearer than before. No real game logic implemented on it yet tho.

12.12.2017
----------
Some real game logic has been implemented. Simple encounter system where your player has a 5% chance to find random encounter with 1-3 enemies. Player always hits with random number between damageMin - damageMax. Same thing for enemies but they have chance to miss. Player can also flee from combat if he happens to succeed. some other small additions aswell. Really productive day!
