#include <stdio.h>
#include <unistd.h> // sleep
#include <pthread.h>
#include <ncurses.h>

#include "system/tln2000.h"

bool running = true;
int i = 0;

void printscreen()
{
    clear();
    printw("-------------------------------\n");
    printw("|          %3s    =o=o=  %3s  | %1sDIR\n",
           (tln::annunciators::getAnnunciatorGps()) ? "GPS" : "...",
           (tln::annunciators::getAnnunciatorWrn()) ? "WRN" : "...",
           (tln::annunciators::getAnnunciatorDirect()) ? "*" : ".");
    printw("|[%20s]  %3s  |\n|[%20s]  %3s  | %1sMSG\n",
           tln::display::getTop(),
           (tln::annunciators::getAnnunciatorPtk()) ? "PTK" : "...",
           tln::display::getBot(),
           (tln::annunciators::getAnnunciatorAdv()) ? "ADV" : "...",
           (tln::annunciators::getAnnunciatorMsg()) ? "*" : ".");
    printw("-------------------------------\n");
    printw("                                %1sENT\n",
           (tln::annunciators::getAnnunciatorEnt()) ? "*" : ".");

    printw("%1sNAV  %1sWPT  %1sFPL  %1sCALC  %1sAUX         %1sAPT/VOR\n",
           (tln::annunciators::getAnnunciatorNav()) ? "*" : ".",
           (tln::annunciators::getAnnunciatorWpt()) ? "*" : ".",
           (tln::annunciators::getAnnunciatorFpl()) ? "*" : ".",
           (tln::annunciators::getAnnunciatorCalc()) ? "*" : ".",
           (tln::annunciators::getAnnunciatorAux()) ? "*" : ".",
           (tln::annunciators::getAnnunciatorAptVor()) ? "*" : ".");

    printw("state = %i, t = %i\n", tln::getState(), i);

    refresh();
}

void *tlnBackground(void *vargp)
{
    while (running)
    {
        tln::changeState(tln::TLN_EVENT_UPDATE);

        printscreen();

        sleep(1);
        i++;
    }
    return 0;
}

int main(int argc, const char *argv[])
{
    initscr();
    cbreak();
    noecho();

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, tlnBackground, NULL);

    while (running)
    {
        int in = getch();

        switch (in)
        {
        case 'p':
            tln::changeState(tln::TLN_EVENT_BTN_POWER);
            break;
        case 'n':
            tln::changeState(tln::TLN_EVENT_BTN_NAV);
            break;
        case 'N':
            tln::changeState(tln::TLN_EVENT_BTN_NAV_HOLD);
            break;
        case 'w':
            tln::changeState(tln::TLN_EVENT_BTN_WPT);
            break;
        case 'W':
            tln::changeState(tln::TLN_EVENT_BTN_WPT_HOLD);
            break;
        case 'f':
            tln::changeState(tln::TLN_EVENT_BTN_FPL);
            break;
        case 'c':
            tln::changeState(tln::TLN_EVENT_BTN_CALC);
            break;
        case 'a':
            tln::changeState(tln::TLN_EVENT_BTN_AUX);
            break;
        case 'A':
            tln::changeState(tln::TLN_EVENT_BTN_AUX_HOLD);
            break;
        case 'v':
            tln::changeState(tln::TLN_EVENT_BTN_APTVOR);
            break;
        case 'd':
            tln::changeState(tln::TLN_EVENT_BTN_DIRECT);
            break;
        case 'm':
            tln::changeState(tln::TLN_EVENT_BTN_MSG);
            break;
        case 'e':
            tln::changeState(tln::TLN_EVENT_BTN_ENT);
            break;
        case '1':
            tln::changeState(tln::TLN_EVENT_BTN_ROT_IN_CC);
            break;
        case '2':
            tln::changeState(tln::TLN_EVENT_BTN_ROT_IN_CW);
            break;
        case '3':
            tln::changeState(tln::TLN_EVENT_BTN_ROT_OUT_CC);
            break;
        case '4':
            tln::changeState(tln::TLN_EVENT_BTN_ROT_OUT_CW);
            break;
        case 'u':
            tln::changeState(tln::TLN_EVENT_UPDATE);
            break;
        case 'q':
            running = false;
            break;
        }

        printscreen();
    }

    pthread_join(thread_id, 0);

    endwin();
    pthread_exit(NULL);

    return 0;
}