#include "game.h"
#include "collision.h"
#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;

bool Game::load()
{
	//Add code for loading and initialising objects
	Colour c;
	c.red();
	a = GameObject(CIRCLE, Point(50, 20), 20, 20, c);
	c.white();
	b = GameObject(CIRCLE, Point(100, 50), 20, 20, c);
	return true;
}

void Game::unload()
{
	//Add code for tearing down objects
}

void Game::Update()
{
	Collision c;
	//Add code to update all game objects
	a.Update();
	//b.Update();
	Point collision = c.checkCollision(CollisionObject(a.go.position, a.go.shape, a.go.size, 0), CollisionObject(b.go.position, b.go.shape, b.go.size, 0));
	std::cout << "(" << collision.x << ", " << collision.y << ")" << std::endl;
	a.go.position.x += collision.x;
	a.go.position.y += collision.y;
}

void Game::Draw()
{
	//Add code to draw all game objects
	a.Draw(graphics);
	b.Draw(graphics);
	graphics.Draw(); //This line needed to actually draw all of the objects onscreen
}

/******************* Don't need to edit below here ********************/
Game::Game()
{
	graphics = Graphics(640, 480);
	graphics.init_window();
	
	if(!load())
	{
		std::cout << "Loading failed" << std::endl;
		exit(1);
	}
}

Game::~Game()
{
	unload();
}

void Game::mainLoop()
{
	SDL_Event event;
	auto frame_start_time = Time::now(); //Needs to be initialised to Time::now() so auto knows what type it is
	bool exit = false;

	while(!exit)
	{
		frame_start_time = Time::now();
		
		while(SDL_PollEvent(&event))
		{
			//X button pressed on window
			if(event.type == SDL_QUIT)
			{
				exit = true;
			}
		}
		
		Update();
		Draw();

		//Synchronise frame so that the game runs at 60 fps (or whatever ms_per_frame currently works out at)
		std::chrono::milliseconds frame_duration = std::chrono::duration_cast<std::chrono::milliseconds>(Time::now() - frame_start_time);
		if(frame_duration.count() < ms_per_frame)
		{
			SDL_Delay(ms_per_frame - frame_duration.count());
		}
	}
}
