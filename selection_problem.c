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

	pivot_index=rand()%(right-left+1)+left;  // 피봇을 A[left]~A[right]에서 랜덤하게 선택하고
	pivot=list[pivot_index];

	printf("---처음 리스트---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	printf("\n");
	
	swap(&list[pivot_index],&list[left],&temp);  //피봇과 A[left]의 자리를 바꾼 후

	printf("---피벗과 교환 후 리스트---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	
	printf("\n피벗인덱스 %d\n",pivot_index);

	q=partition(list,left,right);

	s=(q-1)-left+1;  //S = Small group의 크기
	printf("s의 값 %d k의 값 %d\n",s,k);
	if(k<=s) 
		Selection(list,left,q-1,k);  //Small group에서 찾기
	else if(k==s+1)
		return list[q];  // 피봇 = k번째 작은 숫자
	else 
		Selection(list,q+1,right,k-s-1);  // large group에서 찾기
}

//피봇과 배열의 각 원소를 비교하여 피봇보다 작은 숫자는 A[left]~A[p-1]로 옮기고, 
//피봇보다 큰 숫자는 A[p+1]~A[right]로 옮기며, 피봇은 A[p]에 놓는다.
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

	printf("---파티션 후 리스트---\n");
	for(i=0; i<right+1; i++)
		printf("%d  ",list[i]);
	printf("\nhigh값 %d \n",high);
	return high;
}

int main()
{
	int n,i,k,right,left;
	int *p;  //동적할당을 위한 포인터
	int result;
	char ch;

	srand((unsigned)time(NULL));  //시드값

	while(1){
		//입력: A[left]~A[right]와 k, 단, 1≤k≤|A|, |A|=right-left+1
		printf("숫자 몇개? "); scanf("%d",&n);

		p=(int*)malloc(sizeof(int)*n);  //배열 동적할당

		for(i=0; i<n; i++){
			scanf("%d",&p[i]); 
			fflush(stdin);
		}
		printf("\n");

		left=0;
		right=n-1;

		while(1){

			printf("몇 번째로 작은수를 찾을거야? ");
			scanf("%d",&k);
			if(1<=k && k<=n)
				break;
			else
				printf("k 다시 입력 \n");
		}

		result=Selection(p,left,right,k);  //출력: A[left]~A[right]에서 k 번째 작은 원소
		printf("%d번째 작은 원소 = %d\n",k,result);

		printf("다시 할꺼야..? (Y/N)");
		
		fflush(stdin);
		scanf("%c",&ch);
		ch=toupper(ch);
		if(ch != 'Y')
			break;	
	}
}





