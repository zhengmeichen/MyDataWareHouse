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
	
	//ѡ����ʽ:��ֵ�˲�/��ֵ�˲�
	int type;
	printf("��ֵ�˲�������ͼ�� ��������1��\n");
	printf("��ֵ�˲�������ͼ�� ��������2��\n");
	scanf("%d",&type);

	
	//��ֵ�˲�����
	if(type==1)
	{
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
	    FILE *pFout = fopen("��ֵ�˲�.bmp","wb");
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
	}
	
	////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////	
	
	//��ֵ�˲�����
	if(type==2)
	{
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
	    FILE *pFout = fopen("��ֵ�˲�.bmp","wb");
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
