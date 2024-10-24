// Dat154O1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Dat154O1.h"
#include<vector>
#include<string>

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    PROBABILITY(HWND, UINT, WPARAM, LPARAM);

int p = rand() % 100;
static int pw = 10;
static int pn = 10;


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
    LoadStringW(hInstance, IDC_Dat154O1, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance(hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_Dat154O1));

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

    return (int)msg.wParam;
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

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDC_Dat154O1));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_Dat154O1);
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

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
    static int aX = 525;
    static int aY = 190;

    static int bX = 465;
    static int bY = 415;

    static int wY = 360;
    static int nX = 595;

    static int timerLights = 0;
    static int state = 0;

    static bool wGo = true;
    static bool nGo = false;

    static int wCount = 0;
    static int nCount = 0;

    static int intervalW = 0;
    static int intervalN = 0;

    int red = rand() % 255;
    int green = rand() % 255;
    int blue = rand() % 255;



    static std::vector<int> xPos;
    static std::vector<int> yPos;
    static std::vector<HBRUSH> wColor;
    static std::vector<HBRUSH> nColor;

    //counter to increase speed of cars
    static int nSpeedcounter = 0;
    static int wSpeedcounter = 0;
    static int counter = 0;

    int waitingCarsW = 0;
    int waitingCarsN = 0;

    RECT screen;
    GetClientRect(hWnd, &screen);

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
        case IDD_PROBABILITY:
            DialogBox(hInst, MAKEINTRESOURCE(IDD_PROBABILITY), hWnd, PROBABILITY);
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
        HDC phdc = BeginPaint(hWnd, &ps);

        HDC hdc = CreateCompatibleDC(phdc);
        HBITMAP bmp = CreateCompatibleBitmap(phdc, screen.right, screen.bottom);
        SelectObject(hdc, bmp);

        HBRUSH redBrush = CreateSolidBrush(RGB(255, 0, 0));
        HBRUSH greenBrush = CreateSolidBrush(RGB(0, 255, 0));
        HBRUSH blackBrush = CreateSolidBrush(RGB(0, 0, 0));
        HBRUSH greyBrush = CreateSolidBrush(RGB(100, 100, 100));
        HBRUSH lightGreyBrush = CreateSolidBrush(RGB(200, 200, 200));
        HBRUSH yellowBrush = CreateSolidBrush(RGB(255, 255, 0));
        HBRUSH whiteBrush = CreateSolidBrush(RGB(255, 255, 255));
        HBRUSH blueBrush = CreateSolidBrush(RGB(0, 0, 255));
        HBRUSH randomBrush = CreateSolidBrush(RGB(red, green, blue));

        HGDIOBJ hOrg = SelectObject(hdc, lightGreyBrush);

        Rectangle(hdc, 0, 0, screen.right, screen.bottom);

        SelectObject(hdc, whiteBrush);
        Rectangle(hdc, 0, 0, 575, 300);
        Rectangle(hdc, 675, 0, screen.right, 300);
        Rectangle(hdc, 0, 400, 575, screen.bottom);
        Rectangle(hdc, 675, 400, screen.right, screen.bottom);

        //trafikklys:
        SelectObject(hdc, blackBrush);

        RoundRect(hdc, aX, aY, aX + 35, aY + 95, 8, 8); //svart bakgrunn 1. kvad
        RoundRect(hdc, bX, bY, bX + 95, bY + 35, 8, 8); //svart bakrunn 3. kvad

        //lysene:
        SelectObject(hdc, greyBrush);

        Ellipse(hdc, aX + 5, aY + 5, aX + 30, aY + 30); //a1
        Ellipse(hdc, aX + 5, aY + 35, aX + 30, aY + 60); //a2
        Ellipse(hdc, aX + 5, aY + 65, aX + 30, aY + 90);//a3

        Ellipse(hdc, bX + 5, bY + 5, bX + 30, bY + 30); //b1
        Ellipse(hdc, bX + 35, bY + 5, bX + 60, bY + 30); //b2
        Ellipse(hdc, bX + 65, bY + 5, bX + 90, bY + 30); //b3

        if (state == 0)
        {
            SelectObject(hdc, greenBrush);
            Ellipse(hdc, bX + 65, bY + 5, bX + 90, bY + 30); //b3
            SelectObject(hdc, redBrush);
            Ellipse(hdc, aX + 5, aY + 5, aX + 30, aY + 30); //a1
        }
        if (state == 1)
        {
            SelectObject(hdc, redBrush);
            Ellipse(hdc, aX + 5, aY + 5, aX + 30, aY + 30); //a1
            SelectObject(hdc, yellowBrush);
            Ellipse(hdc, aX + 5, aY + 35, aX + 30, aY + 60); //a2
            Ellipse(hdc, bX + 35, bY + 5, bX + 60, bY + 30); //b2
        }
        if (state == 2)
        {
            SelectObject(hdc, greenBrush);
            Ellipse(hdc, aX + 5, aY + 65, aX + 30, aY + 90);//a3
            SelectObject(hdc, redBrush);
            Ellipse(hdc, bX + 5, bY + 5, bX + 30, bY + 30); //b1
        }
        if (state == 3)
        {
            SelectObject(hdc, yellowBrush);
            Ellipse(hdc, aX + 5, aY + 35, aX + 30, aY + 60); //a2
            Ellipse(hdc, bX + 35, bY + 5, bX + 60, bY + 30); //b2
            SelectObject(hdc, redBrush);
            Ellipse(hdc, bX + 5, bY + 5, bX + 30, bY + 30); //b1
        }

        //pw:
        std::wstring pwText = std::to_wstring(pw) + L"%";
        TextOut(hdc, bX - 40, bY + 10, pwText.c_str(), pwText.length());

        //pn:           
        std::wstring pnText = std::to_wstring(pn) + L"%";
        TextOut(hdc, aX, aY - 20, pnText.c_str(), pnText.length());

        for (std::size_t i = 0; i < xPos.size(); i++) {
            SelectObject(hdc, wColor[i]);
            Rectangle(hdc, xPos[i] - 50, wY, xPos[i], wY + 20);
        }



        for (std::size_t i = 0; i < yPos.size(); i++) {
            SelectObject(hdc, nColor[i]);
            Rectangle(hdc, nX, yPos[i] - 50, nX + 20, yPos[i]);
        }

        for (std::size_t i = 0; i < xPos.size(); i++) {
            //COMMENTS: logic for when to delete paintbrush
            if (xPos[i] > screen.right + 50) {
                xPos.erase(xPos.begin() + i);
                DeleteObject(wColor[i]);
                wColor.erase(wColor.begin() + i);
            }

        }
        for (std::size_t i = 0; i < yPos.size(); i++) {
            //COMMENTS: logic for when to delete paintbrush
            if (yPos[i] > screen.bottom + 50) {
                yPos.erase(yPos.begin() + i);
                DeleteObject(nColor[i]);
                nColor.erase(nColor.begin() + i);
            }
        }

        SelectObject(hdc, hOrg);
        DeleteObject(redBrush);
        DeleteObject(greenBrush);
        DeleteObject(greyBrush);
        DeleteObject(blackBrush);
        DeleteObject(lightGreyBrush);
        DeleteObject(yellowBrush);
        DeleteObject(whiteBrush);
        DeleteObject(blueBrush);
        DeleteObject(randomBrush);

        BitBlt(phdc, 0, 0, screen.right, screen.bottom, hdc, 0, 0, SRCCOPY);

        DeleteObject(bmp);
        DeleteDC(hdc);

        EndPaint(hWnd, &ps);
    }
    break;

    case WM_KEYDOWN:
    {
        if (wParam == VK_RIGHT)
        {
            if (pw < 100) {
                pw = pw + 10;
            }
        }
        if (wParam == VK_LEFT)
        {
            if (pw > 9) {
                pw = pw - 10;
            }
        }
        if (wParam == VK_UP)
        {
            if (pn < 100) {
                pn = pn + 10;
            }
        }
        if (wParam == VK_DOWN)
        {
            if (pn > 9) {
                pn = pn - 10;
            }
        }
        break;
    }

    case WM_LBUTTONDOWN:
    {

        if (xPos.size() > 0) {
            if (xPos[xPos.size() - 1] > 70) {
                xPos.push_back(0);
                wColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
            }
        }
        else {
            xPos.push_back(0);
            wColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
        }
        break;
    }

    case WM_RBUTTONDOWN:
    {
        if (yPos.size() > 0) {
            if (yPos[yPos.size() - 1] > 70) {
                yPos.push_back(0);
                nColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
            }
        }
        else {
            yPos.push_back(0);
            nColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
        }
        break;
    }

    case WM_CREATE:
        SetTimer(hWnd, 0, 1000, 0);

        //COMMENTS: Timer for counter 
        SetTimer(hWnd, 1, 10, 0);
        break;

    case WM_TIMER:
    {
        //COMMENTS: Increases counter when the the second time i.e the timer with id is "active"
        if (wParam == 1) {

            counter++;
        }

        //West:

        if (counter == 0 || counter > 60) {
            if (xPos.size() > 0) { //er det noen biler i vektoren
                if (xPos[xPos.size() - 1] > 70) { //sjekk om det ikke er en bil i veien
                    if (p < pw) { //sjekk om det skal spawne en bil
                        xPos.push_back(0);
                        wColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
                        counter = 1;
                    }
                }
            }
            else { //hvis det ikke er biler allerede
                if (p < pw) { //sjekk om det skal spawne
                    xPos.push_back(0);
                    wColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
                    counter = 1;
                }
            }
        }

        //North:

        if (counter == 0 || counter > 60) {

            if (yPos.size() > 0) {
                if (yPos[yPos.size() - 1] > 70) {

                    if (p < pn) {
                        yPos.push_back(0);
                        nColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
                        counter = 1;
                    }
                }
            }
            else {
                if (p < pn) {
                    yPos.push_back(0);
                    nColor.push_back(CreateSolidBrush(RGB(red, green, blue)));
                    counter = 1;
                }
            }

        }

        //Logikk for biler
        //FRA VEST:
        for (std::size_t i = 0; i < xPos.size(); i++) {

            if (xPos[i] < 545 - waitingCarsW * 60) {
                xPos[i] += counter;
            }
            else {
                if (wGo) {
                    xPos[i] += counter;
                }
                else {
                    if (xPos[i] > 545) {

                        xPos[i] += counter;
                        //COMMENTS moved logic for deleting into VM_PAINT
                    }
                    else {

                        waitingCarsW++;

                    }
                }
            }
        }


        //Logikk for biler
        //FRA NORD:
        for (std::size_t i = 0; i < yPos.size(); i++) {

            if (yPos[i] < 270 - waitingCarsN * 60) {
                yPos[i] += counter;
            }
            else {
                if (nGo) {
                    yPos[i] += counter;
                }
                else {
                    if (yPos[i] > 270) {
                        //COMMENTS moved logic for deleting into VM_PAINT
                        yPos[i] += counter;

                    }
                    else {

                        waitingCarsN++;
                    }
                }
            }
        }
        //COMMENTS: resets counter
        //THE cars will go to infinity, and beyond otherwise.
        counter = 0;


        timerLights++;
        if (timerLights == 0) {
            state = 0;
            nGo = false;
            wGo = true;
        }
        if (timerLights == 300) {
            state = 1;
            nGo = false;
            wGo = false;
        }
        if (timerLights == 450) {
            state = 2;
            nGo = true;
            wGo = false;
        }
        if (timerLights == 750) {
            state = 3;
            nGo = false;
            wGo = false;
        }
        if (timerLights == 900) {
            timerLights = 0;
            state = 0;
            nGo = false;
            wGo = true;
        }
        InvalidateRect(hWnd, 0, false);

        break;
    }
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



INT_PTR CALLBACK PROBABILITY(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:

    {

        return (INT_PTR)TRUE;
    }

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            //COMMENTS: Retrieves values from input

            //COMMENTS: Uses this to determine whether or not the retrieved value is a number
            BOOL isNum = false;
            //COMMENTS: IDC_PROBWIN refers to the probability input, &isNum is a reference to the bool, and true means that the input has to be an integer
            int probWest = GetDlgItemInt(hDlg, IDC_PROBWIN, &isNum, true);
            int probNorth = GetDlgItemInt(hDlg, IDC_PROBNIN, &isNum, true);

            //COMMENTS: NEED to set both values, or they won't change


            if (isNum) {
                //COMMENTS: If the value "isNum" check whether or not the value is less than 100%
                if (probWest <= 100) {
                    pw = probWest;

                }
                if (probNorth <= 100) {
                    pn = probNorth;

                }
            }
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
