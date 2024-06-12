#include "../hdr/gameObj.hpp"

Shape::Shape(cchar_t * sprite_char,std::vector<std::vector<std::vector<bool>>> sprite)
      :sprite_char(sprite_char), sprite(sprite){};

#pragma endregion Shape_Defintion





Tshape::Tshape(cchar_t * sprite_char):Shape(sprite_char, {
        {
            {0,1,0},
            {1,1,1},
        },
        {
            {0,1},
            {1,1},
            {0,1},
        },
        {
            {1,1,1},
            {0,1,0},
        },
        {
            {1,0},
            {1,1},
            {1,0},
        }
    }){};


Straight::Straight(cchar_t * sprite_char):Shape(sprite_char,{
        {
            {1},
            {1},
            {1},
            {1},
        },
        {
        {1,1,1,1},
        }
    }){};

Lshape::Lshape(cchar_t * sprite_char):Shape(sprite_char, {
        {
        {1,0},
        {1,0},
        {1,1},
        },
        {
            {0,0,1},
            {1,1,1}
        },
        {
            {1,1},
            {0,1},
            {0,1},
        },
        {
            {1,1,1},
            {1,0,0}
        }
    }){};

Jshape::Jshape(cchar_t * sprite_char):Shape(sprite_char, {
        {
        {0,1},
        {0,1},
        {1,1},
        },
        {
            {1,0,0},
            {1,1,1}
        },
        {
            {1,1},
            {1,0},
            {1,0},
        },
        {
            {1,1,1},
            {0,0,1}
        }
    }){};


Zigzag::Zigzag(cchar_t * sprite_char):Shape(sprite_char, {
        {
        {1,1,0},
        {0,1,1},
        },
        {
            {0,1},
            {1,1},
            {1,0},
        }
    }){};

Sshape::Sshape(cchar_t * sprite_char):Shape(sprite_char , {
        {
        {0,1,1},
        {1,1,0},
        },
        {
            {1,0},
            {1,1},
            {0,1},
        }
    }){};

Oshape::Oshape(cchar_t * sprite_char):Shape(sprite_char, {
    {
        {1,1},
        {1,1}
    }
}){};
