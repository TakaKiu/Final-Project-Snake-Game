// Final Project Snake Game.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>
#include <conio.h>

#include "Snake.h"
#include "Food.h"

#define WIDTH 50
#define HEIGHT 25

using namespace std;

Snake snake({ WIDTH / 2, HEIGHT / 2 }, 1);
Food food;

int score;


void board()
{
	COORD snake_pos = snake.get_pos();
	COORD food_pos = food.get_pos();

	vector<COORD> snake_body = snake.get_body();

	cout << "SCORE : " << score << "\n\n";

	for (int i = 0; i < HEIGHT; i++)
	{
		cout << "\t\t#";
		for (int k = 0; k < WIDTH - 2; k++)
		{
			if (i == 0 || i == HEIGHT - 1) cout << '#';

			else if (i == food_pos.Y && k + 1 == food_pos.X) cout << '&';
			else if (i == snake_pos.Y && k + 1 == snake_pos.X) cout << '0';

			else
			{
				bool isBodyPart = false;
				for (int b = 0; b < snake_body.size()-1; b++)
				{
					if (i == snake_body[b].Y && k+1 == snake_body[b].X)
					{
						cout << 'o';
						isBodyPart = true;
						break;
					}
				}
				if (!isBodyPart) cout << ' ';
			}
		}
		cout << "#\n";
	}

}

int main()
{
	score = 0;
	srand(time(NULL));

	food.gen_food();

	char game_over = false;
	

	while (!game_over)
	{
		board();

		if (_kbhit())
		{
			switch (_getch())
			{
			case 'w': snake.direction('u'); break;
			case 'a': snake.direction('l'); break;
			case 's': snake.direction('d'); break;
			case 'd': snake.direction('r'); break;
			}
		}
		if (snake.collided()) game_over = true;

		if (snake.eaten(food.get_pos()))
		{
			food.gen_food();
			snake.grow();
			score = score + 10;
		}

		snake.move_snake();

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), {0, 0 });


	}
}