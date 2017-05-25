/**
 * File: mapSystem.h
 * Description: mapSystem.c头文件
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.25
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef enum bool {
  FALSE = 0,
  TRUE = 1
} BOOL;  // 布尔值
typedef enum grid {
  ROAD = 0,  // 路
  OBSTACLE = 1,  // 障碍
  START = 2,  // 起点
  TARGET = 3,  // 目标
  VISITED = 4,  // 被访问
  PATH = 5  // 路径
} GRID;  // 地图格
typedef struct map {
  GRID **data;  // 地图数据
  int **weight;  // 权值
  int width,height;  // 地图尺寸
} MAP;  // 地图
