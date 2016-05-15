#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<windows.h>
#define M 51
#define LT(a,b) ((a)>(b))


void Read(int Heap[]);//从文件中读取待排数字
void HeapSort(int Heap[]);//堆排序
void HeapAdjust(int Heap[],int s,int n);//一次筛选
void Save(int Heap[]);//结果保存在文件中
void RandNum(void);//产生随机数进行排序

int count;//用于记录比较次数的全局变量

int main()
{
	int Heap[M];
	int i;
	
	RandNum();
	Read(Heap);
	HeapSort(Heap);

	printf("排序的结果:\n");
	for(i=1;i<M;i++)
	{
		printf("%3d ",Heap[i]);
		if(i%10==0)printf("\n");
	}
	printf("\n关键字比较次数：%d\n",count);
	Save(Heap);
    return 0;
}


void Read(int Heap[])
{
	FILE *fp;
	int i;

    printf("正在从文件中读取数据，请稍后。。。");
    Sleep(2000);
	fp=fopen("RandNum.txt","r");
	if(fp==NULL||fgetc(fp)==EOF)
	{
		printf("读取文件失败，请确认后重新打开程序!\n");
		exit(0);
	}
    rewind(fp);
	printf("\n排序之前的数据:\n");
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

    printf("正在进行堆排序，请稍后。。。\n");
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
    fprintf(fp,"比较次数：%d\n",count);
    for(i=1;i<M;i++)
    {
        fprintf(fp,"%3d ",Heap[i]);
        if(i%10==0)fprintf(fp,"\n");
    }
    printf("已成功写入文件result.txt中！\n");

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