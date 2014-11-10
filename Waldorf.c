#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)  //scanf경고 제거

void alphabat_conversion(char **arr,int m,int n);  //소문자변환
void check(int m,int n,char **map,char *word,int *coordinate);  //문장의 첫 좌표찾기
void output(int f,int m,int n,int w,char **map,char **word,int **coordinate); //결과출력


int main(int argc, char *argv[])
{
	FILE *fp;
	int m,n,w,f=0;
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

		while(f<f_count){  //f_count만큼 반복
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
			printf("input drid #%d\n",f);
			for(i=0; i<m; i++){  //field 값 입력
				fflush(stdin);
				gets(map[i]);		
			}

			alphabat_conversion(map,m,n);  //소문자로 변환

			printf("input find word count >> ");
			scanf("%d",&w);  //찾을 단어 갯수

			word=(char **)malloc(sizeof(char *)*w);  //찾을 문자열 저장을 위한 공간할당
			coordinate=(int **)malloc(sizeof(int *)*w);  //찾은 문자열 좌표 저장을 위한 공간할당
			for(i=0; i<w; i++){
				word[i]=(char *)malloc(sizeof(char)*15);
				coordinate[i]=(int *)malloc(sizeof(int)*2);
			}
			for(i=0; i<w; i++){  //좌표값 초기화
				for(j=0; j<2; j++)
					coordinate[i][j]=-1;
			}

			for(i=0; i<w; i++){  //찾을 문자열 저장
				printf("input find word #%d\n",i);
				scanf("%s",word[i]);			
			}

			alphabat_conversion(word,w,15);  //소문자로 변환

			for(i=0; i<w; i++)  //좌표찾기
				check(m,n,map,word[i],coordinate[i]);
			f++;
			output(f,m,n,w,map,word,coordinate);  //결과출력
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

		while(f<f_count){  //f_count만큼 반복
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
			for(i=0; i<w; i++){  //좌표값 초기화
				for(j=0; j<2; j++)
					coordinate[i][j]=-1;
			}
			

			for(i=0; i<w; i++){  //찾을 문자열 저장
				fscanf(fp,"%s",word[i]);			
			}

			alphabat_conversion(word,w,15);  //소문자로 변환

			for(i=0; i<w; i++)  //좌표찾기
				check(m,n,map,word[i],coordinate[i]);
			f++;
			output(f,m,n,w,map,word,coordinate);  //결과출력
		}
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

//output
void output(int f,int m,int n,int w,char **map,char **word,int **coordinate){
	int i;

	printf("Case #%d\n\n",f);

	printf("%d %d\n",m,n);

	for(i=0;i<m;i++)
		printf("%s\n",map[i]);

	printf("\n%d\n",w);

	for(i=0;i<w;i++)
		printf("%s\n\n",word[i]);	

	for(i=0; i<w; i++){  //좌표 출력
		if(coordinate[i][0] != -1 && coordinate[i][1] != -1)
			printf("%d %d\n\n",coordinate[i][0],coordinate[i][1]);
		else
			printf("격자안에서 %s를 찾을 수 없어\n\n",word[i]);
	}
}

//문장의 첫 좌표찾기
void check(int m,int n,char **map,char *word,int *coordinate){
	int i,j,i2,j2;
	int direction; 
	//방향(1-왼쪽위,2-왼쪽,3-왼쪽아래,4-아래,5-오른쪽아래,6-오른쪽,7-오른쪽위,8-위
	int check;
	int len=strlen(word);
	int i3,j3;
	int count;

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(map[i][j] == word[0]){ //첫단어를 찾고							
				for(i2=i-1; i2<i+2; i2++){  //그주위탐색
					for(j2=j-1; j2<j+2; j2++){
						count=2; check=0;
						if((i2>-1 && j2>-1 && i2<m && j2<n) && map[i2][j2] == word[1]){  //방향 설정
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

							switch(direction){  //그방향으로 쭉 탐색
							case 1 :  //왼쪽위 i-1,j-1
								i3=i2-1; j3=j2-1;
								while(i3>-1 && j3>-1){
									if(map[i3--][j3--] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 2 :  //왼쪽 i,j-1
								i3=i2; j3=j2-1;
								while(j3>-1){
									if(map[i3][j3--] == word[count++]){
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;							
							case 3 :  //왼쪽아래 i+1,j-1
								i3=i2+1; j3=j2-1;
								while(i3<m && j3>-1){
									if(map[i3++][j3--] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 4 :  //아래 i+1,j
								i3=i2+1; j3=j2;
								while(i3<m){
									if(map[i3++][j3] == word[count++]){																		
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;							
							case 5 :  //오른쪽아래 i+1,j+1
								i3=i2+1; j3=j2+1;
								while(i3<m && j3<n){
									if(map[i3++][j3++] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;
							case 6 :  //오른쪽 i,j+1
								i3=i2; j3=j2+1;
								while(j3<n){
									if(map[i3][j3++] == word[count++]){
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 7 :  //오른쪽위 i-1,j+1
								i3=i2-1; j3=j2+1;
								while(i3>-1 && j3<n){
									if(map[i3--][j3++] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;
							case 8 :  //위 i-1,j
								i3=i2-1; j3=j2;
								while(i3>-1){
									if(map[i3--][j3] == word[count++]){																		
										check++;
										if(check == len-2){
											coordinate[0]=i;  //첫첫단어 좌표 저장
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;
							}
						}
					}
				}
			}
		}
	}
}
