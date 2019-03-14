#include "Game.h"
#include <iostream>
#include <fstream>
using namespace sf;

Texture Texturepack::water;
Texture Texturepack::fire;
Texture Texturepack::fog;
Texture Texturepack::square;
Texture Texturepack::ssquare;
Texture Texturepack::b1;
Texture Texturepack::b2;
Texture Texturepack::b3;
Texture Texturepack::b4;
Texture Texturepack::bsquare;
Texture Texturepack::tsquare;
Texture Texturepack::cross;
Texture Texturepack::menu;
Texture Texturepack::scroll;
Texture Texturepack::guide;
Font Texturepack::menuFont;
Font Texturepack::inGameFont;
bool Game::restart = true;
bool Game::exit = false;
Clock Animationclock::c;

void main()
{
	srand(time(0));
	Texturepack hah;
	std::ifstream fin("config.txt");
	bool screen;
	fin >> screen;
	fin.close();
	RenderWindow window;
	if (screen)
		window.create(VideoMode(1920, 1080), "Battleships", Style::Fullscreen);
	else
		window.create(VideoMode(1920, 1080), "Battleships");
	Game* game = nullptr;
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		
		if (Game::restart)
		{
			delete game;
			game = new Game(window);
			Game::restart = false;
		}
		else if (Game::exit)
		{
			delete game;
			window.close();
		}
		else
		{
			window.clear();
			game->Start();
			window.display();
		}
	}
}