#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#define BUCKETS 10  //������� ���ϼ�
#define DIGITS 4  //������� �ڸ���

//���������� ���� ����ü
typedef struct{ 
	int *heap;
	int heap_size;
}HeapType;

//��������� ���� ����ü
typedef struct QueueNode{
	int item;
	struct QueueNode *link;
}QueueNode;
typedef struct{
	QueueNode *front,*rear;
}QueueType;

void selection_sort(int list[],int n,int order);			    //���� ����
void insertion_sort(int list[],int n,int order);		        //���� ����
void bubble_sort(int list[],int n,int order);			        //���� ����
void merge_sort(int list[],int left,int right,int order,int n);	//�պ� ����
void merge(int list[],int left,int mid,int right,int order);
void heap_sort(int list[],int n,int order);                     //���� ����
void insert_max_heap(HeapType *h,int key);  //������ ����
int delete_max_heap(HeapType *h);  //�������� ����
void quick_sort(int list[],int left,int right,int order,int n); //�� ����
int partition(int list[],int left,int right,int order,int n);
void radix_sort(int list[],int n,int order);					//��� ����
void init(QueueType *q);  //ť �ʱ�ȭ
int is_empty(QueueType *q);  //ť ����˻�
void enqueue(QueueType *q,int item);  //ť�� ����
int dequeue(QueueType *q);  //ť���� ����
void shell_sort(int list[],int n,int order);					//�� ����
void inc_insertion(int list[],int first,int last,int gap,int order);
int select_order();  //�������� �������� ����
int input(int arr[]);  //�Է�
void swap(int *a, int *b);  //����
void print(int list[],int n);  //���

int main(int argc,char *argv[])
{
	char ch;
	int order,n;
	int arr[100];
	FILE *fp;
	while(1){
		while(1){
			printf("==================\n");
			printf("���� ���� : s\n���� ���� : i\n���� ���� : b\n");
			printf("�պ� ���� : m\n���� ���� : h\n��� ���� : r\n�� ���� : q\n");
			printf("�� ���� : l\n���α׷� ���� : x\n");
			printf("===================\n");
			printf("���ϴ� ������ �����Ͻÿ� : ");
			scanf("%c",&ch); fflush(stdin);
			ch=tolower(ch);
			if(ch == 'x') exit(1);
			if(ch == 's' || ch == 'i' || ch == 'b' || ch == 'm' || ch == 'h' || ch == 'r'
				|| ch == 'q' || ch == 'l')
				break;
		}
		order=select_order();  //����,�������� ����

		if(argc == 1){  //������ ������ �Է�		
			n=input(arr);      
		}
		else if(argc == 2){
			fp=fopen(argv[1],"r");
			if(fp == NULL){
				printf("Error: %s can not open.\n",argv[1]);
				exit(1);
			}	
			fscanf(fp,"%d",&n);  //������ �ڷ��� ���� �Է�
			for(int i=0; i<n; i++)  //������ �ڷ�� �Է�
				fscanf(fp,"%d",&arr[i]);
		}
		printf("�Է��� ����\n");
		print(arr,n); printf("\n");

		//�޴� ����
		switch(ch){
		case 's' : //���� ����
			printf("-----��������-----\n");
			selection_sort(arr,n,order); break;
		case 'i' :  //���� ����
			printf("-----��������-----\n");
			insertion_sort(arr,n,order); break;
		case 'b' :  //���� ���� 
			printf("-----��������-----\n");
			bubble_sort(arr,n,order); break;
		case 'm' :  //�պ� ���� 
			printf("-----�պ�����-----\n");
			merge_sort(arr,0,n-1,order,n);
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n"); break;
		case 'h' :  //���� ���� 
			printf("-----��������-----\n");
			heap_sort(arr,n,order); 
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n"); break;
		case 'r' :  //��� ���� 
			printf("-----�������-----\n");
			radix_sort(arr,n,order);
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n"); break;
		case 'q' :  //�� ����
			printf("-----�� ����-----\n");
			quick_sort(arr,0,n-1,order,n);
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n"); break;
		case 'l' :  //�� ����
			printf("-----�� ����-----\n");
			shell_sort(arr,n,order);
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n"); break;		
		}
	}
}

//�������� �������� ����
int select_order(){
	char order;

	while(1){
		printf("==================\n");
		printf("�������� : i\n�������� : d\n");
		printf("==================\n");
		scanf("%c",&order); fflush(stdin);

		if(order == 'i' || order == 'I')  //���������̸� 1���� �������� 2����
			return 1; 
		else if(order == 'd' || order == 'D')
			return 2;
	}
}

//�Է�
int input(int arr[]){
	char ch[10];
	int check,i,j;

	for(i=0; i<50; i++){
		check=0;
		printf("���� �Է�(�ִ� 50��,'='�Է��ϸ� �Է� ����): ");
		scanf("%s",ch); fflush(stdin);
		if(ch[0] == '=')  //'='�� �Է� ����
			break;

		for(j=0; j<strlen(ch); j++)  //�Էµ� ���ڿ��� ���ڰ� �ƴҼ���������..
			if(ch[j] < 48 && 57 < ch[j])
				check++;

		if(check == 0)
			arr[i]=atoi(ch);
		else
			i--;		
	}
	return i;
}

//����
void swap(int *a, int *b){
	int t;

	t = *a;
	*a = *b;
	*b = t;
}

//���
void print(int list[],int n){
	for(int i=0; i<n; i++)
		printf("%d  ",list[i]);
	printf("\n");
}

//���� ����(�����ʿ��� �ּҰ��� ���� ù������ ��ȯ)
void selection_sort(int list[],int n,int order){
	int i,j,index;
	for(i=0; i<n-1; i++){
		index=i;  //�ּ�or�ִ밪�� �ε���
		for(j=i+1; j<n; j++){
			if(order == 1){
				if(list[j] < list[index])  //�������� 
					index=j; 
			}
			else{
				if(list[j] > list[index])  //��������
					index=j; 
			}
		}
		swap(&list[i],&list[index]);
		print(list,n);
	}
	printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
	print(list,n);
	printf("\n");
}

//���� ����(���ĵǾ��ִ� �κп� ���ο� ���ڵ带 ����, ��ҵ��� �̵��� �̿�����) 
void insertion_sort(int list[],int n,int order){
	int i,j,key;
	for(i=1; i<n; i++){
		key=list[i];
		if(order == 1){  //��������
			for(j=i-1; j>=0 && list[j] > key; j--)
				list[j+1]=list[j];  //�ڷ� �δ�
		}
		else{  //��������
			for(j=i-1; j>=0 && list[j] < key; j--)
				list[j+1]=list[j];  //�ڷιδ�
		}
		list[j+1]=key;  //�ڷ� �ٹо����� 
		print(list,n);
	}
	printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
	print(list,n);
	printf("\n");
}

//���� ����(������ 2���� ���ڵ带 ��,��ȯ, ��罺ĵ�� �ٳ������� �Ϸ�)
void bubble_sort(int list[],int n,int order){	
	int i,j;

	for(i=n-1; i>0; i--){  //��ĵ n-1��
		for(j=0;j<i; j++){  //��ĵ �������� ��ȯ
			if(order == 1){  
				if(list[j] > list[j+1])  //��������
					swap(&list[j],&list[j+1]);
			}
			else{ 
				if(list[j] < list[j+1])   //��������
					swap(&list[j],&list[j+1]);
			}
			print(list,n);
		}		
	}
	printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
	print(list,n);
	printf("\n");
}

//�պ� ����(����Ʈ�� �ΰ��� �����ϰ� �պ��ϸ鼭 ����)
void merge_sort(int list[],int left,int right,int order,int n){
	int mid;
	if(left<right){
		mid=(left+right)/2;  //����
		merge_sort(list,left,mid,order,n);
		merge_sort(list,mid+1,right,order,n);
		merge(list,left,mid,right,order);  //�պ�
	}
	print(list,n);
}
//�պ�
void merge(int list[],int left,int mid,int right,int order){
	int sorted[100];
	int i,j,k,l;
	i=left; j=mid+1; k=left;
	if(order == 1){  //��������
		while(i <= mid && j<=right){  
			if(list[i] <= list[j]) sorted[k++]=list[i++];  //�������� ����
			else sorted[k++]=list[j++];
		}
	}
	else{  //��������
		while(i <= mid && j<=right){
			if(list[i] >= list[j]) sorted[k++]=list[i++];  //ū���� ����
			else sorted[k++]=list[j++];
		}
	}

	if(i>mid){  //�����ִ� ���ڵ庹��
		for(l=j; l<=right; l++)
			sorted[k++]=list[l];
	}
	else{
		for(l=i; l<=mid; l++)
			sorted[k++]=list[l];
	}
	for(l=left; l<=right; l++)  //������ ����
		list[l]=sorted[l];
}

//���� ����
void heap_sort(int list[],int n,int order){
	int i;
	HeapType h;
	h.heap = (int*)malloc(sizeof(int)*n+1);
	if(h.heap == NULL){
		printf("���� �޸� �Ҵ� ����");
		exit(1);
	}
	h.heap_size=0;  //���� �ʱ�ȭ

	for(i=0; i<n; i++)
		insert_max_heap(&h,list[i]);
	if(order == 1){ //��������
		for(i=n-1; i>=0; i--)
			list[i]=delete_max_heap(&h);
	}
	else{  //��������
		for(i=0; i<n; i++)
			list[i]=delete_max_heap(&h);
	}
	//free(h.heap);	
} 

//������ ����
void insert_max_heap(HeapType *h,int key){
	int i;
	i=++(h->heap_size);
	//Ʈ���� �ö󰡸鼭 ��ġ�� �� Ž��
	while((i!=1) && (key > h->heap[i/2])){ 
		h->heap[i] = h->heap[i/2];
		i /= 2;
	}
	h->heap[i] = key; 
}

//�������� ����
int delete_max_heap(HeapType *h){
	int parent,child;
	int key,temp;

	key = h->heap[1];  //������ ��Ʈ���
	temp =h ->heap[(h->heap_size)--];  //���ġ�� ������ ���
	parent=1;
	child=2;
	while(child <= h->heap_size){
		//���� �ڽĳ���� ū �ڽ��� ã�´�
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

//�� ����
void quick_sort(int list[],int left,int right,int order,int n){
	if(left<right){
		int q=partition(list,left,right,order,n);
		quick_sort(list,left,q-1,order,n);
		quick_sort(list,q+1,right,order,n);
	}	
}

//�� ����
int partition(int list[],int left,int right,int order,int n){
	int pivot;
	int low,high;
	low=left;
	high=right+1;
	pivot=list[left];	
	do{
		if(order == 1){  //��������
			do{
				low++;
			}while(low<=right && list[low]<pivot);
			do{
				high--;
			}while(high>=left && list[high]>pivot);
		}
		else{  //��������
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

//��� ����
void radix_sort(int list[],int n,int order){
	int i,b,d,factor=1;
	QueueType queues[BUCKETS];

	for(b=0; b<BUCKETS; b++) init(&queues[b]);  //ť�ʱ�ȭ

	for(d=0; d<DIGITS; d++){  //���Ľ��� �����ڸ�������
		for(i=0; i<n; i++)
			enqueue(&queues[(list[i]/factor)%10],list[i]);
		if(order == 1){  //��������
		for(b=i=0; b<BUCKETS; b++)
			while(!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		}
		else{  //��������
			for(b=BUCKETS-1,i=0; b>=0; b--)
			while(!is_empty(&queues[b]))
				list[i++] = dequeue(&queues[b]);
		}
		print(list,n);  //�߰����� ���
		factor *= 10;  //�ڸ��� �ø�
	}
}

//ť �ʱ�ȭ
void init(QueueType *q){
	q->front = q->rear = 0;
}

//ť ����˻�
int is_empty(QueueType *q){
	return (q->front == NULL);
}

//ť�� ����
void enqueue(QueueType *q,int item){
	QueueNode *temp =(QueueNode*)malloc(sizeof(QueueNode));
	if(temp == NULL)
		printf("�޸��Ҵ����\n");
	else{
		temp->item = item;  //������ ����
		temp->link = NULL;  //��ũ�ʵ� �ʱ�ȭ
		if(is_empty(q)){  //ť�� �����϶�
			q->front = temp;
			q->rear = temp;
		}
		else{  //ť�� ������ �ƴҶ�
			q->rear->link = temp;
			q->rear = temp;
		}
	}
}

//ť���� ����
int dequeue(QueueType *q){
	QueueNode *temp = q->front;
	int item;
	if(is_empty(q)){
		printf("ť�� ������ϴ�.\n"); exit(1);
	}
	else{
		item = temp->item;
		q->front = q->front->link;
		if(q->front == NULL)  //�������
			q->rear = NULL;
		free(temp);
		return item;
	}
}

//�� ����
void shell_sort(int list[],int n,int order){
	int i,gap;
	for(gap=n/2; gap>0; gap=gap/2){  //gap����
		if((gap%2) == 0) gap++;
		for(i=0; i<gap; i++)  //�κи���Ʈ�� ������ gap
			inc_insertion(list,i,n-1,gap,order);
		printf("gap = %d\n",gap);
		print(list,n);
	}
}			

//�� ���� ����(gap�� �̿��� ��������)
void inc_insertion(int list[],int first,int last,int gap,int order){
	int i,j,key;
	for(i=first+gap; i<=last; i=i+gap){
		key=list[i];
		if(order == 1)  //��������
			for(j=i-gap; j>=first && key<list[j];j=j-gap)
				list[j+gap]=list[j];		
		else  //��������
			for(j=i-gap; j>=first && key>list[j];j=j-gap)
				list[j+gap]=list[j];
		list[j+gap]=key;
	}
}