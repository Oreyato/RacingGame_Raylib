#ifndef MATHS_H
#define MATHS_H

namespace Maths {
	float degToRad(float degreeP) {
		return degreeP * PI / 180.0f;
	}

	float radToDeg(float radP) {
		return radP * 180.0f / PI;
	}
}

#endif // MATHS_H
