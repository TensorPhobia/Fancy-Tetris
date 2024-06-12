#include <ncurses.h>
#include <vector>

class Shape {
public:
  cchar_t * sprite_char;
  std::vector<std::vector<std::vector<bool>>> sprite;
  Shape(cchar_t * sprite_char,std::vector<std::vector<std::vector<bool>>> sprite);
 
};

class Tshape : public Shape {
public:
  Tshape(cchar_t * sprite_char);
};

class Straight : public Shape {
public:
  Straight(cchar_t * sprite_char);
};

class Lshape : public Shape {
public:
  Lshape(cchar_t * sprite_char);
};

class Jshape : public Shape {
public:
  Jshape(cchar_t * sprite_char);
};

class Zigzag : public Shape {
public:
  Zigzag(cchar_t * sprite_char);
};

class Sshape : public Shape {
public:
  Sshape(cchar_t * sprite_char);
};

class Oshape : public Shape {
public:
  Oshape(cchar_t * sprite_char);
};