#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>

#pragma pack(1)

using namespace std;

struct RGB24BIT//�������ؽṹ��,˳�������̺�
{	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}**rgb,**rgbout;

//���������mu�Ǿ�ֵ��sigma�Ƿ���
//���X���Ӹ�˹�ֲ�N��mu,sigma)
//KΪ�Ŵ�ϵ����K��������Խ��
double GaussianNoise(double mu,double sigma,int k) 
{
	//������˹����
	static double V1,V2,S;
	static int phase=0;
	double U1,U2;
	double X;
	if(phase==0)
	{
		do
		{
			U1=(double)rand()/RAND_MAX;
			U2=(double)rand()/RAND_MAX;
			V1=2*U1-1;
			V2=2*U2-1;
			S=V1*V1+V2*V2;
		}while(S>=1||S==0);
		X=V1*sqrt(-2*log(S)/S);
	} 
	else
	{
		X=V2*sqrt(-2*log(S)/S);
	}
	phase=1-phase;
	return k*(mu+sigma*X); //���ظ�˹�ֲ��ĺ����� 
}


int main()
{
	FILE *pFin;
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	double mu;//��ֵ 
	double sigma;//����
	int k;//�Ŵ���
	
	printf("�������ֵΪmu��\n");
	scanf("%lf",&mu);
	printf("�����뷽��Ϊsigma��\n");
	scanf("%lf",&sigma);
	printf("������Ŵ���Ϊk��\n");
	scanf("%d",&k);
	
	for (int i = 0 ; i < height ; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//��˹��������
			double temp= GaussianNoise(mu,sigma,k);
			if(rgb[i][j].blue+temp>255)
			{
				rgb[i][j].blue=255;
				rgb[i][j].green=255;
				rgb[i][j].red=255;
			}
			else if(rgb[i][j].blue+temp<0)
			{
				rgb[i][j].blue=0;
				rgb[i][j].green=0;
				rgb[i][j].red=0;
			}
			else
			{
				rgb[i][j].blue += temp;
				rgb[i][j].green += temp;
				rgb[i][j].red += temp;
			}
		}
	} 
	 
	//�����Ӹ�˹�������ļ� 
    FILE *pFout = fopen("Gaussian Noise.bmp","wb");
    if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i], sizeof(RGB24BIT), width, pFout);
	}
	printf("���ͼƬ�ɹ�!!!\n");  
	printf("���г����Խ���!!!\n");
	
	//�ͷ�ָ����ڴ�ռ� 
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		free(rgbout[i]);
	}
	free(rgb);
	free(rgbout);
	fclose(pFin);
	fclose(pFout);
  
	return 0;
} 
