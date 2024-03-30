#include "Tests.h"
#include <assert.h>
#include "TestImage.h"
#include "TestRectangle.h"
#include "TestImageProcessing.h"

void TestEverything() {
	TestRectangle();
	TestImage();
	TestImageProcessing();
}