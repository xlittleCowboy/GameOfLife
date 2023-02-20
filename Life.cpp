#include "Life.h"

Life::Life(float StartSpawnChance)
{
	srand(time(0));

	this->StartSpawnChance = StartSpawnChance;
}

void Life::SpawnStartCells(Grid* Grid)
{
	for (int i = 0; i < Grid->GetRows(); i++)
	{
		for (int j = 0; j < Grid->GetColumns(); j++)
		{
			if (rand() % 100 <= StartSpawnChance)
			{
				Grid->SetCellOnGrid(Grid->GetFillCell(), i, j);
			}
		}
	}
}

void Life::CheckCells(Grid* Grid)
{
	for (int i = 0; i < Grid->GetRows(); i++)
	{
		for (int j = 0; j < Grid->GetColumns(); j++)
		{
			int NeighbourCellsCount = CountNeighbourCells(Grid, i, j);

			if (!Grid->IsCellAlive(i, j))
			{
				if (NeighbourCellsCount == 3)
				{
					Grid->SetCellOnGrid(Grid->GetFillCell(), i, j);
				}
			}
			else if (Grid->IsCellAlive(i, j))
			{
				if (NeighbourCellsCount < 2 || NeighbourCellsCount > 3)
				{
					Grid->SetCellOnGrid(Grid->GetEmptyCell(), i, j);
				}
			}
		}
	}
}

int Life::CountNeighbourCells(Grid* Grid, int X, int Y)
{
	int CellsCount = 0;

	int X1, Y1;
	X == 0 ? Y1 = X : Y1 = X - 1;
	Y == 0 ? X1 = Y : X1 = Y - 1;

	int X2, Y2;
	X == Grid->GetRows() - 1 ? Y2 = X : Y2 = X + 1;
	Y == Grid->GetColumns() - 1 ? X2 = Y : X2 = Y + 1;

	for (; Y1 <= Y2; Y1++)
	{
		Y == 0 ? X1 = Y : X1 = Y - 1;
		for (; X1 <= X2; X1++)
		{
			if ((Y1 != X || X1 != Y) && Grid->IsCellAlive(Y1, X1))
			{
				CellsCount++;
			}
		}
	}

	return CellsCount;
}