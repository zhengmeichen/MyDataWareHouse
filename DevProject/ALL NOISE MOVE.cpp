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
	printf("选择用高斯滤波对高斯噪声图像进行处理，请输入1：\n");
	printf("选择用高斯滤波对椒盐噪声图像进行处理，请输入2：\n");
	printf("选择用中值滤波对高斯噪声图像进行处理，请输入3：\n");
	printf("选择用中值滤波对椒盐噪声图像进行处理，请输入4：\n");
	printf("选择用均值滤波对高斯噪声图像进行处理，请输入5：\n");
	printf("选择用均值滤波对椒盐噪声图像进行处理，请输入6：\n");	
	int type;
	scanf("%d",&type);
	
	//用高斯滤波对高斯噪声图像进行处理 
	if(type==1)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//高斯滤波处理 
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
		
		//输出添加高斯滤波的文件 
	    FILE *pFout = fopen("高斯滤波处理高斯噪声.bmp","wb");
	    if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
	
	//用高斯滤波对椒盐噪声图像进行处理 
	if(type==2)
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
		
		//高斯滤波 
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
		
		//输出添加高斯滤波的文件 
	    FILE *pFout = fopen("高斯滤波处理椒盐噪声.bmp","wb");
	    if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
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
	
	
	//中值滤波对高斯噪声图像进行处理
	if(type==3)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//中值滤波处理 
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
	    FILE *pFout = fopen("中值滤波处理高斯噪声.bmp","wb");
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
	
	//中值滤波对椒盐噪声图像进行处理 
	if(type==4)
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
		
		//中值滤波处理 
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
	    FILE *pFout = fopen("中值滤波处理椒盐噪声.bmp","wb");
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
	
	
	//均值滤波对高斯噪声图像进行处理 
	if(type==5)
	{
		FILE *pFin;
		pFin = fopen("Gaussian Noise.bmp","rb");	
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
		
		//均值滤波处理 
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
	    FILE *pFout = fopen("均值滤波处理高斯噪声.bmp","wb");
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
	 
	//均值滤波对椒盐噪声图像进行处理 
	if(type==6)
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
		
		//均值滤波处理 
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
	    FILE *pFout = fopen("均值滤波处理椒盐噪声.bmp","wb");
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
