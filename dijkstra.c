/**
 * File: dijkstra.c
 * Description: 迪杰斯特拉算法实现
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.18
 */
// 2017.5.18 先停止编写此算法
#include <stdio.h>
#define MAX_X 5
#define MAX_Y 3
/*
0 1 2 3 4 max_x*y +
0 1 2 3 4 x+0(y)
---------
5 6 7 8 9 max_x*y +
0 1 2 3 4 x+1(y)
---------
10 11 12 13 14 max_x*y +
0  1  2  3  4  x+2(y)
*/
void pos2index(int *index,int x,int y)
{
  *index  = (y * MAX_X) + x;
}
void index2pos(int index,int *x,int *y)
{
  *y = index / MAX_X;
  *x = index % MAX_X;
}
int main()
{
  
  return 0;
}
