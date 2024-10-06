#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define N 1000
#define False 0
#define True 1
//book�ڵ�
typedef struct Book{
	char id[50];	//Ψһ
	char name[50];
	char author[50];
	char publisher[50];
	int pub_year;
}Book;
//����ڵ�
typedef struct Node{
	struct Node* next;
	struct Book book;
}Node,*pNode;

void welcome();			//�����û��Ѻý���
void insNode(pNode head,int id_arr[]);	//����ڵ�
void delNode(pNode head,int id_arr[]);	//ɾ���ڵ�
int isEmpty(pNode head);	//�п�
int fun_1(pNode head);		//���ļ����ص�����
void updNode(pNode head,int id_arr[]);	//���½ڵ�
void putFresh(pNode head);	//���������ݵ���
void saveBook(pNode head);	//�־û�����
void loadBook(pNode *head);	//���س־û��洢������
void saveArray(int id_arr[]);	//�־û�id����
void loadArray(int id_arr[]);	//����id����
void printBook(pNode head);
int main() {
	//����id���飺Ҫ���ŷ�Χ��0-N,��id_arr[N]==1ʱ��ʾ��id�Ѿ�����,Ϊ0��ʾ�����ڡ�
	int id_arr[N]={0};
   //����ͷ���
	pNode head=(pNode)malloc(sizeof(Node));
	head->next=NULL;
	loadBook(&head);
	loadArray(id_arr);
	welcome();
	
	while(1){	
		char c;
		c=_getch();	//_getch() �������������ذ��µ��ַ�������Ҫ���س�����Ҳ��������ַ���
		switch(c){
			case '1':
				insNode(head,id_arr);  //headΪͷָ�룬Ҳ����ͷ�ڵ�ĵ�ַ
				break;	 //¼����Ŀ��Ϣ
			case '2': 
				delNode(head,id_arr);
				break;	//ɾ����Ŀ��Ϣ
			case '3': 
				updNode(head,id_arr);
				break;	//������Ŀ��Ϣ
			case '4': 
				putFresh(head);
				break;	//���������Ŀ��Ϣ
			case '5': 
				fun_1(head);
				break;	//��������
			case '6': 
				printBook(head);
				break;	
			case '0':
				system("cls");
				printf("�ټ���\n");
				exit(0);
				break;	//�˳�ϵͳ
			default: 
				printf("���������룡\n");
				break;
			}
		
}
}
void welcome(){
	printf("*********************************\n");
	printf("*\t��Ŀ�嵥�������\t*\t\n");
	printf("*********************************\n");
	printf("*\t��ѡ�����б�\t\t*\n");
	printf("*********************************\n");
	printf("*\t1.������Ŀ\t\t*\n");
	printf("*\t2.ɾ����Ŀ��Ϣ\t\t*\n");
	printf("*\t3.�޸���Ŀ��Ϣ\t\t*\n");
	printf("*\t4.������°���Ŀ��Ϣ\t*\n"); //����������µģ������ͬȫ�����
	printf("*\t5.���ļ��������ݵ���\t*\n");
	printf("*\t6.��ӡ������Ŀ\t\t*\n");
	printf("*\t0.�˳�����\t\t*\n");
	printf("*********************************\n");
}

//����
void insNode(pNode head,int id_arr[]){
	
	int n;	//����������
	pNode p=head;
	pNode newNode=(pNode)malloc(sizeof(Node));
	newNode->next=NULL;

	printf("�������š����ơ����ߡ������硢�������(�Կո��س��ָ�):\n");
	scanf("%s%s%s%s%d",newNode->book.id,newNode->book.name,
		newNode->book.author,newNode->book.publisher,&newNode->book.pub_year);
	//�ж�id�Ƿ����
	while(1){
		n=atoi(newNode->book.id);
		if(id_arr[n]==1){
			printf("��Ŀ����Ѵ��ڣ����������롣\n");
			printf("�������š����ơ����ߡ������硢�������(�Կո��س��ָ�):\n");
			scanf("%s%s%s%s%d",newNode->book.id,newNode->book.name,
			newNode->book.author,newNode->book.publisher,&newNode->book.pub_year);
		}
		else
			break;
		}
	while(p->next!=NULL){
		p=p->next;
}
	//���뵽β��
	p->next=newNode;	
	//д���ļ���
	saveBook(head);
	saveArray(id_arr);
	n=atoi(newNode->book.id);
	id_arr[n]=1;
	saveBook(head);
	
	printf("����ɹ���\n");
}

//�����ɾ��
void delNode(pNode head,int id_arr[]){
	int flag=0;		//0��ʾδ�ҵ���1��ʾ�ҵ�
	pNode p=head;	//pָ��ͷ�ڵ�,Ŀ�ģ���p->nextָ��Ҫɾ����Ŀ��
	pNode q=NULL;
	int i;
	char n[20];
	if(isEmpty(head)){
		printf("����Ϊ�ա�\n");
	}
	else{
		printf("������Ҫɾ������Ŀ��š�\n");
		scanf("%s",n);
		
		while(p->next){
			if(strcmp(n,p->next->book.id))	//��ͬ����0
			{//��ͬʱ
				p=p->next;
			}
			else{ //��ͬʱ
				flag=1;
				q=p->next;	//qָ��Ҫɾ���Ľڵ�
				i=atoi(q->book.id);
				p->next=q->next;
				free(q);
				id_arr[i]=0;
				saveBook(head);
				saveArray(id_arr);
				
				break;
			}	
		}
		if (flag==0)
			printf("δ�ҵ��ñ�ŵ��顣\n");
		else
			printf("�ɹ�ɾ�����Ϊ��%s����Ŀ��\n",n);
	}
}

void updNode(pNode head,int id_arr[]){
	int flag=0;	//0��ʾ�޸�ʧ�ܣ�1��ʾ�޸ĳɹ�
	pNode p=head->next;
	int i;
	char n[20];
	if(isEmpty(head)){
		printf("����Ϊ��\n");
		return;
	}
	printf("������Ҫ�޸ĵ���Ŀ��š�\n");
	scanf("%s",n);
	if(isEmpty(head)){
		printf("����Ϊ��");
	}
	else{
		//��������Ѱ�Ҹýڵ�
		while(p){
			if(strcmp(p->book.id,n))	//��ͬ�򷵻�0
			{
				p=p->next;
			}
			else{
				printf("�Ѿ��ҵ��ý��\n");
				id_arr[atoi(p->book.id)]=0;
				printf("�밴�����룺��š����ơ����ߡ������硢�������(�Կո��س��ָ�)��\n");
				scanf("%s%s%s%s%d",p->book.id,p->book.name,p->book.author,
					p->book.publisher,&p->book.pub_year);
				i=atoi(p->book.id);
				id_arr[i]=1;
				flag=1;
				break;
			}
		}
	
	if(flag==0)
		printf("δ�ҵ��ñ�ţ��޸�ʧ�ܣ������ԡ�\n");
	else{
		printf("�޸ĳɹ���\n");
		saveBook(head);
	}
	}
}

void putFresh(pNode head){
	pNode p=head;
	int n;  //��n��ʾ���µ����
	if(isEmpty(head))
		{
			printf("����Ϊ�ա�\n");
			return;
	}
	else
		{	
			p=p->next;
			//����n���ڵ�һ�����
			n=p->book.pub_year;
			while(p!=NULL){ //�ҵ�����year
				if(p->book.pub_year>n)
					n=p->book.pub_year;
				p=p->next;
			}
			//ѭ�������ҵ�������year������������year����Ŀ
			p=head->next;  //p��ָ���һ�����
			printf("������������ݵ���Ŀ��Ϣ��\n");
			while(p){
				if(p->book.pub_year==n)
					printf("��Ŀ��ţ�%s ������%s ���ߣ�%s �����磺%s ������ݣ�%d\n",
					p->book.id,p->book.name,p->book.author,
					p->book.publisher,p->book.pub_year);	
				p=p->next;
			}
		}
}
int isEmpty(pNode head){
	if(head->next==NULL)
		return 1;	//��
	else	
		return 0;	//�ǿ�
}

//�־û��洢
void saveBook(pNode head){
	FILE* fp;
	pNode p;
	fp=fopen("./book_info.txt","w");	
	if(fp==NULL){ 
		printf("�ļ���ʧ�ܣ�\n");
		return;} 
	p=head->next;
	while(p!=NULL){
		fprintf(fp,"%s %s %s %s %d\n",p->book.id,p->book.name,p->book.author,
			p->book.publisher,p->book.pub_year);
		p=p->next;	
	}
	
	fclose(fp);
}

//�����ļ�
void loadBook(pNode *head){
	char line[256];
	char *token;
	FILE* fp=fopen("./book_info.txt","r");
	pNode p=*head;		
	pNode newNode=(pNode)malloc(sizeof(Node));
	memset(newNode, 0, sizeof(Node));
	newNode->next=NULL;
	//���ļ�
	if(fp==NULL)
{		printf("û���ļ���������ȡ!\n");
		return;
}
	 // ���ж�ȡ����
	while (fgets(line, sizeof(line), fp) != NULL) {
		token = strtok(line, " ");
		sscanf(token, "%s", newNode->book.id);
		token = strtok(NULL, " ");
		sscanf(token, "%s", newNode->book.name);
		token = strtok(NULL, " ");
		sscanf(token, "%s", newNode->book.author);
		token = strtok(NULL, " ");
		sscanf(token, "%s", newNode->book.publisher);
		token = strtok(NULL, " ");
		sscanf(token, "%d", &newNode->book.pub_year);
		//��ͷ������д������
		p->next=newNode;
		p=p->next;
		//д����ɺ��ٴ���һ���½�㣬�ٴ�ѭ��ʱ�ͻ��������д��
		newNode=(pNode)malloc(sizeof(Node));
		memset(newNode, 0, sizeof(Node));
		newNode->next=NULL;
	}	
	free(newNode);	//ѭ������ʱʣ��һ���ս��
	fclose(fp);
	printf("��ȡ�ɹ���\n");
}

// �����鱣�浽�ļ�
void saveArray(int id_arr[]) {
    FILE *fp = fopen("./arr_info.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fwrite(id_arr, sizeof(int), N, fp);
    fclose(fp);
}

// ���ļ��лָ�����
void loadArray(int id_arr[]) {
    FILE *fp = fopen("./arr_info.txt", "rb");
    if (fp == NULL) {
        return;
    }
    fread(id_arr, sizeof(int), N, fp);
    fclose(fp);
}


int fun_1(pNode head){	//���ú��������ʵ������һ
	char line[256];	//�����洢ÿ��
	char *token; //�����洢���ŷָ���ÿ���ַ���
	FILE *fp;
	pNode p=head;
	pNode newNode=(pNode)malloc(sizeof(Node));
	newNode->next=NULL;

	fp= fopen("booklist.csv","r"); // CSV�ļ���
	if (fp == NULL) {
        perror("�ļ�Ϊ��");
        return False;
	}
	 // ���ж�ȡ����
	while (fgets(line, sizeof(line), fp) != NULL) {
		token = strtok(line, ",");
		sscanf(token, "%s", newNode->book.id);
		token = strtok(NULL, ",");
		sscanf(token, "%s", newNode->book.name);
		token = strtok(NULL, ",");
		sscanf(token, "%s", newNode->book.author);
		token = strtok(NULL, ",");
		sscanf(token, "%s", newNode->book.publisher);
		token = strtok(NULL, ",");
		sscanf(token, "%d", &newNode->book.pub_year);
		//��������
		while(p->next)
			p=p->next;
		//ѭ������pָ�����һ���ڵ�
		p->next=newNode;
		p=p->next;
		printf("����ɹ���\n");
		saveBook(head);
		//�����½ڵ�
		newNode=(pNode)malloc(sizeof(Node));
		newNode->next=NULL;
	}
    // �ر��ļ�
    fclose(fp);
	return True;
	}

void printBook(pNode head){
	pNode move=head->next;
	while(move!=NULL)
	{
		printf("%s  %s  %s  %s  %d\n",move->book.id,move->book.name,move->book.author,move->book.publisher,move->book.pub_year);
		move=move->next;
	}}