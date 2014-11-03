#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define BUCKETS 10  //기수정렬 버켓수
#define DIGITS 4  //기수정렬 자릿수

//히프정렬을 위한 구조체
typedef struct{ 
	int *heap;
	int heap_size;
}HeapType;

//기수정렬을 위한 구조체
typedef struct QueueNode{
	int item;
	struct QueueNode *link;
}QueueNode;
typedef struct{
	QueueNode *front,*rear;
}QueueType;

void selection_sort(int list[],int n,int order);			    //선택 정렬
void insertion_sort(int list[],int n,int order);		        //삽입 정렬
void bubble_sort(int list[],int n,int order);			        //버블 정렬
void merge_sort(int list[],int left,int right,int order,int n);	//합병 정렬
void merge(int list[],int left,int mid,int right,int order);
void heap_sort(int list[],int n,int order);                     //히프 정렬
void insert_max_heap(HeapType *h,int key);  //히프에 삽입
int delete_max_heap(HeapType *h);  //히프에서 삭제
void quick_sort(int list[],int left,int right,int order,int n); //퀵 정렬
int partition(int list[],int left,int right,int order,int n);
void radix_sort(int list[],int n,int order);					//기수 정렬
void init(QueueType *q);  //큐 초기화
int is_empty(QueueType *q);  //큐 공백검사
void enqueue(QueueType *q,int item);  //큐에 삽입
int dequeue(QueueType *q);  //큐에서 삭제
void shell_sort(int list[],int n,int order);					//쉘 정렬
void inc_insertion(int list[],int first,int last,int gap,int order);
int select_order();  //오름차순 내림차순 선택
int input(int arr[]);  //입력
void swap(int *a, int *b);  //스왑
void print(int list[],int n);  //출력

int main(int argc,char *argv[])
{
	char ch;
	int order,n;
	int arr[100];
	FILE *fp;
	while(1){
		while(1){
			printf("==================\n");
			printf("선택 정렬 : s\n삽입 정렬 : i\n버블 정렬 : b\n");
			printf("합병 정렬 : m\n히프 정렬 : h\n기수 정렬 : r\n퀵 정렬 : q\n");
			printf("쉘 정렬 : l\n프로그램 종료 : x\n");
			printf("===================\n");
			printf("원하는 정렬을 선택하시오 : ");
			scanf("%c",&ch); fflush(stdin);
			ch=tolower(ch);
			if(ch == 'x') exit(1);
			if(ch == 's' || ch == 'i' || ch == 'b' || ch == 'm' || ch == 'h' || ch == 'r'
				|| ch == 'q' || ch == 'l')
				break;
		}
		order=select_order();  //오름,내림차순 결정

		if(argc == 1){  //정렬할 데이터 입력		
			n=input(arr);      
		}
		else if(argc == 2){
			fp=fopen(argv[1],"r");
			if(fp == NULL){
				printf("Error: %s can not open.\n",argv[1]);
				exit(1);
			}	
			fscanf(fp,"%d",&n);  //정렬할 자료의 갯수 입력
			for(int i=0; i<n; i++)  //정렬할 자료들 입력
				fscanf(fp,"%d",&arr[i]);
		}
		printf("입력한 숫자\n");
		print(arr,n); printf("\n");

		//메뉴 선택
		switch(ch){
		case 's' : //선택 정렬
			printf("-----선택정렬-----\n");
			selection_sort(arr,n,order); break;
		case 'i' :  //삽입 정렬
			printf("-----삽입정렬-----\n");
			insertion_sort(arr,n,order); break;
		case 'b' :  //버블 정렬 
			printf("-----버블정렬-----\n");
			bubble_sort(arr,n,order); break;
		case 'm' :  //합병 정렬 
			printf("-----합병정렬-----\n");
			merge_sort(arr,0,n-1,order,n);
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n"); break;
		case 'h' :  //히프 정렬 
			printf("-----히프정렬-----\n");
			heap_sort(arr,n,order); 
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n"); break;
		case 'r' :  //기수 정렬 
			printf("-----기수정렬-----\n");
			radix_sort(arr,n,order);
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n"); break;
		case 'q' :  //퀵 정렬
			printf("-----퀵 정렬-----\n");
			quick_sort(arr,0,n-1,order,n);
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n"); break;
		case 'l' :  //쉘 정렬
			printf("-----쉘 정렬-----\n");
			shell_sort(arr,n,order);
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n"); break;		
		}
	}
}

//오름차순 내림차순 선택
int select_order(){
	char order;

	while(1){
		printf("==================\n");
		printf("오름차순 : i\n내림차순 : d\n");
		printf("==================\n");
		scanf("%c",&order); fflush(stdin);

		if(order == 'i' || order == 'I')  //오름차순이면 1리턴 내림차순 2리턴
			return 1; 
		else if(order == 'd' || order == 'D')
			return 2;
	}
}

//입력
int input(int arr[]){
	char ch[10];
	int check,i,j;

	for(i=0; i<50; i++){
		check=0;
		printf("숫자 입력(최대 50개,'='입력하면 입력 종료): ");
		scanf("%s",ch); fflush(stdin);
		if(ch[0] == '=')  //'='은 입력 종료
			break;

		for(j=0; j<strlen(ch); j++)  //입력된 문자열이 숫자가 아닐수도있으니..
			if(ch[j] < 48 && 57 < ch[j])
				check++;

		if(check == 0)
			arr[i]=atoi(ch);
		else
			i--;		
	}
	return i;
}

//스왑
void swap(int *a, int *b){
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

//출력
void print(int list[],int n){
	for(int i=0; i<n; i++)
		printf("%d  ",list[i]);
	printf("\n");
}

//선택 정렬(오른쪽에서 최소값을 왼쪽 첫번쨰와 교환)
void selection_sort(int list[],int n,int order){
	int i,j,index;
	for(i=0; i<n-1; i++){
		index=i;  //최소or최대값의 인덱스
		for(j=i+1; j<n; j++){
			if(order == 1){
				if(list[j] < list[index])  //오름차순 
					index=j; 
			}
			else{
				if(list[j] > list[index])  //내림차순
					index=j; 
			}
		}
		swap(&list[i],&list[index]);
		print(list,n);
	}
	printf("\n정렬이 완료 되었습니다.\n");
	print(list,n);
	printf("\n");
}

//삽입 정렬(정렬되어있는 부분에 새로운 레코드를 삽입, 요소들의 이동은 이웃끼리) 
void insertion_sort(int list[],int n,int order){
	int i,j,key;
	for(i=1; i<n; i++){
		key=list[i];
		if(order == 1){  //오름차순
			for(j=i-1; j>=0 && list[j] > key; j--)
				list[j+1]=list[j];  //뒤로 민다
		}
		else{  //내림차순
			for(j=i-1; j>=0 && list[j] < key; j--)
				list[j+1]=list[j];  //뒤로민다
		}
		list[j+1]=key;  //뒤로 다밀었을때 
		print(list,n);
	}
	printf("\n정렬이 완료 되었습니다.\n");
	print(list,n);
	printf("\n");
}

//버블 정렬(인접한 2개의 레코드를 비교,교환, 모든스캔이 다끝났을때 완료)
void bubble_sort(int list[],int n,int order){	
	int i,j;

	for(i=n-1; i>0; i--){  //스캔 n-1번
		for(j=0;j<i; j++){  //스캔 내에서의 교환
			if(order == 1){  
				if(list[j] > list[j+1])  //오름차순
					swap(&list[j],&list[j+1]);
			}
			else{ 
				if(list[j] < list[j+1])   //내림차순
					swap(&list[j],&list[j+1]);
			}
			print(list,n);
		}		
	}
	printf("\n정렬이 완료 되었습니다.\n");
	print(list,n);
	printf("\n");
}

//합병 정렬(리스트를 두개로 분할하고 합병하면서 정렬)
void merge_sort(int list[],int left,int right,int order,int n){
	int mid;
	if(left<right){
		mid=(left+right)/2;  //분할
		merge_sort(list,left,mid,order,n);
		merge_sort(list,mid+1,right,order,n);
		merge(list,left,mid,right,order);  //합병
	}
	print(list,n);
}
//합병
void merge(int list[],int left,int mid,int right,int order){
	int sorted[100];
	int i,j,k,l;
	i=left; j=mid+1; k=left;
	if(order == 1){  //오름차순
		while(i <= mid && j<=right){  
			if(list[i] <= list[j]) sorted[k++]=list[i++];  //작은것을 먼저
			else sorted[k++]=list[j++];
		}
	}
	else{  //내림차순
		while(i <= mid && j<=right){
			if(list[i] >= list[j]) sorted[k++]=list[i++];  //큰것을 먼저
			else sorted[k++]=list[j++];
		}
	}

	if(i>mid){  //남아있는 레코드복사
		for(l=j; l<=right; l++)
			sorted[k++]=list[l];
	}
	else{
		for(l=i; l<=mid; l++)
			sorted[k++]=list[l];
	}
	for(l=left; l<=right; l++)  //원본에 복사
		list[l]=sorted[l];
}

//히프 정렬
void heap_sort(int list[],int n,int order){
	int i;
	HeapType h;
	h.heap = (int*)malloc(sizeof(int)*n+1);
	if(h.heap == NULL){
		printf("히프 메모리 할당 에러");
		exit(1);
	}
	h.heap_size=0;  //히프 초기화

	for(i=0; i<n; i++)
		insert_max_heap(&h,list[i]);
	if(order == 1){ //오름차순
		for(i=n-1; i>=0; i--)
			list[i]=delete_max_heap(&h);
	}
	else{  //내림차순
		for(i=0; i<n; i++)
			list[i]=delete_max_heap(&h);
	}
	//free(h.heap);	
} 

//히프에 삽입
void insert_max_heap(HeapType *h,int key){
	int i;
	i=++(h->heap_size);
	//트리를 올라가면서 배치할 곳 탐색
	while((i!=1) && (key > h->heap[i/2])){ 
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = key; 
}

//히프에서 삭제
int delete_max_heap(HeapType *h){
	int parent,child;
	int key,temp;

	key = h->heap[1];  //삭제할 루트노드
	temp =h ->heap[(h->heap_size)--];  //재배치할 마지막 노드
	parent=1;
	child=2;
	while(child <= h->heap_size){
		//현재 자식노드중 큰 자식을 찾는다
		if((child < h->heap_size) && (h->heap[child] < h->heap[child+1]))
			child++;
		if(temp >= h->heap[child]) break;
		h->heap[parent] = h->heap[child];
		parent = child;
		child *= 2;
	}
	h->heap[parent] = temp;
	return key;
}

//퀵 정렬
void quick_sort(int list[],int left,int right,int order,int n){
	if(left<right){
		int q=partition(list,left,right,order,n);
		quick_sort(list,left,q-1,order,n);
		quick_sort(list,q+1,right,order,n);
	}	
}

//퀵 분할
int partition(int list[],int left,int right,int order,int n){
	int pivot;
	int low,high;
	low=left;
	high=right+1;
	pivot=list[left];	
	do{
		if(order == 1){  //오름차순
			do{
				low++;
			}while(low<=right && list[low]<pivot);
			do{
				high--;
			}while(high>=left && list[high]>pivot);
		}
		else{  //내림차순
			do{
				low++;
			}while(low<=right && list[low]>pivot);
			do{
				high--;
			}while(high>=left && list[high]<pivot);
		}
		if(low<high) swap(&list[low],&list[high]); 
	}while(low<high);
	swap(&list[left],&list[high]);
	print(list,n);
	return high;
}

//기수 정렬
void radix_sort(int list[],int n,int order){
	int i,b,d,factor=1;
	QueueType queues[BUCKETS];

	for(b=0; b<BUCKETS; b++) init(&queues[b]);  //큐초기화

	for(d=0; d<DIGITS; d++){  //정렬시작 작은자릿수부터
		for(i=0; i<n; i++)
			enqueue(&queues[(list[i]/factor)%10],list[i]);
		if(order == 1){  //오름차순
		for(b=i=0; b<BUCKETS; b++)
			while(!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		}
		else{  //내림차순
			for(b=BUCKETS-1,i=0; b>=0; b--)
			while(!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		}
		print(list,n);  //중간과정 출력
		factor *= 10;  //자릿수 올림
	}
}

//큐 초기화
void init(QueueType *q){
	q->front = q->rear = 0;
}

//큐 공백검사
int is_empty(QueueType *q){
	return (q->front == NULL);
}

//큐에 삽입
void enqueue(QueueType *q,int item){
	QueueNode *temp =(QueueNode*)malloc(sizeof(QueueNode));
	if(temp == NULL)
		printf("메모리할당실패\n");
	else{
		temp->item = item;  //데이터 저장
		temp->link = NULL;  //링크필드 초기화
		if(is_empty(q)){  //큐가 공백일때
			q->front = temp;
			q->rear = temp;
		}
		else{  //큐가 공백이 아닐때
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

//큐에서 삭제
int dequeue(QueueType *q){
	QueueNode *temp = q->front;
	int item;
	if(is_empty(q)){
		printf("큐가 비었습니다.\n"); exit(1);
	}
	else{
		item = temp->item;
		q->front = q->front->link;
		if(q->front == NULL)  //공백상태
			q->rear = NULL;
		free(temp);
		return item;
	}
}

//쉘 정렬
void shell_sort(int list[],int n,int order){
	int i,gap;
	for(gap=n/2; gap>0; gap=gap/2){  //gap조정
		if((gap%2) == 0) gap++;
		for(i=0; i<gap; i++)  //부분리스트의 개수는 gap
			inc_insertion(list,i,n-1,gap,order);
		printf("gap = %d\n",gap);
		print(list,n);
	}
}			

//쉘 정렬 과정(gap을 이용한 삽입정렬)
void inc_insertion(int list[],int first,int last,int gap,int order){
	int i,j,key;
	for(i=first+gap; i<=last; i=i+gap){
		key=list[i];
		if(order == 1)  //오름차순
			for(j=i-gap; j>=first && key<list[j];j=j-gap)
				list[j+gap]=list[j];		
		else  //내림차순
			for(j=i-gap; j>=first && key>list[j];j=j-gap)
				list[j+gap]=list[j];
		list[j+gap]=key;
	}
}