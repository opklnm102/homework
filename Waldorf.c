#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

void alphabat_conversion(char **arr,int m,int n);  //�ҹ��ں�ȯ

void check(int m,int n,char **map,char *word,int *coordinate){
	int i,j,i2,j2;
	//int right,left,up,down,ru_diagonal,rd_diagonal,lu_diagonal,ld_diagonal;  //8����
	//right=left=up=down=ru_diagonal=rd_diagonal=lu_diagonal=ld_diagonal=0;
	int direction; 
	//����(1-������,2-����,3-���ʾƷ�,4-�Ʒ�,5-�����ʾƷ�,6-������,7-��������,8-��

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			if(map[i][j] == word[0]){ //ù�ܾ ã���� �������� Ž��

				for(i2=i-1; i2<i+2; i2++){
					for(j2=j-1; j2<j+2; j2++){
						if(map[i2][j2] == word[1]){  //���� ����
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

		for(i=0; i<m; i++){  //field �� �Է�
			fflush(stdin);
			gets(map[i]);		
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

		for(i=0; i<w; i++){  //ã�� ���ڿ� ����
			fscanf(fp,"%s",word[i]);			
		}

		alphabat_conversion(word,w,15);  //�ҹ��ڷ� ��ȯ

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

//�ҹ��� ��ȯ
void alphabat_conversion(char **arr,int m,int n){
	int i,j;

	for(i=0; i<m; i++){
		for(j=0; j<n; j++){
			arr[i][j]=tolower(arr[i][j]);
		}
	}
}
