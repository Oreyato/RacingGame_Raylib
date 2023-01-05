#ifndef LEVELS_H
#define LEVELS_H

#include <vector>

class Levels
{
public:
	Levels();

	void loadLevels();

	const std::vector<int> getLevel(float levelNbP);

private:
	std::vector<std::vector<int>> levels;

	std::vector<int> LEVEL_000;
	std::vector<int> LEVEL_001;
};

#endif // LEVELS_H