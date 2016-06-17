typedef struct
{
	int xPos;
	int yPos;
	int xLast;
	int yLast;
	int gold;
	int potions;
	int magic;
	int wep;
	int room;
	int onTile;
	int damage;
	int attack;
	int health;
	int monsHealth;
} Hero;

typedef struct
{
	int xSize;
	int ySize;
	int xGold;
	int yGold;
	int xMons;
	int yMons;
	int xHero;
	int yHero;
	int xPot;
	int yPot;
	int xWep;
	int yWep;
	int xMag;
	int yMag;
	int xSta;
	int ySta;
	int doorLocN;
	int doorLocS;
	int doorLocE;
	int doorLocW;
} Room;

void assignValues(Room * room, char line[]);
void drawRoom(Room * room, Hero * hero, int xPos, int yPos);
void inputChoice(Hero * hero, int input);
void drawHallways();
