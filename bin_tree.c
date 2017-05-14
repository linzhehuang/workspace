/**
 * File: bin_tree.c
 * Description: 实现二叉树的创建（非递归）、中序遍历
 * （非递归）、计算叶子节点个数（递归）
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.2
 * Date: 2017.5.14
 */
#include "bin_tree.h"

BOOL create_bin_tree(BIN_TREE *root)
{
  /* 创建根节点 */
  DATA_TYPE data = '\0';
  scanf("%c",&data);
  if(data == '#'){
    return FALSE; // 根节点为空，创建失败
  }
  else
  {
    *root = (NODE*)malloc(sizeof(NODE));
    (*root)->data = data;
    (*root)->left_subtree = NULL;
    (*root)->right_subtree = NULL;
  }
  
  /* 创建非根节点 */
  // 存放父层的节点列表
  NODE **parent_list = (NODE**)malloc(sizeof(NODE*));
  parent_list[0] = *root;
  // 父节点个数
  int parent_amount = 1;  
  
  while(1)
  {
    // 当前节点个数，设置为父节点个数的两倍
    int current_amount = parent_amount * 2;
    // 创建临时列表存放当前深度的节点
    NODE **tmp_list = (NODE**)malloc(sizeof(NODE*)
    * current_amount);
    // 用于记录当前深度节点非空节点个数
    int count = 0;
    // 创建当前层次的所有节点
    int j = 0;
    for(;j < current_amount;++j)
    {
      DATA_TYPE data = '\0';
      scanf("%c",&data);
	  if(data != '#')  // 不为空节点
      {
        // 新建节点并赋值
        NODE *current_node = (NODE*)malloc(sizeof(NODE));
        current_node->data = data;
        current_node->left_subtree = NULL;
        current_node->right_subtree = NULL;
        // 加入到临时列表中
        tmp_list[count] = current_node;
        // 非空节点数加1
        count++;
        // 与父节点建立关系
        if(j%2 == LEFT)
        {
          (parent_list[j/2])->left_subtree = current_node;
        }
        else
        {
          (parent_list[j/2])->right_subtree = current_node;
        }
      }
    }  // for循环结束
    
    // 释放父层列表
    free(parent_list);
    // 更新父层列表
    parent_list = tmp_list;
	// 更新父节点数
	parent_amount = count;
    // 若非空节点数为0，则停止创建
    if(count == 0) break;
  }
  return TRUE;
}
BOOL traversal(BIN_TREE root)
{
  // 检查参数
  if(!root) return FALSE;
  // 新建一个栈
  STACK stack = {NULL,0};
  // 入栈
  BOOL push(NODE **node)
  {
	stack.top++;
	if(!stack.stack) stack.stack = (NODE**)malloc(sizeof(NODE*));
	else stack.stack = (NODE**)realloc(stack.stack,sizeof(NODE*) * stack.top);
	stack.stack[stack.top-1] = *node;
	return TRUE;
  }
  // 出栈
  BOOL pop()
  {
	stack.top--;
	stack.stack = (NODE**)realloc(stack.stack,sizeof(NODE*) * stack.top);
	return TRUE;
  }
  // 取得栈顶元素
  NODE *top()
  {
	return stack.stack[stack.top-1];
  }
  // 栈是否为空
  BOOL is_empty()
  {
	if(stack.top == 0) return TRUE;
	else return FALSE;
  }
  // 开始遍历
  NODE *p = root;
  while(p || !is_empty())
  {  
    while(p)
    {
      push(&p);
      p = p->left_subtree;  
    }
    p = top();  
    pop();
    printf("%c",p->data);  
    p = p->right_subtree;
  }
  return TRUE;
}
int get_leaf_amount(BIN_TREE root)
{
  if(!root)
  {
	return 0;
  }
  else if(!root->left_subtree && !root->right_subtree)
  {
	return 1;
  }
  else
  {
	return get_leaf_amount(root->left_subtree) + 
	get_leaf_amount(root->right_subtree);
  }
}
int main()
{
  BIN_TREE tree = NULL;
  printf("按从上到下、从左到右的顺序创建，\
\"#\"代表空节点。例子如下：\n");
  printf("   A\n  /  \\\n B   C\n /\nD\n");
  printf("此时应输入：ABCD#####\n");
  
  create_bin_tree(&tree);
  printf("中序遍历结果：");
  traversal(tree);
  printf("\n叶子节点数：%d",get_leaf_amount(tree));
}