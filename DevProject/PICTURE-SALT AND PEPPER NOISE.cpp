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
	
	/////添加椒盐噪声
	double SNR;
	//输入信噪比
	printf("输入信噪比SNR（SNR的范围【0-1】）：\n");
	scanf("%lf",&SNR);
	srand((unsigned)time(NULL));
	 
	unsigned char temp;
	
	//变成噪声点的像素总数为 height*width*(1-SNR)
	for(int i=0;i<height*sqrt(1-SNR);i++)
	{
		for(int j=0;j<width*sqrt(1-SNR);j++)
		{
			temp=(rand()%2)*255;//余数为0，temp为0；余数为1，temp为255； 
			//temp的值为0为椒噪声，temp的值为255为盐噪声
			int RandomH=rand()%height;//噪声点坐标 
			int RandomW=rand()%width;//噪声点坐标  
			rgb[RandomH][RandomW].blue=temp;
			rgb[RandomH][RandomW].green=temp;
			rgb[RandomH][RandomW].red=temp;
		}
	} 
	
	//输出添加椒盐噪声的文件 
    FILE *pFout = fopen("Salt AND Pepper Noise.bmp","wb");
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
