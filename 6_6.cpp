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
	int *p = new int[size];
	
	for(int i=0; i<5; i++)
		if(s1[i] == del_key)





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
	cout << "��ģ ���� �迭�� ����Ѵ�" << endl;
	ap=ArrayUtility2::concat(x,y,size);

	for(int i=0; i<10; i++)
		cout << ap[i] << ' ';

	delete []ap;

	cout << "�迭 x[]���� y[]�� �� ����� ����Ѵ�. ������ " << retSize << endl;
	ap=ArrayUtility2::remove(x,y,size,retSize);

}