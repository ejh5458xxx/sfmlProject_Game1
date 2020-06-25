#include "Includes/myRectangle.h"
#include <iostream>

void myRectangle::set_values(int iWidth, int iHeight)
{
	width = iWidth;
	height = iHeight;
}

int myRectangle::area(void)
{
	return width * height;
}
