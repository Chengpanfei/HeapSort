#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define M 2
#define LT(a,b) ((a)>(b))


void Read(float List[]);//���ļ��ж�ȡ��������
void HeapSort(float List[]);//������
void ListAdjust(float List[],int s,int n);//һ��ɸѡ
void Save(float List[]);//����������ļ���
void RandNum(void);//�����������������
int Partition(float List[],int low,int high);
void QuickSort(float List[],int low,int high);

int count;//���ڼ�¼�Ƚϴ�����ȫ�ֱ���

int main()
{
	float List[M];
	int i;
	char choice;
	
	//RandNum();
	Read(List);
	
	printf("��ѡ�����򷽷���\n");
	printf("1:������\t2:��������\n");
	
	choice=getchar();
	do{
		if(choice=='1')
		{
			HeapSort(List);
			break;
		}
		else if(choice=='2')
		{
			QuickSort(List,1,M-1);
			break;
		}
		else 
		{
			fflush(stdin);
			printf("���������룺\n");
			choice=getchar();
		}
	}while(1);


	printf("����Ľ��Ϊ:\n");
	for(i=1;i<M;i++)
	{
		printf("%6.2f ",List[i]);
		if(i%10==0)printf("\n");
	}
	printf("\n�ؼ��ֱȽϴ�����%d\n",count);
	Save(List);
    return 0;
}


void Read(float List[])
{
	FILE *fp;
	int i;

    printf("���ڴ��ļ��ж�ȡ���ݣ����Ժ󡣡���");
    Sleep(2000);
	fp=fopen("RandNum.txt","r");
	if(fp==NULL||fgetc(fp)==EOF)
	{
		printf("��ȡ�ļ�ʧ�ܣ���ȷ�Ϻ����´򿪳���!\n");
		exit(0);
	}
    rewind(fp);
	printf("\n����֮ǰ������:\n");
	for(i=1;i<M;i++)
	{
		fscanf(fp,"%f ",List+i);
		printf("%6.2f ",List[i]);
		if(i%10==0)printf("\n");
	}
    printf("\n");
}

void HeapSort(float List[])
{
	int i;

    printf("���ڽ��ж��������Ժ󡣡���\n");
    Sleep(2000);
	for(i=M/2;i>0;i--)
	{
		ListAdjust(List,i,M-1);
	}
	for(i=M-1;i>1;i--)
	{
		List[0]=List[i];
		List[i]=List[1];
		List[1]=List[0];
		ListAdjust(List,1,i-1);
	}
}


void ListAdjust(float List[],int s,int n)
{
	int i;

	List[0]=List[s];
	for(i=2*s;i<=n;i*=2)
	{
		count+=2;
		if(i<n&&LT(List[i],List[i+1]))i++;
		if(!LT(List[0],List[i]))break;
		List[s]=List[i];
		s=i;
	}
	List[s]=List[0];
}

void Save(float List[])
{
    FILE *fp;
    int i;

    fp=fopen("result.txt","w");
    fprintf(fp,"�Ƚϴ�����%d\n",count);
    for(i=1;i<M;i++)
    {
        fprintf(fp,"%f ",List[i]);
        if(i%10==0)fprintf(fp,"\n");
    }
    printf("�ѳɹ�д���ļ�result.txt�У�\n");

}




int Partition(float List[],int low,int high)
{
	List[0]=List[low];
	while(low<high)
	{
		count+=2;
		while(low<high&&List[0]<=List[high])
		{
			high--;
			count++;
		}
		List[low]=List[high];
		while(low<high&&List[0]>=List[low])
		{
			low++;
			count++;
		}
		List[high]=List[low];
	}
	List[low]=List[0];
	return low;
}

void QuickSort(float List[],int low,int high)
{
	int pivotloc;
	if(low<high)
	{
		pivotloc=Partition(List,low,high);
		QuickSort(List,low,pivotloc-1);
		QuickSort(List,pivotloc+1,high);
	}
}


void RandNum(void)
{
	FILE *fp;
	int i;
	float t;
	
	fp=fopen("RandNum.txt","w");
	srand(time(NULL));
	for(i=0;i<M-1;i++)
	{
		t=(float)(rand()%10000+1)/100;
		if((rand()%2)>0)t=-t;
		fprintf(fp,"%f ",t);
	}
	fclose(fp);
}