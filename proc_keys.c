#include "includes/cube3d.h"

int press_key(int keycode, t_mlx *mlx)
{
    if (keycode == 126 || keycode == 13)
    {
      double rotSpeed = 0.3;
      if(mlx->pos.worldMap[(int)(mlx->pos.posX + mlx->pos.dirX)][(int)(mlx->pos.posY)] == 0) mlx->pos.posX += mlx->pos.dirX * rotSpeed;
      if(mlx->pos.worldMap[(int)(mlx->pos.posX)][(int)(mlx->pos.posY + mlx->pos.dirY)] == 0) mlx->pos.posY += mlx->pos.dirY * rotSpeed;
      draw_ray_casting(mlx);
    }
    if (keycode == 125 || keycode == 1)
    {
      double rotSpeed = 0.3;

      if(mlx->pos.worldMap[(int)(mlx->pos.posX - mlx->pos.dirX)][(int)(mlx->pos.posY)] == 0) mlx->pos.posX -= mlx->pos.dirX * rotSpeed;
      if(mlx->pos.worldMap[(int)(mlx->pos.posX)][(int)(mlx->pos.posY - mlx->pos.dirY)] == 0) mlx->pos.posY -= mlx->pos.dirY * rotSpeed;
      draw_ray_casting(mlx);
    }
    // key left
    if (keycode == 123)
    {
      double rotSpeed = 0.1;
      double oldDirX = mlx->pos.dirX;
      mlx->pos.dirX = mlx->pos.dirX * cos(rotSpeed) - mlx->pos.dirY * sin(rotSpeed);
      mlx->pos.dirY = oldDirX * sin(rotSpeed) + mlx->pos.dirY * cos(rotSpeed);
      double oldPlaneX = mlx->pos.planeX;
      mlx->pos.planeX = mlx->pos.planeX * cos(rotSpeed) - mlx->pos.planeY * sin(rotSpeed);
      mlx->pos.planeY = oldPlaneX * sin(rotSpeed) + mlx->pos.planeY * cos(rotSpeed);
      draw_ray_casting(mlx);
    }
    // key A
       if (keycode == 0)
    {
      double rotSpeed = 0.2;
      if(mlx->pos.worldMap[(int)(mlx->pos.posY + mlx->pos.dirX * rotSpeed)][(int)(mlx->pos.posX)] == 0) mlx->pos.posY -= -mlx->pos.dirX * rotSpeed;
      if(mlx->pos.worldMap[(int)(mlx->pos.posY)][(int)(mlx->pos.posX - mlx->pos.dirY * rotSpeed)] == 0) mlx->pos.posX -= mlx->pos.dirY * rotSpeed;
      draw_ray_casting(mlx);
    }
    // key d
       if (keycode == 2)
    {
      double rotSpeed = 0.2;
      if(mlx->pos.worldMap[(int)(mlx->pos.posY - mlx->pos.dirX)][(int)(mlx->pos.posX)] == 0) mlx->pos.posY += -mlx->pos.dirX * rotSpeed;
      if(mlx->pos.worldMap[(int)(mlx->pos.posY)][(int)(mlx->pos.posX + mlx->pos.dirY)] == 0) mlx->pos.posX += mlx->pos.dirY * rotSpeed;
      draw_ray_casting(mlx);
    }
    if (keycode == 124)
    {
      double rotSpeed = 0.1;
      double oldDirX = mlx->pos.dirX;
      mlx->pos.dirX = mlx->pos.dirX * cos(-rotSpeed) - mlx->pos.dirY * sin(-rotSpeed);
      mlx->pos.dirY = oldDirX * sin(-rotSpeed) + mlx->pos.dirY * cos(-rotSpeed);
      double oldPlaneX = mlx->pos.planeX;
      mlx->pos.planeX = mlx->pos.planeX * cos(-rotSpeed) - mlx->pos.planeY * sin(-rotSpeed);
      mlx->pos.planeY = oldPlaneX * sin(-rotSpeed) + mlx->pos.planeY * cos(-rotSpeed);
      draw_ray_casting(mlx);
    }
    if (keycode == 53)
    {
      mlx_clear_window(mlx->mlx_ptr, mlx->win);
      mlx_destroy_window(mlx->mlx_ptr, mlx->win);
      free(mlx->pos.worldMap);
      exit(0);
      return (0);
    }
    return(0);
}