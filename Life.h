#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>
#include "Grid.h"

class Life
{
private:
	int StartSpawnChance;

public:
	Life(float StartSpawnChance);

	void SpawnStartCells(Grid* Grid);

	void CheckCells(Grid* Grid);
	int CountNeighbourCells(Grid* Grid, int X, int Y);
};

