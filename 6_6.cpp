#include<iostream>
using namespace std;

class ArrayUtility2{
public:
	//s1�� s2�� ������ ���ο� �迭�� ���� �����ϰ� ������ ����
	static int* concat(int s1[], int s2[], int size);
	//s1���� s2�� �ִ� ���ڸ� ��� ������ ���ο� �迭�� ���� �����Ͽ� ����, �����ϴ� �迭�� ũ���
	//retSize�� ����. retSize�� 0�� ��� NULL����
	static int* remove(int s1[], int s2[], int size, int& retSize);
};

//�Լ�����
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

	int *ap=ArrayUtility2::concat(s1,s2,size);  //10���� �迭�� ������

	for(int i=0; i<5; i++){  //�ش� �� �迭 ���� loop	 	
		del_key=s2[i];
		while(true){  //�ߺ��Ǵ� �� ������ ���� loop�� 2������
			int count=0;
			for(int j=0; j<retSize; j++)
				if(ap[j] == del_key)
					for(int k=j; k<retSize; k++){  //������ �����ش�  
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

	cout << "������ 5�� �Է��϶�. �迭 x�� �����Ѵ�.>> ";
	for(int i=0; i<5; i++)  cin >> x[i];
	cout << "������ 5�� �Է��϶�. �迭 y�� �����Ѵ�.>> ";
	for(int i=0; i<5; i++)	cin >> y[i];

	size=(sizeof(x)+sizeof(y))/sizeof(int);
	ap=ArrayUtility2::concat(x,y,size);  //function call
	cout << "��ģ ���� �迭�� ����Ѵ�" << endl;	

	for(int i=0; i<size; i++)
		cout << ap[i] << ' ';
	cout << endl;
	delete []ap;

	ap=ArrayUtility2::remove(x,y,size,retSize);  //function call
	cout << "�迭 x[]���� y[]�� �� ����� ����Ѵ�. ������ " << retSize << endl;

	for(int i=0; i<retSize; i++)
		cout << ap[i] << ' ';
	cout << endl;
	delete []ap;
}