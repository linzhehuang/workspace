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
#define MAX_X 10
#define MAX_Y 6

void pos2index(int *index,int x,int y)
{
  *index  = (y * (MAX_X-1)) + x;
}
void index2pos(int index,int *x,int *y)
{
  *y = (index / (MAX_X-1)) - 1;
  *x = index - (*y * (MAX_X-1));
}
int main()
{
  
  return 0;
}