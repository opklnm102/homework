#include<stdio.h>  //map�� �����̸������ check
#include<stdlib.h>
#include<conio.h>

#define row 15 //map�� ũ��
#define col 15

int main()
{
	int map[row][col]={0};
	int i,j,x=0,y=0;
	int goState=6;  //8(��) 2(�Ʒ�) 4(��) 6(��)
	int left=0,right=row-1,top=1,bottom=col-1;  //������ ��	
	int count=0;  //loop ���� ����

	for(i=0;i<row;i++)  //check �� map���
	{
		for(j=0;j<col;j++)
		{
			printf(" %d",map[i][j]);
		}
		printf("\n");
	}	

	while(1)
	{
		getch();
		system("cls");
		map[y][x]=1;

		for(i=0;i<row;i++)  //check �� map���
		{
			for(j=0;j<col;j++)
			{
				printf(" %d",map[i][j]);
			}
			printf("\n");
		}

		switch(goState)  //�����̵�
		{
		case 2 : y++;     //�Ʒ�
			if(y==bottom){
				goState=4;
				bottom--;
			}break;
		case 4 : x--;     //��
			if(x==left){
				goState=8;
				left++;
			}break;
		case 6 : x++;     //��
			if(x==right){
				goState=2;
				right--;
			}break;
		case 8 : y--;     //��
			if(y==top){
				goState=6;
				top++;
			}break;
		}

		for(i=0;i<row;i++)  //map�� ���� check���� �˻�
		{
			for(j=0;j<col;j++)
			{
				if(map[i][j]==1)
					count++;
			}
		}

		if(count==row*col)
			break;
		else
			count=0;
	}
}