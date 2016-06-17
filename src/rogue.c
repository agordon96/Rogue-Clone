/***********************************rogue.c***********************************
Student Name: Aaron Gordon          Student Number: 0884023
Date: March 4th, 2015               Course Name: CIS*2500 Intermediate Programming
I have exclusive control over this submission via my password.
By including this statement in this header comment, I certify that:
        1) I have read and understood the University policy on academic integrity;
        2) I have completed the Computing with Integrity Tutorial on Moodle; and
        3) I have achieved at least 80% in the Computing with Integrity Self Test.
I assert that this work is my own. I have appropriately acknowledged any and all material
(data, images, ideas or words) that I have used, whether directly quoted or paraphrased.
Furthermore, I certify that this assignment was prepared by me specifically for this course.
******************************************************************************/

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include "rogue.h"

int main(int argc, char * argv[])
{
    FILE * fp;
	char line[6][256] = {"", "", "", "", "", ""};
	char ch, input;
	int i;

	Hero * hero = malloc(sizeof(Hero));
	Room * room1 = malloc(sizeof(Room));
	Room * room2 = malloc(sizeof(Room));
	Room * room3 = malloc(sizeof(Room));
	Room * room4 = malloc(sizeof(Room));
	Room * room5 = malloc(sizeof(Room));
	Room * room6 = malloc(sizeof(Room));

	hero->health = 10;
	hero->attack = 1;
	hero->damage = 0;
	hero->monsHealth = 0;

	initscr();
	refresh();

	if(argc < 2)
	{
		printf("No argument inputted. Exiting Rogue...\n");
		exit(0);
	}

	fp = fopen(argv[1], "r");
    if(fp == NULL)
	{
		printf("Error opening file. Exiting Rogue...\n");
		exit(0);
	}

	for(i = 0; i < 6; i++)
	{
		while((ch = fgetc(fp)) != '\n')
		{
			line[i][strlen(line[i])] = ch;
		}

		switch(i)
		{
			case 0:
				assignValues(room1, line[i]);
				drawRoom(room1, hero, 5, 3);
				break;
			case 1:
				assignValues(room2, line[i]);
				drawRoom(room2, hero, 35, 3);
				break;
			case 2:
				assignValues(room3, line[i]);
				drawRoom(room3, hero, 65, 3);
				break;
			case 3:
				assignValues(room4, line[i]);
				drawRoom(room4, hero, 5, 33);
				break;
			case 4:
				assignValues(room5, line[i]);
				drawRoom(room5, hero, 35, 33);
				break;
			case 5:
				assignValues(room6, line[i]);
				drawRoom(room6, hero, 65, 33);
				break;
		}
	}
	drawHallways();

	while(input != 'q')
	{
		if(hero->health <= 0)
		{
			hero->health = 0;
			mvprintw(0, 0, "You have died. A monster killed you and for some reason you didn't use a potion. Press any key...");
			mvprintw(62, 0, "            Gold: %d         Potions: %d            Health: %d", hero->gold, hero->potions, hero->health);
			refresh();
			getch();
			break;
		}
		mvaddch(hero->yLast, hero->xLast, hero->onTile);
		mvaddch(hero->yPos, hero->xPos, '@');
		mvprintw(62, 0, "                                                                    ");
		mvprintw(62, 0, "            Gold: %d         Potions: %d            Health: %d", hero->gold, hero->potions, hero->health);
		move(hero->yPos, hero->xPos);
		refresh();
		input = getchar();
		mvprintw(0, 0, "                                                     ");
		inputChoice(hero, input);
	}
	clear();
	move(0, 0);
	mvprintw(0, 0, "Game will now end.");
	mvprintw(1, 0, "You earned %d gold and %d potion(s) in your adventure.", hero->gold, hero->potions);
	mvprintw(2, 0, "You found %d weapon(s) and discovered %d magic too!", hero->wep, hero->magic);
	mvprintw(3, 0, "Thanks for playing! Type any key to exit the game.");

	free(room1);
	free(room2);
	free(room3);
	free(room4);
	free(room5);
	free(room6);
	free(hero);

	noecho();
	cbreak();
	refresh();
	getch();
	endwin();
	fclose(fp);

    return 0;
}
