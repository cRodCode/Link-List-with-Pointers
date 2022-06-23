// Module:      BallClass
// Author:      Carlos Rodriguez
// Date:        April 17, 2021
// Purpose:     BallClass implementation file
//

#include "framework.h"
#include "Rodriguez_S21_023_Lab_16.h"


BallClass::BallClass(HWND hWnd)
{
	// get client window dimensions
	RECT rClient;
	GetClientRect(hWnd, &rClient);					// window

	// set start location in the middle
	rDim.left = rClient.right / 2;
	rDim.top = rClient.bottom / 2;

	// set ball size
	int ballSize = GetRandomInt(10, 25);			// balls are round
	rDim.right = rDim.left + ballSize;
	rDim.bottom = rDim.top + ballSize;

	// set initial speed and direction
	pSpeed.x = GetRandomInt(-20, 20);				// horizontal
	pSpeed.y = GetRandomInt(-20, 20);				// verticle

	// pick a color
	r = GetRandomInt(0, 255);						// red
	g = GetRandomInt(0, 255);						// green
	b = GetRandomInt(0, 255);						// blue

	Next = nullptr;									// initialize point to next node
}


void BallClass::Draw(HDC hdc)
{
	// create brushes
	HBRUSH brush, oldBrush;
	brush = CreateSolidBrush(RGB(r, g, b));
	oldBrush = (HBRUSH)SelectObject(hdc, brush);

	// draw spheare
	Ellipse(hdc, rDim.left, rDim.top, rDim.right, rDim.bottom);

	// release brushes
	SelectObject(hdc, oldBrush);
	DeleteObject(brush);
}

void BallClass::Move(HWND hWnd)
{
	// get client window dimensions
	RECT rClient;
	GetClientRect(hWnd, &rClient);					// window

	// check for collision
	if (rDim.left <= 0)								// did ball hit left wall
		pSpeed.x = abs(pSpeed.x);
	if (rDim.right >= rClient.right)				// did ball hit right wall
		pSpeed.x = abs(pSpeed.x) * -1;
	if (rDim.top <= 0)								// did ball hit top
		pSpeed.y = abs(pSpeed.y);
	if (rDim.bottom >= rClient.bottom)				// did ball hit bottom
		pSpeed.y = abs(pSpeed.y) * -1;

	// move according to speed
	rDim.top += pSpeed.y;
	rDim.left += pSpeed.x;
	rDim.bottom += pSpeed.y;
	rDim.right += pSpeed.x;
}

void BallClass::SetNext(BallClass* Node)
{
	Next = Node;
}

BallClass* BallClass::GetNext()
{
	return Next;
}

// return random integer between iMin and iMax
int BallClass::GetRandomInt(int iMin, int iMax)
{
	random_device rd;								// non-deterministic generator
	mt19937 gen(rd());								// to seed mersenne twister.
	uniform_int_distribution<> dist(iMin, iMax);	// distribute results inside center rect

	return dist(gen);								// return random # between iMin and iMax
}