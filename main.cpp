#include "hdr/settings.hpp"
#include "hdr/ui.hpp"
#include <algorithm>
#include <cctype>
#include <chrono>
#include <clocale>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <ncurses.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <array>
#include "hdr/gameObj.hpp"
#include "hdr/unicode.hpp"

struct Point {
  int x, y;
  Point() : x(0), y(0){};
  Point(int x, int y) : x(x), y(y){};
};







class PlayGround {
  std::vector<std::vector<bool>> board;
  std::vector<int> filledRows;
  WINDOW *win;
  int width, height, elvation;

public:
  PlayGround(int width, int height) : width(width), height(height) {
    int screenMaxY, screenMaxX;
    getmaxyx(stdscr, screenMaxY, screenMaxX);
    board = std::vector(height, std::vector<bool>(width, false));
    win = newwin(height + 2, width + 2, (screenMaxY - (height + 2)) / 2,
                 (screenMaxX - (width + 2)) / 2); // add 2 accounting for box()
    box(win, 0, 0);
    refresh();
    wrefresh(win);
  }
  void gameOver() {
    wattron(win, A_REVERSE);
    short rand_clr = rand() % (total_clr-1);
    for (int rows = 0; rows < height; rows++) {
      if (rows & 0b1) {
        wattron(win, COLOR_PAIR(rand_clr));
      }

      for (int cols = 0; cols < width; cols++) {
        mvwaddch(win, rows + 1, cols + 1, ' ');
      }
      wattroff(win, COLOR_PAIR(rand_clr));
      std::this_thread::sleep_for(std::chrono::milliseconds(50));
      wrefresh(win);
    }
    wattroff(win, A_REVERSE);
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  void reset() {
    board = std::vector(height, std::vector<bool>(width, false));
    werase(win);
    box(win, 0, 0);
    refresh();
    wrefresh(win);
  }
  bool draw(Point pos,Shape *shape,int rotation) {
    /*this function does return false when it cannot draw*/
    for (int rows = 0; rows < shape->sprite[rotation].size(); rows++) {
      for (int cols = 0; cols < shape->sprite[rotation][0].size(); cols++) {
        if(board[rows+pos.y][cols+pos.x]){
            return false;
        }      
      }
    }

    for (int rows = 0; rows < shape->sprite[rotation].size(); rows++) {
      for (int cols = 0; cols < shape->sprite[rotation][0].size(); cols++) {
        if(shape->sprite[rotation][rows][cols]){
            board[rows][cols] = true;   
        }
      }
    }

    for (int rows = 0; rows < shape->sprite[rotation].size(); rows++) {
      for (int cols = 0; cols < shape->sprite[rotation][0].size(); cols++) {
        if(shape->sprite[rotation][rows][cols]){
            mvwadd_wch(win, pos.y + 1 + rows, pos.x + 1 + cols, shape->sprite_char);
        }
      }
    }
    
    wrefresh(win);
    return true;
  }
  void clear(Point pos) {
    board[pos.y][pos.x] = false;
    mvwaddch(win, pos.y + 1, pos.x + 1, ' ');
    wrefresh(win);
  }
  bool hitTheFloor(Point pos) {
    return pos.y == height - 1;
  }
  bool hitSomePiece(Point pos, int Xoffset, int Yoffset) {
    return board[pos.y + Yoffset][pos.x + Xoffset];
  }

  void preventOutOfBounds(Point &pos) {
    pos.y = std::clamp(pos.y, 0, height - 1);
    pos.x = std::clamp(pos.x, 0, width - 1);
  }

  void clearFilledLines() {
    while (!filledRows.empty()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1000));
      char str[width + 1];

      for (int rows = filledRows.back(); rows >= 0; rows--) {
        mvwinnstr(win, rows, 1, str, width);
        mvwaddstr(win, rows + 1, 1, str);
      }

      for (int rows = filledRows.back(); rows >= 1; rows--) {
        for (int cols = 0; cols < width; cols++) {
          board[rows][cols] = board[rows - 1][cols];
        }
      }

      for (int cols = 0; cols < width; cols++) {
        mvwaddch(win, 1, cols + 1, ' ');
      }

      for (int cols = 0; cols < width; cols++) {
        board[0][cols] = false;
      }

      wrefresh(win);
      filledRows.pop_back();
    }
  }

  void underlineFilledLines() {
    for (int rows = 0; rows < height; rows++) {
      int colFilled = 0;
      for (int cols = 0; cols < width; cols++) {
        if (board[rows][cols]) {
          colFilled++;
        }
      }
      if (colFilled == width) {
        filledRows.push_back(rows);
        for (int cols = 0; cols < width; cols++) {
          mvwaddch(win, rows + 1, cols + 1, '_');
        }
      }
    }
    wrefresh(win);
  }

  ~PlayGround() { delwin(win); }
};

int main() {
  INIT_NCURSES();
  setlocale(LC_ALL, "");
  srand(time(NULL));
  auto playGround = PlayGround(Tetris_Width, Tetris_Height);
  unsigned long long int tick = 0;
  unsigned long long int lastTick = 0;


    // Print the cchar_t object on the screen
  printf("%lc",wchars[1]);
  refresh();
  bool isRunning = true;
  auto pos = Point(0, 0);
  auto lastPos = pos;
  int key = ERR;
  while (isRunning) {
    std::this_thread::sleep_for(std::chrono::microseconds(50));
    tick++;
    playGround.clear(pos);
    playGround.clearFilledLines();
    lastPos = pos;
    if (tick % 10000 == 0) {
        pos.y++;
    } else {
      switch (std::toupper((key = getch()))) {
      case 'Q': {
        isRunning = false;
        break;
      }
      case KEY_DOWN: {
        pos.y++;
        playGround.preventOutOfBounds(pos);
        break;
      }
      case KEY_UP: {
        pos.y--;
        playGround.preventOutOfBounds(pos);
        break;
      }
      case KEY_LEFT: {
        pos.x--;
        playGround.preventOutOfBounds(pos);
        break;
      }
      case KEY_RIGHT: {
        pos.x++;
        playGround.preventOutOfBounds(pos);
        break;
      }
      }
    }

    if (playGround.hitSomePiece(pos, 0, 0)) {
      pos = lastPos;
    }

    /* if (playGround.hitTheFloor(pos) || playGround.hitSomePiece(pos, 0, 1)) {
      playGround.draw(pos,&oshape,0);
      playGround.underlineFilledLines();
      lastTick = tick;
      pos = Point(0, 0);
    }

    if(!playGround.draw(pos,&oshape,0)){//check if unable to draw
        playGround.gameOver();
        playGround.reset();
        pos = Point(0,0);
        tick = lastTick = 0;
    }
  */  
  }
  endwin();
  return EXIT_SUCCESS;
}
