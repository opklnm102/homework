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
	char bit[20];  //��Ʈ
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
void inorder(TreeNode *root);  //������ȸ
int duplication(HeapType *h, char ch[]);  //���� �ߺ��˻�

//������Ʈ�� ������ ���
void insert_huffman(TreeNode **root, char ch[], int weight, TreeNode *left, TreeNode *right){
	TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
	if(node == NULL){
		printf("�޸� ����\n");
		exit(1);
	}
	strcpy(node->ch,ch);
	node->weight = weight;
	node->left_child = left;
	node->right_child = right;



}





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
	TreeNode *root = NULL;
	HeapType h;
	element e,e1,e2;

	h.heap=(element*)malloc(sizeof(element)*size);  //��������
	//hh.heap=(element*)malloc(sizeof(element)*(2*size-1));
	h.heap_size=0;  //���� �ʱ�ȭ
	//hh.heap_size=0;
	for(i=0; i<size; i++)
		h.heap[i].ptree=NULL;
	/*for(i=0; i<(2*size); i++)
		hh.heap[i].ptree=NULL;*/

	//min_heap�� ����� loop
	for(i=0; i<size; i++){
		printf("����? "); scanf("%s",ch); fflush(stdin);
		ch[1]='\0';  //���ڰ� �ƴ϶� ���ڿ��� �ԷµǸ� ù��° ���ڸ� ����
		printf("�󵵼�? "); scanf("%d",&weight);  fflush(stdin);
		//�ߺ� check(�ߺ��� ��� �� ���� ���Ѵ�)
		if(duplication(&h, ch)){
			i--;
		}
		else{
			node = make_tree(NULL,NULL);
			e.key = node->weight = weight;
			strcpy(node->ch,ch);
			e.ptree = node;
			insert_min_heap(&h,e);
			inorder(h.heap[1].ptree);//������ȸ			
			printf("\n");
		}
	}
	//huffman_tree�� ����� loop
	for(i=1; i<size; i++){		
		//�ּҰ��� ������ �ΰ��� ��� ����
		e1=delete_min_heap(&h);
		e2=delete_min_heap(&h);
		//�ΰ��� ��带 ��ģ��.
		x=make_tree(e1.ptree,e2.ptree);
		e.key = x->weight = e1.key+e2.key;
		strcpy(x->ch,"W-");  //���ͳγ�忡 ����(w-n)����
		itoa(++c,num,10);
		strcat(x->ch,num);			
		e.ptree=x;  
		insert_min_heap(&h,e);
		insert_huffman(&root,  x->ch, x->weight, x->left_child, x->right_child);	

	}
	e=delete_min_heap(&h);  //���� root��带 ������(�ּ�����)
	destory_tree(e.ptree);  //Ʈ�� ����(�ּ�����)

	//free(h.heap);
	
}

//�������� ����
void insert_min_heap(HeapType *h,element item){
	int i,j;
	i=++(h->heap_size);  //1���� �ֱ� ���� ��������
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));

	if((i != 1) && (item.key < h->heap[i/2].key)){
		while((i != 1) && (item.key < h->heap[i/2].key)){  //key�� �θ��庸�� ������� �ٲ۴�.(��Ʈ�� �ö󰣴�)
			h->heap[i]=h->heap[i/2];  //[i]�� �ڽĳ�� [i/2]�� �θ���

			if(i%2 == 0){  //¦��(�� �����ڽ�) ptree�� ��带 ����Ų��
				tmp->left_child = item.ptree->left_child;
				tmp->right_child = item.ptree->right_child;
				item.ptree->left_child = h->heap[i/2].ptree;
				item.ptree->right_child = h->heap[i/2].ptree->right_child;
				h->heap[i/2].ptree->left_child = tmp->left_child;
				h->heap[i/2].ptree->right_child = tmp->right_child;
				j=i/2;
				if(j/2 >= 1){
					if(j%2 == 0)
						h->heap[j/2].ptree->left_child = item.ptree;
					else
						h->heap[j/2].ptree->right_child = item.ptree;
				}
			}
			else{  //Ȧ��(�� �������ڽ�)
				tmp->left_child = item.ptree->left_child;
				tmp->right_child = item.ptree->right_child;
				item.ptree->left_child = h->heap[i/2].ptree->left_child;
				item.ptree->right_child =h->heap[i/2].ptree;
				h->heap[i/2].ptree->left_child = tmp->left_child;
				h->heap[i/2].ptree->right_child = tmp->right_child;
				j=i/2;
				if(j/2 >= 1){
					if(j%2 == 0)
						h->heap[j/2].ptree->left_child = item.ptree;
					else
						h->heap[j/2].ptree->right_child = item.ptree;
				}
			}
			i /= 2;		
		}
	}
	else if((i != 1) && (item.key >= h->heap[i/2].key)){  //���ġ �ȉ������
		if(i%2 == 0)  //¦��(�� �����ڽ�) ptree�� ��带 ����Ų��			
			h->heap[i/2].ptree->left_child = item.ptree;		
		else  //Ȧ��(�� �������ڽ�)
			h->heap[i/2].ptree->right_child = item.ptree;
	}
	h->heap[i]=item;
	free(tmp);
}

//�������� ����
element delete_min_heap(HeapType *h){
	int parent,child,j;
	element item,temp;
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));

	item=h->heap[1];  //��Ʈ �ְ�
	temp=h->heap[(h->heap_size)--];  //������ ��� �ְ� size����
	if(h->heap_size >= 1){
		if((h->heap_size+1)%2 == 0)  //������ ���� �θ���� ������ �����ش�.
			h->heap[(h->heap_size+1)/2].ptree->left_child =NULL;
		else
			h->heap[(h->heap_size+1)/2].ptree->right_child =NULL;
	}
	parent=1;
	child=2;

	while(child <= h->heap_size){  //��������带 ����������
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key)) 
			child++;    	//������ Ű���� Ŭ��� child�� ������ ��带 ����Ű��
		if(temp.key <= h->heap[child].key) break;  //���ġ ����		
		j=parent/2;

		if(child%2 == 0){  //¦��(�� �����ڽ�) ptree�� ��带 ����Ų��
			tmp->left_child = h->heap[child].ptree->left_child ;
			tmp->right_child = h->heap[child].ptree->right_child;
			h->heap[child].ptree->left_child = h->heap[parent].ptree;
			h->heap[child].ptree->right_child = h->heap[parent].ptree->right_child;
			h->heap[parent].ptree->left_child = tmp->left_child;
			h->heap[parent].ptree->right_child = tmp->right_child;
			if(j/2 >= 1){
				if(j%2 == 0)
					h->heap[j/2].ptree->left_child = h->heap[child].ptree;
				else
					h->heap[j/2].ptree->right_child = h->heap[child].ptree;
			}
		}
		else{  //Ȧ��(�� �������ڽ�)
			tmp->left_child = h->heap[child].ptree->left_child ;
			tmp->right_child = h->heap[child].ptree->right_child;
			h->heap[child].ptree->left_child = h->heap[parent].ptree->left_child;
			h->heap[child].ptree->right_child = h->heap[parent].ptree;
			h->heap[parent].ptree->left_child = tmp->left_child;
			h->heap[parent].ptree->right_child = tmp->right_child;
			if(j/2 >= 1){
				if(j%2 == 0)
					h->heap[j/2].ptree->left_child = h->heap[child].ptree;
				else
					h->heap[j/2].ptree->right_child = h->heap[child].ptree;
			}
		}		
		h->heap[parent] = h->heap[child];  //�ڽ��� �θ�� �ø���.
		parent = child;
		child *= 2;
	}
	if(temp.ptree->ch[1] == '\0'){
		temp.ptree->left_child = h->heap[parent].ptree->left_child;
		temp.ptree->right_child = h->heap[parent].ptree->right_child;
	}
	h->heap[parent] = temp;
	if(parent/2 >= 1){
		if(parent%2 ==0)
			h->heap[parent/2].ptree->left_child = h->heap[parent].ptree;
		else
			h->heap[parent/2].ptree->right_child = h->heap[parent].ptree;
	}

	free(tmp);
	if(item.ptree->ch[1] == '\0'){  //���������� �ܸ�����
		item.ptree->left_child = NULL;
		item.ptree->right_child = NULL;
	}
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

//������ȸ
void inorder(TreeNode *root){
	if(root){
		inorder(root->left_child);
		printf("%s  ",root->ch);
		inorder(root->right_child);
	}
}

//�ߺ��� ��� 1���� �ƴҰ�� 0 ����
int duplication(HeapType *h, char ch[]){
	int i;
	for(i=1; i<=h->heap_size; i++){
		if(strcmp(ch,h->heap[i].ptree->ch) == 0){  //�ߺ� ���� check
			printf("���ڰ� �ߺ��� ���� ���ϰڽ��ϴ�\n");
			return 1;
		}
	}
	return 0;
}

