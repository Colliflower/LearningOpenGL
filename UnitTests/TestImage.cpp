#include "pch.h"
#include "../LearningOpenGL/Image.h"

using namespace trv;

TEST(ImageTest, TestBadPath) {
	bool failed = false;

	try
	{
		Image<char> image = load_image<char>("");
	}
	catch (...)
	{
		failed = true;
	}

	ASSERT_TRUE(failed);
}