
//3. 정렬하고자 하는 자료는 
//첫째, 표준 입력 방식으로 숫자 또는 문자열 형태로 입력 받도록 합니다(최대 50개 이내).  
// 둘째, 데이터 화일 입력 방식으로 화일의 첫번째 라인은 자료의 개수가 있고,
//그 이후에는 자료의 개수 만큼 자료의 줄이 존재한다고 가정하여 자료를 입력 받도록 합니다. 
//즉, 프로그램 실행시에 데이터 화일이 지정되지 않으면 표준 입력 방식을 사용하고, 지정되어 있으면
//화일 입력 방식으로 동작해야 합니다. 단, 입력하는 자료의 끝은 '='으로 지정하며, 
//   기수정렬의 경우에는 동일한 자리 수로 변환되는 숫자도 고려합니다. 
//
//4. 입력된 자료를 순서대로 먼저 출력하고, 선택한 정렬 방법과 정렬 방식으로 주어진 자료를 
//   정렬하면서, 중간 수행 결과와 최종 정렬된 결과를 출력하도록 합니다.

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

void selection_sort(int list[],int n,int order);			//선택 정렬
void insertion_sort(int list[],int n,int order);		    //삽입 정렬
void bubble_sort(int list[],int n,int order);			    //버블 정렬
void merge_sort(int list[],int left,int right,int order,int n);	//합병 정렬
void merge(int list[],int left,int mid,int right,int order);
void heap_sort(int list[],int n,int order);                 //히프 정렬
void quick_sort(int list[],int left,int right,int order);   //퀵 정렬
void radix_sort(int list[],int n,int order);			    //기수 정렬
void shell_sort(int list[],int n,int order);				//쉘 정렬
int select_order();  //오름차순 내림차순 선택
int input(int arr[]);  //입력
void swap(int *a, int *b);  //스왑
void print(int list[],int n);  //출력

int main(int argc,char *argv[])
{
	char ch;
	int order,n;
	int arr[100];
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
			if(ch == 's' || ch == 'i' || ch == 'b' || ch == 'm' || ch == 'h' || ch == 'r'
				|| ch == 'q' || ch == 'l' || ch == 'x')
				break;
		}

		order=select_order();  //오름,내림차순 결정
		n=input(arr);          //정렬할 데이터 입력
		printf("입력한 숫자\n");
		print(arr,n); printf("\n");

		//메뉴 선택
		switch(ch){
		case 's' : //선택 정렬
			selection_sort(arr,n,order); break;
		case 'i' :  //삽입 정렬
			insertion_sort(arr,n,order); break;
		case 'b' :  //버블 정렬 
			//버블 정렬
			bubble_sort(arr,n,order); break;
		case 'm' :  //합병 정렬 
			merge_sort(arr,0,n-1,order,n);
			printf("\n정렬이 완료 되었습니다.\n");
			print(arr,n);
			printf("\n");
			break;
		case 'h' :  //히프 정렬 

			break;
		case 'r' :  //기수 정렬 

			break;
		case 'q' :  //퀵 정렬

			break;
		case 'l' :  //쉘 정렬

			break;
		case 'x' :  //종료
			exit(1);
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

} 

//퀵 정렬
void quick_sort(int list[],int left,int right,int order){

}

//기수 정렬
void radix_sort(int list[],int n,int order){

}

//쉘 정렬
void shell_sort(int list[],int n,int order){

}			