#pragma once
#include "Header.h"
#include "Field.h"
#include "Battleships.h"
#include "AI.h"
class Player
{
protected:
	Field field;
	std::vector<Ship*> ship;
	RenderWindow& window;
	Point selected;
	Point delay;
	AI bot;
	Trigger trigger;
	std::vector<int> c;
	bool setter = false;
	bool firstturn;
	void RandSelected() { selected.x = rand() % 10; selected.y = rand() % 10; }
public:
	Player(RenderWindow& window, Point d) : window(window), delay(d), firstturn(true) { c.resize(4); }
	void Reveal() { field.Reveal(); }
	void Hide() { field.Hide(); }
	void Reset() { field.Reset(); }
	void Deselect() { field.GetSquare(selected).DeSelect(); selected = 0; }
	bool CheckSetted()
	{
		if (c[0] == 4 && c[1] == 3 && c[2] == 2 && c[3] == 1 && !setter)
			return true;
		return false;
	}
	int Destroyed()
	{
		int c = 0;
		for (int i = 0; i < ship.size(); i++)
			if (ship[i]->GetDestroyed())
				c++;
		return c;
	}
	bool EndCheck()
	{

		if (Destroyed() == ship.size())
			return true;
		return false;
	}
	const bool GetSetter() { return setter; }
	void DrawField()
	{
		field.Set(delay);
		for (int i = 0; i<10; i++)
			for (int j = 0; j < 10; j++)
			{
				window.draw(field.GetSquare(Point(i, j)).GetSprite());
				window.draw(field.GetSquare(Point(i, j)).GetCloud());
				window.draw(field.GetSquare(Point(i, j)).GetCross());
			}
			for (int i = 0; i < ship.size(); i++)
				if (field.GetRevealed() || ship[i]->GetDestroyed())
					window.draw(ship[i]->GetSprite());
			for (int i = 0; i<10; i++)
				for (int j = 0; j < 10; j++)
					window.draw(field.GetSquare(Point(i, j)).GetFire().GetSprite());
	}
	void Move()
	{
			field.GetSquare(selected).DeSelect();
			if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && trigger.TriggerKeyPress() && selected.x > 0)
				selected.x--;
			if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && trigger.TriggerKeyPress() && selected.x < 9)
				selected.x++;
			if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && trigger.TriggerKeyPress() && selected.y < 9)
				selected.y++;
			if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && trigger.TriggerKeyPress() && selected.y > 0)
				selected.y--;
			field.GetSquare(selected).Select();
	}
	void Set()
	{
		if (Keyboard::isKeyPressed(Keyboard::Num1) && !setter && c[0] < 4)
		{
			ship.push_back(new Gunboat());
			c[0]++;
			setter = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num2) && !setter && c[1] < 3)
		{
			ship.push_back(new Schooner());
			c[1]++;
			setter = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num3) && !setter && c[2] < 2)
		{
			ship.push_back(new Frigate());
			c[2]++;
			setter = true;
		}
		else if (Keyboard::isKeyPressed(Keyboard::Num4) && !setter && c[3] < 1)
		{
			ship.push_back(new Battleship());
			c[3]++;
			setter = true;
		}
		if (setter)
		{
			ship[ship.size() - 1]->Set(delay + selected);
			if (Keyboard::isKeyPressed(Keyboard::R) && trigger.TriggerKeyPress())
				ship[ship.size() - 1]->Rotate();
			if (Keyboard::isKeyPressed(Keyboard::Enter) && ship[ship.size() - 1]->Check(delay) && ship[ship.size() - 1]->Occupy(field, delay))
			{
				setter = false;
			}
		}
	}
	void AITurn(bool& turn)
	{
		bot.Conquer(field, turn, selected, delay, ship);
	}
	void Turn (bool& turn)
	{
		if (firstturn)
		{
			trigger.Restart();
			firstturn = false;
		}
		if ((Keyboard::isKeyPressed(Keyboard::Enter) || Keyboard::isKeyPressed(Keyboard::Tab)) && trigger.TriggerKeyPress() && !field.GetSquare(selected).GetDestroyed())
		{
			if(!field.GetSquare(selected).Destroy())
				turn = !turn;
				for (int i = 0; i < ship.size(); i++)
					ship[i]->Destroy(field, delay);
		}

	}
	void AISet()
	{
		if (c[0] < 4)
		{
			ship.push_back(new Gunboat());
			c[0]++;
		}
		else if (c[1] < 3)
		{
			ship.push_back(new Schooner());
			c[1]++;
		}
		else if (c[2] < 2)
		{
			ship.push_back(new Frigate());
			c[2]++;
		}
		else if (c[3] < 1)
		{
			ship.push_back(new Battleship());
			c[3]++;
		}
		while (true)
		{
			RandSelected();
			ship[ship.size() - 1]->Rotate();
			ship[ship.size() - 1]->Set(delay + selected);
			if (ship[ship.size() - 1]->Check(delay) && ship[ship.size() - 1]->Occupy(field, delay))
				break;
		}
		Deselect();
	}
	~Player()
	{
		for (int i = 0; i < ship.size(); i++)
			delete ship[i];
	}
};