#include<stdio.h>  //map을 달팽이모양으로 check
#include<stdlib.h>
#include<conio.h>

#define row 15 //map의 크기
#define col 15

int main()
{
	int map[row][col]={0};
	int i,j,x=0,y=0;
	int goState=6;  //8(위) 2(아래) 4(왼) 6(오)
	int left=0,right=row-1,top=1,bottom=col-1;  //각방향 끝	
	int count=0;  //loop 종료 조건

	for(i=0;i<row;i++)  //check 전 map출력
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

		for(i=0;i<row;i++)  //check 후 map출력
		{
			for(j=0;j<col;j++)
			{
				printf(" %d",map[i][j]);
			}
			printf("\n");
		}

		switch(goState)  //방향이동
		{
		case 2 : y++;     //아래
			if(y==bottom){
				goState=4;
				bottom--;
			}break;
		case 4 : x--;     //왼
			if(x==left){
				goState=8;
				left++;
			}break;
		case 6 : x++;     //오
			if(x==right){
				goState=2;
				right--;
			}break;
		case 8 : y--;     //위
			if(y==top){
				goState=6;
				top++;
			}break;
		}

		for(i=0;i<row;i++)  //map이 전부 check인지 검사
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