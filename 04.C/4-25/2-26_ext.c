#include <ncurses.h>
#include <unistd.h>

int main() {
    initscr();
    noecho();
    curs_set(0);

    int row, col;
    getmaxyx(stdscr, row, col);

    int mid_y = row / 2;
    int max_x = col - 1; 
    for (int pass = 0; pass < 3; pass++) {
        
        for (int x = 0; x < max_x; x++) {
            mvprintw(mid_y, x, "*");
            refresh();
            usleep(100000);
            mvprintw(mid_y, x, " "); 
        }

        for (int x = max_x - 1; x >= 0; x--) {
            mvprintw(mid_y, x, "*");
            refresh();
            usleep(100000);
            mvprintw(mid_y, x, " "); 
        }
    }

    clear();
    refresh();
    
    endwin();
    return 0;
}
