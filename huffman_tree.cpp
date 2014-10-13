//하나의 자료에는 문자와 빈도수  입출력방식 2가지
//중복을 검사하여 유일한 문자를 지닌 자료들만 입력
//빈도수를 이용하여 허프만트리(최소히프) 생성
//중간 노드들 w-? 으로 생성
//히프에 자료가 삽입/삭제 될때마다 중위순회로 출력
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct TreeNode{
	char ch[5];  //문자
	int weight;  //빈도수
	struct TreeNode *left_child;
	struct TreeNode *right_child;
}TreeNode;
typedef struct{
	TreeNode *ptree;
	int key;  //빈도수를 key값으로 가진다.
}element;
typedef struct{  
	element *heap;
	int heap_size;
}HeapType;


void huffman_tree(int size);  //허프만트리생성
TreeNode *make_tree(TreeNode *left,TreeNode *right);  //이진트리(노드) 생성
void destory_tree(TreeNode *root);  //이진트리 파괴
void insert_min_heap(HeapType *h,element item);  //히프에 삽입
element delete_min_heap(HeapType *h);  //히프에서 삭제

int main()
{
	int size;	

	printf("문자 개수? "); scanf("%d",&size); fflush(stdin);
	huffman_tree(size);
}

void huffman_tree(int size){
	int i,c=0,weight;
	char ch[5],num[4];	
	TreeNode *node, *x;
	HeapType h;
	element e,e1,e2;
	
	h.heap=(element*)malloc(sizeof(element)*size);  //히프생성
	h.heap_size=0;  //히프 초기화
	
	for(i=0; i<size; i++){
		printf("문자? "); scanf("%s",ch); fflush(stdin);
		printf("빈도수? "); scanf("%d",&weight);  fflush(stdin);
		node = make_tree(NULL,NULL);
		e.key = node->weight = weight;
		strcpy(node->ch,ch);
		e.ptree = node;
		insert_min_heap(&h,e);
	}
	for(i=1; i<size; i++){
		//최소값을 가지는 두개의 노드 삭제
		e1=delete_min_heap(&h);
		e2=delete_min_heap(&h);
		//두개의 노드를 합친다.
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

//히프에서 삽입
void insert_min_heap(HeapType *h,element item){
	int i;
	i=++(h->heap_size);  //1부터 넣기 위해 전위증가

	while((i != 1) && (item.key < h->heap[i/2].key)){
		h->heap[i]=h->heap[i/2];
		i /= 2;
	}
	h->heap[i]=item;
}

//히프에서 삭제
element delete_min_heap(HeapType *h){
	int parent,child;
	element item,temp;
	item=h->heap[1];  //루트 넣고
	temp=h->heap[(h->heap_size)--];  //마지막 노드 넣고 size감소
	parent=1;
	child=2;
	while(child <= h->heap_size){
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key))
			child++;
		if(temp.key >= h->heap[child].key) break;  //재배치 종료
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return item;
}

//이진트리 생성(트리에 들어갈 노드를 만든다)/
TreeNode *make_tree(TreeNode *left,TreeNode *right){
	TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
	if(node == NULL){
		printf("메모리 에러\n");
		exit(1);
	}
	node->left_child = left;
	node->right_child = right;
	return node;
}

//이진트리 제거
void destory_tree(TreeNode *root){
	if(root == NULL) return;
	destory_tree(root->left_child);
	destory_tree(root->right_child);
	free(root);
}



