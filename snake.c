#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>

typedef struct _Grid {
  unsigned int x, y;
} Grid;

typedef struct _Snake {
  Grid* body;
  unsigned int len;
} Snake;

int direction = 1;
int dirLock = 0;
int isRun = 1;

int getch() {
    int c = 0;
    struct termios org_opts, new_opts;

    tcgetattr(STDIN_FILENO, &org_opts);
    memcpy(&new_opts, &org_opts, sizeof(org_opts));
    
    new_opts.c_lflag &= ~(ICANON | ECHO | ECHOE | ECHOK | ECHONL | ECHOPRT | ECHOKE);
    tcsetattr(STDIN_FILENO, TCSANOW, &new_opts);
    
    c = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &org_opts);

    return c;
}

void delay(long ms) {
  struct timeval begin, now;
  gettimeofday(&begin, NULL);
  
  for (;;) {
    gettimeofday(&now, NULL);
    long dist = (now.tv_sec - begin.tv_sec) * 1000;
    dist += (now.tv_usec -begin.tv_usec) / 1000;
    if (dist > ms) break;
  }
}

int canPlace(int x, int y, Snake* s) {
  int i = 0;
  for (; i < s->len; i++)
    if (x == s->body[i].x &&
        y == s->body[i].y)
        return 0;
  return 1;
}

int whichPartOfSnake(int x, int y, Snake* s) {
  // not-0, head-1, body-2, tail-3
  int i = 0;
  for (; i < s->len; i++)
    if (x == s->body[i].x &&
        y == s->body[i].y) {
      if (i == 0) return 1;
      else if (i == (s->len-1)) return 3;
      else return 2;
    }
  return 0;
}

int isCrash(Grid head, Snake* s, int w, int h) {
  if (head.x < 0 || head.x >= w)
    return 1;
  if (head.y < 0 || head.y >= h)
    return 1;
  
  int i = 1;
  for (; i < s->len; i++)
    if (head.x == s->body[i].x &&
        head.y == s->body[i].y)
        return 1;
  return 0;
}

int isEatFood(Grid head, Grid f) {
  if (f.x == head.x && f.y == head.y)
    return 1;
  return 0;
}

int getRandNum(int f, int t) {
  return rand()%(t-f+1)+f;
}

void placeFood(Grid* f, Snake* s, int w, int h) {
  int x = 0, y = 0;
  for(;;) {
    x = getRandNum(0, w-1);
    y = getRandNum(0, h-1);
    if (canPlace(x, y, s) == 1) break;
  }
  f->x = x;
  f->y = y;
}

void initSnake(Snake* s, int w, int h) {
  int wM = w / 2, hM = h / 2;
  s->body = (Grid*)malloc((w*h-1));
  s->len = 3;
  
  s->body[0].x = wM + 1;
  s->body[0].y = hM;
  s->body[1].x = wM;
  s->body[1].y = hM;
  s->body[2].x = wM - 1;
  s->body[2].y = hM;
}

void moveGrid(Grid* g, int d) {
  Grid offsets[4] = {
    // up right down left
    { .x = 0, .y = -1 },
    { .x = 1, .y = 0 },
    { .x = 0, .y = 1 },
    { .x = -1, .y = 0 }
  };
  g->x += offsets[d].x;
  g->y += offsets[d].y;
}

void moveSnake(Snake* s, int d, int isGrow) {
  Grid tail = {
    .x = s->body[s->len-1].x,
    .y = s->body[s->len-1].y
  };
  
  int i = s->len - 1;
  for(; i > 0; i--) {
    s->body[i].x = s->body[i-1].x;
    s->body[i].y = s->body[i-1].y;
  }
  moveGrid(&(s->body[0]), d);
  
  if (isGrow == 1) {
    s->body[s->len].x = tail.x;
    s->body[s->len].y = tail.y;
    s->len++;
  }
}

void drawFrame(Snake* s, Grid* f, int w, int h) {
  system("clear");
  int i = 0, j = 0;
  
  for (j = 0; j < w+2; j++) printf("-");
  printf("\n");
  
  for (; i < h; i++) {
    printf("|");
    for (j = 0; j < w; j++) {
      switch (whichPartOfSnake(j, i, s)) {
      case 1:
        printf("O");
      break;
      case 2:
      case 3:
        printf("+");
      break;
      default:
        if (j == f->x && i == f->y) {
          printf("*");
        }
        else {
          printf(" ");
        }
      break;
      }
    }
    printf("|\n");
  }
  
  for (j = 0; j < w+2; j++) printf("-");
  printf("\n");
}

void* keyEventListener(void* arg) {
  int c;
  while (isRun) {
    while (dirLock);
    c = getch();
    if (c == 'q') isRun = 0;
    else {
      switch (c) {
      case 'w':
      case '2':
        if (direction != 2) { 
          direction = 0;
          dirLock = 1;
        }
      break;
      case 'd':
      case '6':
        if (direction != 3) { 
          direction = 1;
          dirLock = 1;
        }
      break;
      case 's':
      case '8':
        if (direction != 0) { 
          direction = 2;
          dirLock = 1;
        }
      break;
      case 'a':
      case '4':
        if (direction != 1) { 
          direction = 3;
          dirLock = 1;
        }
      break;
      default:
      continue;
      }
    }
  }
  
  return NULL;
}

int main(void) {
  int mapW = 16, mapH = 10;
  int isGrow = 0;
  Snake snake;
  Grid food;
  pthread_t listener_tid;
  
  if (pthread_create(&listener_tid, NULL, 
    keyEventListener, NULL)) {
    printf("Create keyEventListener failed.");
    return -1;
  }
  
  srand((unsigned)time(NULL));
  initSnake(&snake, mapW, mapH);
  placeFood(&food, &snake, mapW, mapH);
  
  while (isRun) {
    drawFrame(&snake, &food, mapW, mapH);
    delay(400);
    moveSnake(&snake, direction, isGrow);
    if (dirLock == 1) dirLock = 0;
    if (isGrow == 1) isGrow = 0;
    if (isEatFood(snake.body[0], food) == 1) {
      isGrow = 1;
      placeFood(&food, &snake, mapW, mapH);
    }
    else if (isCrash(snake.body[0], &snake, mapW, mapH) == 1) {
      isRun = 0;
      break;
    }
  }

  printf("Game over!\n");
  // pthread_cancel() unsupport in android.
  //pthread_cancel(listener_tid);
  pthread_join(listener_tid, NULL);

  return 0;
}
