/**
 * File: bin_tree.c
 * Description: ʵ�ֶ������Ĵ������ǵݹ飩���������
 * ���ǵݹ飩������Ҷ�ӽڵ�������ݹ飩
 * Author: linzhehuang
 * Blog: http://www.cnblogs.com/linzhehuang/
 * Version: 0.0.2
 * Date: 2017.5.14
 */
#include "bin_tree.h"

BOOL create_bin_tree(BIN_TREE *root)
{
  /* �������ڵ� */
  DATA_TYPE data = '\0';
  scanf("%c",&data);
  if(data == '#'){
    return FALSE; // ���ڵ�Ϊ�գ�����ʧ��
  }
  else
  {
    *root = (NODE*)malloc(sizeof(NODE));
    (*root)->data = data;
    (*root)->left_subtree = NULL;
    (*root)->right_subtree = NULL;
  }
  
  /* �����Ǹ��ڵ� */
  // ��Ÿ���Ľڵ��б�
  NODE **parent_list = (NODE**)malloc(sizeof(NODE*));
  parent_list[0] = *root;
  // ���ڵ����
  int parent_amount = 1;  
  
  while(1)
  {
    // ��ǰ�ڵ����������Ϊ���ڵ����������
    int current_amount = parent_amount * 2;
    // ������ʱ�б��ŵ�ǰ��ȵĽڵ�
    NODE **tmp_list = (NODE**)malloc(sizeof(NODE*)
    * current_amount);
    // ���ڼ�¼��ǰ��Ƚڵ�ǿսڵ����
    int count = 0;
    // ������ǰ��ε����нڵ�
    int j = 0;
    for(;j < current_amount;++j)
    {
      DATA_TYPE data = '\0';
      scanf("%c",&data);
	  if(data != '#')  // ��Ϊ�սڵ�
      {
        // �½��ڵ㲢��ֵ
        NODE *current_node = (NODE*)malloc(sizeof(NODE));
        current_node->data = data;
        current_node->left_subtree = NULL;
        current_node->right_subtree = NULL;
        // ���뵽��ʱ�б���
        tmp_list[count] = current_node;
        // �ǿսڵ�����1
        count++;
        // �븸�ڵ㽨����ϵ
        if(j%2 == LEFT)
        {
          (parent_list[j/2])->left_subtree = current_node;
        }
        else
        {
          (parent_list[j/2])->right_subtree = current_node;
        }
      }
    }  // forѭ������
    
    // �ͷŸ����б�
    free(parent_list);
    // ���¸����б�
    parent_list = tmp_list;
	// ���¸��ڵ���
	parent_amount = count;
    // ���ǿսڵ���Ϊ0����ֹͣ����
    if(count == 0) break;
  }
  return TRUE;
}
BOOL traversal(BIN_TREE root)
{
  // ������
  if(!root) return FALSE;
  // �½�һ��ջ
  STACK stack = {NULL,0};
  // ��ջ
  BOOL push(NODE **node)
  {
	stack.top++;
	if(!stack.stack) stack.stack = (NODE**)malloc(sizeof(NODE*));
	else stack.stack = (NODE**)realloc(stack.stack,sizeof(NODE*) * stack.top);
	stack.stack[stack.top-1] = *node;
	return TRUE;
  }
  // ��ջ
  BOOL pop()
  {
	stack.top--;
	stack.stack = (NODE**)realloc(stack.stack,sizeof(NODE*) * stack.top);
	return TRUE;
  }
  // ȡ��ջ��Ԫ��
  NODE *top()
  {
	return stack.stack[stack.top-1];
  }
  // ջ�Ƿ�Ϊ��
  BOOL is_empty()
  {
	if(stack.top == 0) return TRUE;
	else return FALSE;
  }
  // ��ʼ����
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
  printf("�����ϵ��¡������ҵ�˳�򴴽���\
\"#\"����սڵ㡣�������£�\n");
  printf("   A\n  /  \\\n B   C\n /\nD\n");
  printf("��ʱӦ���룺ABCD#####\n");
  
  create_bin_tree(&tree);
  printf("������������");
  traversal(tree);
  printf("\nҶ�ӽڵ�����%d",get_leaf_amount(tree));
}