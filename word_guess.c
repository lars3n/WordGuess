#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//使用一个结构体储存要记录的玩家信息 
struct stRecords
{
	int m_rank;
	char m_name[20];
	int m_score;
};

//生成record.txt文件 
int makeRecordFile()
{
	FILE *pFile;
	char a_chRank[10];
	int i;
	
	pFile=fopen("record.txt", "w+");
	fputs("排名", pFile);
	fputs("\t", pFile);
	fputs("姓名", pFile);
	fputs("\t", pFile);
	fputs("成绩", pFile);
	fputs("\n", pFile);
	for(i=0;i<5;i++) 
	{
		itoa(i+1, a_chRank, 10);
		fputs(a_chRank, pFile);
		fputs("\t", pFile);
		fputs("小明", pFile);
		fputs("\t", pFile);
		fputs("0", pFile);
		fputs("\n", pFile);
	}
	fclose(pFile);
	return(0);
}
//生成wordlist.txt文件 
int makeWordFile()
{
	FILE *pFile;
	int i;
	char aa_chWordList[200][50]={"account","act","addition","adjustment","advertisement","agreement","air","amount","amusement","animal","answer","apparatus","approval","argument","art","attack","attempt","attention","attraction","authority","back","balance","base","behavior","belief","birth","bit","bite","blood","blow","body","brass","bread","breath","brother","building","burn","burst","business","butter","canvas","care","cause","chalk","chance","change","cloth","coal","color","comfort","committee","company","comparison","competition","condition","connection","control","cook","copper","copy","cork","copy","cough","country","cover","crack","credit","crime","crush","cry","current","curve","damage","danger","daughter","day","death","debt","decision","degree","design","desire","destruction","detail","development","digestion","direction","discovery","discussion","disease","disgust","distance","distribution","division","doubt","drink","driving","dust","earth","edge","education","effect","end","error","event","example","exchange","existence","expansion","experience","expert","fact","fall","family","father","fear","feeling","fiction","field","fight","fire","flame","flight","flower","fold","food","force","form","friend","front","fruit","glass","gold","government","grain","grass","grip","group","growth","guide","harbor","harmony","hate","hearing","heat","help","history","hole","hope","hour","humor","ice","idea","impulse","increase","industry","ink","insect","instrument","insurance","interest","invention","iron","jelly","join","journey","judge","jump","kick","kiss","knowledge","land","language","laugh","low","lead","learning","leather","letter","level","lift","light","limit","linen","liquid","list","look","loss","love","machine","man","manager","mark","market","mass","meal","measure","meat","meeting","memory"};
	pFile=fopen("wordlist.txt", "w+");
	for(i=0;i<200;i++)
	{
		fputs(aa_chWordList[i], pFile);
		fputs("\n", pFile);
	}
	fclose(pFile);
	return(0);
}
//输入分数；与前五名成绩作对比 
int record(int myscore)
{
	FILE *pFile;
	char buff[255];
	char recordl[6][50];
	int i=0, j;
	
	pFile=fopen("record.txt", "r");
	if(pFile == NULL)
	{
		printf("[!]文件不存在，正在创建...\n");
		makeRecordFile();
		pFile=fopen("record.txt", "r");
	}
	while (!feof(pFile))
	{
		fgets(buff, 255, pFile);
		{
			strcpy(recordl[i], buff);
			i++;
			//printf("%s", buff);
		}
	}
	fclose(pFile);

	////////////////////////////////////////////////////////////
	char *p_chOneString;
	char cOneRecord[3][50]; //将字符串分割成数组; 
	int iRank;
	char *szName;
	int score;
	i=0;j=0;
	struct stRecords stRecords[5];
	
	for(i=1;i<6;i++)
	{
		j=0;
		p_chOneString=strtok(recordl[i], "\t");
		while(p_chOneString!=NULL)
		{
			strcpy(cOneRecord[j], p_chOneString) ;
			j++;
			p_chOneString=strtok(NULL, "\t");
		}
		
		iRank=atoi(cOneRecord[0]);
		szName=cOneRecord[1];
		score=atoi(cOneRecord[2]);
		
		stRecords[i-1].m_rank=iRank;
		strcpy(stRecords[i-1].m_name, szName);
		stRecords[i-1].m_score=score;
	}

	char yrname[100];
	int yrrank;

	for(i=0;i<5;i++)
	{
		if(myscore>=stRecords[i].m_score)
		{
			yrrank=i+1;
			printf("[!]恭喜你获得了第%d名\n", yrrank);
			//判断玩家是否有输入数据
			//int c;
			//while((c = getchar()) != '\n' && c != EOF);
			
			do
			{
				printf("[?]请输入你的名字:");
				fflush(stdin);

			}while(*(gets(yrname)) == NULL);
			printf("[!]你的名字是:%s;已成功保存\n", yrname);
			
			if(yrrank<5)			 //如果当前排名在前五名，则将当前排名下面的记录全部往后挪一位，第五名会被覆盖 
			{
				for(i=0;i<5-yrrank;i++)			 
				{
					stRecords[4-i]=stRecords[3-i];
				}
				stRecords[yrrank-1].m_rank=yrrank;
				strcpy(stRecords[yrrank-1].m_name, yrname);
				stRecords[yrrank-1].m_score=myscore;			
				break;
			}			
			stRecords[i].m_rank=yrrank;
			strcpy(stRecords[i].m_name, yrname);
			stRecords[i].m_score=myscore;			
			break;
		}
	}
	//接下来开始写入记录 
	char rankw[10];
	char scorew[10];

	pFile=fopen("record.txt", "w+");
	fputs(recordl[0], pFile);	//写入列名
	for(i=0;i<5;i++) 
	{
		itoa(i+1, rankw, 10);
		itoa(stRecords[i].m_score, scorew, 10);
		fputs(rankw, pFile);
		fputs("\t", pFile);
		fputs(stRecords[i].m_name, pFile);
		fputs("\t", pFile);
		fputs(scorew, pFile);
		fputs("\n", pFile);
	}
	fclose(pFile);	
	return(0);
}
//计算字符在字符串中的个数 
int count(char szWord[], char cChar)
{
	int iLenWord=strlen(szWord);
	int i;
	int iIndexCount=0;
	for(i=0;i<iLenWord;i++)
	{
		if(szWord[i]==cChar)
		{
			iIndexCount++;
		}
	}
	if(iIndexCount>0)
	{
		return(iIndexCount);
	}
	else
	{
		return(-1);
	}
}
//查找字符在字符串中的索引位置 
int *index(char szWord[], char cChar)
{
	int iLenth=strlen(szWord);
	int i,j;
	int a_iIndexArr[iLenth];
	int *p_iIndex;
	for(i=0,j=0;i<iLenth;i++)
	{
		if(szWord[i]==cChar)
		{
			a_iIndexArr[j]=i;		//将索引位置添加到indexl数组 
			j++;
		}
	}
	p_iIndex=a_iIndexArr;
	return(p_iIndex);
}

//用来打印hidden word 
void printHword(char a_chHiddenWord[], int iLength)
{
	int i;
	for(i=0;i<iLength;i++)	
	{
		printf("%c ", a_chHiddenWord[i]);
		fflush(stdout);
	}
	printf("\n");
}
//猜词，返回正确和错误的次数 
void *guessWord(char word[])
{
	int len=strlen(word);
	char ch='-';
	char *ret, ret2;
	char c;
	int i, pos;
	int wrong=0;
	int right=0;
	int *p;

	int *indexl;
	int indCount;
	char hword[len];	//初始化hword 
	for(i=0;i<len;i++)	
	{
		hword[i]='-';
	}
	
	while(1)
	{
		ret=strchr(hword, ch);	//如果'-'仍存在于hword 
		if(ret!=NULL)
		{
			printHword(hword, len-1);
			fflush(stdin);
			c=getchar();
			if(c=='0')	//如果玩家在猜字过程中输入0则返回exit字符串 
			{
				p="exit";
				return(p);
			}
			indCount=count(word, c);
			if(indCount!=-1)	//假如该字符被猜到 
			{
				indexl = index(word, c);
				int new[indCount];
				for(i=0;i<indCount;i++)
				{
					new[i]=indexl[i];
				}
				for(i=0;i<indCount;i++)
				{
					hword[new[i]]=word[new[i]];
				}
				right++;
				continue;			
			}
			else
			{
				wrong++;
				continue;
			}			
		}
		else
		{
			printHword(hword, len);
			printf("[Result]答对了%d次，答错了%d次!\n", right-1, wrong);
			break;
		}
	}
	int sum[2]={right, wrong};		 
	p=sum;
	return(p);
}
//根据要猜的次数生成随机数 
int *randnum(int n)
{
	int i;
	int a_iArr[n];
	srand( (unsigned)time( NULL ) );
	for(i=0;i<n;i++) 
	{		
		a_iArr[i]=rand()%200+1;		//200是指生成随机数的范围 
	}
	int *pi=a_iArr;
	return(pi);
}
//根据要猜的次数获取单词数组 
char **getWord(int guess_ti)
{
	FILE *fp;
	char buff[255];
	char wordlist[200][20];
	int i=0, j;	
	
	//分配动态内存，使用一个二维数组指针返回单词列表 
	char **myword;
	myword=(int**)malloc(guess_ti*sizeof(int*));
	for(i=0;i<guess_ti;++i)
	{
		myword[i]=(int*)malloc(guess_ti*sizeof(int));
	}
	
	fp = fopen("wordlist.txt", "r");
	if(fp == NULL)
	{
		printf("[!]文件不存在，正在创建...\n");
		makeWordFile();
		fp=fopen("wordlist.txt", "r");
	}
	while (!feof(fp))
	{
		fgets(buff, 255, fp);
		{
			strcpy(wordlist[i], buff);
			i++;
		}
	}
	fclose(fp);
	//获取随机数 
	int *randArr;
	randArr=randnum(guess_ti);
	//按照生成的随机数从单词文件取出单词 
	for(i=0;i<guess_ti;i++)
	{
		strcpy(myword[i], wordlist[randArr[i]-1]);
	}
	/*
	for(i=0;i<guess_ti;i++)
	{
		printf("%s\n", myword[i]);
	}
	*/
	return(myword);
}
//计算得分 
int grade(int timeusage, int wrong)
{
	int score;
	score=100-timeusage-wrong;
	return(score);
}
//查询排行榜 
int query()
{
	FILE *fp;
	char buff[255];
	int i=0;
	
	fp=fopen("record.txt", "r");
	if(fp == NULL)
	{
		printf("[!]文件不存在，正在创建...\n");
		makeRecordFile();
		fp=fopen("record.txt", "r");
	}
	while (!feof(fp))
	{
		fgets(buff, 255, fp);
		{
			printf("%s\n", buff);
			i++;
		}
	}
	fclose(fp);
}

int main()
{
	char cOpt[10];	//玩家操作选项 
	char guess_t[10];	//玩家选择要猜的多少个单词 
	int guess_ti;	//同上，不过这个是整形 
	int i;
	char **myword;	//接收要猜的单词列表 
	int *presult;	//接收猜词的结果 
	time_t start_t, end_t;	//统计时间用的变量 
	int timeusage;			//玩家用时 
	int score;				//玩家猜一个单词的得分 
	int scores;				//玩家总得分 
	int avscore;			//玩家的平均得分 
	char *ptr;
	char wrongc[10];		//玩家可以猜错的次数		
	int wrongt=20;			//同上，但是是整形，默认为20 
	
	while(1)
	{	
		printf("=================猜=========单=========词===================\n");
		printf("----------------------by--------lars3n----------------------\n")
		printf("-------------------------- 规则-----------------------------\n");
		printf("[One]每个字猜字时间超过60s则得分为0\n");
		printf("[Two]每个字猜猜错一定次数则得分为0，默认为20，可自行设置\n");
		printf("[Thr]每次猜词的数量不得大于10\n");
		printf("[For]在猜字过程可以输入0来退出猜词\n");
		printf("------------------------------------------------------------\n");
		printf("[?]请选择: 1,猜单词   2,查询排行榜    3,设置:\n");
		gets(cOpt);
		if(strcmp(cOpt, "1")==0)
		{
			printf("[?]请问要猜几个词?:\n");
			fflush(stdin);
			while(*(ptr = gets(guess_t)) == NULL)	//用循环判断玩家输入是否为空 
			{
				printf("[?]请问要猜几个词?:\n");
			}
			
			guess_ti=atoi(guess_t);			//将玩家输入的字符串转成整形 
			if(guess_ti>10)		
			{
				printf("[Sorry]对不起，单词数量不能超过10\n");
				continue;
			}
			
			myword=getWord(guess_ti);
			
			scores=0;
			for(i=0;i<guess_ti;i++)
			{	
				printf("============第%d 个单词==========\n", i+1);
				time(&start_t);			
				presult=guessWord(myword[i]);
				
				if(strcmp(presult, "exit")==0)
				{
					break;
				}
				time(&end_t);
				timeusage=difftime(end_t, start_t);
				if((timeusage>60)||(presult[1]>wrongt))
				{
					score=0;
				}
				else
				{
					score=grade(timeusage, presult[1]);			//计算玩家得分 
				}
				printf("[!]使用时间%d 秒\n", timeusage);
				printf("[!]此次成绩:%d\n", score);
				scores=scores+score;
				free(myword[i]);    		//释放内存 
			}
			avscore=scores/guess_ti;
			printf("[!]平均分数%d\n", avscore);
			record(avscore);
		}
		else if(strcmp(cOpt, "2")==0)
		{
			query();
		}
		else if(strcmp(cOpt, "3")==0)
		{
			printf("[?]请输入允许猜错的次数，当前为%d :\n", wrongt);
			fflush(stdin);
			gets(wrongc);
			wrongt=atoi(wrongc);
			if((wrongt<0)||(wrongt>30))			//设置失败后，将变量调回默认值 
			{
				printf("设置失败,不得小于0或者大于30\n");
				wrongt=20;
			}
			printf("设置成功\n");
		}
		else
		{
			printf("[!]非法选项\n");
		}
		
	}
	
	return(0);
}
