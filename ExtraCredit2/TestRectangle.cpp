#include "TestRectangle.h"
#include "Rectangle.h"
#include <assert.h>

void TestRectangleTranslate() {
	Rectangle r1{ 0,3,6,3 };
	assert(r1 - Point(-1, 6) == Rectangle(1, -3, 6, 3));
	assert(r1 + Point(-1, 6) == Rectangle(-1, 9, 6, 3));
}

void TestRectangleOther() {
	Rectangle r1{ 0,3,6,3 }, r2{ 2,1,5,2 }, r3{ 0,1,5,2 };
	assert((r1 & r2) == Rectangle(2, 1, 4, 1));
	assert((r1 & r1) == r1);
	assert((r2 & r1) == Rectangle(2, 1, 4, 1));
	assert((r1 & r3) == Rectangle(0, 1, 5, 1));
	assert((r1 | r2) == Rectangle(0, 3, 7, 4));
	assert((r2 | r1) == Rectangle(0, 3, 7, 4));
	assert((r1 | r1) == Rectangle(0, 3, 6, 3));
	assert((r3 | r2) == Rectangle(0, 1, 7, 2));
}

void TestRectangle() {
	TestRectangleTranslate();
	TestRectangleOther();
}