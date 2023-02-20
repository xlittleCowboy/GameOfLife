#include <iostream>
#include <SFML/Graphics.hpp>
#include "Grid.h"
#include "Life.h"

/*
    SPAWN NEW CELLS WITH LMB
*/

int main()
{
    // Window Setup
    const int WindowWidth = 800;
    const int WindowHeight = 800;

    sf::RenderWindow Window(sf::VideoMode(WindowWidth, WindowHeight), "Game Of Life", sf::Style::Close);
    Window.setVerticalSyncEnabled(true);

    // Grid Setup
    Grid* MainGrid = new Grid(sf::Color::Green, sf::Color::Black, 10, WindowWidth, WindowHeight);
    MainGrid->SpawnStartCells(15);

    // Main Loop
    while (Window.isOpen())
    {
        sf::Event Event;
        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed)
                Window.close();
            if (Event.type == sf::Event::KeyPressed)
                if (Event.key.code == sf::Keyboard::Escape)
                    Window.close();
        }

        // Update Grid & Draw It
        MainGrid->UpdateGrid(Event, 0.15f);

        Window.clear();
        MainGrid->DrawGrid(Window);
        Window.display();
    }

    delete MainGrid;

    return 0;
}