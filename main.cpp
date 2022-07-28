#include <iostream>

#include <SFML/Graphics.hpp>

#include "./TicTacToe.cpp"

int main()
{
    sf::RenderWindow window(sf::VideoMode(500, 800), "Tic Tac Toe", sf::Style::Titlebar | sf::Style::Close);

    TicTacToe game(window);

    game.run();

    game.close();

    return 0;
}
