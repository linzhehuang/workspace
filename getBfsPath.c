typedef enum bool {
  FALSE = 0,
  TRUE = 1
} BOOL;
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
  int width,height;  // 地图尺寸
} MAP;  // 地图
// 
#include <stdio.h>
#include <malloc.h>

BOOL getBfsPath(MAP map) {
  if(!map.data) return FALSE;
  // 寻找起点和目标
  int startX = 0,startY = 0,
  targetX = 0,targetY = 0;
  int i = 0,j = 0,count = 0;
  for(i = 0;i < map.width;i++) {
    for(j = 0;j < map.height;j++) {
      if(map.data[i][j] == START) {
        startX = i;
        startY = j;
        count++;
      }
      else if(map.data[i][j] == TARGET) {
        targetX = i;
        targetY = j;
        count++;
      }
      else continue;
    }
  }
  // 未找到起点或目标
  if(count != 2) return FALSE;
  
  typedef struct triple {
    int x,y;  // 位置
    int parent;  // 父节点
  } TRIPLE;  // 三元组
  // 创建三元组表并定义其插入操作
  int tripleIndex = 0;
  int mapSize = map.width * map.height;
  TRIPLE *triple = (TRIPLE*)malloc(sizeof(TRIPLE) * mapSize);
  void insert(int x,int y,int parent) {
    triple[tripleIndex].x = x;
    triple[tripleIndex].y = y;
    triple[tripleIndex].parent = parent;
    tripleIndex++;
  }
  // 该点是否可访问
  BOOL isAccess(int x,int y) {
    if(y < 0 || y >= map.height) return FALSE;
    else if(x < 0 || x >= map.width) return FALSE;
    else {
      GRID gridData = map.data[x][y];
      if(gridData == VISITED) return FALSE;
      else if(gridData == OBSTACLE) return FALSE;
      else if(gridData == START) return FALSE;
      else return TRUE;
    }
  }
  // 周围点相对当前点偏移值
  int offset[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
  int currentX = startX,currentY = startY;
  insert(currentX,currentY,-1);
  
  // 开始遍历
  i = 0;
  while(currentX != targetX || currentY != targetY) {
    // 访问当前点的周围可访问点并加入三元组表
    for(j = 0;j < 4;j++) {
      int neighborX = currentX + offset[j][0],
      neighborY = currentY + offset[j][1];
      if(isAccess(neighborX,neighborY) == TRUE) {
        map.data[neighborX][neighborY] = VISITED;
        insert(neighborX,neighborY,i);
      }
    }
    i++;
    // 起点与目标被隔断
    if(i == tripleIndex) return FALSE;
    // 更新当前点
    currentX = triple[i].x;
    currentY = triple[i].y;
  }
  
  // 回溯标记路径
  while(i != -1) {
    map.data[currentX][currentY] = PATH;
    currentX = triple[i].x;
    currentY = triple[i].y;
    i = triple[i].parent;
  } 
  // 还原起点和目标位置数据
  map.data[startX][startY] = START;
  map.data[targetX][targetY] = TARGET;
  return TRUE;
}
BOOL setGridData(MAP map,int x,int y,GRID type) {
  if(!map.data) return FALSE;
  else if(x < 0 || x >= map.width ||
  y < 0 || y >= map.height) return FALSE;
  else {
    map.data[x][y] = type;
    return TRUE;
  }
}
BOOL showMap(MAP map) {
  int i = 0,j = 0;
  char symbolList[6] = {'0','#','@','@','0','+'};
  for(i = 0;i < map.height;i++) {
    for(j = 0;j < map.width;j++) {
      printf("%c ",symbolList[map.data[j][i]]);
    }
    printf("\n");
  }
}
BOOL createMap(MAP *map) {
  if(map->width <= 0 || map->height <= 0) return FALSE;
  // 每个地图格默认赋值为ROAD
  GRID **col = (GRID**)malloc(sizeof(GRID*) * map->width);
  int i = 0,j = 0;
  for(;i < map->width;i++) {
    GRID *row = (GRID*)malloc(sizeof(GRID) * map->height);
    for(j = 0;j < map->height;j++) {
      row[j] = ROAD;
    }
    col[i] = row;
  }
  // 传出地图
  map->data = col;
  return TRUE;
}
int main() {
  MAP map = {NULL,11,11};
  createMap(&map);
  setGridData(map,0,3,START);
  setGridData(map,10,2,TARGET);
  
  setGridData(map,1,0,OBSTACLE);
  setGridData(map,1,1,OBSTACLE);
  setGridData(map,1,2,OBSTACLE);
  setGridData(map,1,3,OBSTACLE);
  setGridData(map,1,4,OBSTACLE);
  setGridData(map,1,5,OBSTACLE);
  setGridData(map,1,6,OBSTACLE);
  
  setGridData(map,2,3,OBSTACLE);
  setGridData(map,3,3,OBSTACLE);
  setGridData(map,4,3,OBSTACLE);
  setGridData(map,5,3,OBSTACLE);
  setGridData(map,6,3,OBSTACLE);
  setGridData(map,7,3,OBSTACLE);
  setGridData(map,8,3,OBSTACLE);
  setGridData(map,9,3,OBSTACLE);
  setGridData(map,10,3,OBSTACLE);
  
  getBfsPath(map);
  showMap(map);
}