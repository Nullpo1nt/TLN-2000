#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>  // sleep

#include "system/annunciators.h"
#include "system/display.h"
#include "system/tln2000.h"

bool running = true;
int i = 0;

void printscreen() {
    clear();
    printw("-------------------------------\n");
    printw("|          %3s    =o=o=  %3s  | %1sDIR\n", (getAnnunciatorGps()) ? "GPS" : "...",
           (getAnnunciatorWrn()) ? "WRN" : "...", (getAnnunciatorDirect()) ? "*" : ".");
    printw("|[%20s]  %3s  |\n|[%20s]  %3s  | %1sMSG\n", displayGetTop(), (getAnnunciatorPtk()) ? "PTK" : "...",
           displayGetBot(), (getAnnunciatorAdv()) ? "ADV" : "...", (getAnnunciatorMsg()) ? "*" : ".");
    printw("-------------------------------\n");
    printw("                                %1sENT\n", (getAnnunciatorEnt()) ? "*" : ".");

    printw("%1sNAV  %1sWPT  %1sFPL  %1sCALC  %1sAUX         %1sAPT/VOR\n", (getAnnunciatorNav()) ? "*" : ".",
           (getAnnunciatorWpt()) ? "*" : ".", (getAnnunciatorFpl()) ? "*" : ".", (getAnnunciatorCalc()) ? "*" : ".",
           (getAnnunciatorAux()) ? "*" : ".", (getAnnunciatorAptVor()) ? "*" : ".");

    printw("state = %i, t = %i\n", getState(), i);

    refresh();
}

void *tlnBackground(void *vargp) {
    while (running) {
        changeState(TLN_EVENT_UPDATE);

        printscreen();

        sleep(1);
        i++;
    }
    return 0;
}

int main(int argc, const char *argv[]) {
    initscr();
    cbreak();
    noecho();

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    pthread_t thread_id;
    pthread_create(&thread_id, NULL, tlnBackground, NULL);

    while (running) {
        int in = getch();

        switch (in) {
            case 'p':
                changeState(TLN_EVENT_BTN_POWER);
                break;
            case 'n':
                changeState(TLN_EVENT_BTN_NAV);
                break;
            case 'N':
                changeState(TLN_EVENT_BTN_NAV_HOLD);
                break;
            case 'w':
                changeState(TLN_EVENT_BTN_WPT);
                break;
            case 'W':
                changeState(TLN_EVENT_BTN_WPT_HOLD);
                break;
            case 'f':
                changeState(TLN_EVENT_BTN_FPL);
                break;
            case 'c':
                changeState(TLN_EVENT_BTN_CALC);
                break;
            case 'a':
                changeState(TLN_EVENT_BTN_AUX);
                break;
            case 'A':
                changeState(TLN_EVENT_BTN_AUX_HOLD);
                break;
            case 'v':
                changeState(TLN_EVENT_BTN_APTVOR);
                break;
            case 'd':
                changeState(TLN_EVENT_BTN_DIRECT);
                break;
            case 'm':
                changeState(TLN_EVENT_BTN_MSG);
                break;
            case 'e':
                changeState(TLN_EVENT_BTN_ENT);
                break;
            case '1':
                changeState(TLN_EVENT_BTN_ROT_IN_CC);
                break;
            case '2':
                changeState(TLN_EVENT_BTN_ROT_IN_CW);
                break;
            case '3':
                changeState(TLN_EVENT_BTN_ROT_OUT_CC);
                break;
            case '4':
                changeState(TLN_EVENT_BTN_ROT_OUT_CW);
                break;
            case 'u':
                changeState(TLN_EVENT_UPDATE);
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