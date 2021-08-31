#pragma once

#include "Point.h"
#include "Vector.h"
#include "Point2.h"
#include "Vector2.h"
#include "Point3.h"
#include "Rect.h"
#include "RGBColour.h"
#include "Matrix.h"

namespace Integrian2D
{
	typedef Point<2, float> Point2f;
	typedef Point<3, float> Point3f;
	typedef Vector<2, float> Vector2f;
	typedef Rect<float> Rectf;
	typedef Matrix<2, 2, float> Matrix2x2;
	typedef Matrix<3, 3, float> Matrix3x3;
}

