#include "Grid.h"

Grid::~Grid()
{
	for (int i = 0; i < Rows; i++)
	{
		delete[] CurrentGrid[i];
	}

	delete[] CurrentGrid;
}

Grid::Grid(const sf::Color& AliveCellColor, const sf::Color& DeadCellColor, int CellSize,
	int Width, int Height, bool RandomCellColor, bool GlitchEffect)
{
	srand(time(0));

	this->CellSize = CellSize;

	this->AliveCellColor = AliveCellColor;
	this->DeadCellColor = DeadCellColor;

	this->RandomCellColor = RandomCellColor;
	this->GlitchEffect = GlitchEffect;

	if (RandomCellColor)
	{
		this->AliveCellColor = sf::Color(rand() % 255, rand() % 255, rand() % 255);
	}

	Rows = Height / CellSize;
	Columns = Width / CellSize;

	CurrentGrid = new sf::RectangleShape*[Rows];
	OldGrid = new sf::RectangleShape*[Rows];

	for (int i = 0; i < Rows; i++)
	{
		CurrentGrid[i] = new sf::RectangleShape[Columns];
		OldGrid[i] = new sf::RectangleShape[Columns];
	}
}

void Grid::ClearGrid()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			CurrentGrid[i][j].setPosition(sf::Vector2f(j * CellSize, i * CellSize));
			CurrentGrid[i][j].setSize(sf::Vector2f(CellSize, CellSize));
			CurrentGrid[i][j].setFillColor(DeadCellColor);

			OldGrid[i][j] = CurrentGrid[i][j];
		}
	}
}

void Grid::DrawGrid(sf::RenderWindow& Window)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			if (GlitchEffect)
			{
				OldGrid[i][j].setFillColor(sf::Color(rand() % 255, rand() % 255, rand() % 255)); 
			}

			CurrentGrid[i][j] = OldGrid[i][j];
			Window.draw(CurrentGrid[i][j]);
		}
	}
}

bool Grid::IsCellAlive(int X, int Y)
{
	return CurrentGrid[X][Y].getFillColor() == AliveCellColor;
}

void Grid::SetCellOnGrid(sf::Color CellColor, int X, int Y)
{
	if (X >= Columns || Y >= Rows) return;

	OldGrid[Y][X].setFillColor(CellColor);
}

void Grid::SpawnStartCells(int StartSpawnChance)
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Rows; j++)
		{
			if (rand() % 100 <= StartSpawnChance)
			{
				SetCellOnGrid(AliveCellColor, j, i);
			}
		}
	}

	Clock.restart();
}

void Grid::CheckCells()
{
	for (int i = 0; i < Rows; i++)
	{
		for (int j = 0; j < Columns; j++)
		{
			int NeighbourCellsCount = CountNeighbourCells(i, j);

			if (!IsCellAlive(i, j))
			{
				if (NeighbourCellsCount == 3)
				{
					SetCellOnGrid(AliveCellColor, j, i);
				}
			}
			else if (IsCellAlive(i, j))
			{
				if (NeighbourCellsCount < 2 || NeighbourCellsCount > 3)
				{
					SetCellOnGrid(DeadCellColor, j, i);
				}
			}
		}
	}
}

int Grid::CountNeighbourCells(int X, int Y)
{
	int CellsCount = 0;

	int X1, Y1;
	X == 0 ? Y1 = X : Y1 = X - 1;
	Y == 0 ? X1 = Y : X1 = Y - 1;

	int X2, Y2;
	X == Rows - 1 ? Y2 = X : Y2 = X + 1;
	Y == Columns - 1 ? X2 = Y : X2 = Y + 1;

	for (; Y1 <= Y2; Y1++)
	{
		Y == 0 ? X1 = Y : X1 = Y - 1;
		for (; X1 <= X2; X1++)
		{
			if ((Y1 != X || X1 != Y) && IsCellAlive(Y1, X1))
			{
				CellsCount++;
			}
		}
	}

	return CellsCount;
}

void Grid::UpdateGrid(const sf::Event& Event, float UpdateDelay, sf::RenderWindow& Window)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2f MousePosition(Event.mouseMove.x, Event.mouseMove.y);

		MousePosition.x /= CellSize;
		MousePosition.y /= CellSize;
		SetCellOnGrid(AliveCellColor, MousePosition.x, MousePosition.y);
	}
	else
	{
		if (Clock.getElapsedTime().asSeconds() >= UpdateDelay)
		{
			CheckCells();
			Clock.restart();
		}
	}

	DrawGrid(Window);
}

void Grid::Restart(int StartSpawnChance)
{
	ClearGrid();
	SpawnStartCells(StartSpawnChance);
}
