#if defined(UNICODE) && !defined(_UNICODE)
    #define _UNICODE
#elif defined(_UNICODE) && !defined(UNICODE)
    #define UNICODE
#endif

#include "project.h"
#include "game.h"

#include <tchar.h>
#include <windows.h>
#include <CommCtrl.h>
#include <math.h>
#include <objbase.h>
#include <string.h>
#include <iostream>





/*  Declare Windows procedure  */
LRESULT CALLBACK WindowProcedure (HWND, UINT, WPARAM, LPARAM);

void AddControl(HWND hwnd);

float scale = 3;
Game simon_game;
HBITMAP hColorImage, hBlackImage;
HWND hWndScore;

/*  Make the class name into a global variable  */
TCHAR szClassName[ ] = _T("CodeBlocksWindowsApp");

int WINAPI WinMain (HINSTANCE hThisInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR lpszArgument,
                     int nCmdShow)
{
    HWND hwnd;               /* This is the handle for our window */
    MSG messages;            /* Here messages to the application are saved */
    WNDCLASSEX wincl;        /* Data structure for the windowclass */

    /* The Window structure */
    wincl.hInstance = hThisInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
    wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
    wincl.cbSize = sizeof (WNDCLASSEX);

    /* Use default icon and mouse-pointer */
    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIconSm = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = NULL;                 /* No menu */
    wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
    wincl.cbWndExtra = 0;                      /* structure or the window instance */
    /* Use Windows's default colour as the background of the window */
    wincl.hbrBackground = (HBRUSH) COLOR_BACKGROUND;

    /* Register the window class, and if it fails quit the program */
    if (!RegisterClassEx (&wincl))
        return 0;

    /* The class is registered, let's create the program*/
    hwnd = CreateWindowEx (
           0,                   /* Extended possibilites for variation */
           szClassName,         /* Classname */
           _T("Simon Game"),       /* Title Text */
           WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, /* default window */
           CW_USEDEFAULT,       /* Windows decides the position */
           CW_USEDEFAULT,       /* where the window ends up on the screen */
           270*scale,                 /* The programs width */
           285*scale,                 /* and height in pixels */
           HWND_DESKTOP,        /* The window is a child-window to desktop */
           NULL,                /* No menu */
           hThisInstance,       /* Program Instance handler */
           NULL                 /* No Window Creation data */
           );


    /* Make the window visible on the screen */
    ShowWindow (hwnd, nCmdShow);

    /* Run the message loop. It will run until GetMessage() returns 0 */
    while (GetMessage (&messages, NULL, 0, 0))
    {
        /* Translate virtual-key messages into character messages */
        TranslateMessage(&messages);
        /* Send message to WindowProcedure */
        DispatchMessage(&messages);
    }

    /* The program return-value is 0 - The value that PostQuitMessage() gave */
    return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

    switch (message)                  /* handle the messages */
    {
        case WM_CREATE:
            AddControl(hwnd);



            break;
        case WM_COMMAND:
            switch(LOWORD(wParam)){
                case BUTTON_1:
                    simon_game.talk();
                    simon_game.WhoTalk(1);
                break;
                case BUTTON_2:
                    simon_game.talk();
                    simon_game.WhoTalk(2);
                break;
                case BUTTON_3:
                    simon_game.talk();
                    simon_game.WhoTalk(3);
                break;
                case BUTTON_4:
                    simon_game.talk();
                    simon_game.WhoTalk(4);
                break;
            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}


void AddControl(HWND hwnd){
        hColorImage = (HBITMAP) LoadImageW(NULL, L"Red.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        hBlackImage = (HBITMAP) LoadImageW(NULL, L"Black.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);

        HWND hbut1 = CreateWindow(
            "BUTTON",  // Predefined class; Unicode assumed
            "",      // Button text
            WS_TABSTOP | WS_VISIBLE | WS_CHILD |  BS_DEFPUSHBUTTON | BS_BITMAP,  // Styles
            10*scale,         // x position
            10*scale,         // y position
            100*scale,        // Button width
            100*scale,        // Button height
            hwnd,     // Parent window
            (HMENU) BUTTON_1,       // No menu.
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);      // Pointer not needed
        SendMessage(hbut1, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        hColorImage = (HBITMAP) LoadImageW(NULL, L"Green.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);

        HWND hbut2 = CreateWindow("BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD |  BS_DEFPUSHBUTTON | BS_BITMAP,
            150*scale, 10*scale, 100*scale, 100*scale, hwnd,
            (HMENU) BUTTON_2,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);
         SendMessage(hbut2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        hColorImage = (HBITMAP) LoadImageW(NULL, L"Blue.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        HWND hbut3 = CreateWindow(
            "BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP,
            10*scale, 160*scale, 100*scale,100*scale,hwnd,
            (HMENU) BUTTON_3,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);
         SendMessage(hbut3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        hColorImage = (HBITMAP) LoadImageW(NULL, L"Yellow.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        HWND hbut4 = CreateWindow(
            "BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON | BS_BITMAP,
            150*scale, 160*scale, 100*scale,100*scale,hwnd,
            (HMENU) BUTTON_4,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);
         SendMessage(hbut4, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        CreateWindow(
            "BUTTON", "Start Game",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
            75*scale, 120*scale, 120*scale,30*scale,hwnd,
            (HMENU) BUTTON_START,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);

        HBRUSH brush = CreateSolidBrush(RGB(88, 88, 88));
        SetClassLongPtr(hwnd, GCLP_HBRBACKGROUND, (LONG)brush);

        CreateWindow("static", "Score: ", WS_VISIBLE| WS_CHILD, 200*scale,120*scale, 30*scale,11*scale, hwnd,
                     NULL,NULL,NULL);
        hWndScore = CreateWindow("Static", "0", WS_VISIBLE| WS_CHILD, 225*scale,120*scale, 10*scale,11*scale, hwnd,
                     NULL,NULL,NULL);

        /*  Para cambiar el texto de una ventana
        SetWindowText(hWndScore, TEXT("Control string"));
        */


}






