#include "includes/cube3d.h"

void init_position(pos_gamer *pos)
{
  pos->posX = 10;
  pos->posY = 14;  //x and y start position
  pos->dirX = -1;
  pos->dirY = 0; //initial direction vector
  pos->planeX = 0; 
  pos->planeY = 0.66; //the 2d raycaster version of camera plane
}