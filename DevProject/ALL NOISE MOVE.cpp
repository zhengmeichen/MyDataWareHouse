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
	printf("ѡ���ø�˹�˲��Ը�˹����ͼ����д���������1��\n");
	printf("ѡ���ø�˹�˲��Խ�������ͼ����д���������2��\n");
	printf("ѡ������ֵ�˲��Ը�˹����ͼ����д���������3��\n");
	printf("ѡ������ֵ�˲��Խ�������ͼ����д���������4��\n");
	printf("ѡ���þ�ֵ�˲��Ը�˹����ͼ����д���������5��\n");
	printf("ѡ���þ�ֵ�˲��Խ�������ͼ����д���������6��\n");	
	int type;
	scanf("%d",&type);
	
	//�ø�˹�˲��Ը�˹����ͼ����д��� 
	if(type==1)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//��˹�˲����� 
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				rgbout[i][j].blue=(rgb[i-1][j-1].blue+rgb[i-1][j].blue*2+rgb[i-1][j+1].blue+rgb[i][j-1].blue*2+
			rgb[i][j].blue*4+rgb[i][j+1].blue*2+rgb[i+1][j-1].blue+rgb[i+1][j].blue*2+rgb[i+1][j+1].blue) /16;
				rgbout[i][j].green=(rgb[i-1][j-1].green+rgb[i-1][j].green*2+rgb[i-1][j+1].green+rgb[i][j-1].green*2+
			rgb[i][j].green*4+rgb[i][j+1].green*2+rgb[i+1][j-1].green+rgb[i+1][j].green*2+rgb[i+1][j+1].green) /16;
				rgbout[i][j].red=(rgb[i-1][j-1].red+rgb[i-1][j].red*2+rgb[i-1][j+1].red+rgb[i][j-1].red*2+
			rgb[i][j].red*4+rgb[i][j+1].red*2+rgb[i+1][j-1].red+rgb[i+1][j].red*2+rgb[i+1][j+1].red) /16;
			}
		}
		
		//�����Ӹ�˹�˲����ļ� 
	    FILE *pFout = fopen("��˹�˲������˹����.bmp","wb");
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
	
	//�ø�˹�˲��Խ�������ͼ����д��� 
	if(type==2)
	{
		FILE *pFin;
		pFin = fopen("Salt AND Pepper Noise.bmp","rb");	
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
		
		//��˹�˲� 
		for (int i = 1; i < height-1; i ++)
		{
			for (int j = 1; j < width-1; j ++)
			{
				rgbout[i][j].blue=(rgb[i-1][j-1].blue+rgb[i-1][j].blue*2+rgb[i-1][j+1].blue+rgb[i][j-1].blue*2+
			rgb[i][j].blue*4+rgb[i][j+1].blue*2+rgb[i+1][j-1].blue+rgb[i+1][j].blue*2+rgb[i+1][j+1].blue) /16;
				rgbout[i][j].green=(rgb[i-1][j-1].green+rgb[i-1][j].green*2+rgb[i-1][j+1].green+rgb[i][j-1].green*2+
			rgb[i][j].green*4+rgb[i][j+1].green*2+rgb[i+1][j-1].green+rgb[i+1][j].green*2+rgb[i+1][j+1].green) /16;
				rgbout[i][j].red=(rgb[i-1][j-1].red+rgb[i-1][j].red*2+rgb[i-1][j+1].red+rgb[i][j-1].red*2+
			rgb[i][j].red*4+rgb[i][j+1].red*2+rgb[i+1][j-1].red+rgb[i+1][j].red*2+rgb[i+1][j+1].red) /16;
			}
		}
		
		//�����Ӹ�˹�˲����ļ� 
	    FILE *pFout = fopen("��˹�˲�����������.bmp","wb");
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
	
	
	//��ֵ�˲��Ը�˹����ͼ����д���
	if(type==3)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//��ֵ�˲����� 
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				double R[9] = {0};
				double G[9] = {0};
				double B[9] = {0};
				int z = 0;
				for(int x = i - 1; x <= i + 1; x ++)
				{
					for(int y = j - 1; y <= j + 1; y ++)
					{
						R[z] = rgb[x][y].red;
						G[z] = rgb[x][y].green;
						B[z] = rgb[x][y].blue;
						z ++;
					}
				}
				double tempR = 0;
				double tempG = 0;
				double tempB = 0;
				for(int xx = 0; xx < 9; xx ++)
				{	
					for(int yy = 0; yy < 9; yy ++)
					{
						if (R[yy] > R[yy + 1])
						{
							tempR = R[yy];
							R[yy] = R[yy + 1];
							R[yy + 1] = tempR;
						}
						if (G[yy] > G[yy + 1])
						{
							tempG = G[yy];
							G[yy] = G[yy + 1];
							G[yy + 1] = tempG;
						}
						if (B[yy] > B[yy + 1])
						{
							tempB = B[yy];
							B[yy] = B[yy + 1];
							B[yy + 1] = tempB;
						}
					}
				}
				rgb[i][j].blue = B[4];
				rgb[i][j].green = G[4];
				rgb[i][j].red = R[4];
			}
		}
		
		//��������ֵ�˲����ļ� 
	    FILE *pFout = fopen("��ֵ�˲������˹����.bmp","wb");
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
	
	//��ֵ�˲��Խ�������ͼ����д��� 
	if(type==4)
	{
		FILE *pFin;
		pFin = fopen("Salt AND Pepper Noise.bmp","rb");	
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
		
		//��ֵ�˲����� 
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				double R[9] = {0};
				double G[9] = {0};
				double B[9] = {0};
				int z = 0;
				for(int x = i - 1; x <= i + 1; x ++)
				{
					for(int y = j - 1; y <= j + 1; y ++)
					{
						R[z] = rgb[x][y].red;
						G[z] = rgb[x][y].green;
						B[z] = rgb[x][y].blue;
						z ++;
					}
				}
				double tempR = 0;
				double tempG = 0;
				double tempB = 0;
				for(int xx = 0; xx < 9; xx ++)
				{	
					for(int yy = 0; yy < 9; yy ++)
					{
						if (R[yy] > R[yy + 1])
						{
							tempR = R[yy];
							R[yy] = R[yy + 1];
							R[yy + 1] = tempR;
						}
						if (G[yy] > G[yy + 1])
						{
							tempG = G[yy];
							G[yy] = G[yy + 1];
							G[yy + 1] = tempG;
						}
						if (B[yy] > B[yy + 1])
						{
							tempB = B[yy];
							B[yy] = B[yy + 1];
							B[yy + 1] = tempB;
						}
					}
				}
				rgb[i][j].blue = B[4];
				rgb[i][j].green = G[4];
				rgb[i][j].red = R[4];
			}
		}
		
		//��������ֵ�˲����ļ� 
	    FILE *pFout = fopen("��ֵ�˲�����������.bmp","wb");
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
	
	
	//��ֵ�˲��Ը�˹����ͼ����д��� 
	if(type==5)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//��ֵ�˲����� 
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				double R[9] = {0};
				double G[9] = {0};
				double B[9] = {0};
				int z = 0;
				for(int x = i - 1; x <= i + 1; x ++)
				{
					for(int y = j - 1; y <= j + 1; y ++)
					{
						R[z] = rgb[x][y].red;
						G[z] = rgb[x][y].green;
						B[z] = rgb[x][y].blue;
						z ++;
					}
				}
				double tempR = 0;
				double tempG = 0;
				double tempB = 0;
				for(int xx = 0; xx < 9; xx ++)
				{	
					tempR += R[xx];
					tempG += G[xx];
					tempB += B[xx];
				}
				rgb[i][j].blue = tempB / 9;
				rgb[i][j].green = tempG / 9;
				rgb[i][j].red = tempR / 9;
			}
		}
		//�����Ӿ�ֵ�˲����ļ� 
	    FILE *pFout = fopen("��ֵ�˲������˹����.bmp","wb");
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
	 
	//��ֵ�˲��Խ�������ͼ����д��� 
	if(type==6)
	{
		FILE *pFin;
		pFin = fopen("Salt AND Pepper Noise.bmp","rb");	
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
		
		//��ֵ�˲����� 
		for (int i = 1; i < height - 1; i ++)
		{
			for (int j = 1; j < width - 1; j ++)
			{
				double R[9] = {0};
				double G[9] = {0};
				double B[9] = {0};
				int z = 0;
				for(int x = i - 1; x <= i + 1; x ++)
				{
					for(int y = j - 1; y <= j + 1; y ++)
					{
						R[z] = rgb[x][y].red;
						G[z] = rgb[x][y].green;
						B[z] = rgb[x][y].blue;
						z ++;
					}
				}
				double tempR = 0;
				double tempG = 0;
				double tempB = 0;
				for(int xx = 0; xx < 9; xx ++)
				{	
					tempR += R[xx];
					tempG += G[xx];
					tempB += B[xx];
				}
				rgb[i][j].blue = tempB / 9;
				rgb[i][j].green = tempG / 9;
				rgb[i][j].red = tempR / 9;
			}
		}
		//�����Ӿ�ֵ�˲����ļ� 
	    FILE *pFout = fopen("��ֵ�˲�����������.bmp","wb");
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
}
