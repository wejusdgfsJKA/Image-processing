#include "Tests.h"
#include <assert.h>
#include "TestImage.h"
#include "TestRectangle.h"
#include "TestImageProcessing.h"
#include "TestDrawing.h"

void TestEverything() {
	TestRectangle();
	TestImage();
	TestImageProcessing();
	TestDrawing();
}