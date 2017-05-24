/**
 * File: bfs_array.c
 * Description: 广度优先遍历数组，寻找最短路径
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.18
 */
#include <stdio.h>
#define MAX_X 10
#define MAX_Y 5

int arr[MAX_X][MAX_Y] = {0};
int obstacle[MAX_X][MAX_Y] = {0};
// 目标位置
int target_x = 6,target_y = 4;
/* tree[n][0]--x
 * tree[n][1]--y
 * tree[n][2]--parent 
 */
int tree[MAX_X * MAX_Y][3] = {0};
int tree_index = 0;
// 是否可访问
int is_access(int ele_x,int ele_y)
{
  // 越界
  if(ele_x < 0 || ele_x >= MAX_X ||
  ele_y < 0 || ele_y >= MAX_Y )
  {
	return 0;
  }
  // 被访问过
  else if(arr[ele_x][ele_y] == -1)
  {
    return 0;
  }
  // 障碍
  else if(obstacle[ele_x][ele_y] == 1)
  {
	return 0;
  }
  else
  {
	return 1;
  }
}
// 是否可通过
int is_through(int orgin_x,int orgin_y,int x,int y)
{
  int dist_x = x - orgin_x,
  dist_y = y - orgin_y;
  // 上 右 下 左
  int obstacle_list[4] = {
	obstacle[orgin_x][orgin_y-1] ,
    obstacle[orgin_x+1][orgin_y] ,
    obstacle[orgin_x][orgin_y+1] ,
    obstacle[orgin_x-1][orgin_y] };
  if(!dist_x || !dist_y) return 1;
  else {
	// 上左 上右 下右 下左
	if(dist_x == -1 && dist_y == -1)
	{
	  if(obstacle_list[0] == 1 && obstacle_list[3] == 1) return 0;
	  else return 1;
	}
	else if(dist_x == 1 && dist_y == -1)
	{
	  if(obstacle_list[0] == 1 && obstacle_list[1] == 1) return 0;
	  else return 1;
	}
	else if(dist_x == 1 && dist_y == 1)
	{
	  if(obstacle_list[1] == 1 && obstacle_list[2] == 1) return 0;
	  else return 1;
	}
	else
	{
	  if(obstacle_list[3] == 1 && obstacle_list[2] == 1) return 0;
	  else return 1;
	}
  }
}
int create_node(int ele_x,int ele_y,int parent)
{
  tree[tree_index][0] = ele_x;
  tree[tree_index][1] = ele_y;
  tree[tree_index][2] = parent;
  tree_index++;
}
int vist(int start_x,int start_y)
{
  // 将开始节点作为根节点，根节点父节点设置为-1
  create_node(start_x,start_y,-1);
  
  int current_x = start_x , current_y = start_y;
  // 偏移值，顺序为
  // 上、上右、
  // 右、下右、
  // 下、下左、
  // 左、上左
  int offset[8][2] = {
	{0,-1},{1,-1},
    {1,0},{1,1},
	{0,1},{-1,1},
	{-1,0},{-1,-1} };
  int index = 0;
  
  while(current_x != target_x || current_y != target_y)
  {
	// 将当前点设置为已访问
    arr[current_x][current_y] = -1;
	// 访问其周围的点
	int i = 0;
	for(;i < 8;i++)
	{
	  int tmp_x = current_x + offset[i][0],
	  tmp_y = current_y + offset[i][1];
	  // 可访问
	  if(is_access(tmp_x,tmp_y))
	  {
		// 
		if(!is_through(current_x,current_y,tmp_x,tmp_y)) continue;
		// 将该点设置为已访问
		arr[tmp_x][tmp_y] = -1;
		// 在树中创建节点
	    create_node(tmp_x,tmp_y,index);
	  }
	}
	// 更新当前点位置
	index++;
	
	current_x = tree[index][0];
	current_y = tree[index][1];
  }
  // 标记路径
  
  int j = tree_index-1;
  while(tree[j][0] != target_x || 
  tree[j][1] != target_y) j--;
  
  do{
    arr[tree[j][0]][tree[j][1]] = -5;
	//printf("[%d,%d]%d,",tree[j][0],tree[j][1],j);
	j = tree[j][2];
  } while(j != -1);
  printf("\n");
}

int main()
{
  //
  obstacle[1][0] = 1;
  obstacle[1][1] = 1;
  obstacle[1][2] = 1;
  obstacle[1][3] = 1;
  
  //obstacle[3][1] = 1;
  obstacle[3][2] = 1;
  obstacle[3][3] = 1;
  obstacle[3][4] = 1;
  
  obstacle[4][1] = 1;
  obstacle[5][1] = 1;
  obstacle[6][1] = 1;
  obstacle[7][1] = 1;
  //
  vist(0,0);
  arr[0][0] = -8;
  arr[target_x][target_y] = -9;
  int i = 0;
  for(;i < MAX_Y;i++)
  {
	int j = 0;
	for(j = 0;j < MAX_X;j++)
	{
	  if(arr[j][i] != 0) printf("%d ",arr[j][i]);
	  else if(obstacle[j][i] == 1) printf("-# ");
	  else printf("-0 ");
	}
	printf("\n");
  }
}