#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>

#pragma pack(1)

using namespace std;

//�������ؽṹ��,˳�������̺�
struct RGB24BIT
{	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}**rgb, **rgbout;

struct RGB24BIT1
{	
	double blue;
	double green;
	double red;
}**rgbh, **rgbv,**rgbl;
	
int main()
{	
	printf("��ͼ���񻯴���ķ�����ѡ��Sobel��������1��\n");
	printf("��ͼ���񻯴���ķ�����ѡ��Laplace��������2��\n");
	int type;
	scanf("%d",&type);
	
	//Sobel
	if(type==1)
	{
		FILE *pFin;
		pFin = fopen("Gray.bmp","rb");	
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
		
		rgbv = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		rgbh = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		rgbl = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		//������̬��ά����
		for (int i = 0 ; i < height ; i ++)
		{
			rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			rgbout[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			
			rgbv[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
			rgbh[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
			rgbl[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
		}
		
		//��ȡͼ��
		for (int i = 0 ; i < height ; i++) 
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
			
		//Sobel���Ӵ���ͼ�� 
		double T;
		printf("��������ֵTΪ��\n");
		scanf("%lf",&T);
		
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				//ˮƽģ�� 
				rgbh[i][j].blue=(-rgb[i-1][j-1].blue+rgb[i-1][j+1].blue-rgb[i][j-1].blue*2+
			rgb[i][j+1].blue*2-rgb[i+1][j-1].blue+rgb[i+1][j+1].blue) /4;
				rgbh[i][j].green=(-rgb[i-1][j-1].green+rgb[i-1][j+1].green-rgb[i][j-1].green*2+
			rgb[i][j+1].green*2-rgb[i+1][j-1].green+rgb[i+1][j+1].green) /4;
				rgbh[i][j].red=(-rgb[i-1][j-1].red+rgb[i-1][j+1].red-rgb[i][j-1].red*2+
			rgb[i][j+1].red*2-rgb[i+1][j-1].red+rgb[i+1][j+1].red) /4;
				//��ֱģ�� 
				rgbv[i][j].blue=(-rgb[i-1][j-1].blue-rgb[i-1][j].blue*2-rgb[i-1][j+1].blue+
			rgb[i+1][j-1].blue+rgb[i+1][j].blue*2+rgb[i+1][j+1].blue) /4;
				rgbv[i][j].green=(-rgb[i-1][j-1].green-rgb[i-1][j].green*2-rgb[i-1][j+1].green+
			rgb[i+1][j-1].green+rgb[i+1][j].green*2+rgb[i+1][j+1].green) /4;
				rgbv[i][j].red=(-rgb[i-1][j-1].red-rgb[i-1][j].red*2-rgb[i-1][j+1].red+
			rgb[i+1][j-1].red+rgb[i+1][j].red*2+rgb[i+1][j+1].red) /4;
			
				//���ݶȷ��� 
				rgbout[i][j].blue=pow(rgbh[i][j].blue*rgbh[i][j].blue+rgbv[i][j].blue*rgbv[i][j].blue,0.5); 
				rgbout[i][j].green=pow(rgbh[i][j].green*rgbh[i][j].green+rgbv[i][j].green*rgbv[i][j].green,0.5); 
				rgbout[i][j].red=pow(rgbh[i][j].red*rgbh[i][j].red+rgbv[i][j].red*rgbv[i][j].red,0.5); 
	
				//�ݶ�ͼ���ֵ�� 
				if(rgbout[i][j].blue+rgbout[i][j].green+rgbout[i][j].red>T)
				{
					rgbout[i][j].blue=255;
					rgbout[i][j].green=255;
					rgbout[i][j].red=255;
				}
				else
				{
					rgbout[i][j].blue=0;
					rgbout[i][j].green=0;
					rgbout[i][j].red=0;
				}
			}
		}
		
		
		//��������ص�ֵ���ҵ�һ�����ʵ���ֵ 
		/*FILE *pout;
		pout = fopen("�����ص�ֵ.txt","wb");	
		if(pout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		} 
		for(int i = 0;i < height ;i++)
		{
			for(int j = 0;j < width ;j++)
			{
				fprintf(pout,"%d\t",rgbout[i][j].blue);
				fprintf(pout,"%d\t",rgbout[i][j].green);
				fprintf(pout,"%d\t\n",rgbout[i][j].red);
			}
		} */
		
		
		//������Sobel���ļ� 
	    FILE *pFout = fopen("Sobel.bmp","wb");
	    if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
	
	//Laplace
	if(type==2)
	{	
		FILE *pFin;
		pFin = fopen("Gray.bmp","rb");	
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
		
		rgbv = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		rgbh = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		rgbl = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
		
		//������̬��ά����
		for (int i = 0 ; i < height ; i ++)
		{
			rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			rgbout[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			
			rgbv[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
			rgbh[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
			rgbl[i] = (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
		}
		
		//��ȡͼ��
		for (int i = 0 ; i < height ; i++) 
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
		
		printf("ѡ��Laplace��������1\n");
		printf("ѡ��Laplace+ԭͼ��������2\n");
		int temp;
		scanf("%d",&temp);
		
		if(temp==1) 
		{
			//������˹����
			for(int i=1;i<ih.biHeight-1;i++)
			{
				for(int j=1;j<ih.biWidth-1;j++)
				{
					rgbl[i][j].blue=(-rgb[i-1][j].blue-rgb[i][j-1].blue-rgb[i][j+1].blue-rgb[i+1][j].blue+rgb[i][j].blue*4);
					rgbl[i][j].green=(-rgb[i-1][j].green-rgb[i][j-1].green-rgb[i][j+1].green-rgb[i+1][j].green+rgb[i][j].green*4);
					rgbl[i][j].red=(-rgb[i-1][j].red-rgb[i][j-1].red-rgb[i][j+1].red-rgb[i+1][j].red+rgb[i][j].red*4);
				
					rgbout[i][j].blue+=rgbl[i][j].blue;
					rgbout[i][j].green+=rgbl[i][j].green;
					rgbout[i][j].red+=rgbl[i][j].red;
				}
			}
			
			//������Laplace���ļ� 
		    FILE *pFout = fopen("Laplace.bmp","wb");
		    if(pFout==NULL)
			{
				printf("�ļ���ʧ�ܣ�");
				return 0;
			}
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < height; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
		
		
		if(temp==2)
		{
			//������˹����
			for(int i=1;i<ih.biHeight-1;i++)
			{
				for(int j=1;j<ih.biWidth-1;j++)
				{
					rgbl[i][j].blue=(-rgb[i-1][j].blue-rgb[i][j-1].blue-rgb[i][j+1].blue-rgb[i+1][j].blue+rgb[i][j].blue*4);
					rgbl[i][j].green=(-rgb[i-1][j].green-rgb[i][j-1].green-rgb[i][j+1].green-rgb[i+1][j].green+rgb[i][j].green*4);
					rgbl[i][j].red=(-rgb[i-1][j].red-rgb[i][j-1].red-rgb[i][j+1].red-rgb[i+1][j].red+rgb[i][j].red*4);
				
					rgbout[i][j].blue=rgb[i][j].blue;
					rgbout[i][j].green=rgb[i][j].green;
					rgbout[i][j].red=rgb[i][j].red;
				
					rgbout[i][j].blue+=rgbl[i][j].blue;
					rgbout[i][j].green+=rgbl[i][j].green;
					rgbout[i][j].red+=rgbl[i][j].red;
				}
			}
			
			//������Laplace+ԭͼ���ļ� 
		    FILE *pFout = fopen("Laplace+ԭͼ.bmp","wb");
		    if(pFout==NULL)
			{
				printf("�ļ���ʧ�ܣ�");
				return 0;
			}
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < height; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
			
	return 0;	
	}
	
}
