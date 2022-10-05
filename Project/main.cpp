#include <iostream>
#include <string>
#include<SFML/Graphics.hpp>
#include <Windows.h>
using namespace std;
using namespace sf;
void drawCircle(int, int);
void recordTheInput(int);
#define scr_width 1200
#define scr_height 750
#define grid_size 100
#define row_size 6
#define col_size 7
#define margin 20
sf::RenderWindow window(sf::VideoMode(scr_width, scr_height), "Connect Four");

//Gamelogic data
void checkWiner(int, int);
string player, player1 = "Red player", player2 = "Yellow player", winner;
int x[6][7]; 
int point[] = { 5,5,5,5,5,5,5 };
int win = 0;
int start_col = 0;
int start_row = 0;
int end_col = 0;
int end_row = 0;
int color=0;
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
	//Title
	sf::Texture texture;
	sf::Sprite title;
	texture.loadFromFile("titleimg1.JPG");
	title.setTexture(texture);
	title.setPosition(770,20);
	//Connect fonts
	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Font font2;
	font2.loadFromFile("Milky Coffee.ttf");
	//Numbers
	sf::Text text;
	text.setFont(font);
	string num[]={"1","2","3","4","5","6","7"};
	text.setString("");
	text.setCharacterSize(80);
	//Status
	sf::Text status;
	status.setFont(font2);
	status.setString("");
	status.setCharacterSize(50);
	//win text
	sf::Text winText;
	winText.setFont(font2);
	winText.setString("WIN!");
	winText.setCharacterSize(150);
	winText.setPosition(810,385);
	//
	//winner name
	sf::Text winName;
	winName.setFont(font2);
	winName.setString("");
	winName.setCharacterSize(50);
	winName.setPosition(810,350);
	//
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
				if (win==0 &&event.key.code > 26 && event.key.code < 34)//GET INPUT //Num1=27
				{
					cout << event.key.code << endl;//Testing porposes
					recordTheInput(event.key.code-26);
					break;
				}
				if (event.key.code == sf::Keyboard::Space)//Space code is 57, RESET the program
				{
					win = 0;
					player = player1;
					for (int i = 0; i < 7; i++)
					{
						point[i] = 5;
					}
					for (int i = 0; i < 6; i++) //Assign '0' to every x
					{
						for (int t = 0; t < 7; t++)
						{
							x[i][t] = 0;
						}
					}
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
			text.setString(num[i]);
			text.setPosition(sf::Vector2f(50 + grid_size * i, 620));
			window.draw(text);
		}
		window.draw(title);
		if(win!=0)
		{
			if(win==1)
			{
				if(player == player2)
					winName.setFillColor(sf::Color(247, 52, 52));
				if(player == player1)
					winName.setFillColor(sf::Color(250, 200, 50));
				winName.setString(winner);
				window.draw(winName);
				window.draw(winText);
				status.setString("Press SPACE to start new game");
			}
			else
				status.setString("GAME DRAW,\n Press SPACE to start new game");
			status.setCharacterSize(30);
			status.setPosition(750,180);
			status.setFillColor(sf::Color(255,255,255));
			//change color
			color=11;
			if (start_col == end_col)
			{				
				if (x[start_row][start_col] == 2)
					color = 22;
				while (start_row <= end_row)
				{
					x[start_row][start_col] = color;
					start_row++;
				}
			}
			else if (start_row == end_row)
			{
				if (x[start_row][start_col] == 2)
					color = 22;
				while (end_col <= start_col)
				{
					x[start_row][end_col] = color;
					end_col++;
				}
			}
			else if (start_row < end_row && start_col > end_col)
			{
				if (x[start_row][start_col] == 2)
					color = 22;
				while (end_col <= start_col)
				{
					x[start_row][start_col] = color;
					start_row++;start_col--;
				}
			}
			else if (start_row < end_row && start_col < end_col)
			{
				if (x[start_row][start_col] == 2)
					color = 22;
				while (start_col <= end_col)
				{
					x[start_row][start_col] = color;
					start_row++;start_col++;
				}
			}
			//
		}
		else
		{
			if(player == player1)
			{
				status.setString("\t  RED\nPlayer Turn ");
				status.setFillColor(sf::Color(247, 52, 52));
			}	
			else
			{
				status.setString("  YELLOW\nPlayer Turn ");
				status.setFillColor(sf::Color(250, 200, 50));
			}				
			status.setCharacterSize(40);
			status.setPosition(850,150);
		}
		window.draw(status);
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
		if (x[row][colomn] == 1)
			circle.setFillColor(sf::Color(247, 52, 52)); //red
		if(x[row][colomn] == 2)
			circle.setFillColor(sf::Color(250, 200, 50)); //yellow
		if (x[row][colomn] == 11)
			circle.setFillColor(sf::Color(166, 10, 10)); //dark red
		if (x[row][colomn] == 22)
			circle.setFillColor(sf::Color(138, 104, 4)); //dark yellow
		window.draw(circle);
	}
	else if(win == 0)//Check wether game drow
	{
		for(int i=0;i<=6;i++)
		{
			if (point[i]!=0)
				break;
			if(point[6]==0)
				win=2;	
		}
	}
}

void recordTheInput(int index)
{	index--;
	if(point[index]>=0)
	{		
		if (player == player1)
		{
			x[point[index]][index] = 1;
			checkWiner(point[index], index);
			if(win==1)
				winner=player1;
			player = player2;
		}
		else if (player == player2)
		{
			x[point[index]][index] = 2;
			checkWiner(point[index], index);
			if(win==1)
				winner=player2;
			player = player1;
		}
		point[index]--;
	}	
}

void checkWiner(int row, int column)//Game LOGIC part.
{
	int coun = 1, condition = 1, y = row, z = column, n = 0;
	start_row = row;end_row = row;
	start_col = column;end_col = column;
	if (row < 3)//Down form last entered
	{
		while (1)
		{
			end_col = column;
			if (x[y][column] == x[y + 1][column])
				coun++;
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.1..........."<<endl;//Testing purpose
				end_row = y + 1;				
				win = 1;
				break;
			}
			y++;
		}
	}

	y = row; coun = 1;
	while (win == 0)//Left form last entered
	{
		end_row = row; end_col=column;
		if ((z - 1) >= 0)
		{
			if (x[y][z] == x[y][z - 1])
			{
				end_col=z-1;
				coun++;
			}
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.2..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z--;
		}
		else
			break;
	}
	if(win==0) //special porpose
		end_col=z;
	z = column;
	while (win == 0)//Right form last entered
	{
		if ((z + 1) <= 6)
		{
			if (x[y][z] == x[y][z + 1])
			{
				coun++;
				start_col=z+1;
			}				
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.3..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z++;
		}
		else
			break;
	}
	
	y = row; z = column; coun = 1;
	if(win==0) //special porpose
	{
		start_row = row; end_row=row;
		start_col = column; end_col=column;
	}
	while (win == 0)//Left Down form last entered
	{
		if ( (y + 1) <= 5 && (z - 1) >= 0 )
		{
			if (x[y][z] == x[y+1][z - 1])
			{
				end_row=y+1;end_col=z-1;
				coun++;
			}
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.4..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z--; y++;
		}
		else
			break;
	}
	cout<<end_row<<" start end 2 "<<end_col<<endl;
	y = row; z = column;
	while (win == 0)//Right Up form last entered
	{
		if ((y - 1) >= 0 && (z + 1) <= 6)
		{
			if (x[y][z] == x[y - 1][z + 1])
			{
				start_row=y-1;start_col=z+1;
				coun++;
			}
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.5..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z++; y--;
		}
		else
			break;
	}
	
	if(win==0) //special porpose
	{
		start_row = row; end_row=row;
		start_col = column; end_col=column;
	}
	y = row; z = column; coun = 1;
	while (win == 0)//Left Up form last entered
	{
		if ((y - 1) <= 5 && (z - 1) >= 0)
		{
			if (x[y][z] == x[y - 1][z - 1])
			{
				start_row = y-1;
				start_col = z-1;
				coun++;
			}
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.6..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z--; y--;
		}
		else
			break;
	}
	y = row; z = column;
	while (win == 0)//Right Down form last entered
	{
		if ((y + 1) >= 0 && (z + 1) <= 6)
		{
			if (x[y][z] == x[y + 1][z + 1])
			{
				end_row = y+1;
				end_col = z+1;
				coun++;
			}
			else
				break;
			if (coun == 4)
			{cout << ".........WIN.7..........."<<endl;//Testing purpose
				win = 1;
				break;
			}
			z++; y++;
		}
		else
			break;
	}
}
