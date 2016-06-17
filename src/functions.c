#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include "rogue.h"

void assignValues(Room * room, char line[])
{
	char * token;

	room->xGold = 0;
	room->xHero = 0;
	room->xMons = 0;
	room->xPot = 0;

	room->xSize = atoi(strtok(line, "X"));
	token = strtok(NULL, " ");
	room->ySize = atoi(token);
	while(token != NULL)
	{
		int i = 1;
		int j = 0;
		char str1[5] = "";
		char str2[5] = "";

		token = strtok(NULL, " ");
		if(token == NULL)
		{
			break;
		}

		while(isdigit(token[i]))
		{
			str1[i-1] = token[i];
			i++;
		}

		while(isdigit(token[i+1]))
		{
			str2[j] = token[i+1];
			i++;
			j++;
		}
		switch(token[0])
		{
			case 'd':
				if(token[1] == 'w')
				{
					room->doorLocW = atoi(str2);
				}
				else if(token[1] == 'e')
				{
					room->doorLocE = atoi(str2);
				}
				else if(token[1] == 's')
				{
					room->doorLocS = atoi(str2);
				}
				else if(token[1] == 'n')
				{
					room->doorLocN = atoi(str2);
				}
				break;
			case 'g':
				room->xGold = atoi(str1);
				room->yGold = atoi(str2);
				break;
			case 'M':
				room->xMons = atoi(str1);
				room->yMons = atoi(str2);
				break;
			case 'h':
				room->xHero = atoi(str1);
				room->yHero = atoi(str2);
				break;
			case 'p':
				room->xPot = atoi(str1);
				room->yPot = atoi(str2);
				break;
			case 'w':
				room->xWep = atoi(str1);
				room->yWep = atoi(str2);
				break;
			case 'm':
				room->xMag = atoi(str1);
				room->yMag = atoi(str2);
				break;
			case 's':
				room->xSta = atoi(str1);
				room->ySta = atoi(str2);
		}
	}
}

void drawRoom(Room * room, Hero * hero, int xPos, int yPos)
{
	int i, j;

	for(i = xPos; i <= (xPos + room->xSize + 1); i++)
	{
		mvaddch(yPos, i, '-');
		mvaddch((yPos + room->ySize + 1), i, '-');
	}
	for(i = yPos; i <= (yPos + room->ySize + 1); i++)
	{
		mvaddch(i, xPos, '|');
		mvaddch(i, (xPos + room->xSize + 1), '|');
	}
	for(i = (xPos + 1); i <= xPos + room->xSize; i++)
	{
		for(j = (yPos + 1); j <= yPos + room->ySize; j++)
		{
			mvaddch(j, i, '.');
		}
	}

	if(room->xHero > 0)
	{
		hero->xPos = (xPos + room->xHero);
		hero->yPos = (yPos + room->yHero);
	}
	if(room->xGold > 0)
	{
		mvaddch(yPos + room->yGold, xPos + room->xGold, '*');
	}
	if(room->xMons > 0)
	{
		mvaddch(yPos + room->yMons, xPos + room->xMons, 'M');
	}
	if(room->xPot > 0)
	{
		mvaddch(yPos + room->yPot, xPos + room->xPot, 'p');
	}
	if(room->xMag > 0)
	{
		mvaddch(yPos + room->yMag, xPos + room->xMag, 'm');
	}
	if(room->xWep > 0)
	{
		mvaddch(yPos + room->yWep, xPos + room->xWep, 'w');
	}
	if(room->xSta > 0)
	{
		mvaddch(yPos + room->ySta, xPos + room->xSta, '%');
	}
	if(room->doorLocN > 0)
	{
		mvaddch(yPos, room->doorLocN + xPos, '+');
	}
	if(room->doorLocS > 0)
	{
		mvaddch(yPos + room->ySize + 1, room->doorLocS + xPos, '+');
	}
	if(room->doorLocE > 0)
	{
		mvaddch(room->doorLocE + yPos, xPos + room->xSize + 1, '+');
	}
	if(room->doorLocW > 0)
	{
		mvaddch(room->doorLocW + yPos, xPos, '+');
	}
}

void inputChoice(Hero * hero, int input)
{
	hero->xLast = hero->xPos;
	hero->yLast = hero->yPos;

	mvaddch(hero->yPos, hero->xPos, ' ');
	switch(input)
	{
		case 'w':
			hero->yPos -= 1;
			break;
		case 'a':
			hero->xPos -= 1;
			break;
		case 's':
			hero->yPos += 1;
			break;
		case 'd':
			hero->xPos += 1;
			break;
		case 'q':
			break;
		case 'p':
			hero->potions -= 1;
			hero->health += 5;
			mvaddstr(0, 0, "Drank a potion and gained 5 health.");
		default:
			mvaddstr(0, 0, "Incorrect input. See the README.txt for assistance.");
			break;
	}

	char s = mvinch(hero->yPos, hero->xPos) & A_CHARTEXT;
	if(s == '-' || s == '|')
	{
		hero->xPos = hero->xLast;
		hero->yPos = hero->yLast;
	}
	else if(s == '*')
	{
		mvaddstr(0, 0, "You got 10 gold.");
		hero->gold += 10;
	}
	else if(s == 'M')
	{
		hero->damage += hero->attack;
		hero->health -= 2;
		mvprintw(0, 0, "You hit the monster for %d damage.", hero->attack);
		if(hero->damage >= (10 + hero->monsHealth))
		{
			hero->monsHealth += 2;
			hero->damage = 0;
			mvprintw(0, 0, "You have killed the monster and gained 20 gold.");
			hero->gold += 20;
			mvaddch(hero->yPos, hero->xPos, '.');
		}
		hero->yPos = hero->yLast;
		hero->xPos = hero->xLast;
	}
	else if(s == 'p')
	{
		mvaddstr(0, 0, "You found a potion.");
		hero->potions += 1;
	}
	else if(s == 'w')
	{
		mvaddstr(0, 0, "You picked up a weapon.");
		hero->wep += 1;
		hero->attack += 1;
	}
	else if(s == 'm')
	{
		mvaddstr(0, 0, "You picked up magic.");
		hero->magic += 1;
		hero->attack += 1;
	}

	if(s == '%')
	{
		mvaddstr(0, 0, "You've found a staircase!");
	}
	else if(s == '+')
	{
		mvaddstr(0, 0, "You've opened a door.");
	}
	else if(s == '#')
	{
		mvaddstr(0, 0, "You're walking through a hallway.");
	}

	if(s == '%' || s == '+' || s == '#')
	{
		hero->onTile = s;
	}
	else
	{
		hero->onTile = '.';
	}
}

void drawHallways()
{
	int i, j, k;
	char s;

	for(i = 2; i <= 95; i++)
	{
		mvaddch(31, i, '#');
		for(j = 6; j <= 35; j++)
		{
			if((mvinch(j, i) & A_CHARTEXT) == '+')
			{
				if(j > 33)
				{
					for(k = (j - 1); k >= 33; k--)
					{
						s = mvinch(k, i) & A_CHARTEXT;
						if(s == '-' || s == '|')
						{
							mvaddch(k, i, s);
						}
						else
						{
							mvaddch(k, i, '#');
						}
					}
				}
				else if(j < 33)
				{
					for(k = (j + 1); k <= 33; k++)
					{
						s = mvinch(k, i) & A_CHARTEXT;
						if(s == '-' || s == '|')
						{
							mvaddch(k, i, s);
						}
						else
						{
							mvaddch(k, i, '#');
						}
					}
				}
			}
		}
	}
}
