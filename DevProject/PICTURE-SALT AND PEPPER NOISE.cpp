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
}**rgb, **rgbout;
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
	
	/////��ӽ�������
	double SNR;
	//���������
	printf("���������SNR��SNR�ķ�Χ��0-1������\n");
	scanf("%lf",&SNR);
	srand((unsigned)time(NULL));
	 
	unsigned char temp;
	
	//������������������Ϊ height*width*(1-SNR)
	for(int i=0;i<height*sqrt(1-SNR);i++)
	{
		for(int j=0;j<width*sqrt(1-SNR);j++)
		{
			temp=(rand()%2)*255;//����Ϊ0��tempΪ0������Ϊ1��tempΪ255�� 
			//temp��ֵΪ0Ϊ��������temp��ֵΪ255Ϊ������
			int RandomH=rand()%height;//���������� 
			int RandomW=rand()%width;//����������  
			rgb[RandomH][RandomW].blue=temp;
			rgb[RandomH][RandomW].green=temp;
			rgb[RandomH][RandomW].red=temp;
		}
	} 
	
	//�����ӽ����������ļ� 
    FILE *pFout = fopen("Salt AND Pepper Noise.bmp","wb");
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
