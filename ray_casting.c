#include "includes/cube3d.h"

void verLine(int x, int drawStart, int drawEnd, int color, t_mlx mlx)
{
    while (drawStart < drawEnd)
    {
        mlx.img.data[drawStart * mlx.args.screen_w + x] = color;
        drawStart++;
    }
}

int draw_ray_casting(t_mlx *mlx)
{
      int x;

      x = 0;
      mlx->img.img_ptr = mlx_new_image(mlx->mlx_ptr, mlx->args.screen_w, mlx->args.screen_h);
      mlx->img.data = (int *)mlx_get_data_addr(mlx->img.img_ptr, &mlx->img.bpp, &mlx->img.size_l,
		  &mlx->img.endian);
      while (x < mlx->args.screen_w)
      {
      double cameraX = 2 * x / (double)mlx->args.screen_w - 1; 
      double rayDirX = mlx->pos.dirX + mlx->pos.planeX * cameraX;
      double rayDirY = mlx->pos.dirY + mlx->pos.planeY * cameraX;
      int mapX = (int)(mlx->pos.posX);
      int mapY = (int)(mlx->pos.posY);

      double sideDistX;
      double sideDistY;

      double deltaDistX = fabs(1 / rayDirX);
      double deltaDistY = fabs(1 / rayDirY);
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?
      //calculate step and initial sideDist

      
      if(rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (mlx->pos.posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - mlx->pos.posX) * deltaDistX;
      }
      if(rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (mlx->pos.posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - mlx->pos.posY) * deltaDistY;
      }
      //perform DDA
      while (hit == 0)
      {
        //jump to next map square, OR in x-direction, OR in y-direction
        if(sideDistX < sideDistY)
        {
          sideDistX += deltaDistX;
          mapX += stepX;
          side = 0;
        }
        else
        {
          sideDistY += deltaDistY;
          mapY += stepY;
          side = 1;
        }
        //Check if ray has hit a wall
        if(mlx->pos.worldMap[mapX][mapY] > 0) hit = 1;
      }
      //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
      if(side == 0) perpWallDist = (mapX - mlx->pos.posX + (1 - stepX) / 2) / rayDirX;
      else          perpWallDist = (mapY - mlx->pos.posY + (1 - stepY) / 2) / rayDirY;

      //Calculate height of line to draw on screen
      int lineHeight = (int)(mlx->args.screen_w / perpWallDist);

      //calculate lowest and highest pixel to fill in current stripe
      int drawStart = -lineHeight / 2 + mlx->args.screen_h / 2;
      if(drawStart < 0)drawStart = 0;
      int drawEnd = lineHeight / 2 + mlx->args.screen_h / 2;
      if(drawEnd >= mlx->args.screen_h)drawEnd = mlx->args.screen_h - 1;

      //choose wall color
      int color = 0xFFFFFF;
      int red_color = 0xff3333;
      int green_color = 0x339933;
      int blue_color = 0x3366cc;
      int yellow_color = 0xffff55;
      if (mlx->pos.worldMap[mapX][mapY] == 1)
        color = red_color;
      if (mlx->pos.worldMap[mapX][mapY] == 2)
        color = green_color;
      if (mlx->pos.worldMap[mapX][mapY] == 3)
        color = blue_color;
      if (mlx->pos.worldMap[mapX][mapY] == 4)
        color = 0xFFFFFF; 
      if (mlx->pos.worldMap[mapX][mapY] == 4)
        color = yellow_color; 

      //give x and y sides different brightness
      if(side == 1) {color = color / 1.5;}
    

      //draw the pixels of the stripe as a vertical line
      verLine(x, drawStart, drawEnd, color, *mlx);
      x++;
      }
      mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, mlx->img.img_ptr, 0, 0);
    return (0);
}