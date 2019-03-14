#pragma once
#include "Header.h"
#include "Field.h"
#include "Battleships.h"

class AI
{
	Point damaged;
	int damagedTrigger;
	int side;
	int buff;
	int c;
public:
	AI() :damagedTrigger(0), side(0), buff(2), c(0) {}
	void Conquer(Field& field, bool& turn, Point& selected, Point& delay, std::vector<Ship*>& ship)
	{

		if (side > 0)
		{
			if (damagedTrigger == 2)
			{
				switch (side)
				{
				case 1:
					side = 3;
					break;
				case 2:
					side = 4;
					break;
				case 3:
					side = 1;
					break;
				case 4:
					side = 2;
					break;
				}
				damagedTrigger = 1;
				buff = 1;
			}
			if (side == 1)
				while (damaged.y - buff >= 0 && !field.GetSquare(damaged - Point(0, buff)).GetDestroyed())
					if (field.GetSquare(damaged - Point(0, buff)).Destroy())
						buff++;
					else
					{
						turn = !turn;
						damagedTrigger = 2;
						break;
					}
			if (side == 2)
				while (damaged.x + buff <= 9 && !field.GetSquare(damaged + Point(buff, 0)).GetDestroyed())
					if (field.GetSquare(damaged + Point(buff, 0)).Destroy())
						buff++;
					else
					{
						turn = !turn;
						damagedTrigger = 2;
						break;
					}
			if (side == 3)
				while (damaged.y + buff <= 9 && !field.GetSquare(damaged + Point(0, buff)).GetDestroyed())
					if (field.GetSquare(damaged + Point(0, buff)).Destroy())
						buff++;
					else
					{
						turn = !turn;
						damagedTrigger = 2;
						break;
					}
			if (side == 4)
				while (damaged.x - buff >= 0 && !field.GetSquare(damaged - Point(buff, 0)).GetDestroyed())
					if (field.GetSquare(damaged - Point(buff, 0)).Destroy())
						buff++;
					else
					{
						turn = !turn;
						damagedTrigger = 2;
						break;
					}
			c++;
			if (c == 20)
				damagedTrigger = 2;
		}
		else if (damagedTrigger == 1)
		{
			if (damaged.y > 0 && !field.GetSquare(damaged - Point(0, 1)).GetDestroyed())
				if (field.GetSquare(damaged - Point(0, 1)).Destroy())
					side = 1;
				else
					turn = !turn;
			else if (damaged.x < 9 && !field.GetSquare(damaged + Point(1, 0)).GetDestroyed())
				if (field.GetSquare(damaged + Point(1, 0)).Destroy())
					side = 2;
				else
					turn = !turn;
			else if (damaged.y < 9 && !field.GetSquare(damaged + Point(0, 1)).GetDestroyed())
				if (field.GetSquare(damaged + Point(0, 1)).Destroy())
					side = 3;
				else
					turn = !turn;
			else if (damaged.x > 0 && !field.GetSquare(damaged - Point(1, 0)).GetDestroyed())
				if (field.GetSquare(damaged - Point(1, 0)).Destroy())
					side = 4;
				else
					turn = !turn;
		}
		else if(damagedTrigger == 0)
		{
			selected.x = rand() % 10; selected.y = rand() % 10;
			if (!field.GetSquare(selected).GetDestroyed())
				if (!field.GetSquare(selected).Destroy())
					turn = !turn;
				else
				{
					damagedTrigger = 1;
					damaged = selected;
				}
		}
		for (int i = 0; i < ship.size(); i++)
			if (ship[i]->Destroy(field, delay))
			{
				damagedTrigger = 0;
				side = 0;
				buff = 2;
				c = 0;
			}
	}
};