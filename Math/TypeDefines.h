#pragma once

#ifndef INTEGRIAN2D_TYPEDEFINES_H
#define INTEGRIAN2D_TYPEDEFINES_H

#include "Point.h"
#include "Vector.h"
#include "Point2.h"
#include "Vector2.h"
#include "Rect.h"

namespace Integrian2D
{
	typedef Point<2, float> Point2f;
	typedef Vector<2, float> Vector2f;
	typedef Rect<float> Rectf;
}

#endif // !INTEGRIAN2D_TYPEDEFINES_H