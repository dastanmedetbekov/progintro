#include <ncurses.h>
#include <unistd.h>

void sleepyjo() {
    usleep(100000);
}

int main() {
    initscr();
    curs_set(0); 
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    int y = LINES / 2; 
    int max_x = COLS - 2;

    for (int pass = 0; pass < 3; pass++) {
        int hell = 0;

        for (int x = 0; x <= max_x; x++) {
            clear();
            mvprintw(y, x, "*");
            refresh();
            sleepyjo();
            if (getch() != ERR) {
                hell = 1;
                break;
            }
        }

        if (hell == 1) {
            break;
        }

        for (int x = max_x; x >= 0; x--) {
            clear();
            mvprintw(y, x, "*");
            refresh();
            sleepyjo();
            if (getch() != ERR) {
                hell = 1;
                break;
            }
        }
        if (hell == 1) {
            break;
        }
    }

    clear();
    refresh();
    endwin();
    return 0;
}
