#include<iostream>
using namespace std;

class ArrayUtility2{
public:
	//s1과 s2를 연결한 새로운 배열을 동적 생성하고 포인터 리턴
	static int* concat(int s1[], int s2[], int size);
	//s1에서 s2에 있는 숫자를 모두 삭제한 새로운 배열을 동적 생성하여 리턴, 리턴하는 배열의 크기는
	//retSize에 전달. retSize가 0인 경우 NULL리턴
	static int* remove(int s1[], int s2[], int size, int& retSize);
};

//함수구현
int* ArrayUtility2::concat(int s1[], int s2[], int size){
	int *p = new int[size];

	for(int i=0; i<5; i++){
		p[i]=s1[i];
		p[i+5]=s2[i];
	}
	return p;
}

int* ArrayUtility2::remove(int s1[],int s2[], int size, int& retSize){
	int del_key;
	retSize = size;

	int *ap=ArrayUtility2::concat(s1,s2,size);  //10개의 배열이 생성됨

	for(int i=0; i<5; i++){  //해당 값 배열 삭제 loop	 	
		del_key=s2[i];
		while(true){  //중복되는 값 때문에 삭제 loop를 2중으로
			int count=0;
			for(int j=0; j<retSize; j++)
				if(ap[j] == del_key)
					for(int k=j; k<retSize; k++){  //앞으로 땡겨준다  
						ap[k] = ap [k+1];
						retSize--;
						count++;
					}
					if(count == 0) break;
		}
	}	

	int *p = new int[retSize];
	for(int i=0; i<retSize; i++)
		p[i] = ap[i];
	delete []ap;
	return p;
}

int main()
{
	int x[5],y[5];
	int *ap,size,retSize=0;	

	cout << "정수를 5개 입력하라. 배열 x에 삽입한다.>> ";
	for(int i=0; i<5; i++)  cin >> x[i];
	cout << "정수를 5개 입력하라. 배열 y에 삽입한다.>> ";
	for(int i=0; i<5; i++)	cin >> y[i];

	size=(sizeof(x)+sizeof(y))/sizeof(int);
	ap=ArrayUtility2::concat(x,y,size);  //function call
	cout << "합친 정수 배열을 출력한다" << endl;	

	for(int i=0; i<size; i++)
		cout << ap[i] << ' ';
	cout << endl;
	delete []ap;

	ap=ArrayUtility2::remove(x,y,size,retSize);  //function call
	cout << "배열 x[]에서 y[]를 뺀 결과를 출력한다. 개수는 " << retSize << endl;

	for(int i=0; i<retSize; i++)
		cout << ap[i] << ' ';
	cout << endl;
	delete []ap;
}