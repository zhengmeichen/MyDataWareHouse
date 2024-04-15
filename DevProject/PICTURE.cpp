#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<fstream>

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
	int type;
	printf("������任���ͣ�\n");
	printf("1:ˮƽ\n");
	printf("2:��ֱ\n");
	printf("3:�Ĺ���\n");
	scanf("%d",&type);
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//������̬��ά����
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}

	for (int i = 0 ; i < height ; i++)//��ȡͼ�� 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}

	if (type == 1)
	{
		rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		for (int i = 0 ; i < height ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width*2);
		}
		for (int i = 0 ; i < height ; i++)
		{
			for (int j = 0; j < width; j++)
			{
				rgbout[i][j] = rgb[i][j];
			}
			for (int j = width; j < width*2; j++)
			{
				rgbout[i][j] = rgb[i][width*2 - 1 - j];
			}
		}
		
		FILE *pFout = fopen("ˮƽƴ��ͼ.bmp","wb");
		ih.biWidth = width * 2;
		ih.biHeight = height;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width*2, pFout);
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
	else if(type == 2)
	{
		int widthout = width;
		int heightout = height * 2;
		rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height*2);
		for (int i = 0 ; i < height * 2 ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}
		for (int i = 0 ; i < width ; i++)
		{
			for (int j = 0; j < height; j++)
			{
				rgbout[j][i] = rgb[height - 1 - j][i];
			}
			for (int j = height; j < height*2; j++)
			{
				rgbout[j][i] = rgb[j - height][i];
			}
		}
		FILE *pFout = fopen("��ֱƴ��ͼ.bmp","wb");
		ih.biWidth = width;
		ih.biHeight = height * 2;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height*2; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
	else if (type == 3)
	{
		//int widthout = width * 2;
		//int heightout = height * 2;
		rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height*2);
		for (int i = 0 ; i < height*2 ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width*2);
		}
		for (int i = height ; i < height*2 ; i++)
		{	//ˮƽ 
			for (int j = width; j < width*2; j++)
			{
				rgbout[i][j] = rgb[i - height][width*2 - 1 - j];
			}
		}
		for (int i = 0 ; i < width ; i++)
		{	//	��ֱ 
			for (int j = height; j < height*2; j++)
			{
				rgbout[j][i] = rgb[j - height][i];
			}
			for (int j = 0; j < height; j++)
			{
				rgbout[j][i] = rgb[height - 1 - j][i];
			}
		}
		for (int i = width ; i < width*2 ; i++)
		{
			for (int j = 0; j < height; j++)
			{
				rgbout[j][i] = rgb[j][i - width];
			}
		}
		FILE *pFout = fopen("�Ĺ���.bmp","wb");
		ih.biWidth = width * 2;
		ih.biHeight = height * 2;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height*2; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width*2, pFout);
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
