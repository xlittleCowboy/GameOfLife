#pragma once

#include <SFML/Graphics.hpp>
#include <ctime>

#include "Cell.h"

class Grid
{
private:
	sf::Clock Clock;

	sf::Color AliveCellColor;
	sf::Color DeadCellColor;

	int CellSize;

	int Rows;
	int Columns;

	bool RandomCellColor;
	bool GlitchEffect;

	// Two-dimensial arrays of Old & Current grids 
	sf::RectangleShape** CurrentGrid;
	sf::RectangleShape** OldGrid;

	void SpawnStartCells(int StartSpawnChance);

	void ClearGrid();
	void DrawGrid(sf::RenderWindow& Window);

	bool IsCellAlive(int X, int Y);
	void SetCellOnGrid(sf::Color CellColor, int X, int Y);

	void CheckCells();
	int CountNeighbourCells(int X, int Y);

public:
	Grid(const sf::Color& AliveCellColor, const sf::Color& DeadCellColor, int CellSize,
		int Width, int Height, bool RandomCellColor = false, bool GlitchEffect = false);
	~Grid();

	void Restart(int StartSpawnChance);
	void UpdateGrid(const sf::Event& Event, float UpdateDelay, sf::RenderWindow& Window);
};