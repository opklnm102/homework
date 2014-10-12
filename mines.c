#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

void check(int n,int m,char *mf);  //지뢰찾기

int main(int argc, char *argv[])
{
	FILE *fp;
	char *mf,*row;
	int n,m,i,j,f_id;  //n=row, m=col

	f_id = 1;

	if(argc == 1){  //콘솔입출력
		scanf("%d %d",&n,&m);
		fflush(stdin);		

		while(n != 0 && m!= 0){
			mf = (char *)malloc(sizeof(char) * n * m);  //field 생성
			if(mf == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}

			for(i=0; i<n; i++)  //field 초기화
				for(j=0; j<m; j++)
					mf[i*m+j] = '0';

			row = (char *)malloc(sizeof(char) * (m+1));  //한줄입력을 위한 동적할당
			if(row == NULL)
				return -2;

			for(i=0; i<n; i++){  //지뢰값 입력
				gets(row);  					
				for(j=0; j<m; j++)
					if(row[j] == '*')	
						mf[i*m+j] = '*';		
			}			

			check(n,m,mf);  //지뢰찾기 함수 호출			

			//지뢰값 출력
			printf("Field #%d\n",f_id);
			for(i=0; i<n; i++){
				for(j=0; j<m; j++)
					printf("%c",mf[i*m+j]);
				printf("\n");
			}

			scanf("%d %d",&n,&m);  //다음 field를 할지 끝낼지
			fflush(stdin);
			if(n == 0 && m ==0)
				break;
			f_id++;
			printf("\n");
		}//while loop 	
	}//argc=1

	else if(argc == 2){  //파일입출력

		fp=fopen(argv[1],"r");
		if(fp == NULL){
			printf("Error: %s can not open.\n",argv[1]);
			return -1;
		}

		fscanf(fp,"%d %d",&n,&m);

		while(n != 0 && m!= 0){
			mf = (char *)malloc(sizeof(char) * n * m);  //field 생성
			if(mf == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}

			for(i=0; i<n; i++)  //field 초기화
				for(j=0; j<m; j++)
					mf[i*m+j] = '0';

			row = (char *)malloc(sizeof(char) * (m+1));  //한줄입력을 위한 동적할당
			if(row == NULL)
				return -2;
			fseek(fp,2,SEEK_CUR);  //line feed와 carriage return 때문에 현재커서에서 2바이트씩 이동

			for(i=0; i<n; i++){  //지뢰값 입력
				fgets(row,m+1,fp);  
				fseek(fp,2,SEEK_CUR);  //LF와 CR때문에 현재커서에서 2바이트씩 이동   <LF+CR=\n>
				for(j=0; j<m; j++)
					if(row[j] == '*')	
						mf[i*m+j] = '*';
			}

			check(n,m,mf);  //지뢰찾기 함수호출

			//지뢰값 출력
			printf("Field #%d\n",f_id);
			for(i=0; i<n; i++){
				for(j=0; j<m; j++)
					printf("%c",mf[i*m+j]);
				printf("\n");
			}

			fscanf(fp,"%d %d",&n,&m);  //다음 field할지 끝낼지
			fflush(stdin);
			if(n == 0 && m ==0)
				break;
			f_id++;
			printf("\n");
		}//while loop 	
	}//argc=2
}//main

//지뢰찾기 (*이 아닌 셀일때 주위에 *이 있으면 증가)
void check(int n,int m,char *mf){
	int i,j,i2,j2;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(mf[i*m+j] != '*'){ 					
				if(i == 0 && j == 0){  //왼쪽 아래 구석
					for(i2=i; i2<i+2; i2++)  
						for(j2=j; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(i == n-1 && j == 0){  //왼쪽 위 구석
					for(i2=i-1; i2<i+1; i2++)  
						for(j2=j; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(i == 0 && j == m-1){  //오른쪽 아래 구석

					for(i2=i; i2<i+2; i2++)  
						for(j2=j-1; j2<j+1; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(i == n-1 && j == m-1){  //오른쪽 위 구석
					for(i2=i-1; i2<i+1; i2++)  
						for(j2=j-1; j2<j+1; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;

				}
				else if(i == 0){  //맨 윗줄
					for(i2=i; i2<i+2; i2++) 
						for(j2=j-1; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(i == n-1){  //맨 아랫줄
					for(i2=i-1; i2<i+1; i2++)  
						for(j2=j-1; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(j == 0){  //맨 왼쪽줄
					for(i2=i-1; i2<i+2; i2++)  
						for(j2=j; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else if(j == m-1){  //맨 오른쪽줄
					for(i2=i-1; i2<i+2; i2++)  
						for(j2=j-1; j2<j+1; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
				else{  //막힌데 없을 때
					for(i2=i-1; i2<i+2; i2++)  
						for(j2=j-1; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*')
								mf[i*m+j]++;
				}
			}
		}
	}
}