// Module:  CIS023_S2020_HW14-15 Miguel Antonio Logarta.cpp
// Author:  Miguel Antonio Logarta
// Date:    March 29, 2020
// Purpose: Practice using recursion to solve a problem
//          Perform recursion within an object
//          Use a recursive process to implement a recursive algorithm

#include "CIS023_S2020_HW14-15 Miguel Antonio Logarta.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

HWND hWnd_A;                // First number
HWND hWnd_B;                // Second number
HWND hWnd_N;                // Nth number
HWND hWnd_Output;           // Output box
HWND hWnd_btnFibonacci;     // Button to do conversion

// Exception class
class notValid {};

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

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
    LoadStringW(hInstance, IDC_CIS023S2020HW1415MIGUELANTONIOLOGARTA, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_CIS023S2020HW1415MIGUELANTONIOLOGARTA));

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
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CIS023S2020HW1415MIGUELANTONIOLOGARTA));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_CIS023S2020HW1415MIGUELANTONIOLOGARTA);
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
      CW_USEDEFAULT, 0, 210, 270, nullptr, nullptr, hInstance, nullptr);

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
            case BN_CLICKED:
                if (LOWORD(lParam) == (WORD)hWnd_btnFibonacci)      // Find number button
                {
                    try
                    {
                        TCHAR szA[TCHAR_SIZE];              // User input
                        TCHAR szB[TCHAR_SIZE];              // User input
                        TCHAR szN[TCHAR_SIZE];              // User input
                        TCHAR szOutput[TCHAR_SIZE];         // Output to the window
                        int iA = 0;                         // User input converted to int
                        int iB = 0;                         // User input converted to int
                        int iN = 0;                         // User input converted to int

                        GetWindowText(hWnd_A,               // Get user input
                            szA,                            // Destination TCHAR
                            100);                           // Size of TCHAR
                        GetWindowText(hWnd_B,               // Get user input
                            szB,                            // Destination TCHAR
                            100);                           // Size of TCHAR
                        GetWindowText(hWnd_N,               // Get user input
                            szN,                            // Destination TCHAR
                            100);                           // Size of TCHAR

                        // Convert user input to int
                        // Edit controls only accept digits
                        // _tstoi() converts non-numeric and blanks to 0, floors doubles too
                        iA = _tstoi(szA);
                        iB = _tstoi(szB);
                        iN = _tstoi(szN);

                        // Check for wrong inputs
                        if (iA <= 0 || iB <= 0 || iN <= 0)
                        {
                            throw notValid();
                        }

                        // Start calculating
                        Fibonacci FibonacciObject(hWnd_Output, iA, iB, iN);
                    }
                    catch (notValid)
                    {
                        // Create a message box telling the user made an input error
                        MessageBox(NULL,
                            TEXT("Inputs must be integers greater than 0"),
                            TEXT("INPUT ERROR"),
                            MB_ICONERROR);
                    }
                }
                break;
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
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_CREATE:
        {
        // Create prompts
        CreateWindow(TEXT("STATIC"),
            TEXT("First number:"),
            WS_VISIBLE | WS_CHILD,
            10, 15, 100, 20, hWnd, NULL, NULL, NULL);

        CreateWindow(TEXT("STATIC"),
            TEXT("Second number:"),
            WS_VISIBLE | WS_CHILD,
            10, 55, 120, 20, hWnd, NULL, NULL, NULL);

        CreateWindow(TEXT("STATIC"),
            TEXT("Nth number:"),
            WS_VISIBLE | WS_CHILD,
            10, 95, 120, 20, hWnd, NULL, NULL, NULL);

        // Create edit controls
        // ES_NUMBER to only accept numbers. Can't input decimals or negatives
        hWnd_A = CreateWindow(TEXT("EDIT"),
            NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
            120, 15, 60, 20, hWnd, NULL, NULL, NULL);

        hWnd_B = CreateWindow(TEXT("EDIT"),
            NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
            120, 55, 60, 20, hWnd, NULL, NULL, NULL);

        hWnd_N = CreateWindow(TEXT("EDIT"),
            NULL,
            WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_NUMBER,
            120, 95, 60, 20, hWnd, NULL, NULL, NULL);

        // Create Button
        hWnd_btnFibonacci = CreateWindow(TEXT("BUTTON"),
            TEXT("FIND NUMBER"),
            WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            30, 130, 120, 30, hWnd, NULL, NULL, NULL);

        // Create output 
        hWnd_Output = CreateWindow(TEXT("STATIC"),
            TEXT(""),
            WS_VISIBLE | WS_CHILD | WS_BORDER,
            40, 175, 100, 20, hWnd, NULL, NULL, NULL);

        }
        break;
    case WM_DESTROY:
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
