#pragma once
#include "Header.h"
#include "Player.h"
#include "Menu.h"

class Game
{
	RenderWindow& window;
	Event ev;
	Player player1;
	Player player2;
	bool playerTurn;
	bool isMenu;
	bool isContextMenu;
	bool lol;
	Water water;
	MainMenu menu;
	ContextMenu contextMenu;
	Trigger trigger;
	Stat stat;
	End end;
	bool guide;
public:
	static bool restart;
	static bool exit;
	Game(RenderWindow& window) :window(window), player1(window, Point(1, 2)), player2(window, Point(13, 2)), playerTurn(true), isMenu(true), stat(player1, player2), end(player1, player2), lol(true), guide(false) { }
	void Start()
	{
		window.pollEvent(ev);
		if (ev.type == Event::Closed)
			window.close();
		Menu();
	}
	void Menu()
	{
		if ((Keyboard::isKeyPressed(Keyboard::Enter) && trigger.TriggerKeyPress() && isMenu ) || !isMenu)
		{
			switch (menu.GetM())
			{
			case 0:
				isMenu = false;
				READYSP();
				break;
			case 1:
				isMenu = false;
				READYMP();
				break;
			case 2:
				guide = true;
				break;
			case 3:
				Game::exit = true;
				break;
			}
		}
		else
		{
			menu.MenuMove();
			if (guide)
			{
				menu.DrawGuide(window);
				if (Keyboard::isKeyPressed(Keyboard::Escape))
					guide = false;
			}
			else
				menu.Draw(window);
		}
	}
	void READYSP()
	{
		water.Draw(window);
		player1.DrawField();
		player2.DrawField();
		STEADYSP();
	}
	void STEADYSP()
	{
		if (isContextMenu)
		{
			if (((Keyboard::isKeyPressed(Keyboard::Enter) && contextMenu.GetM() == 0) ) || (Keyboard::isKeyPressed(Keyboard::Escape) && trigger.TriggerKeyPress()))
				isContextMenu = false;
			if ((Keyboard::isKeyPressed(Keyboard::Enter) && contextMenu.GetM() == 1) )
				Game::restart = true;
			contextMenu.MenuMove();
			contextMenu.Draw(window);
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape) && trigger.TriggerKeyPress())
				isContextMenu = true;
			player1.Reveal();
			if (!player2.CheckSetted())
				player2.AISet();
			else if (!player1.CheckSetted())
			{
				player2.Reset();
				player2.Deselect();
				player1.Move();
				player1.Set();
				if (Keyboard::isKeyPressed(Keyboard::Tab) && trigger.TriggerKeyPress() && !player1.GetSetter())
				{
					player1.Deselect();
					player1.AISet();
				}
			}
			else
			{
				player1.Reset();
				player1.Deselect();
				GOSP();
			}
		}
	}
	void GOSP()
	{
		stat.LoadStat();
		stat.Draw(window);
		if (playerTurn)
		{
			player2.Move();
			player2.Turn(playerTurn);
		}
		else
		{
			player1.AITurn(playerTurn);
		}
		if (player1.EndCheck() || player2.EndCheck())
		{
			player2.Reveal();
			end.LoadEndingSP();
			end.Draw(window);
			if (Keyboard::isKeyPressed(Keyboard::Space))
				Game::restart = true;
		}
	}
	void READYMP()
	{
		water.Draw(window);
		player1.DrawField();
		player2.DrawField();
		STEADYMP();
	}
	void STEADYMP()
	{
		if (isContextMenu)
		{
			if (((Keyboard::isKeyPressed(Keyboard::Enter) && contextMenu.GetM() == 0) ) || (Keyboard::isKeyPressed(Keyboard::Escape) && trigger.TriggerKeyPress()))
				isContextMenu = false;
			if ((Keyboard::isKeyPressed(Keyboard::Enter) && contextMenu.GetM() == 1) )
				Game::restart = true;
			contextMenu.MenuMove();
			contextMenu.Draw(window);
		}
		else
		{
			if (Keyboard::isKeyPressed(Keyboard::Escape) && trigger.TriggerKeyPress())
				isContextMenu = true;
			if (!player1.CheckSetted())
			{
				player1.Reveal();
				player1.Move();
				player1.Set();
				if (Keyboard::isKeyPressed(Keyboard::Tab) && trigger.TriggerKeyPress() && !player1.GetSetter())
				{
					player1.Deselect();
					player1.AISet();
				}
			}
			else if (!player2.CheckSetted())
			{
				player1.Deselect();
				player1.Reset();
				player1.Hide();
				player2.Reveal();
				player2.Move();
				player2.Set();
				if (Keyboard::isKeyPressed(Keyboard::Tab) && trigger.TriggerKeyPress() && !player2.GetSetter())
				{
					player2.Deselect();
					player2.AISet();
				}
			}
			else if (lol)
			{
				player2.Reset();
				player2.Deselect();
				player2.Hide();
				lol = false;
			}
			else
			{
				GOMP();
			}
		}
	}
	void GOMP()
	{
		stat.LoadStat();
		stat.Draw(window);
		if (playerTurn)
		{
			player2.Move();
			player2.Turn(playerTurn);
		}
		else
		{
			player1.Move();
			player1.Turn(playerTurn);
		}
		if (player1.EndCheck() || player2.EndCheck())
		{
			player1.Reveal();
			player2.Reveal();
			end.LoadEndingMP();
			end.Draw(window);
			if (Keyboard::isKeyPressed(Keyboard::Space))
				Game::restart = true;
		}
	}
};