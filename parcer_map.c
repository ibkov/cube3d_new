#include "includes/cube3d.h"
#include "gnl/get_next_line.h"
#include <stdio.h>

void parcer_map(char *file_name, pos_gamer *pos)
{
    
    char *line_map;
    int i;
    int j;
    int w;
    int h;
    int fd; 

    h = 1;
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line_map) != 0)
    {
        
        w = 0; 
        while (line_map[w])
            w++;
        h++;
    }
    pos->worldMap = (int**)malloc(sizeof(int*) * h);
    i = 0;
    while(i <= h)
    {
        pos->worldMap[i] = (int*)malloc(sizeof(int) * w);
        i++;
    }
    i = 0;
    j = 0;
    close(fd);
    fd = open(file_name, O_RDONLY);
    while (get_next_line(fd, &line_map) != 0)
    {
        i = 0;
        while (line_map[i] && i < w)
        { 
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;  
            
        }
        if (j < h)
            j++;   
            
    }
    i= 0;
    while (line_map[i])
        {
            pos->worldMap[j][i] = (line_map[i] - 48);
            i++;
        }
}