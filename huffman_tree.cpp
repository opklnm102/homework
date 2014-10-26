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
	char bit[20];  //비트
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
void inorder(TreeNode *root);  //중위순회
int duplication(HeapType *h, char ch[]);  //문자 중복검사

//허프만트리 생성시 사용
void insert_huffman(TreeNode **root, char ch[], int weight, TreeNode *left, TreeNode *right){
	TreeNode *node=(TreeNode*)malloc(sizeof(TreeNode));
	if(node == NULL){
		printf("메모리 에러\n");
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

	printf("문자 개수? "); scanf("%d",&size); fflush(stdin);
	huffman_tree(size);
}

void huffman_tree(int size){
	int i,c=0,weight;
	char ch[5],num[4];	
	TreeNode *node, *x;
	TreeNode *root = NULL;
	HeapType h;
	element e,e1,e2;

	h.heap=(element*)malloc(sizeof(element)*size);  //히프생성
	//hh.heap=(element*)malloc(sizeof(element)*(2*size-1));
	h.heap_size=0;  //히프 초기화
	//hh.heap_size=0;
	for(i=0; i<size; i++)
		h.heap[i].ptree=NULL;
	/*for(i=0; i<(2*size); i++)
		hh.heap[i].ptree=NULL;*/

	//min_heap를 만드는 loop
	for(i=0; i<size; i++){
		printf("문자? "); scanf("%s",ch); fflush(stdin);
		ch[1]='\0';  //문자가 아니라 문자열이 입력되면 첫번째 문자만 저장
		printf("빈도수? "); scanf("%d",&weight);  fflush(stdin);
		//중복 check(중복일 경우 값 저장 안한다)
		if(duplication(&h, ch)){
			i--;
		}
		else{
			node = make_tree(NULL,NULL);
			e.key = node->weight = weight;
			strcpy(node->ch,ch);
			e.ptree = node;
			insert_min_heap(&h,e);
			inorder(h.heap[1].ptree);//중위순회			
			printf("\n");
		}
	}
	//huffman_tree를 만드는 loop
	for(i=1; i<size; i++){		
		//최소값을 가지는 두개의 노드 삭제
		e1=delete_min_heap(&h);
		e2=delete_min_heap(&h);
		//두개의 노드를 합친다.
		x=make_tree(e1.ptree,e2.ptree);
		e.key = x->weight = e1.key+e2.key;
		strcpy(x->ch,"W-");  //인터널노드에 문자(w-n)삽입
		itoa(++c,num,10);
		strcat(x->ch,num);			
		e.ptree=x;  
		insert_min_heap(&h,e);
		insert_huffman(&root,  x->ch, x->weight, x->left_child, x->right_child);	

	}
	e=delete_min_heap(&h);  //최종 root노드를 꺼내서(최소히프)
	destory_tree(e.ptree);  //트리 삭제(최소히프)

	//free(h.heap);
	
}

//히프에서 삽입
void insert_min_heap(HeapType *h,element item){
	int i,j;
	i=++(h->heap_size);  //1부터 넣기 위해 전위증가
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));

	if((i != 1) && (item.key < h->heap[i/2].key)){
		while((i != 1) && (item.key < h->heap[i/2].key)){  //key가 부모노드보다 작을경우 바꾼다.(루트로 올라간다)
			h->heap[i]=h->heap[i/2];  //[i]는 자식노드 [i/2]는 부모노드

			if(i%2 == 0){  //짝수(즉 왼쪽자식) ptree는 노드를 가리킨다
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
			else{  //홀수(즉 오른쪽자식)
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
	else if((i != 1) && (item.key >= h->heap[i/2].key)){  //재배치 안됬을경우
		if(i%2 == 0)  //짝수(즉 왼쪽자식) ptree는 노드를 가리킨다			
			h->heap[i/2].ptree->left_child = item.ptree;		
		else  //홀수(즉 오른쪽자식)
			h->heap[i/2].ptree->right_child = item.ptree;
	}
	h->heap[i]=item;
	free(tmp);
}

//히프에서 삭제
element delete_min_heap(HeapType *h){
	int parent,child,j;
	element item,temp;
	TreeNode *tmp = (TreeNode*)malloc(sizeof(TreeNode));

	item=h->heap[1];  //루트 넣고
	temp=h->heap[(h->heap_size)--];  //마지막 노드 넣고 size감소
	if(h->heap_size >= 1){
		if((h->heap_size+1)%2 == 0)  //마지막 노드와 부모와의 연결을 끊어준다.
			h->heap[(h->heap_size+1)/2].ptree->left_child =NULL;
		else
			h->heap[(h->heap_size+1)/2].ptree->right_child =NULL;
	}
	parent=1;
	child=2;

	while(child <= h->heap_size){  //마지막노드를 만날때까지
		if((child<h->heap_size) && (h->heap[child].key > h->heap[child+1].key)) 
			child++;    	//왼쪽의 키값이 클경우 child가 오른쪽 노드를 가리키게
		if(temp.key <= h->heap[child].key) break;  //재배치 종료		
		j=parent/2;

		if(child%2 == 0){  //짝수(즉 왼쪽자식) ptree는 노드를 가리킨다
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
		else{  //홀수(즉 오른쪽자식)
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
		h->heap[parent] = h->heap[child];  //자식을 부모로 올린다.
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
	if(item.ptree->ch[1] == '\0'){  //허프만에서 단말노드들
		item.ptree->left_child = NULL;
		item.ptree->right_child = NULL;
	}
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

//중위순회
void inorder(TreeNode *root){
	if(root){
		inorder(root->left_child);
		printf("%s  ",root->ch);
		inorder(root->right_child);
	}
}

//중복일 경우 1리턴 아닐경우 0 리턴
int duplication(HeapType *h, char ch[]){
	int i;
	for(i=1; i<=h->heap_size; i++){
		if(strcmp(ch,h->heap[i].ptree->ch) == 0){  //중복 문자 check
			printf("문자가 중복됨 저장 안하겠습니다\n");
			return 1;
		}
	}
	return 0;
}

