#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<fstream>

#pragma pack(1)

using namespace std;
struct RGB24BIT//定义像素结构体,顺序是蓝绿红
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
		printf("文件打开失败！");
		return 0;
	}
	int type;
	printf("请输入变换类型：\n");
	printf("1:水平\n");
	printf("2:垂直\n");
	printf("3:四宫格\n");
	scanf("%d",&type);
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//创建动态二维数组
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}

	for (int i = 0 ; i < height ; i++)//读取图像 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}

	if (type == 1)
	{
		rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		for (int i = 0 ; i < height ; i ++)
		{	//创建动态二维数组
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
		
		FILE *pFout = fopen("水平拼接图.bmp","wb");
		ih.biWidth = width * 2;
		ih.biHeight = height;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width*2, pFout);
		}
		printf("输出图片成功!"); 
		//释放指针的内存空间 
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
		{	//创建动态二维数组
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
		FILE *pFout = fopen("垂直拼接图.bmp","wb");
		ih.biWidth = width;
		ih.biHeight = height * 2;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height*2; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
		}
		printf("输出图片成功!"); 
		//释放指针的内存空间 
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
		{	//创建动态二维数组
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width*2);
		}
		for (int i = height ; i < height*2 ; i++)
		{	//水平 
			for (int j = width; j < width*2; j++)
			{
				rgbout[i][j] = rgb[i - height][width*2 - 1 - j];
			}
		}
		for (int i = 0 ; i < width ; i++)
		{	//	垂直 
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
		FILE *pFout = fopen("四宫格.bmp","wb");
		ih.biWidth = width * 2;
		ih.biHeight = height * 2;
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height*2; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width*2, pFout);
		}
		printf("输出图片成功!"); 
		//释放指针的内存空间 
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
