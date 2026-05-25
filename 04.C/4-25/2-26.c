#include <ncurses.h>
#include <unistd.h>

int main() {
    initscr();
    noecho();
    move(0,0);
    curs_set(0);

    int row, col;
    getmaxyx(stdscr, row, col);

    int befx = -1;
    int befy = -1;
    
    for (int x = 0; x < col; x++) {
        for (int y = 0; y < row; y++) {
            if (befx != -1 && befy != -1) {
                mvprintw(befy, befx, " ");
            }
            mvprintw(y, x, "O");
            befx = x;
            befy = y;
            usleep(10000);
            refresh();
        }
    }

    endwin();

}
