#include "Levels.h"

Levels::Levels() {
    levels.emplace_back(Level{
        0,
        {
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
            7,	1,	8,	7,	0,	7,	0,	7,	0,	7,	1,	7,
            7,	1,	7,	8,	7,	0,	7,	0,	7,	0,	1,	7,
            7,	1,	0,	7,	0,	7,	0,	7,	0,	7,	1,	7,
            7,	1,	7,	0,	7,	0,	7,	0,	7,	0,	1,	7,
            7,	1,	0,	7,	0,	7,	0,	7,	0,	7,	1,	7,
            7,	1,	7,	0,	7,	0,	7,	0,	7,	0,	1,	7,
            7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
        },
        10,
        12
    });
    
    levels.emplace_back(Level{
        1,
        {
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	7,	1,	1,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	1,	1,	0,	0,	0,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	1,	0,	0,	0,	0,	0,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	1,	0,	0,	0,	0,	0,	0,	1,	7,	7,	7,	7,	1,	1,	1,	7,
            7,	7,	7,	7,	7,	7,	1,	0,	0,	1,	0,	0,	0,	1,	7,	7,	1,	1,	1,	0,	4,	7,
            7,	7,	7,	7,	1,	1,	1,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	4,	7,
            7,	7,	7,	1,	1,	0,	0,	0,	0,	1,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	4,	7,
            7,	7,	1,	1,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	7,
            7,	7,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	1,	1,	7,	7,
            7,	7,	1,	0,	0,	0,	1,	1,	1,	7,	7,	1,	1,	0,	0,	0,	0,	1,	1,	7,	7,	7,
            7,	7,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	1,	1,	1,	1,	1,	1,	7,	7,	7,	7,
            7,	1,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	1,	0,	0,	0,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	1,	0,	8,	8,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	1,	1,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
        },
        18,
        22
    });

    levels.emplace_back(Level {
        2,
        {
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	7,	7,	7,	1,	1,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	7,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	7,	7,	7,	7,
            7,	7,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	7,	7,	7,
            7,	1,	1, 	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	7,	7,
            7,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	1,	1,	0,	0,	0,	1,	7,	7,
            7,	1,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	7,
            7,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	7,
            7,	1,	8,	8,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	7,
            7,	1,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	1,	0,	0,	0,	1,	7,
            7,	1,	4,	4,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	0,	1,	7,	7,
            7,	1,	0,	0,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	7,	7,
            7,	1,	0,	0,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	7,	7,
            7,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	7,	7,	7,
            7,	7,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	7,	7,	1,	1,	1,	7,	7,	7,	7,
            7,	7,	7,	1,	1,	1,	1,	1,	1,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
            7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
        },
        17,
        22
    });

    levels.emplace_back(Level{
    3,
    {
        7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	7,	7,	1,	1,	0,	0,	0,	0,	0,	1,	1,	1,	1,	7,	7,	7,	7,
        7,	7,	7,	1,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	7,	7,	7,
        7,	7,	1,	1, 	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	1,	7,	7,
        7,	1,	0,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	1,	1,	0,	0,	0,	1,	7,	7,
        7,	1,	0,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	7,
        7,	1,	0,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	1,	7,
        7,	7,	1,	8,	8,	1,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	0,	1,	0,	0,	0,	1,	7,
        7,	7,	1,	0,	0,	1,	0,	0,	0,	1,	1,	1,	1,	1,	1,	0,	0,	1,	0,	0,	0,	1,	7,
        7,	7,	1,	4,	4,	1,	0,	0,	0,	0,	0,	0,	0,	1,	1,	0,	0,	1,	0,	0,	1,	7,	7,
        7,	7,	1,	0,	0,	1,	1,	0,	0,	0,	0,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	7,	7,
        7,	7,	1,	0,	0,	0,	1,	1,	1,	1,	1,	0,	0,	0,	1,	0,	0,	0,	0,	0,	1,	7,	7,
        7,	7,	1,	0,	0,	0,	0,	1,	1,	1,	1,	0,	0,	0,	1,	1,	0,	0,	0,	1,	7,	7,	7,
        7,	7,	7,	1,	0,	0,	0,	1,	1,	1,	0,	0,	0,	1,	7,	7,	1,	1,	1,	7,	7,	7,	7,
        7,	7,	7,	7,	1,	0,	0,	0,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	1,	0,	0,	0,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	1,	0,	0,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	1,	0,	0,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	1,	0,	0,	0,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	7,	1,	1,	1,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,
        7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7,	7
    },
    23,
    23
    });
}

void Levels::setCurrentLevel(int levelNbP)
{
    currentLevel = levels[levelNbP];
}

Level& Levels::getLevel(int levelNbP) {

    return levels[levelNbP];
}

Level& Levels::getFilledLevel(int widthP, int heightP, int typeP)
{
    int vectorSize = widthP * heightP;
    std::vector<int> filledVector = std::vector<int>( vectorSize, typeP );

    Level level {
    -1,
    filledVector,
    heightP,
    widthP
    };

    return level;
}