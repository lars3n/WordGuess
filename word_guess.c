#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

//ʹ��һ���ṹ�崢��Ҫ��¼�������Ϣ 
struct stRecords
{
	int m_rank;
	char m_name[20];
	int m_score;
};

//����record.txt�ļ� 
int makeRecordFile()
{
	FILE *pFile;
	char a_chRank[10];
	int i;
	
	pFile=fopen("record.txt", "w+");
	fputs("����", pFile);
	fputs("\t", pFile);
	fputs("����", pFile);
	fputs("\t", pFile);
	fputs("�ɼ�", pFile);
	fputs("\n", pFile);
	for(i=0;i<5;i++) 
	{
		itoa(i+1, a_chRank, 10);
		fputs(a_chRank, pFile);
		fputs("\t", pFile);
		fputs("С��", pFile);
		fputs("\t", pFile);
		fputs("0", pFile);
		fputs("\n", pFile);
	}
	fclose(pFile);
	return(0);
}
//����wordlist.txt�ļ� 
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
//�����������ǰ�����ɼ����Ա� 
int record(int myscore)
{
	FILE *pFile;
	char buff[255];
	char recordl[6][50];
	int i=0, j;
	
	pFile=fopen("record.txt", "r");
	if(pFile == NULL)
	{
		printf("[!]�ļ������ڣ����ڴ���...\n");
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
	char cOneRecord[3][50]; //���ַ����ָ������; 
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
			printf("[!]��ϲ�����˵�%d��\n", yrrank);
			//�ж�����Ƿ�����������
			//int c;
			//while((c = getchar()) != '\n' && c != EOF);
			
			do
			{
				printf("[?]�������������:");
				fflush(stdin);

			}while(*(gets(yrname)) == NULL);
			printf("[!]���������:%s;�ѳɹ�����\n", yrname);
			
			if(yrrank<5)			 //�����ǰ������ǰ�������򽫵�ǰ��������ļ�¼ȫ������Ųһλ���������ᱻ���� 
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
	//��������ʼд���¼ 
	char rankw[10];
	char scorew[10];

	pFile=fopen("record.txt", "w+");
	fputs(recordl[0], pFile);	//д������
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
//�����ַ����ַ����еĸ��� 
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
//�����ַ����ַ����е�����λ�� 
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
			a_iIndexArr[j]=i;		//������λ����ӵ�indexl���� 
			j++;
		}
	}
	p_iIndex=a_iIndexArr;
	return(p_iIndex);
}

//������ӡhidden word 
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
//�´ʣ�������ȷ�ʹ���Ĵ��� 
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
	char hword[len];	//��ʼ��hword 
	for(i=0;i<len;i++)	
	{
		hword[i]='-';
	}
	
	while(1)
	{
		ret=strchr(hword, ch);	//���'-'�Դ�����hword 
		if(ret!=NULL)
		{
			printHword(hword, len-1);
			fflush(stdin);
			c=getchar();
			if(c=='0')	//�������ڲ��ֹ���������0�򷵻�exit�ַ��� 
			{
				p="exit";
				return(p);
			}
			indCount=count(word, c);
			if(indCount!=-1)	//������ַ����µ� 
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
			printf("[Result]�����%d�Σ������%d��!\n", right-1, wrong);
			break;
		}
	}
	int sum[2]={right, wrong};		 
	p=sum;
	return(p);
}
//����Ҫ�µĴ������������ 
int *randnum(int n)
{
	int i;
	int a_iArr[n];
	srand( (unsigned)time( NULL ) );
	for(i=0;i<n;i++) 
	{		
		a_iArr[i]=rand()%200+1;		//200��ָ����������ķ�Χ 
	}
	int *pi=a_iArr;
	return(pi);
}
//����Ҫ�µĴ�����ȡ�������� 
char **getWord(int guess_ti)
{
	FILE *fp;
	char buff[255];
	char wordlist[200][20];
	int i=0, j;	
	
	//���䶯̬�ڴ棬ʹ��һ����ά����ָ�뷵�ص����б� 
	char **myword;
	myword=(int**)malloc(guess_ti*sizeof(int*));
	for(i=0;i<guess_ti;++i)
	{
		myword[i]=(int*)malloc(guess_ti*sizeof(int));
	}
	
	fp = fopen("wordlist.txt", "r");
	if(fp == NULL)
	{
		printf("[!]�ļ������ڣ����ڴ���...\n");
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
	//��ȡ����� 
	int *randArr;
	randArr=randnum(guess_ti);
	//�������ɵ�������ӵ����ļ�ȡ������ 
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
//����÷� 
int grade(int timeusage, int wrong)
{
	int score;
	score=100-timeusage-wrong;
	return(score);
}
//��ѯ���а� 
int query()
{
	FILE *fp;
	char buff[255];
	int i=0;
	
	fp=fopen("record.txt", "r");
	if(fp == NULL)
	{
		printf("[!]�ļ������ڣ����ڴ���...\n");
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
	char cOpt[10];	//��Ҳ���ѡ�� 
	char guess_t[10];	//���ѡ��Ҫ�µĶ��ٸ����� 
	int guess_ti;	//ͬ�ϣ�������������� 
	int i;
	char **myword;	//����Ҫ�µĵ����б� 
	int *presult;	//���ղ´ʵĽ�� 
	time_t start_t, end_t;	//ͳ��ʱ���õı��� 
	int timeusage;			//�����ʱ 
	int score;				//��Ҳ�һ�����ʵĵ÷� 
	int scores;				//����ܵ÷� 
	int avscore;			//��ҵ�ƽ���÷� 
	char *ptr;
	char wrongc[10];		//��ҿ��Բ´�Ĵ���		
	int wrongt=20;			//ͬ�ϣ����������Σ�Ĭ��Ϊ20 
	
	while(1)
	{	
		printf("=================��=========��=========��===================\n");
		printf("----------------------by--------lars3n----------------------\n")
		printf("-------------------------- ����-----------------------------\n");
		printf("[One]ÿ���ֲ���ʱ�䳬��60s��÷�Ϊ0\n");
		printf("[Two]ÿ���ֲ²´�һ��������÷�Ϊ0��Ĭ��Ϊ20������������\n");
		printf("[Thr]ÿ�β´ʵ��������ô���10\n");
		printf("[For]�ڲ��ֹ��̿�������0���˳��´�\n");
		printf("------------------------------------------------------------\n");
		printf("[?]��ѡ��: 1,�µ���   2,��ѯ���а�    3,����:\n");
		gets(cOpt);
		if(strcmp(cOpt, "1")==0)
		{
			printf("[?]����Ҫ�¼�����?:\n");
			fflush(stdin);
			while(*(ptr = gets(guess_t)) == NULL)	//��ѭ���ж���������Ƿ�Ϊ�� 
			{
				printf("[?]����Ҫ�¼�����?:\n");
			}
			
			guess_ti=atoi(guess_t);			//�����������ַ���ת������ 
			if(guess_ti>10)		
			{
				printf("[Sorry]�Բ��𣬵����������ܳ���10\n");
				continue;
			}
			
			myword=getWord(guess_ti);
			
			scores=0;
			for(i=0;i<guess_ti;i++)
			{	
				printf("============��%d ������==========\n", i+1);
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
					score=grade(timeusage, presult[1]);			//������ҵ÷� 
				}
				printf("[!]ʹ��ʱ��%d ��\n", timeusage);
				printf("[!]�˴γɼ�:%d\n", score);
				scores=scores+score;
				free(myword[i]);    		//�ͷ��ڴ� 
			}
			avscore=scores/guess_ti;
			printf("[!]ƽ������%d\n", avscore);
			record(avscore);
		}
		else if(strcmp(cOpt, "2")==0)
		{
			query();
		}
		else if(strcmp(cOpt, "3")==0)
		{
			printf("[?]����������´�Ĵ�������ǰΪ%d :\n", wrongt);
			fflush(stdin);
			gets(wrongc);
			wrongt=atoi(wrongc);
			if((wrongt<0)||(wrongt>30))			//����ʧ�ܺ󣬽���������Ĭ��ֵ 
			{
				printf("����ʧ��,����С��0���ߴ���30\n");
				wrongt=20;
			}
			printf("���óɹ�\n");
		}
		else
		{
			printf("[!]�Ƿ�ѡ��\n");
		}
		
	}
	
	return(0);
}
