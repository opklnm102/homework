
//3. �����ϰ��� �ϴ� �ڷ�� 
//ù°, ǥ�� �Է� ������� ���� �Ǵ� ���ڿ� ���·� �Է� �޵��� �մϴ�(�ִ� 50�� �̳�).  
// ��°, ������ ȭ�� �Է� ������� ȭ���� ù��° ������ �ڷ��� ������ �ְ�,
//�� ���Ŀ��� �ڷ��� ���� ��ŭ �ڷ��� ���� �����Ѵٰ� �����Ͽ� �ڷḦ �Է� �޵��� �մϴ�. 
//��, ���α׷� ����ÿ� ������ ȭ���� �������� ������ ǥ�� �Է� ����� ����ϰ�, �����Ǿ� ������
//ȭ�� �Է� ������� �����ؾ� �մϴ�. ��, �Է��ϴ� �ڷ��� ���� '='���� �����ϸ�, 
//   ��������� ��쿡�� ������ �ڸ� ���� ��ȯ�Ǵ� ���ڵ� ����մϴ�. 
//
//4. �Էµ� �ڷḦ ������� ���� ����ϰ�, ������ ���� ����� ���� ������� �־��� �ڷḦ 
//   �����ϸ鼭, �߰� ���� ����� ���� ���ĵ� ����� ����ϵ��� �մϴ�.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void selection_sort(int list[],int n,int order);			//���� ����
void insertion_sort(int list[],int n,int order);		    //���� ����
void bubble_sort(int list[],int n,int order);			    //���� ����
void merge_sort(int list[],int left,int right,int order,int n);	//�պ� ����
void merge(int list[],int left,int mid,int right,int order);
void heap_sort(int list[],int n,int order);                 //���� ����
void quick_sort(int list[],int left,int right,int order);   //�� ����
void radix_sort(int list[],int n,int order);			    //��� ����
void shell_sort(int list[],int n,int order);				//�� ����
int select_order();  //�������� �������� ����
int input(int arr[]);  //�Է�
void swap(int *a, int *b);  //����
void print(int list[],int n);  //���

int main(int argc,char *argv[])
{
	char ch;
	int order,n;
	int arr[100];
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
			if(ch == 's' || ch == 'i' || ch == 'b' || ch == 'm' || ch == 'h' || ch == 'r'
				|| ch == 'q' || ch == 'l' || ch == 'x')
				break;
		}

		order=select_order();  //����,�������� ����
		n=input(arr);          //������ ������ �Է�
		printf("�Է��� ����\n");
		print(arr,n); printf("\n");

		//�޴� ����
		switch(ch){
		case 's' : //���� ����
			selection_sort(arr,n,order); break;
		case 'i' :  //���� ����
			insertion_sort(arr,n,order); break;
		case 'b' :  //���� ���� 
			//���� ����
			bubble_sort(arr,n,order); break;
		case 'm' :  //�պ� ���� 
			merge_sort(arr,0,n-1,order,n);
			printf("\n������ �Ϸ� �Ǿ����ϴ�.\n");
			print(arr,n);
			printf("\n");
			break;
		case 'h' :  //���� ���� 

			break;
		case 'r' :  //��� ���� 

			break;
		case 'q' :  //�� ����

			break;
		case 'l' :  //�� ����

			break;
		case 'x' :  //����
			exit(1);
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

} 

//�� ����
void quick_sort(int list[],int left,int right,int order){

}

//��� ����
void radix_sort(int list[],int n,int order){

}

//�� ����
void shell_sort(int list[],int n,int order){

}			