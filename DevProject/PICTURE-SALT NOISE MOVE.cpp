#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>

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
	pFin = fopen("Salt AND Pepper Noise.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//创建二维动态指针 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//创建动态二维数组
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//读取图像
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//选择处理方式:中值滤波/均值滤波
	int type;
	printf("均值滤波法处理图像 ，请输入1：\n");
	printf("中值滤波法处理图像 ，请输入2：\n");
	scanf("%d",&type);

	
	//均值滤波处理
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
		//输出添加均值滤波的文件 
	    FILE *pFout = fopen("均值滤波.bmp","wb");
	    if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgb[i], sizeof(RGB24BIT), width, pFout);
		}
		printf("输出图片成功!!!\n");  
		printf("运行程序以结束!!!\n");
		
		
		//释放指针的内存空间 
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
	
	//中值滤波处理
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
		
		//输出添加中值滤波的文件 
	    FILE *pFout = fopen("中值滤波.bmp","wb");
	    if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgb[i], sizeof(RGB24BIT), width, pFout);
		}
		printf("输出图片成功!!!\n");  
		printf("运行程序以结束!!!\n");
		
		//释放指针的内存空间 
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
