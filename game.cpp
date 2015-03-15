#include "game.h"

#include <iostream>
#include <chrono>

typedef std::chrono::high_resolution_clock Time;

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

bool Game::load()
{
	//Add code for loading and initialising objects
	Colour c;
	c.light_blue();
	tri = GameObject(TRIANGLE, Point(50,50), 30, 40, c);
	return true;
}

void Game::unload()
{
	//Add code for tearing down objects
}

void Game::Update()
{
	//Add code to update all game objects
	tri.Update();
}

void Game::Draw()
{
	//Add code to draw all game objects
	tri.Draw(graphics);
	graphics.Draw();
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
