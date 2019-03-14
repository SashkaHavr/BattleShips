#pragma once
#include "Header.h"

class Fire
{
	int time;
	int frame;
	Sprite spr;
public:
	Sprite& GetSprite() { return spr; }
	Fire() : frame(0) {}
	void Set(Point x)
	{
		spr.setTexture(Texturepack::fire);
		time = Animationclock::GetTime();
		if (time > 7)
			Animationclock::Restart();
		spr.setTextureRect(IntRect(80 * time, 0, 80, 80));
		spr.setPosition(x.x, x.y);
	}
};

class Square
{
	Fire fire;
	Sprite clspr;
	Sprite spr;
	Sprite cross;
	bool revealed;
	bool destroyed;
	bool selected;
	bool busy;
	bool shipishere;
public:
	Square() : revealed(0), selected(0), destroyed(0), busy(0), shipishere(0) {}
	Sprite& GetSprite() { return spr; }
	Fire& GetFire() { return fire; }
	Sprite& GetCloud() { return clspr; }
	Sprite& GetCross() { return cross; }
	const bool GetBusiness() { return busy; }
	const bool GetDestroyed() { return destroyed; }
	void Occupy() { busy = 1; }
	void Free() { busy = 0; }
	void Reveal() { revealed = 1; }
	void Hide() { revealed = 0; }
	void Select() { selected = 1; }
	void DeSelect() { selected = 0; }
	void SetShip() { shipishere = 1; }
	bool Destroy()
	{
		Reveal();
		destroyed = 1;
		if (shipishere)
			return true;
		return false;
	}
	void Set(Point x)
	{
		if (selected)
			spr.setTexture(Texturepack::ssquare);
		else if (busy)
			spr.setTexture(Texturepack::bsquare);
		else
			spr.setTexture(Texturepack::square);
		spr.setPosition(80 * x.x, 80 * x.y);
		if (destroyed && shipishere)
			fire.Set(Point(80 * x.x, 80 * x.y));
		else if (destroyed)
		{
			cross.setTexture(Texturepack::cross);
			cross.setPosition(80 * x.x, 80 * x.y);
		}
		if (!revealed)
		{
			clspr.setTexture(Texturepack::fog);
			clspr.setPosition(80 * x.x + 2, 80 * x.y + 2);
		}
		else
			clspr.setTexture(Texturepack::tsquare);
	}
};

class Field
{
	Square** field;
	bool revealed;
public:

	Field() : revealed(false)
	{
		field = new Square*[10];
		for (int i = 0; i < 10; i++)
			field[i] = new Square[10];
	}
	Square& GetSquare(Point i) { return field[i.x][i.y]; }
	const bool GetRevealed() { return revealed; }
	void Set(Point x)
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				field[i][j].Set(Point(x.x + i, x.y+j));
	}
	void Reveal()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				field[i][j].Reveal();
		revealed = true;
	}
	void Hide()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				field[i][j].Hide();
		revealed = false;
	}
	void Reset()
	{
		for (int i = 0; i < 10; i++)
			for (int j = 0; j < 10; j++)
				field[i][j].Free();
	}
	void Occupy(Point x)
	{
		field[x.x][x.y].SetShip();
		field[x.x][x.y].Occupy();
		if(x.x < 9)
			field[x.x + 1][x.y].Occupy();
		if(x.y < 9)
			field[x.x][x.y + 1].Occupy();
		if(x.x > 0)
			field[x.x - 1][x.y].Occupy();
		if(x.y > 0)
			field[x.x][x.y - 1].Occupy();
		if (x.x < 9 && x.y < 9)
			field[x.x + 1][x.y + 1].Occupy();
		if (x.x < 9 && x.y > 0)
			field[x.x + 1][x.y - 1].Occupy();
		if (x.x > 0 && x.y < 9)
			field[x.x - 1][x.y + 1].Occupy();
		if (x.x > 0 && x.y > 0)
			field[x.x - 1][x.y - 1].Occupy();
	}
	void Desroy(Point x)
	{
		field[x.x][x.y].Destroy();
		if (x.x < 9)
			field[x.x + 1][x.y].Destroy();
		if (x.y < 9)
			field[x.x][x.y + 1].Destroy();
		if (x.x > 0)
			field[x.x - 1][x.y].Destroy();
		if (x.y > 0)
			field[x.x][x.y - 1].Destroy();
		if (x.x < 9 && x.y < 9)
			field[x.x + 1][x.y + 1].Destroy();
		if (x.x < 9 && x.y > 0)
			field[x.x + 1][x.y - 1].Destroy();
		if (x.x > 0 && x.y < 9)
			field[x.x - 1][x.y + 1].Destroy();
		if (x.x > 0 && x.y > 0)
			field[x.x - 1][x.y - 1].Destroy();
	}
	~Field()
	{
		for (int i = 0; i < 10; i++)
			delete[] field[i];
		delete[] field;
	}
};

