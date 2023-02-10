#ifndef LEVELS_H
#define LEVELS_H

#include <vector>

struct Level
{
	Level() {};
	Level(int numP, std::vector<int> descP, int rowNbP, int colNbP) :
		number{ numP },
		description{ descP },
		rowNb{ rowNbP },
		colNb{ colNbP }
	{
		size = rowNb * colNb;
	};

	int number;
	std::vector<int> description;
	int rowNb;
	int colNb;
	int size;
};

class Levels
{
public:
	Levels();

	void setCurrentLevel(int levelNbP);

	Level& getCurrentLevel() { return currentLevel; } 
	Level& getLevel(int levelNbP);

	Level getFilledLevel(int widthP, int heightP, int typeP);

private:
	std::vector<Level> levels;

	Level currentLevel;
};

#endif // LEVELS_H