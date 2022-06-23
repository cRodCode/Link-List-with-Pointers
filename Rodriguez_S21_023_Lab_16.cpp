// Project:     Rodriguez_S21_023_Lab_16
// Author:      Carlos Rodriguez
// Date:        April 16, 2021
// Purpose:     Create a linked list of object pointers.
//              Load, expand, and traverse a linked list without regard to the number of nodes.
//              Emptyand delete a linked list
//

#include "framework.h"
#include "Rodriguez_S21_023_Lab_16.h"

#define MAX_LOADSTRING 100
#define WM_TIMER_MOVE 252
#define WM_TIMER_CREATE 2002

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name


TCHAR szCounter[TCHAR_SIZE];                    // TChar counter to display

// linked list node pointers
BallClass* firstNode = nullptr,                 // top of list
         * lastNode = nullptr,                  // bottom of list
         * currentNode = nullptr;               // current node

int iNode = 1;                                  // which node is being displayed
int iCount = 0;                                 // count of how many nodes loaded

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void Next(HWND);                                // move to next node

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_RODRIGUEZS21023LAB16, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_RODRIGUEZS21023LAB16));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_RODRIGUEZS21023LAB16));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_RODRIGUEZS21023LAB16);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...

            // get window client rectangle sizes
            RECT rClient;                                 // windows rectangle
            GetClientRect(hWnd, &rClient);                // fill rClient with window coordinates
            int cx = rClient.right - rClient.left;        // cx = width of window
            int cy = rClient.bottom - rClient.top;        // cy = height of window

            // create memory device
            HDC memdc = CreateCompatibleDC(hdc);                             // create memory copy of dc
            unsigned bpp = GetDeviceCaps(hdc, BITSPIXEL);                    // discover color depth
            HBITMAP hBmp = CreateBitmap(cx, cy, 1, bpp, NULL);               // create bitmap for background
            HBITMAP hTmpBmp = (HBITMAP)SelectObject(memdc, (HGDIOBJ)hBmp);   // fill memory dc

            // draw GDI background
            FillRect(memdc, &rClient, (HBRUSH)GetStockObject(WHITE_BRUSH));

            // run through list and paint each ball
            currentNode = firstNode;                   // start at beginning of list

            while (currentNode != nullptr)             // run through list
            {
                currentNode->Draw(memdc);              // paint the GDI element
                currentNode = currentNode->GetNext();  // advance to the next node
            }

            //update the main DC
            BitBlt(hdc, 0, 0, cx, cy, memdc, 0, 0, SRCCOPY); // blt memory dc to window dc

            // clean up
            SelectObject(memdc, (HGDIOBJ)hTmpBmp);    // return to original dc
            DeleteDC(memdc);                          // delete temp dc
            DeleteObject(hBmp);                       // delete object

            // display counter
            TextOut(                                  // display text on window
                hdc,                                  // handle to the device context
                10, 10,                               // location
                szCounter,                            // TChar to display
                lstrlen(szCounter));                  // length of TCHAR

            EndPaint(hWnd, &ps);
        }
        break;
    case WM_TIMER:
    {
        if (wParam == WM_TIMER_MOVE)                  // move timer
        {
            currentNode = firstNode;                  // start at beginning of list

            while (currentNode != nullptr)            // run through list
            {
                currentNode->Move(hWnd);              // move the ball

                InvalidateRect(hWnd,                  // force WM_PAINT message
                    NULL,                             // entire window
                    FALSE);                           // false for non-flicker

                currentNode = currentNode->GetNext(); // advance to the next node
            }
        }

        // create objects
        if (wParam == WM_TIMER_CREATE)
        {
            BallClass* newNode = new BallClass(hWnd);   // create object

            // append new node to linked list
            if (firstNode == nullptr)					// if this is the first node
                firstNode = newNode;					//      set new node as first node
            else                                        // not the first node
            {
                lastNode->SetNext(newNode);             // last node points to new node
            }

            lastNode = newNode;                         // new node is new last node

            iCount++;   // one more node loaded

            Int2TCHAR(iCount, szCounter);               // convert counter number to TCHAR
        }
    }
        break;
    case WM_CREATE:

        // create timer
        SetTimer(hWnd, WM_TIMER_CREATE, 100, NULL);    // 100 millisecond delay instantiates 
        SetTimer(hWnd, WM_TIMER_MOVE, 10, NULL);       // 10 millisecond delay motion

        break;

    case WM_DESTROY:
        // delete linked list
        if (currentNode)							// if no currentNode, then list is empty
        {
            lastNode->SetNext(nullptr);				// null last next pointer to prevent delete of empty node

            BallClass* tempNode = nullptr;		    // temporary node pointer
            currentNode = firstNode;				// start at top of list
            while (currentNode != nullptr)			// loop until entire list deleted
            {
                tempNode = currentNode->GetNext();	// save pointer to next node
                delete currentNode;					// delete the current node
                currentNode = tempNode;				// move to the next node
            }
        }
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}

// move forward one node
void Next(HWND hWnd)
{
    try
    {
        if (currentNode == nullptr)					// if this is the first time a button is clicked
            currentNode = firstNode;				// get the first node
        else
            currentNode = currentNode->GetNext();	// otherwise, load the next node

        if (currentNode == nullptr)					// ran off the end of the list
            throw 1;

        iNode++; // next node

        if (iNode > iCount)
            iNode = 1;
        InvalidateRect(hWnd, NULL, TRUE);			// force paint

    }
    catch (int)
    {
        MessageBox(NULL,							// display error message
            TEXT("Node is empty."),
            TEXT("List Error"),
            MB_ICONERROR);
    }
}