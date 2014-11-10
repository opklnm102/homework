#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#pragma warning(disable:4996)  //scanf��� ����

void alphabat_conversion(char **arr,int m,int n);  //�ҹ��ں�ȯ
void check(int m,int n,char **map,char *word,int *coordinate);  //������ ù ��ǥã��
void output(int f,int m,int n,int w,char **map,char **word,int **coordinate); //������


int main(int argc, char *argv[])
{
	FILE *fp;
	int m,n,w,f=0;
	int f_count;  //case�� ��
	char **map,**word;  //grid(������)�� ã���ܾ� 
	int **coordinate;  //��ǥ�� ����
	int i,j;  

	//input
	if(argc == 1){  //�ܼ��Է�
		while(1){
			printf("input case>> "); scanf("%d",&f_count);  //Case # �Է�
			if(1<=f_count && f_count<=20) break;  //f�� ������ 1~20
		}

		while(f<f_count){  //f_count��ŭ �ݺ�
			while(1){
				printf("input m X n>> "); scanf("%d %d",&m,&n);
				if((1<= m && m<=60) && (1<=n && n<=60)) break; //m,n�� ���� 1~60
			}

			map=(char **)malloc(sizeof(char *)*m);  //field ����
			for(i=0; i<m; i++)
				map[i]=(char *)malloc(sizeof(char)*n);
			if(map == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}
			printf("input drid #%d\n",f);
			for(i=0; i<m; i++){  //field �� �Է�
				fflush(stdin);
				gets(map[i]);		
			}

			alphabat_conversion(map,m,n);  //�ҹ��ڷ� ��ȯ

			printf("input find word count >> ");
			scanf("%d",&w);  //ã�� �ܾ� ����

			word=(char **)malloc(sizeof(char *)*w);  //ã�� ���ڿ� ������ ���� �����Ҵ�
			coordinate=(int **)malloc(sizeof(int *)*w);  //ã�� ���ڿ� ��ǥ ������ ���� �����Ҵ�
			for(i=0; i<w; i++){
				word[i]=(char *)malloc(sizeof(char)*15);
				coordinate[i]=(int *)malloc(sizeof(int)*2);
			}
			for(i=0; i<w; i++){  //��ǥ�� �ʱ�ȭ
				for(j=0; j<2; j++)
					coordinate[i][j]=-1;
			}

			for(i=0; i<w; i++){  //ã�� ���ڿ� ����
				printf("input find word #%d\n",i);
				scanf("%s",word[i]);			
			}

			alphabat_conversion(word,w,15);  //�ҹ��ڷ� ��ȯ

			for(i=0; i<w; i++)  //��ǥã��
				check(m,n,map,word[i],coordinate[i]);
			f++;
			output(f,m,n,w,map,word,coordinate);  //������
		}
	}
	else if(argc == 2){  //�����Է�
		fp=fopen(argv[1],"r");
		if(fp == NULL){
			printf("Error : %s can not open.\n",argv[1]);
			return -1;
		}

		while(1){
			fscanf(fp,"%d",&f_count);  //Case # �Է�
			if(1<=f_count && f_count<=20) break;  //f�� ������ 1~20
		}

		while(f<f_count){  //f_count��ŭ �ݺ�
			while(1){
				fscanf(fp,"%d %d",&m,&n);
				if((1<= m && m<=60) && (1<=n && n<=60)) break; //m,n�� ���� 1~60
			}

			map=(char **)malloc(sizeof(char *)*m);  //field ����
			for(i=0; i<m; i++)
				map[i]=(char *)malloc(sizeof(char)*n);
			if(map == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}
			
			for(i=0; i<m; i++){  ////field �� �Է�				
				fscanf(fp,"%s",map[i]);
			}

			alphabat_conversion(map,m,n);  //�ҹ��ڷ� ��ȯ

			fscanf(fp,"%d",&w);  //ã�� �ܾ� ����

			word=(char **)malloc(sizeof(char *)*w);  //ã�� ���ڿ� ������ ���� �����Ҵ�
			coordinate=(int **)malloc(sizeof(int *)*w);  //ã�� ���ڿ� ��ǥ ������ ���� �����Ҵ�
			for(i=0; i<w; i++){
				word[i]=(char *)malloc(sizeof(char)*15);
				coordinate[i]=(int *)malloc(sizeof(int)*2);
			}
			for(i=0; i<w; i++){  //��ǥ�� �ʱ�ȭ
				for(j=0; j<2; j++)
					coordinate[i][j]=-1;
			}
			

			for(i=0; i<w; i++){  //ã�� ���ڿ� ����
				fscanf(fp,"%s",word[i]);			
			}

			alphabat_conversion(word,w,15);  //�ҹ��ڷ� ��ȯ

			for(i=0; i<w; i++)  //��ǥã��
				check(m,n,map,word[i],coordinate[i]);
			f++;
			output(f,m,n,w,map,word,coordinate);  //������
		}
	}
}

//�ҹ��� ��ȯ
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

	for(i=0; i<w; i++){  //��ǥ ���
		if(coordinate[i][0] != -1 && coordinate[i][1] != -1)
			printf("%d %d\n\n",coordinate[i][0],coordinate[i][1]);
		else
			printf("���ھȿ��� %s�� ã�� �� ����\n\n",word[i]);
	}
}

//������ ù ��ǥã��
void check(int m,int n,char **map,char *word,int *coordinate){
	int i,j,i2,j2;
	int direction; 
	//����(1-������,2-����,3-���ʾƷ�,4-�Ʒ�,5-�����ʾƷ�,6-������,7-��������,8-��
	int check;
	int len=strlen(word);
	int i3,j3;
	int count;

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(map[i][j] == word[0]){ //ù�ܾ ã��							
				for(i2=i-1; i2<i+2; i2++){  //������Ž��
					for(j2=j-1; j2<j+2; j2++){
						count=2; check=0;
						if((i2>-1 && j2>-1 && i2<m && j2<n) && map[i2][j2] == word[1]){  //���� ����
							if(i2 == i-1 && j2 == j-1)  //������
								direction=1;
							else if(i2 == i && j2 == j-1)  //����
								direction=2;
							else if(i2 == i+1 && j2 == j-1)  //���ʾƷ�
								direction=3;
							else if(i2 == i+1 && j2 == j)  //�Ʒ�
								direction=4;
							else if(i2 == i+1 && j2 == j+1)  //�����ʾƷ�
								direction=5;
							else if(i2 == i && j2 == j+1)  //������
								direction=6;
							else if(i2 == i-1 && j2 == j+1)  //��������
								direction=7;
							else if(i2 == i-1 && j2 == j)  //��
								direction=8;						

							switch(direction){  //�׹������� �� Ž��
							case 1 :  //������ i-1,j-1
								i3=i2-1; j3=j2-1;
								while(i3>-1 && j3>-1){
									if(map[i3--][j3--] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 2 :  //���� i,j-1
								i3=i2; j3=j2-1;
								while(j3>-1){
									if(map[i3][j3--] == word[count++]){
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;							
							case 3 :  //���ʾƷ� i+1,j-1
								i3=i2+1; j3=j2-1;
								while(i3<m && j3>-1){
									if(map[i3++][j3--] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 4 :  //�Ʒ� i+1,j
								i3=i2+1; j3=j2;
								while(i3<m){
									if(map[i3++][j3] == word[count++]){																		
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;							
							case 5 :  //�����ʾƷ� i+1,j+1
								i3=i2+1; j3=j2+1;
								while(i3<m && j3<n){
									if(map[i3++][j3++] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;
							case 6 :  //������ i,j+1
								i3=i2; j3=j2+1;
								while(j3<n){
									if(map[i3][j3++] == word[count++]){
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;								
							case 7 :  //�������� i-1,j+1
								i3=i2-1; j3=j2+1;
								while(i3>-1 && j3<n){
									if(map[i3--][j3++] == word[count++]){										
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
											coordinate[1]=j;
											return;
										}
									}
									else break;
								} break;
							case 8 :  //�� i-1,j
								i3=i2-1; j3=j2;
								while(i3>-1){
									if(map[i3--][j3] == word[count++]){																		
										check++;
										if(check == len-2){
											coordinate[0]=i;  //ùù�ܾ� ��ǥ ����
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
