#include <iostream>
#include <string>
#include<SFML/Graphics.hpp>
#include <Windows.h>
using namespace std;
using namespace sf;
void drawCircle(int, int);
void recordTheInput(int);
#define scr_width 1200
#define scr_height 850
#define grid_size 100
#define row_size 6
#define col_size 7
#define margin 20
sf::RenderWindow window(sf::VideoMode(scr_width, scr_height), "SFML Work");

//Gamelogic data
string player, player1 = "Hello1", player2 = "Hello2";
int x[6][7];
int point[] = { 5,5,5,5,5,5,5 };
int win = 0;
//

int main() {
	player = player1;
	for (int i = 0; i < 6; i++) //Assign '0' to every x
	{
		for (int t = 0; t < 7; t++)
		{
			x[i][t] = 0;
		}
	}
	//Grid
	sf::RectangleShape grid(sf::Vector2f(grid_size, grid_size));
	grid.setFillColor(sf::Color::Transparent);
	grid.setOutlineThickness(2.0f);
	grid.setOutlineColor(sf::Color::White);
	//end_Grid
	window.setFramerateLimit(15);
	while (window.isOpen())
	{
		window.clear();
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				if (player==player && event.key.code > 26 && event.key.code < 34)//GET INPUT //Num1=27
				{
					cout << event.key.code << endl;
					recordTheInput(event.key.code-26);
					break;
				}
				break;
			}
		}

		//Draw stuffs here
		for (int i = 0; i < col_size; i++)
		{
			for (int j = 0; j < row_size; j++)
			{
				grid.setPosition(sf::Vector2f(margin + grid_size * i, margin + grid_size * j)); // (left,up)
				window.draw(grid);
				drawCircle(j, i);//Display wena circles tika methanin check karala ganna
			}
		}
		//end_Draw stuffs here
		window.display();
	}

	return 0;
}

void drawCircle(int row,int colomn)
{
	if(x[row][colomn]!=0)
	{
		sf::CircleShape circle(49);
		circle.setPosition(sf::Vector2f(margin + colomn * 100, margin + row * 100));
		if(x[row][colomn] != 1)
			circle.setFillColor(sf::Color(250, 200, 50));
		if (x[row][colomn] != 2)
			circle.setFillColor(sf::Color(247, 52, 52));
		window.draw(circle);
	}
}

void recordTheInput(int index)
{
	index--;
	if (player == player1)
	{
		x[point[index]][index] = 1;
		player = player2;
	}
	else if (player == player2)
	{
		x[point[index]][index] = 2;
		player = player1;
	}
	point[index]--;
}

