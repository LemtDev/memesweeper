#pragma once

#include "Vei2.h"
#include "Mouse.h"
#include "RectI.h"

#include <vector>

class MemeBoard
{
public:
	class Tile
	{
	public:
		enum tileState : char
		{
			DEFAULT = 0,
			FLAGGED = 1,
			OPEN = 2,
		};

		Tile(Vei2 boardPos, int tDim)
		{
			boardPosition = boardPos;
			// generates hitbox
			hitBox.left = boardPos.x - tDim;
			hitBox.right = boardPos.x + tDim;
			hitBox.top = boardPos.y - tDim;
			hitBox.bottom = boardPos.y + tDim;
		}

		void setAdjacent(int ad) { adjacentBombs = ad; }
		void setUpdated() { hasUpdated = true; }

		int getAdjancent() { return adjacentBombs; }
		bool isUpdated() { return hasUpdated; }

		Vei2 getBoardPosition() { return boardPosition; }

		void setState(tileState tState) { currentState = tState; }
		void setBomb() { isBomb = true; }
		bool getBomb() { return isBomb; }
		RectI& getHitbox() { return hitBox; }
	private:
		tileState currentState = DEFAULT;
		int adjacentBombs = 0;

		bool hasUpdated = false;
		bool isBomb = false;
		Vei2 boardPosition;
		RectI hitBox;
	};

	MemeBoard(Vei2 offset, int bW, int bH, int tileDim, Mouse& gMouse) : boardOffset(offset), boardWidth(bW), boardHeight(bH), tileDimension(tileDim), gameMouse(gMouse)
	{
		for (int y = 0; y < boardHeight; y++)
		{
			for (int x = 0; x < boardWidth; x++)
			{
				tileBoard.push_back({ Vei2{x,y}, tileDimension });
			}
		}
	}

	bool isInTile();

	void spawnBomb(Vei2 bPos);
	bool checkBomb(Vei2 bPos);
	void revealTile(Vei2 bPos);
	void flagTile(Vei2 bPos);

	std::vector<int> checkAdjacent(Vei2 bPos);
	void drawTile(Vei2 bPos);

private:
	Mouse& gameMouse;

	Vei2 boardOffset; // top left X,Y coords of the board;

	std::vector<Tile> tileBoard;

	const int boardWidth;
	const int boardHeight;

	const int tileDimension;
};

