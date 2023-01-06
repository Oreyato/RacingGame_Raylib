#ifndef MATHSUTILS_H
#define MATHSUTILS_H

namespace MathsUtils {
	float degToRad(float degreeP);

	float radToDeg(float radP);

	bool isOdd(int numP);

	typedef struct Vector2Int {
		int x;
		int y;
	} Vector2Int;
}

#endif // MATHSUTILS_H
