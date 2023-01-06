#ifndef LEVELS_H
#define LEVELS_H

#include <vector>

class Levels
{
public:
	Levels();

	void loadLevels();

	void setCurrentLevel(int levelNbP);

	std::vector<int>& getCurrentLevel() { return currentLevel; } 
	std::vector<int>& getLevel(int levelNbP);

private:
	std::vector<std::vector<int>> levels;

	std::vector<int> currentLevel;

	std::vector<int> level_000;
	std::vector<int> level_001;
};

#endif // LEVELS_H