#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include <ctime>
#include "Cell.h"

class Grid
{
private:
	sf::Clock Clock;

	sf::RectangleShape AliveCell;
	sf::RectangleShape DeadCell;

	int CellSize;

	int Rows;
	int Columns;

	// Two-dimensial arrays of Old & Current grids 
	sf::RectangleShape** CurrentGrid;
	sf::RectangleShape** OldGrid;

public:
	Grid(const sf::Color& AliveCellColor, const sf::Color& DeadCellColor, int CellSize, int Width, int Height);
	~Grid();

	void ClearGrid();
	void DrawGrid(sf::RenderWindow& Window);

	bool IsCellAlive(int X, int Y);
	void SetCellOnGrid(sf::RectangleShape Cell, int X, int Y);

	void SpawnStartCells(int StartSpawnChance);
	void CheckCells();
	int CountNeighbourCells(int X, int Y);

	void UpdateGrid(const sf::Event& Event, float UpdateDelay);

	int GetRows() { return Rows; }
	int GetColumns() { return Columns; }

	int GetCellSize() { return CellSize; }

	const sf::RectangleShape& GetFillCell() { return AliveCell; }
	const sf::RectangleShape& GetEmptyCell() { return DeadCell; }
};