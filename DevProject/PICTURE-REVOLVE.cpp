#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>

#define pi 3.1415926

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
	
	double degree;
	printf("������ת�ĽǶ�Ϊ�� ����תΪ��ʱ����ת��\n");
	scanf("%lf",&degree);
	degree=degree*pi/180;//�Ƕ�ת��Ϊ��Ӧ���� 
	
	//ͼ�����ĵ�λ��
	int x0=width/2;
	int y0=height/2;
	
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
	//�����ɫͼ�� 
	for (int i = 0 ; i < height; i++)	
	{
		for(int j=0;j<width;j++)
		{
			rgbout[j][i].red=128;
			rgbout[j][i].blue=128;
			rgbout[j][i].green=128;
		}
	}
	
	//��ת
	int x;
	int y; 
	int x1;
	int y1;
	
	int temp;
	printf("������Ҫ����ת����ʽ��\n");
	printf("ѡ��1������ת��ԭͼ��Ŀ��\n"); 
	printf("ѡ��2������ת��Ŀ����ԭͼ\n");
	printf("ѡ��3��˫���Բ�ֵ����ת\n");
	scanf("%d",&temp);
	
	//����ת
	//���겻�ܺ���Ŀ�����ص�������Ч����㣬������ȡ�������л���©���ٵ�, �ͻ���ɿյ�״�� 
	if(temp==1)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j<width;j++)
			{
				//ԭͼ��Ŀ��
				x=j-x0;//����
				y=i-y0;//���� 
				x1=(int)(cos(degree)*x-sin(degree)*y)+x0;//���� 
				y1=(int)(cos(degree)*y+sin(degree)*x)+y0;//���� 
				//��ȡֵ
				if(x1>=0 && x1<width && y1>=0 && y1<height) //����������� 
				{
					rgbout[y1][x1].blue=rgb[i][j].blue;
					rgbout[y1][x1].green=rgb[i][j].green;
					rgbout[y1][x1].red=rgb[i][j].red;
				}
			}
		} 
		FILE *pFout = fopen("xuanzhuan1.bmp","wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
		}
		printf("���ͼƬ�ɹ�!"); 
		//�ͷ�ָ����ڴ�ռ� 
		for (int i = 0 ; i<height ;i++)
		{
			free(rgb[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
	}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////	
	//����ת��Ŀ����ԭͼ
	//��ԭͼ�����ص���ֵ��������ת��ĸ���λ�õ����ص�.
	if(temp==2)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j<width;j++)
			{
				//Ŀ����ԭͼ
				x=j-x0;//����
				y=i-y0;//���� 
				x1=(int)(cos(degree)*x+sin(degree)*y)+x0;//���� 
				y1=(int)(cos(degree)*y-sin(degree)*x)+y0;//���� 
				//��ȡֵ
				if(x1>=0 && x1<width && y1>=0 && y1<height) //����������� 
				{
					rgbout[i][j].blue=rgb[y1][x1].blue;
					rgbout[i][j].green=rgb[y1][x1].green;
					rgbout[i][j].red=rgb[y1][x1].red;
				}
			}
		} 
		FILE *pFout = fopen("xuanzhuan2.bmp","wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
		}
		printf("���ͼƬ�ɹ�!"); 
		//�ͷ�ָ����ڴ�ռ� 
		for (int i = 0 ; i<height ;i++)
		{
			free(rgb[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
	}
	
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////	
	//˫���Բ�ֵ����ת
	if(temp==3)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j < width;j++)
			{
				x=j-x0;//����
				y=i-y0;//���� 
				
				double xx;
				double yy;
				
				xx=(double)(cos(degree)*x+sin(degree)*y)+x0;//���� 
				yy=(double)(cos(degree)*y-sin(degree)*x)+y0;//���� 
				
				int xi;
				int yi;
				
				xi=(int)xx;//ȡ�� 
				yi=(int)yy;//ȡ�� 
				
				int xxx;
				int yyy;
				
				xxx=xi+1;
				yyy=yi+1; 
				
				if(xi<0 || xi>width-1 || yi<0 || yi>height-1)
				{
					continue;
				}
				if(xi==width-1)
				{
					xxx=xi;
				}
				if(yi==height-1)
				{
					yyy=yi;
				}
				
				double xs=xx-xi;	
				double ys=yy-yi; 
				
				//˫���Բ�ֵ
				rgbout[i][j].blue=(unsigned char)(rgb[yi][xi].blue*(1-xs)*(1-ys)+rgb[yyy][xi].blue*(1-xs)*ys+rgb[yi][xxx].blue*xs*(1-ys)+rgb[yyy][xxx].blue*xs*ys);
				rgbout[i][j].green=(unsigned char)(rgb[yi][xi].green*(1-xs)*(1-ys)+rgb[yyy][xi].green*(1-xs)*ys+rgb[yi][xxx].green*xs*(1-ys)+rgb[yyy][xxx].green*xs*ys);
				rgbout[i][j].red=(unsigned char)(rgb[yi][xi].red*(1-xs)*(1-ys)+rgb[yyy][xi].red*(1-xs)*ys+rgb[yi][xxx].red*xs*(1-ys)+rgb[yyy][xxx].red*xs*ys);
				
				
			}
		} 
		FILE *pFout = fopen("xuanzhuan3.bmp","wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
		}
		printf("���ͼƬ�ɹ�!"); 
		//�ͷ�ָ����ڴ�ռ� 
		for (int i = 0 ; i<height ;i++)
		{
			free(rgb[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		
		return 0;
	}	

	
	return 0;
	
	
	
}
