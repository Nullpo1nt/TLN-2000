#include <ncurses.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>  // sleep

#include "system/annunciators.h"
#include "system/display.h"
#include "system/state.h"
#include "system/tln2000ap.h"

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

    printw("state = %i, t = %i\n", state_current(tln2000sm), i);

    refresh();
}

void *tlnBackground(void *vargp) {
    while (running) {
        state_update(tln2000sm, TLN_EVENT_SYSTEM_UPDATE);
        state_update(tln2000sm, TLN_EVENT_UPDATE);

        printscreen();

        sleep(1);
        i++;
    }
    return 0;
}

int main(int argc, const char *argv[]) {
    tln2000sm = init_tln2000();

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
                state_update(tln2000sm, TLN_EVENT_BTN_POWER);
                break;
            case 'n':
                state_update(tln2000sm, TLN_EVENT_BTN_NAV);
                break;
            case 'N':
                state_update(tln2000sm, TLN_EVENT_BTN_NAV_HOLD);
                break;
            case 'w':
                state_update(tln2000sm, TLN_EVENT_BTN_WPT);
                break;
            case 'W':
                state_update(tln2000sm, TLN_EVENT_BTN_WPT_HOLD);
                break;
            case 'f':
                state_update(tln2000sm, TLN_EVENT_BTN_FPL);
                break;
            case 'c':
                state_update(tln2000sm, TLN_EVENT_BTN_CALC);
                break;
            case 'a':
                state_update(tln2000sm, TLN_EVENT_BTN_AUX);
                break;
            case 'A':
                state_update(tln2000sm, TLN_EVENT_BTN_AUX_HOLD);
                break;
            case 'v':
                state_update(tln2000sm, TLN_EVENT_BTN_APTVOR);
                break;
            case 'd':
                state_update(tln2000sm, TLN_EVENT_BTN_DIRECT);
                break;
            case 'm':
                state_update(tln2000sm, TLN_EVENT_BTN_MSG);
                break;
            case 'e':
                state_update(tln2000sm, TLN_EVENT_BTN_ENT);
                break;
            case '1':
                state_update(tln2000sm, TLN_EVENT_BTN_ROT_IN_CC);
                break;
            case '2':
                state_update(tln2000sm, TLN_EVENT_BTN_ROT_IN_CW);
                break;
            case '3':
                state_update(tln2000sm, TLN_EVENT_BTN_ROT_OUT_CC);
                break;
            case '4':
                state_update(tln2000sm, TLN_EVENT_BTN_ROT_OUT_CW);
                break;
            case 'u':
                state_update(tln2000sm, TLN_EVENT_UPDATE);
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

    free(tln2000sm);

    return 0;
}