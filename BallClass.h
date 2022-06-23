// Module:      BallClass
// Author:      Carlos Rodriguez
// Date:        April 17, 2021
// Purpose:     BallClass header file
//

#pragma once
class BallClass
{
public:
	BallClass(HWND);						// constructor

	void Draw(HDC);							// answer WM_PAINT
	void Move(HWND);						// update location

	// mutators and accessors for linked pointers
	void SetNext(BallClass*);				// set Next (address of next node)
	BallClass* GetNext();					// return Next (address of next node)

private:
	RECT rDim;								// location and size in double
	POINT pSpeed;							// speed and direction
	int r, g, b;							// color

	int GetRandomInt(int, int);				// return random integer

	BallClass* Next;						// address of next node
};

