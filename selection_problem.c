#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<ctype.h>

void swap(int *x, int *y, int *t){
	*t = *x;
	*x = *y;
	*y = *t;
}

//Selection(A, left, right, k)
int Selection(int list[], int left, int right, int k){
	int temp,pivot,pivot_index;
	int s,q,i;

	pivot_index=rand()%(right-left+1)+left;  // �Ǻ��� A[left]~A[right]���� �����ϰ� �����ϰ�
	pivot=list[pivot_index];

	printf("---ó�� ����Ʈ---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	printf("\n");
	
	swap(&list[pivot_index],&list[left],&temp);  //�Ǻ��� A[left]�� �ڸ��� �ٲ� ��

	printf("---�ǹ��� ��ȯ �� ����Ʈ---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	
	printf("\n�ǹ��ε��� %d\n",pivot_index);

	q=partition(list,left,right);

	s=(q-1)-left+1;  //S = Small group�� ũ��
	printf("s�� �� %d k�� �� %d\n",s,k);
	if(k<=s) 
		Selection(list,left,q-1,k);  //Small group���� ã��
	else if(k==s+1)
		return list[q];  // �Ǻ� = k��° ���� ����
	else 
		Selection(list,q+1,right,k-s-1);  // large group���� ã��
}

//�Ǻ��� �迭�� �� ���Ҹ� ���Ͽ� �Ǻ����� ���� ���ڴ� A[left]~A[p-1]�� �ű��, 
//�Ǻ����� ū ���ڴ� A[p+1]~A[right]�� �ű��, �Ǻ��� A[p]�� ���´�.
int partition(int list[], int left, int right)
{
	int pivot, temp;
	int low,high;
	int i;

	low = left;                 
	high = right+1;
	pivot = list[left]; 

	do {	
		do{
		low++;
		}while(low<=right &&list[low]<pivot); 
		do{
		high--;
		}while(high>=left && list[high]>pivot);
		if(low<high) swap(&list[low],&list[high],&temp); 
	} while(low<high);	

	swap(&list[left],&list[high],&temp); 	

	printf("---��Ƽ�� �� ����Ʈ---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	printf("\nhigh�� %d \n",high);
	return high;
}

int main()
{
	int n,i,k,right,left;
	int *p;  //�����Ҵ��� ���� ������
	int result;
	char ch;

	srand((unsigned)time(NULL));  //�õ尪

	while(1){
		//�Է�: A[left]~A[right]�� k, ��, 1��k��|A|, |A|=right-left+1
		printf("���� �? "); scanf("%d",&n);

		p=(int*)malloc(sizeof(int)*n);  //�迭 �����Ҵ�

		for(i=0; i<n; i++){
			scanf("%d",&p[i]); 
			fflush(stdin);
		}
		printf("\n");

		left=0;
		right=n-1;

		while(1){

			printf("�� ��°�� �������� ã���ž�? ");
			scanf("%d",&k);
			if(1<=k && k<=n)
				break;
			else
				printf("k �ٽ� �Է� \n");
		}

		result=Selection(p,left,right,k);  //���: A[left]~A[right]���� k ��° ���� ����
		printf("%d��° ���� ���� = %d\n",k,result);

		printf("�ٽ� �Ҳ���..? (Y/N)");
		
		fflush(stdin);
		scanf("%c",&ch);
		ch=toupper(ch);
		if(ch != 'Y')
			break;	
	}
}





