# BasicEngine
Simple engine to use as base for showing AI algorithms built using SDL.
Or at least, that's my purpose for it. It's a little babby engine that can draw basic shapes, and not much else.
The idea is, when you're trying to do something where the way it does it is more important than how it looks, this might be handy.

With any luck, you shouldn't need to edit Graphics.h/.cpp or about half of Game.cpp.
Fill out the load/unload/update/draw in Game with your logic and either subclass or fill out GameObject's Update - the Draw should work fine as is.
