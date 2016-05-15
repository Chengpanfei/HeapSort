#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define M 51
#define LT(a,b) ((a)>(b))


void Read(int Heap[]);//���ļ��ж�ȡ��������
void HeapSort(int Heap[]);//������
void HeapAdjust(int Heap[],int s,int n);//һ��ɸѡ
void Save(int Heap[]);//����������ļ���
void RandNum(void);//�����������������

int count;//���ڼ�¼�Ƚϴ�����ȫ�ֱ���

int main()
{
	int Heap[M];
	int i;
	
	RandNum();
	Read(Heap);
	HeapSort(Heap);

	printf("����Ľ��:\n");
	for(i=1;i<M;i++)
	{
		printf("%3d ",Heap[i]);
		if(i%10==0)printf("\n");
	}
	printf("\n�ؼ��ֱȽϴ�����%d\n",count);
	Save(Heap);
    return 0;
}


void Read(int Heap[])
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
		fscanf(fp,"%d ",Heap+i);
		printf("%3d ",Heap[i]);
		if(i%10==0)printf("\n");
	}
    printf("\n");
    system("pause");
}

void HeapSort(int Heap[])
{
	int i;

    printf("���ڽ��ж��������Ժ󡣡���\n");
    Sleep(2000);
	for(i=M/2;i>0;i--)
	{
		HeapAdjust(Heap,i,M-1);
	}
	for(i=M-1;i>1;i--)
	{
		Heap[0]=Heap[i];
		Heap[i]=Heap[1];
		Heap[1]=Heap[0];
		HeapAdjust(Heap,1,i-1);
	}
}


void HeapAdjust(int Heap[],int s,int n)
{
	int i;

	Heap[0]=Heap[s];
	for(i=2*s;i<=n;i*=2)
	{
		count+=2;
		if(i<n&&LT(Heap[i],Heap[i+1]))i++;
		if(!LT(Heap[0],Heap[i]))break;
		Heap[s]=Heap[i];
		s=i;
	}
	Heap[s]=Heap[0];
}

void Save(int Heap[])
{
    FILE *fp;
    int i;

    fp=fopen("result.txt","w");
    fprintf(fp,"�Ƚϴ�����%d\n",count);
    for(i=1;i<M;i++)
    {
        fprintf(fp,"%3d ",Heap[i]);
        if(i%10==0)fprintf(fp,"\n");
    }
    printf("�ѳɹ�д���ļ�result.txt�У�\n");

}


void RandNum(void)
{
	FILE *fp;
	int t,i;
	
	fp=fopen("RandNum.txt","w");
	srand(time(NULL));
	for(i=0;i<M-1;i++)
	{
		t=rand()%100+1;
		fprintf(fp,"%d ",t);
	}
	fclose(fp);
}