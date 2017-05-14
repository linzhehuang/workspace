/**
 * File: bin_tree.h
 * Description: bin_tree.c的头文件
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.2
 * Date: 2017.5.14
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

/* Function: create_bin_tree
 * Description: 创建二叉树，按从上到下、从左到右
 * 的顺序创建，"#"代表空节点
 * Parma: 
 *   BIN_TREE *root-二叉树指针
 * Return: BOOL，成功返回TRUE，否则FALSE
 */
BOOL create_bin_tree(BIN_TREE *root);
/* Function: traversal
 * Description: 中序遍历二叉树并输出结果
 * Parma: 
 *   BIN_TREE root-二叉树
 * Return: BOOL，成功返回TRUE，否则FALSE
 */
BOOL traversal(BIN_TREE root);
/* Function: get_leaf_amount
 * Description: 获取二叉树叶子节点数
 * Parma: 
 *   BIN_TREE root-二叉树
 * Return: int，叶子节点数
 */
int get_leaf_amount(BIN_TREE root);