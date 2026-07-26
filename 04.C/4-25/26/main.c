#include <ncurses.h>
#include <unistd.h>

void sleepyjo() {
    usleep(10000);
}

int main() {
    WINDOW *window = initscr();
    
    for (int i = 0; i < COLS; i++) {
        for (int j = 0; j < LINES; j++) {
            mvprintw(j, i, "H");
            sleepyjo();
            refresh();
        }
    }
    getch();
    endwin();
    return 0;
}

