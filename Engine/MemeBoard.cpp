#include "MemeBoard.h"

bool MemeBoard::isInTile()
{
	Vei2 actualMousePos = {gameMouse.GetPos().first, gameMouse.GetPos().second};
	bool isTile = false;

	for (int y = 0; y < tileBoard.size(); y++)
	{
		for (int x = 0; x < tileBoard.size(); x++)
		{
			isTile = tileBoard[y * x].getHitbox().Contains(actualMousePos);
		}
	}

	return isTile;
}

void MemeBoard::spawnBomb(Vei2 bPos)
{
	tileBoard[bPos.y * bPos.x].setBomb();
}

bool MemeBoard::checkBomb(Vei2 bPos)
{
	return tileBoard[bPos.y * bPos.x].getBomb();
}

void MemeBoard::revealTile(Vei2 bPos)
{
	tileBoard[bPos.y * bPos.x].setState(Tile::tileState::OPEN);
}

void MemeBoard::flagTile(Vei2 bPos)
{
	tileBoard[bPos.y * bPos.x].setState(Tile::tileState::FLAGGED);
}

std::vector<int> MemeBoard::checkAdjacent(Vei2 bPos)
{
	std::vector<int> indexReturns;
	static int tilesChecked = 0;
	for (int i = 0; i < tileBoard.size(); i++)
	{
		Vei2 lastCheckedPosition = tileBoard[i].getBoardPosition();

		Vei2 posDifference = lastCheckedPosition - bPos;
		if (posDifference.x >= -1.0f && posDifference.x <= 1.0f && posDifference.y >= -1.0f && posDifference.y <= 1.0f && !tileBoard[i].isUpdated())
		{
			tilesChecked++;
			while (!checkBomb(lastCheckedPosition))
			{
				revealTile(lastCheckedPosition);
				tileBoard[i].setUpdated();
			}

			if (indexReturns.size() < 1 && i >= 8)
			{
				bPos = lastCheckedPosition;
				tilesChecked = 0;
			}

			if (checkBomb(lastCheckedPosition))
			{
				indexReturns.push_back(i);
				tileBoard[bPos.y * bPos.x].setAdjacent(indexReturns.size());
			}
		}
	}


	return indexReturns;
}

void MemeBoard::drawTile(Vei2 bPos)
{
}
