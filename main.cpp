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

/*It will display all the control buttons*/
void AddControl(HWND hwnd);
/*The action performed by the playable buttons*/
void button_action(int button_num);

bool start_game = true,
     loose = false;

/*Scale of the main window and it's components*/
float scale = 3;

/*Instance of the game*/
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
                    button_action(1);
                break;
                case BUTTON_2:
                    button_action(2);
                break;
                case BUTTON_3:
                    button_action(3);
                break;
                case BUTTON_4:
                    button_action(4);
                break;
                case BUTTON_START:
                    simon_game.start();
                    loose = false;
                    int current_number = simon_game.GetCurrentNum();

                    SendMessage(GetDlgItem(hwnd, 100 + current_number), BM_SETSTATE,TRUE, 0);
                    Sleep(1000);
                    SendMessage(GetDlgItem(hwnd, 100 + current_number), BM_SETSTATE,FALSE, 0);
                    start_game = false;
                    MessageBox(hwnd, "Your turn", "Play", MB_OK);
                break;

            }
            break;
        case WM_DESTROY:
            PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
            break;
        default:                      /* for messages that we don't deal with */
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    //cout << "counter: "<< simon_game.counter << " score: "<< simon_game.score << " size: " << simon_game.sequence.size() <<endl;

    if(simon_game.endOfLvl() && !start_game && !loose){
        cout << "End of Level" <<endl;

        //MessageBox(hwnd, "Click OK to play level " score + 1, "New Level", MB_OK); Pasar de int a lo que sea
        switch(simon_game.getSizeSeq()){
            case 3: MessageBox(hwnd, "Lvl 3, That's a good start", "New Level", MB_OK); break;
            case 5:MessageBox(hwnd, "WOW You're on lvl 5", "New Level", MB_OK); break;
            case 8:MessageBox(hwnd, "Omg! You're on fire", "New Level", MB_OK); break;
            case 11:MessageBox(hwnd, "Ok, this can't be true", "New Level", MB_OK); break;
            case 15:MessageBox(hwnd, "Are you cheating?", "New Level", MB_OK); break;
            default: MessageBox(hwnd, "Click OK for a new level", "New Level", MB_OK);
        }

        simon_game.AddALevel();
        cout << "Sequence: ";
        for(int i = 0; i < simon_game.getSizeSeq(); i++){
            int color = simon_game.GetColorPos(i);
            SendMessage(GetDlgItem(hwnd, 100 + color), BM_SETSTATE,TRUE, 0);
            Sleep(1000);
            SendMessage(GetDlgItem(hwnd, 100 + color), BM_SETSTATE,FALSE, 0);
            Sleep(500);
            cout << color << " ";
        }
        cout << endl;
        simon_game.newLevel();
    }
    if(loose){
        //string score = "Your score is ";
        MessageBox(hwnd, "You lost", "Looser", MB_OK);
    }





    return 0;
}


void AddControl(HWND hwnd){
        hColorImage = (HBITMAP) LoadImageW(NULL, L"resources/Red.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        hBlackImage = (HBITMAP) LoadImageW(NULL, L"resources/Black.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);

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

        hColorImage = (HBITMAP) LoadImageW(NULL, L"resources/Green.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);

        HWND hbut2 = CreateWindow("BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD |  BS_PUSHLIKE | BS_BITMAP,
            150*scale, 10*scale, 100*scale, 100*scale, hwnd,
            (HMENU) BUTTON_2,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);
         SendMessage(hbut2, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        hColorImage = (HBITMAP) LoadImageW(NULL, L"resources/Blue.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        HWND hbut3 = CreateWindow(
            "BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_BITMAP,
            10*scale, 160*scale, 100*scale,100*scale,hwnd,
            (HMENU) BUTTON_3,
            (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE),
            NULL);
         SendMessage(hbut3, BM_SETIMAGE, IMAGE_BITMAP, (LPARAM) hColorImage);

        hColorImage = (HBITMAP) LoadImageW(NULL, L"resources/Yellow.bmp", IMAGE_BITMAP, 100*scale, 100*scale, LR_LOADFROMFILE);
        HWND hbut4 = CreateWindow(
            "BUTTON", "",
            WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_PUSHLIKE | BS_BITMAP,
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

       // SetWindowText(hWndScore, TEXT(score));


}

void button_action(int button_num){
    bool check = simon_game.check(button_num);
    if(!check)
        loose = true;
}



