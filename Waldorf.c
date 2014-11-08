#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void alphabat_conversion(char **arr,int m,int n);  //소문자변환

void check(int m,int n,char **map,char *word,int *coordinate){
	int i,j,i2,j2;
	//int right,left,up,down,ru_diagonal,rd_diagonal,lu_diagonal,ld_diagonal;  //8방향
	//right=left=up=down=ru_diagonal=rd_diagonal=lu_diagonal=ld_diagonal=0;
	int direction; 
	//방향(1-왼쪽위,2-왼쪽,3-왼쪽아래,4-아래,5-오른쪽아래,6-오른쪽,7-오른쪽위,8-위

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(map[i][j] == word[0]){ //첫단어를 찾으면 그주위를 탐색

				for(i2=i-1; i2<i+2; i2++){
					for(j2=j-1; j2<j+2; j2++){
						if(map[i2][j2] == word[1]){  //방향 설정
							if(i2 == i-1 && j2 == j-1)  //왼쪽위
								direction=1;
							else if(i2 == i && j2 == j-1)  //왼쪽
								direction=2;
							else if(i2 == i+1 && j2 == j-1)  //왼쪽아래
								direction=3;
							else if(i2 == i+1 && j2 == j)  //아래
								direction=4;
							else if(i2 == i+1 && j2 == j+1)  //오른쪽아래
								direction=5;
							else if(i2 == i && j2 == j+1)  //오른쪽
								direction=6;
							else if(i2 == i-1 && j2 == j+1)  //오른쪽위
								direction=7;
							else if(i2 == i-1 && j2 == j)  //위
								direction=8;
						}
						switch(direction){
						case 1 :
							case 2 :
								case 3 :
									case 4 :
										case 5 :
											case 6 :
												case 7 :
													case 8 :
														

						}
					}
				}
			}


		}
	}



}



int main(int argc, char *argv[])
{
	FILE *fp;
	int m,n,w,f=1;
	int f_count;  //case의 수
	char **map,**word;  //grid(격자판)랑 찾을단어 
	int **coordinate;  //좌표값 저장
	int i,j;  


	//input
	if(argc == 1){  //콘솔입력
		while(1){
			printf("input case>> "); scanf("%d",&f_count);  //Case # 입력
			if(1<=f_count && f_count<=20) break;  //f의 범위는 1~20
		}

		while(1){
			printf("input m X n>> "); scanf("%d %d",&m,&n);
			if((1<= m && m<=60) && (1<=n && n<=60)) break; //m,n의 범위 1~60
		}

		map=(char **)malloc(sizeof(char *)*m);  //field 생성
		for(i=0; i<m; i++)
			map[i]=(char *)malloc(sizeof(char)*n);
		if(map == NULL){
			printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
			return -1;
		}

		for(i=0; i<m; i++){  //field 값 입력
			fflush(stdin);
			gets(map[i]);		
		}

	}
	else if(argc == 2){  //파일입력
		fp=fopen(argv[1],"r");
		if(fp == NULL){
			printf("Error : %s can not open.\n",argv[1]);
			return -1;
		}

		while(1){
			fscanf(fp,"%d",&f_count);  //Case # 입력
			if(1<=f_count && f_count<=20) break;  //f의 범위는 1~20
		}

		while(1){
			fscanf(fp,"%d %d",&m,&n);
			if((1<= m && m<=60) && (1<=n && n<=60)) break; //m,n의 범위 1~60
		}

		map=(char **)malloc(sizeof(char *)*m);  //field 생성
		for(i=0; i<m; i++)
			map[i]=(char *)malloc(sizeof(char)*n);
		if(map == NULL){
			printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
			return -1;
		}

		for(i=0; i<m; i++){  ////field 값 입력				
			fscanf(fp,"%s",map[i]);
		}

		alphabat_conversion(map,m,n);  //소문자로 변환


		fscanf(fp,"%d",&w);  //찾을 단어 갯수

		word=(char **)malloc(sizeof(char *)*w);  //찾을 문자열 저장을 위한 공간할당
		coordinate=(int **)malloc(sizeof(int *)*w);  //찾은 문자열 좌표 저장을 위한 공간할당
		for(i=0; i<w; i++){
			word[i]=(char *)malloc(sizeof(char)*15);
			coordinate[i]=(int *)malloc(sizeof(int)*2);
		}

		for(i=0; i<w; i++){  //찾을 문자열 저장
			fscanf(fp,"%s",word[i]);			
		}

		alphabat_conversion(word,w,15);  //소문자로 변환

		for(i=0; i<w; i++)
			check(m,n,map,word[i],coordinate[i]);





	}


	//output
	printf("Case #%d\n\n",f);

	for(i=0; i<m; i++){		
		printf("%s",map[i]);
		printf("\n");
	}

	for(i=0; i<w; i++){		
		printf("%s",word[i]);
		printf("\n");
	}
}

//소문자 변환
void alphabat_conversion(char **arr,int m,int n){
	int i,j;

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			arr[i][j]=tolower(arr[i][j]);
		}
	}
}
