#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>

void check(int n,int m,char *mf);  //����ã��

int main(int argc, char *argv[])
{
	FILE *fp;
	char *mf,*row;
	int n,m,i,j,f_id;  //n=row, m=col

	f_id = 1;

	if(argc == 1){  //�ܼ������
		printf("input n x m\n");
		scanf("%d %d",&n,&m);
		fflush(stdin);		

		while(n != 0 && m!= 0){
			mf = (char *)malloc(sizeof(char) * n * m);  //field ����
			if(mf == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}
			row = (char *)malloc(sizeof(char) * (m+1));  //�����Է��� ���� �����Ҵ�
			if(row == NULL)
				return -2;			

			for(i=0; i<n; i++)  //field �ʱ�ȭ
				for(j=0; j<m; j++)
					mf[i*m+j] = '0';			

			for(i=0; i<n; i++){  //���ڰ� �Է�
				gets(row);  					
				for(j=0; j<m; j++)
					if(row[j] == '*')	
						mf[i*m+j] = '*';		
			}			

			check(n,m,mf);  //����ã�� �Լ� ȣ��	

			//���ڰ� ���
			printf("\nField #%d\n",f_id);
			for(i=0; i<n; i++){
				for(j=0; j<m; j++)
					printf("%c",mf[i*m+j]);
				printf("\n");
			}

			printf("input n x m\n");
			scanf("%d %d",&n,&m);  //���� field�� ���� ������
			fflush(stdin);
			if(n == 0 && m ==0)
				break;
			f_id++;
			
		}//while loop 	
	}//argc=1

	else if(argc == 2){  //���������

		fp=fopen(argv[1],"r");
		if(fp == NULL){
			printf("Error: %s can not open.\n",argv[1]);
			return -1;
		}

		fscanf(fp,"%d %d",&n,&m);

		while(n != 0 && m!= 0){
			mf = (char *)malloc(sizeof(char) * n * m);  //field ����
			if(mf == NULL){
				printf("ERROR : Can't allocate memory of %d x %d field.\n",n,m);
				return -1;
			}

			row = (char *)malloc(sizeof(char) * (m+1));  //�����Է��� ���� �����Ҵ�
			if(row == NULL)
				return -2;		

			for(i=0; i<n; i++)  //field �ʱ�ȭ
				for(j=0; j<m; j++)
					mf[i*m+j] = '0';				

			for(i=0; i<n; i++){  //���ڰ� �Է�
				fseek(fp,2,SEEK_CUR);  //LF�� CR������ ����Ŀ������ 2����Ʈ�� �̵�   <LF+CR=\n>
				fgets(row,m+1,fp);  

				for(j=0; j<m; j++)
					if(row[j] == '*')	
						mf[i*m+j] = '*';
			}

			check(n,m,mf);  //����ã�� �Լ�ȣ��

			//���ڰ� ���
			printf("Field #%d\n",f_id);
			for(i=0; i<n; i++){
				for(j=0; j<m; j++)
					printf("%c",mf[i*m+j]);
				printf("\n");
			}

			fscanf(fp,"%d %d",&n,&m);  //���� field���� ������
			fflush(stdin);
			if(n == 0 && m ==0)
				break;
			f_id++;
			printf("\n");
		}//while loop 	
	}//argc=2


}//main

//����ã�� (*�� �ƴ� ���϶� ���� 8�� ���� *�� ������ ����)
void check(int n,int m,char *mf){
	int i,j,i2,j2;
	for(i=0; i<n; i++){
		for(j=0; j<m; j++){
			if(mf[i*m+j] != '*'){ 
				for(i2=i-1; i2<i+2; i2++)  
						for(j2=j-1; j2<j+2; j2++)
							if(mf[i2*m+j2] == '*' && (i2>-1 && j2>-1 && i2<n && j2<m) )
								mf[i*m+j]++;
			}
		}
	}
}
