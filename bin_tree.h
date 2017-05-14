/**
 * File: bin_tree.h
 * Description: bin_tree.c的头文件
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.1
 * Date: 2017.5.7
 */
#include <stdio.h>
#include <malloc.h>

// 布尔值
typedef enum {FALSE=0,TRUE=1} BOOL;
// 用于标识当前建立左子树还是右子树
typedef enum {LEFT=0,RIGHT=1} FLAG;
// 节点存放数据的类型
typedef char DATA_TYPE;
// 二叉树节点
typedef struct node {
  DATA_TYPE data;
  struct node *left_subtree,
  *right_subtree;
} NODE , *BIN_TREE;
// 栈
typedef struct stack
{
  NODE **stack;  // 栈体
  int top;  // 栈顶
} STACK;