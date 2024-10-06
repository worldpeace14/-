#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<conio.h>
#define N 1000
#define False 0
#define True 1
//book节点
typedef struct Book{
	char id[50];	//唯一
	char name[50];
	char author[50];
	char publisher[50];
	int pub_year;
}Book;
//链表节点
typedef struct Node{
	struct Node* next;
	struct Book book;
}Node,*pNode;

void welcome();			//启动用户友好界面
void insNode(pNode head,int id_arr[]);	//插入节点
void delNode(pNode head,int id_arr[]);	//删除节点
int isEmpty(pNode head);	//判空
int fun_1(pNode head);		//从文件加载到链表
void updNode(pNode head,int id_arr[]);	//更新节点
void putFresh(pNode head);	//输出最新年份的书
void saveBook(pNode head);	//持久化数据
void loadBook(pNode *head);	//加载持久化存储的数据
void saveArray(int id_arr[]);	//持久化id数组
void loadArray(int id_arr[]);	//导入id数组
void printBook(pNode head);
int main() {
	//创建id数组：要求编号范围在0-N,当id_arr[N]==1时表示该id已经存在,为0表示不存在。
	int id_arr[N]={0};
   //创建头结点
	pNode head=(pNode)malloc(sizeof(Node));
	head->next=NULL;
	loadBook(&head);
	loadArray(id_arr);
	welcome();
	
	while(1){	
		char c;
		c=_getch();	//_getch() 函数会立即返回按下的字符，不需要按回车键。也不会回显字符。
		switch(c){
			case '1':
				insNode(head,id_arr);  //head为头指针，也就是头节点的地址
				break;	 //录入书目信息
			case '2': 
				delNode(head,id_arr);
				break;	//删除书目信息
			case '3': 
				updNode(head,id_arr);
				break;	//更新书目信息
			case '4': 
				putFresh(head);
				break;	//输出最新书目信息
			case '5': 
				fun_1(head);
				break;	//导入数据
			case '6': 
				printBook(head);
				break;	
			case '0':
				system("cls");
				printf("再见！\n");
				exit(0);
				break;	//退出系统
			default: 
				printf("请重新输入！\n");
				break;
			}
		
}
}
void welcome(){
	printf("*********************************\n");
	printf("*\t书目清单管理程序\t*\t\n");
	printf("*********************************\n");
	printf("*\t请选择功能列表\t\t*\n");
	printf("*********************************\n");
	printf("*\t1.新增书目\t\t*\n");
	printf("*\t2.删除书目信息\t\t*\n");
	printf("*\t3.修改书目信息\t\t*\n");
	printf("*\t4.输出最新版书目信息\t*\n"); //输入年份最新的，年份相同全部输出
	printf("*\t5.从文件导入数据到表\t*\n");
	printf("*\t6.打印所有书目\t\t*\n");
	printf("*\t0.退出程序\t\t*\n");
	printf("*********************************\n");
}

//插入
void insNode(pNode head,int id_arr[]){
	
	int n;	//用来存索引
	pNode p=head;
	pNode newNode=(pNode)malloc(sizeof(Node));
	newNode->next=NULL;

	printf("请输入编号、名称、作者、出版社、出版年份(以空格或回车分隔):\n");
	scanf("%s%s%s%s%d",newNode->book.id,newNode->book.name,
		newNode->book.author,newNode->book.publisher,&newNode->book.pub_year);
	//判断id是否存在
	while(1){
		n=atoi(newNode->book.id);
		if(id_arr[n]==1){
			printf("书目编号已存在，请重新输入。\n");
			printf("请输入编号、名称、作者、出版社、出版年份(以空格或回车分隔):\n");
			scanf("%s%s%s%s%d",newNode->book.id,newNode->book.name,
			newNode->book.author,newNode->book.publisher,&newNode->book.pub_year);
		}
		else
			break;
		}
	while(p->next!=NULL){
		p=p->next;
}
	//插入到尾部
	p->next=newNode;	
	//写入文件中
	saveBook(head);
	saveArray(id_arr);
	n=atoi(newNode->book.id);
	id_arr[n]=1;
	saveBook(head);
	
	printf("插入成功。\n");
}

//按编号删除
void delNode(pNode head,int id_arr[]){
	int flag=0;		//0表示未找到，1表示找到
	pNode p=head;	//p指向头节点,目的：让p->next指向要删除的目标
	pNode q=NULL;
	int i;
	char n[20];
	if(isEmpty(head)){
		printf("链表为空。\n");
	}
	else{
		printf("请输入要删除的书目编号。\n");
		scanf("%s",n);
		
		while(p->next){
			if(strcmp(n,p->next->book.id))	//相同返回0
			{//不同时
				p=p->next;
			}
			else{ //相同时
				flag=1;
				q=p->next;	//q指向要删除的节点
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
			printf("未找到该编号的书。\n");
		else
			printf("成功删除编号为：%s的书目。\n",n);
	}
}

void updNode(pNode head,int id_arr[]){
	int flag=0;	//0表示修改失败，1表示修改成功
	pNode p=head->next;
	int i;
	char n[20];
	if(isEmpty(head)){
		printf("链表为空\n");
		return;
	}
	printf("请输入要修改的书目编号。\n");
	scanf("%s",n);
	if(isEmpty(head)){
		printf("链表为空");
	}
	else{
		//遍历链表寻找该节点
		while(p){
			if(strcmp(p->book.id,n))	//相同则返回0
			{
				p=p->next;
			}
			else{
				printf("已经找到该结点\n");
				id_arr[atoi(p->book.id)]=0;
				printf("请按序输入：编号、名称、作者、出版社、出版年份(以空格或回车分隔)。\n");
				scanf("%s%s%s%s%d",p->book.id,p->book.name,p->book.author,
					p->book.publisher,&p->book.pub_year);
				i=atoi(p->book.id);
				id_arr[i]=1;
				flag=1;
				break;
			}
		}
	
	if(flag==0)
		printf("未找到该编号，修改失败，请重试。\n");
	else{
		printf("修改成功。\n");
		saveBook(head);
	}
	}
}

void putFresh(pNode head){
	pNode p=head;
	int n;  //用n表示最新的年份
	if(isEmpty(head))
		{
			printf("链表为空。\n");
			return;
	}
	else
		{	
			p=p->next;
			//先让n等于第一个年份
			n=p->book.pub_year;
			while(p!=NULL){ //找到最大的year
				if(p->book.pub_year>n)
					n=p->book.pub_year;
				p=p->next;
			}
			//循环结束找到了最大的year，现在输出最大year的书目
			p=head->next;  //p先指向第一个结点
			printf("以下是最新年份的书目信息：\n");
			while(p){
				if(p->book.pub_year==n)
					printf("书目编号：%s 书名：%s 作者：%s 出版社：%s 出版年份：%d\n",
					p->book.id,p->book.name,p->book.author,
					p->book.publisher,p->book.pub_year);	
				p=p->next;
			}
		}
}
int isEmpty(pNode head){
	if(head->next==NULL)
		return 1;	//空
	else	
		return 0;	//非空
}

//持久化存储
void saveBook(pNode head){
	FILE* fp;
	pNode p;
	fp=fopen("./book_info.txt","w");	
	if(fp==NULL){ 
		printf("文件打开失败！\n");
		return;} 
	p=head->next;
	while(p!=NULL){
		fprintf(fp,"%s %s %s %s %d\n",p->book.id,p->book.name,p->book.author,
			p->book.publisher,p->book.pub_year);
		p=p->next;	
	}
	
	fclose(fp);
}

//加载文件
void loadBook(pNode *head){
	char line[256];
	char *token;
	FILE* fp=fopen("./book_info.txt","r");
	pNode p=*head;		
	pNode newNode=(pNode)malloc(sizeof(Node));
	memset(newNode, 0, sizeof(Node));
	newNode->next=NULL;
	//打开文件
	if(fp==NULL)
{		printf("没有文件，跳过读取!\n");
		return;
}
	 // 逐行读取数据
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
		//从头把数据写入链表
		p->next=newNode;
		p=p->next;
		//写入完成后再创建一个新结点，再次循环时就会把新数据写入
		newNode=(pNode)malloc(sizeof(Node));
		memset(newNode, 0, sizeof(Node));
		newNode->next=NULL;
	}	
	free(newNode);	//循环结束时剩下一个空结点
	fclose(fp);
	printf("读取成功！\n");
}

// 将数组保存到文件
void saveArray(int id_arr[]) {
    FILE *fp = fopen("./arr_info.txt", "w");
    if (fp == NULL) {
        perror("Error opening file");
        exit(1);
    }
    fwrite(id_arr, sizeof(int), N, fp);
    fclose(fp);
}

// 从文件中恢复数组
void loadArray(int id_arr[]) {
    FILE *fp = fopen("./arr_info.txt", "rb");
    if (fp == NULL) {
        return;
    }
    fread(id_arr, sizeof(int), N, fp);
    fclose(fp);
}


int fun_1(pNode head){	//调用函数则完成实验内容一
	char line[256];	//用来存储每行
	char *token; //用来存储逗号分隔的每个字符串
	FILE *fp;
	pNode p=head;
	pNode newNode=(pNode)malloc(sizeof(Node));
	newNode->next=NULL;

	fp= fopen("booklist.csv","r"); // CSV文件名
	if (fp == NULL) {
        perror("文件为空");
        return False;
	}
	 // 逐行读取数据
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
		//插入数据
		while(p->next)
			p=p->next;
		//循环结束p指向最后一个节点
		p->next=newNode;
		p=p->next;
		printf("插入成功。\n");
		saveBook(head);
		//创建新节点
		newNode=(pNode)malloc(sizeof(Node));
		newNode->next=NULL;
	}
    // 关闭文件
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