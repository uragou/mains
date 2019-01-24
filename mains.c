#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<time.h>

#define NUM 15
#define MAIN 20
int syori(int,int);
void huku(int,int,int,int);
void mainc(int,int);
int idou(void);

int man[NUM][NUM];
char map[NUM][NUM],*po="0";
int yk=0,tt=0;

int main(void)
{
	int lop=0,lop2=0,snum=0,cnum=0,flag=0,srt=NUM*NUM-MAIN;
	
	if(NUM*NUM<=MAIN){
		printf("爆弾エラー\n");
		exit(1);
	}
	
	for(lop=0;lop<NUM;lop++){
		for(lop2=0;lop2<NUM;lop2++){
			map[lop][lop2]='0';
		}
	}
	system("cls");
	while(1){
		printf("残りマス＝%d\n",srt);
		srt=0;
		
		for(lop=0;lop<NUM;lop++){
			for(lop2=0;lop2<NUM;lop2++){
				if(map[lop][lop2]=='0'){
					srt++;
				}
			}
		}
		
		srt=srt-MAIN;
		
		if(flag==2 || srt==0){
			for(lop=0;lop<NUM;lop++){
				for(lop2=0;lop2<NUM;lop2++){
					if(map[lop][lop2]=='f'){
						if(man[lop][lop2]!=-1){
							map[lop][lop2]=' ';
						}else{
							map[lop][lop2]='0'+map[lop][lop2];
						}
					}
				}
			}
			
			
			for(lop=0;lop<NUM;lop++){
				printf(" ");
				for(lop2=0;lop2<NUM;lop2++){
					if(man[lop][lop2]==9){
						printf("9  ");
					}else{
						printf("%c  ",map[lop][lop2]);
					}
					
				}
				printf("\n");
				
			}
			if(flag==2){
				printf("敗北\n");
				break;
			}else if(srt==0){
				printf("勝利\n");
				break;
			}
		}else{
			for(lop=0;lop<NUM;lop++){
				printf(" ");
				for(lop2=0;lop2<NUM;lop2++){
					if(yk==lop2 && tt==lop){
						printf("U  ");
					}else{
						printf("%c  ",map[lop][lop2]);
					}
					
					/*
					if(yk==lop2 && tt==lop){
						printf("U  ");
					}else if(man[lop][lop2]==9){
						printf("9  ");
					}else{
						printf("%c  ",map[lop][lop2]);
					}*/
					//コメントアウト部分を使うと爆弾位置がわかる
				}
				printf("\n");
			}
		}
		printf("Uが現在指定してるマス\n十字キーで移動 スペースでそのマスをあける fキーでフラグ置く\n");
		flag=idou();
		
		system("cls");
	}
	
	return 0;
}

int idou(void){
	int num=0,fg=0,flag2=0;
	static int flg=0;
	do{
		num=getch();
		switch(num){
		case 75://左
			if(yk!=0){
				yk--;
			}
			fg=1;
			break;
		case 80://下
			if(tt!=NUM-1){
				tt++;
			}
			fg=1;
			break;
		case 77://右
			if(yk!=NUM-1){
				yk++;
			}
			fg=1;
			break;
		case 72://上
			if(tt!=0){
				tt--;
			}
			fg=1;
			break;
		case 32://スペース
			if(flg==0){
				flg=1;
				mainc(tt,yk);
				flag2=syori(tt,yk);
			}else{
				flag2=syori(tt,yk);
			}
			fg=1;
			break;
		case 102://f
			*po=map[tt][yk];
			printf("%d\n",*po);
			getch();
			if(strncmp(po,"0",1)==0){
				map[tt][yk]='f';
			}else if(strncmp(po,"f",1)==0){
				map[tt][yk]='0';
			}
			fg=1;
			break;
		default:
			fg=1;//後で消せ
			break;
		}
	}while(fg==0);
	
	return flag2;
}



void mainc(int syo,int sta){
	
	int data=0,tate=0,yoko=0,lop=0,lop2=0,nmain=0,lop3=0,lop4=0;
	
	srand(time(NULL));
	
	for(lop=0;lop<NUM;lop++){
		for(lop2=0;lop2<NUM;lop2++){
			man[lop][lop2]=0;
		}
	}
	lop=0;
	lop2=0;
	
	do{
		man[lop][lop2]=9;
		lop++;
		nmain++;
		if(lop==NUM){
			lop=0;
			lop2++;
		}
	}while(nmain!=MAIN);          //爆弾作る
	lop=0;
	lop2=0;
	do{
		tate=rand()%NUM;
		yoko=rand()%NUM;
		
		data=man[lop][lop2];
		man[lop][lop2]=man[yoko][tate];
		man[yoko][tate]=data;
		
		lop++;
		nmain--;
		if(lop==NUM){
			lop=0;
			lop2++;
		}
	}while(nmain!=0);               //爆弾置き換える
	
	while(1){
		if(man[syo][sta]==9){
			tate=rand()%NUM;
			yoko=rand()%NUM;
			
			data=man[syo][sta];
			man[syo][sta]=man[yoko][tate];
			man[yoko][tate]=data;
		}else{
			break;
		}
	}
	
	
	if(man[0][0]!=9){          //左上
		if(man[0][1]==9){
			man[0][0]++;
		}
		if(man[1][0]==9){
			man[0][0]++;
		}
		if(man[1][1]==9){
			man[0][0]++;
		}
	}
	
	if(man[0][NUM-1]!=9){
		if(man[0][NUM-2]==9){
			man[0][NUM-1]++;
		}
		if(man[1][NUM-1]==9){
			man[0][NUM-1]++;
		}
		if(man[1][NUM-2]==9){
			man[0][NUM-1]++;
		}
	}
	
	if(man[NUM-1][0]!=9){
		if(man[NUM-1][1]==9){
			man[NUM-1][0]++;
		}
		if(man[NUM-2][0]==9){
			man[NUM-1][0]++;
		}
		if(man[NUM-2][1]==9){
			man[NUM-1][0]++;
		}
	}
	
	
	if(man[NUM-1][NUM-1]!=9){          //右下
		if(man[NUM-1][NUM-2]==9){
			man[NUM-1][NUM-1]++;
		}
		if(man[NUM-2][NUM-1]==9){
			man[NUM-1][NUM-1]++;
		}
		if(man[NUM-2][NUM-2]==9){
			man[NUM-1][NUM-1]++;
		}
	}
	
	
	for(lop=1;lop<NUM-1;lop++){//2～14 B～N
		for(lop2=1;lop2<NUM-1;lop2++){
			if(man[lop][lop2]!=9){
				for(lop3=-1;lop3<2;lop3++){
					for(lop4=-1;lop4<2;lop4++){
						if(man[lop+lop3][lop2+lop4]==9){
							man[lop][lop2]++;
						}
					}
				}
			}
		}
	}
	
	for(lop=1;lop<NUM-1;lop++){
		if(man[0][lop]!=9){
			if(man[0][lop-1]==9){
				man[0][lop]++;
			}
			if(man[0][lop+1]==9){
				man[0][lop]++;
			}
			for(lop2=-1;lop2<2;lop2++){
				if(man[1][lop+lop2]==9){
					man[0][lop]++;
				}
			}
		}
		
		if(man[lop][0]!=9){
			if(man[lop-1][0]==9){
				man[lop][0]++;
			}
			if(man[lop+1][0]==9){
				man[lop][0]++;
			}
			for(lop2=-1;lop2<2;lop2++){
				if(man[lop+lop2][1]==9){
					man[lop][0]++;
				}
			}
		}
		
		if(man[lop][NUM-1]!=9){
			
			if(man[lop-1][NUM-1]==9){
				man[lop][NUM-1]++;
			}
			if(man[lop+1][NUM-1]==9){
				man[lop][NUM-1]++;
			}
			for(lop2=-1;lop2<=1;lop2++){
				if(man[lop+lop2][NUM-2]==9){
					man[lop][NUM-1]++;
				}
			}
		}
		
		if(man[NUM-1][lop]!=9){
			
			if(man[NUM-1][lop-1]==9){
				man[NUM-1][lop]++;
			}
			if(man[NUM-1][lop+1]==9){
				man[NUM-1][lop]++;
			}
			for(lop2=-1;lop2<=1;lop2++){
				if(man[NUM-2][lop+lop2]==9){
					man[NUM-1][lop]++;
				}
			}
			
		}
	}
	
	return;
}

int syori(int yoko,int tate){
	int num=0,data=0;
	data=man[yoko][tate];
	if(map[yoko][tate]=='f'){
		data=data;
	}else if(data==9){
		num=2;
		map[yoko][tate]='9';
	}else if(data!=0){
		switch(data){
			case -1:
				break;
			case 1:
				map[yoko][tate]='1';
				break;
			case 2:
				map[yoko][tate]='2';
				break;
			case 3:
				map[yoko][tate]='3';
				break;
			case 4:
				map[yoko][tate]='4';
				break;
			case 5:
				map[yoko][tate]='5';
				break;
			case 6:
				map[yoko][tate]='6';
				break;
			case 7:
				map[yoko][tate]='7';
				break;
			case 8:
				map[yoko][tate]='8';
				break;
		}
		num=0;
	}else{
		map[yoko][tate]=' ';
		man[yoko][tate]=-1;
		if(yoko-1>=0){
			huku(yoko-1,tate,yoko,tate);
		}
		if(yoko+1<NUM){
			huku(yoko+1,tate,yoko,tate);
		}
		if(tate-1>=0){
			huku(yoko,tate-1,yoko,tate);
		}
		if(tate+1<NUM){
			huku(yoko,tate+1,yoko,tate);
		}
		num=0;
	}
	return num;
}

void huku(int yoko,int tate,int myoko,int mtate){
	int data=0;
	data=man[yoko][tate];
	
	if(map[yoko][tate]=='f'){
		data=data;
	}else if(man[yoko][tate]==0){
		map[yoko][tate]=' ';
		man[yoko][tate]=-1;
		if((yoko-1!=myoko || tate!=mtate) && yoko-1>=0 && man[yoko-1][tate]!=-1){
			huku(yoko-1,tate,yoko,tate);
		}
		if((yoko+1!=myoko || tate!=mtate) && yoko+1<NUM && man[yoko+1][tate]!=-1){
			huku(yoko+1,tate,yoko,tate);
		}
		if((yoko!=myoko || tate-1!=mtate) && tate-1>=0 && man[yoko][tate-1]!=-1){
			huku(yoko,tate-1,yoko,tate);
		}
		if((yoko!=myoko || tate+1!=mtate) && tate+1<NUM && man[yoko][tate+1]!=-1){
			huku(yoko,tate+1,yoko,tate);
		}
	}else{
		switch(data){
			case -1:
				break;
			case 1:
				map[yoko][tate]='1';
				break;
			case 2:
				map[yoko][tate]='2';
				break;
			case 3:
				map[yoko][tate]='3';
				break;
			case 4:
				map[yoko][tate]='4';
				break;
			case 5:
				map[yoko][tate]='5';
				break;
			case 6:
				map[yoko][tate]='6';
				break;
			case 7:
				map[yoko][tate]='7';
				break;
			case 8:
				map[yoko][tate]='8';
				break;
			case 9:
				break;
		}
	}
	
	return;
}