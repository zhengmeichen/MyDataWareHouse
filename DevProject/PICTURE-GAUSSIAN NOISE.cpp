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
}**rgb,**rgbout;

//输入参数：mu是均值，sigma是方差
//输出X服从高斯分布N（mu,sigma)
//K为放大系数，K愈大噪声越密
double GaussianNoise(double mu,double sigma,int k) 
{
	//产生高斯样本
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
	return k*(mu+sigma*X); //返回高斯分布的横坐标 
}


int main()
{
	FILE *pFin;
	pFin = fopen("ZMC.bmp","rb");	
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
	
	double mu;//均值 
	double sigma;//方差
	int k;//放大倍数
	
	printf("请输入均值为mu：\n");
	scanf("%lf",&mu);
	printf("请输入方差为sigma：\n");
	scanf("%lf",&sigma);
	printf("请输入放大倍数为k：\n");
	scanf("%d",&k);
	
	for (int i = 0 ; i < height ; i++)
	{
		for (int j = 0; j < width; j++)
		{
			//高斯噪声处理
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
	 
	//输出添加高斯噪声的文件 
    FILE *pFout = fopen("Gaussian Noise.bmp","wb");
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
