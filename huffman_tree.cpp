//�ϳ��� �ڷῡ�� ���ڿ� �󵵼�  ����¹�� 2����
//�ߺ��� �˻��Ͽ� ������ ���ڸ� ���� �ڷ�鸸 �Է�
//�󵵼��� �̿��Ͽ� ������Ʈ��(�ּ�����) ����
//�߰� ���� w-? ���� ����
//������ �ڷᰡ ����/���� �ɶ����� ������ȸ�� ���
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TreeNode{
	char ch[5];  //����
	int weight;  //�󵵼�
	struct TreeNode *left_child;
	struct TreeNode *right_child;
}TreeNode;
typedef struct{
	TreeNode *ptree;
	int key;  //�󵵼��� key������ ������.
}element;
typedef struct{  
	element *heap;
	int heap_size;
}HeapType;


void huffman_tree(int size);  //������Ʈ������
TreeNode *make_tree(TreeNode *left,TreeNode *right);  //����Ʈ��(���) ����
void destory_tree(TreeNode *root);  //����Ʈ�� �ı�
void insert_min_heap(HeapType *h,element item);  //������ ����
element delete_min_heap(HeapType *h);  //�������� ����

int main()
{
	int size;	

	printf("���� ����? "); scanf("%d",&size); fflush(stdin);
	huffman_tree(size);
}

void huffman_tree(int size){
	int i,c=0,weight;
	char ch[5],num[4];	
	TreeNode *node, *x;
	HeapType h;
	element e,e1,e2;
	
	h.heap=(element*)malloc(sizeof(element)*size);  //��������
	h.heap_size=0;  //���� �ʱ�ȭ
	
	for(i=0; i<size; i++){
		printf("����? "); scanf("%s",ch); fflush(stdin);
		printf("�󵵼�? "); scanf("%d",&weight);  fflush(stdin);
		node = make_tree(NULL,NULL);
		e.key = node->weight = weight;
		strcpy(node->ch,ch);
		e.ptree = node;
		insert_min_heap(&h,e);
	}
	for(i=1; i<size; i++){
		//�ּҰ��� ������ �ΰ��� ��� ����
		e1=delete_min_heap(&h);
		e2=delete_min_heap(&h);
		//�ΰ��� ��带 ��ģ��.
		x=make_tree(e1.ptree,e2.ptree);
		e.key = x->weight = e1.key+e2.key;
		strcpy(x->ch,"W-");
		itoa(++c,num,10);
		strcat(x->ch,num);			
		e.ptree=x;
		insert_min_heap(&h,e);
	}
	e=delete_min_heap(&h);
	destory_tree(e.ptree);
}

//�������� ����
void insert_min_heap(HeapType *h,element item){
	int i;
	i=++(h->heap_size);  //1���� �ֱ� ���� ��������

	while((i != 1) && (item.key < h->heap[i/2].key)){
		h->heap[i]=h->heap[i/2];
		i /= 2;
	}
	h->heap[i]=item;
}

//�������� ����
element delete_min_heap(HeapType *h){
	int parent,child;
	element item,temp;
	item=h->heap[1];  //��Ʈ �ְ�
	temp=h->heap[(h->heap_size)--];  //������ ��� �ְ� size����
	parent=1;
	child=2;
	while(child <= h->heap_size){
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
			child++;
		if(temp.key >= h->heap[child].key) break;  //���ġ ����
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//����Ʈ�� ����(Ʈ���� �� ��带 �����)/
TreeNode *make_tree(TreeNode *left,TreeNode *right){
	TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
	if(node == NULL){
		printf("�޸� ����\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}

//����Ʈ�� ����
void destory_tree(TreeNode *root){
	if(root == NULL) return;
	destory_tree(root->left_child);
	destory_tree(root->right_child);
	free(root);
}



