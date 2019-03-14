#pragma once
#include "Header.h"
#include <string>

class Menu
{
protected:
	Sprite menu;
	std::vector<Text> text;
	Trigger trigger;
	int m;
public:
	Menu() :m(0) {}
	const int GetM() { return m; }
	void MenuMove()
	{
		text[m].setFillColor(Color::White);
		if (Keyboard::isKeyPressed(Keyboard::Down) && trigger.TriggerKeyPress())
			if (m + 1 == text.size())
				m = 0;
			else if (m + 1 < text.size())
				m++;
		if (Keyboard::isKeyPressed(Keyboard::Up) && trigger.TriggerKeyPress())
			if (m == 0)
				m = text.size() - 1;
			else if (m > 0)
				m--;
		text[m].setFillColor(Color::Red);
	}
	void Draw(RenderWindow& window)
	{
		window.draw(menu);
		for (int i = 0; i < text.size(); i++)
			window.draw(text[i]);
	}
};

class MainMenu : public Menu
{
	Sprite guide;
public:
	MainMenu() : Menu::Menu(), guide(Texturepack::guide)
	{
		text.resize(4);
		menu.setTexture(Texturepack::menu);
		text[0] = Text("Single Player", Texturepack::menuFont, 170);
		text[0].setPosition(820, 310);
		text[1] = Text("Local PvP", Texturepack::menuFont, 170);
		text[1].setPosition(820, 410);
		text[2] = Text("Guide", Texturepack::menuFont, 170);
		text[2].setPosition(900, 510);
		text[3] = Text("Exit", Texturepack::menuFont, 170);
		text[3].setPosition(920, 610);
	}
	void DrawGuide(RenderWindow& window)
	{
		window.draw(guide);
	}
};


class ContextMenu : public Menu
{
public:
	ContextMenu() : Menu::Menu()
	{
		menu.setPosition(650, 150);
		text.resize(2);
		menu.setTexture(Texturepack::scroll);
		text[0] = Text("Resume", Texturepack::menuFont, 170);
		text[0].setPosition(840, 310);
		text[1] = Text("Exit to main Menu", Texturepack::menuFont, 170);
		text[1].setPosition(720, 410);
	}
};


class IngameText
{
protected:
	std::vector<Text> text;
	Player& player1;
	Player& player2;
public:
	IngameText(Player& p1, Player& p2) : player1(p1), player2(p2){}
	void Draw(RenderWindow& window)
	{
		for (int i = 0; i < text.size(); i++)
			window.draw(text[i]);
	}
};

class Stat : public IngameText
{
public:
	Stat(Player& p1, Player& p2) : IngameText(p1, p2)
	{
		text.resize(3);
		text[0] = Text("Ships left", Texturepack::inGameFont, 50);
		text[0].setPosition(850, 10);
	}
	void LoadStat()
	{
		text[1] = Text(std::to_string(10 - player1.Destroyed()), Texturepack::inGameFont, 100);
		text[2] = Text(std::to_string(10 - player2.Destroyed()), Texturepack::inGameFont, 100);
		text[1].setPosition(95, 10);
		text[2].setPosition(1730, 10);
	}
};

class End : public IngameText
{
public:
	End(Player& p1, Player& p2) : IngameText(p1, p2)
	{
		text.resize(2);
		text[0] = Text("Press space to exit to main menu", Texturepack::inGameFont, 50);
		text[0].setPosition(600, 800);
	}
	void LoadEndingSP()
	{
		if (player2.EndCheck())
		{
			text[1] = Text("You won", Texturepack::menuFont, 500);
			text[1].setPosition(550, -100);
			text[1].setFillColor(Color::Green);
			text[1].setStyle(Text::Bold);
		}
		else if (player1.EndCheck())
		{
			text[1] = Text("You lost", Texturepack::menuFont, 500);
			text[1].setPosition(550, -100);
			text[1].setFillColor(Color::Red);
			text[1].setStyle(Text::Bold);
		}
	}
	void LoadEndingMP()
	{
		if (player2.EndCheck())
		{
			text[1] = Text("Player 1 won", Texturepack::menuFont, 500);
			text[1].setPosition(500, -100);
			text[1].setFillColor(Color::Green);
			text[1].setStyle(Text::Bold);
		}
		else if (player1.EndCheck())
		{
			text[1] = Text("Player 2 won", Texturepack::menuFont, 500);
			text[1].setPosition(500, -100);
			text[1].setFillColor(Color::Red);
			text[1].setStyle(Text::Bold);
		}
	}
};