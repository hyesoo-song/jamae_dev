#include <stdio.h>
#include <stdlib.h>
#include "account.h"
#define START_ACCOUNT 202100001

void acc_create(char*);
void acc_deposit(char*);
void acc_withdraw(char*);
void acc_balance(char*);

int main(int argc,char* argv[]){
 int num;
 FILE *fp;
 fp=fopen(argv[1],"wb");
 fclose(fp);
 do{
	printf("------MENU------\n");
	printf("1. 계좌생성\n");
	printf("2. 입금\n");
	printf("3. 출금\n");
	printf("4. 잔액조회\n");
	printf("5. 프로그램 종료\n");
	printf("----------------\n");
	printf("원하는 메뉴를 입력하시오: ");
	scanf("%d",&num);
	switch(num){
		case 1:
			acc_create(argv[1]);
			break;
		case 2:
			acc_deposit(argv[1]);
			break;
		case 3:
			acc_withdraw(argv[1]);
			break;
		case 4:
			acc_balance(argv[1]);
			break;
		case 5:
			remove(argv[1]);
			exit(0);
	}

 }while(num != 5);
}

void acc_create(char *file){
	struct customer rec;
	FILE *fp;
	char *account;
	fp=fopen(file,"r+");
	
	printf("계좌 생성 메뉴 - 계좌번호, 이름, 초기 입금액을 띄어쓰기로 구분하여 입력해주시기 바랍니다.\n");
	if(scanf("%d %s %d",&rec.account_num,rec.name,&rec.balance)==3){
		fseek(fp,(rec.account_num-START_ACCOUNT)*sizeof(rec),SEEK_SET);
		if(fread(account,sizeof(rec.account_num),1,fp)>0)
			printf("이미 존재하는 계좌번호입니다.\n");
		else
			fwrite(&rec,sizeof(rec),1,fp);	
	}
	fclose(fp);	
}

void acc_deposit(char *file){
	struct customer rec;
	int num;
	int dmoney;
	FILE *fp;
	fp=fopen(file,"rb+");
	
	printf("입금 메뉴\n");
	printf("계좌번호를 입력하세요: ");
	if(scanf("%d",&num)==1){
		fseek(fp,(num-START_ACCOUNT)*sizeof(rec),SEEK_SET);
		if((fread(&rec,sizeof(rec),1,fp)>0) && (rec.account_num != 0)){
			printf("입금할 금액을 입력하세요: ");
			scanf("%d",&dmoney);
			rec.balance = rec.balance + dmoney;
			fseek(fp,-sizeof(rec),SEEK_CUR);
			fwrite(&rec,sizeof(rec),1,fp);
			
		
		}else printf("NO RECORD!\n");
	}else printf("입력 오류\n");
	fclose(fp);
	fflush(fp);
}

void acc_withdraw(char *file){
	struct customer rec;
	int num;
	int wmoney;
	FILE *fp;
	fp=fopen(file,"rb+");

	printf("출금 메뉴\n");
	printf("계좌번호를 입력하세요: ");
	if(scanf("%d",&num)==1){
		fseek(fp,(num-START_ACCOUNT)*sizeof(rec),SEEK_SET);
		if((fread(&rec,sizeof(rec),1,fp)>0) && (rec.account_num != 0)){
			printf("출금할 금액을 입력하세요: ");
			scanf("%d",&wmoney);
			rec.balance = rec.balance - wmoney;
			fseek(fp,-sizeof(rec),SEEK_CUR);
			fwrite(&rec,sizeof(rec),1,fp);

		}else printf("NO RECORD!\n");
	}else printf("입력 오류\n");
	fclose(fp);
	fflush(fp);
}

void acc_balance(char *file){
	struct customer rec;
	int num;
	FILE *fp;
	fp=fopen(file,"rb");

	printf("잔액조회 메뉴\n");
	printf("계좌번호를 입력하세요: ");
	if(scanf("%d",&num)==1){
		fseek(fp,(num-START_ACCOUNT)*sizeof(rec),SEEK_SET);
		if((fread(&rec,sizeof(rec),1,fp)>0) && (rec.account_num != 0)){
			printf("*계좌번호: %d\n",rec.account_num);
			printf("*이름: %s\n",rec.name);
			printf("*잔액: %d\n",rec.balance);
		}else printf("NO RECORD!\n");
	}
	fclose(fp);
}
 
