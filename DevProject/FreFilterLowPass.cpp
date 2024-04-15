#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>
#include "FFTNEW.h"

typedef struct RGB24BIT
{	//定义像素结构体,顺序是蓝绿红
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

double H(double D,double D0)
{	//返回传递函数的值
	return 1.0/(1 + (D/D0)*(D/D0));
}

double H1(double D,double D0)
{	//返回传递函数的值
	return 1.0/(1 + (D0/D)*(D0/D));
}

int low_pass_filter(char *in , char *out)
{
	FILE *pFin,*pFout;												//定义文件指针 
	BITMAPFILEHEADER bfile;											//定义文件头
	BITMAPINFOHEADER binfo;											//定义信息头
	pFin=fopen(in,"rb");											//读取文件

	if(!pFin)
	{	//判断文件是否打开成功
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////图像信息的读取/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//读取文件头
	fread(&binfo,sizeof(binfo),1,pFin);									//读取信息头
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//创建输入文件二维指针
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//给指针动态分配内存
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//读取图像
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////定义二维复数数组///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////图像的预处理（灰度化）和复数数组的处理/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//将原图变为灰度图
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//处理同时将值赋给实部
			arr[i][j].y=0;		//虚部处理为0
		}
	}

	/////////////////////////////傅里叶变换//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////低通滤波处理/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//低通滤波
		for (int j = 0 ; j < width ;j++)
		{
			if (sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)) < 0.2*width)
			{
				continue;
			}
			arr[i][j].x = 0;
			arr[i][j].y = 0;
		}
	}
	
	////////////////////////////傅里叶反变换回去/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////将得到的复数数组变换回图像///////////////////////////////////
	for (int i = 0 ; i < height ;i++)
	{
		for(int j = 0 ; j < width ;j++)
		{
			double tmp=sqrt(arr[i][j].x * arr[i][j].x + arr[i][j].y*arr[i][j].y);
			if (tmp>255)
			{
				rgb[i][j].blue=255;
				rgb[i][j].green=255;
				rgb[i][j].red=255;
			}
			else
			{
				rgb[i][j].blue=(unsigned char)tmp;
				rgb[i][j].green=(unsigned char)tmp;
				rgb[i][j].red=(unsigned char)tmp;
			}
		}
	}
	//////////////////////////////////文件输出//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出理想低通滤波图像成功!!!\n");
	///////////////////////////////////////////关闭文件指针,释放内存////////////////////////////
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		free(arr[i]);
	}
	free(rgb);
	free(arr);
	fclose(pFin);
	fclose(pFout);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
int low_pass_Butterworth(char *in,char *out)
{
	FILE *pFin,*pFout;												//定义文件指针 
	BITMAPFILEHEADER bfile;											//定义文件头
	BITMAPINFOHEADER binfo;											//定义信息头
	pFin=fopen(in,"rb");											//读取文件

	if(!pFin)
	{	//判断文件是否打开成功
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////图像信息的读取/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//读取文件头
	fread(&binfo,sizeof(binfo),1,pFin);									//读取信息头
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//创建输入文件二维指针
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//给指针动态分配内存
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//读取图像
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////定义二维复数数组///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////图像的预处理（灰度化）和复数数组的处理/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//将原图变为灰度图
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//处理同时将值赋给实部
			arr[i][j].y=0;		//虚部处理为0
		}
	}

	/////////////////////////////傅里叶变换//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////Butterworth低通滤波处理/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//Butterworth低通滤波
		for (int j = 0 ; j < width ;j++)
		
		{
			double tmp = H(sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)),0.1*width);
			arr[i][j].x *= tmp;
			arr[i][j].y *= tmp;
		}
	}
	
	////////////////////////////傅里叶反变换回去/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////将得到的复数数组变换回图像///////////////////////////////////
	for (int i = 0 ; i < height ;i++)
	{
		for(int j = 0 ; j < width ;j++)
		{
			double tmp=sqrt(arr[i][j].x * arr[i][j].x + arr[i][j].y*arr[i][j].y);
			if (tmp>255)
			{
				rgb[i][j].blue=255;
				rgb[i][j].green=255;
				rgb[i][j].red=255;
			}
			else
			{
				rgb[i][j].blue=(unsigned char)tmp;
				rgb[i][j].green=(unsigned char)tmp;
				rgb[i][j].red=(unsigned char)tmp;
			}

		}
	}
	//////////////////////////////////文件输出//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出Butterworth低通滤波图像成功!!!\n");
	///////////////////////////////////////////关闭文件指针,释放内存////////////////////////////
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		free(arr[i]);
	}
	free(rgb);
	free(arr);
	fclose(pFin);
	fclose(pFout);

}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
int high_pass_filter(char *in , char *out)
{
	FILE *pFin,*pFout;												//定义文件指针 
	BITMAPFILEHEADER bfile;											//定义文件头
	BITMAPINFOHEADER binfo;											//定义信息头
	pFin=fopen(in,"rb");											//读取文件

	if(!pFin)
	{	//判断文件是否打开成功
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////图像信息的读取/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//读取文件头
	fread(&binfo,sizeof(binfo),1,pFin);									//读取信息头
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//创建输入文件二维指针
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//给指针动态分配内存
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//读取图像
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////定义二维复数数组///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////图像的预处理（灰度化）和复数数组的处理/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//将原图变为灰度图
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//处理同时将值赋给实部
			arr[i][j].y=0;		//虚部处理为0
		}
	}

	/////////////////////////////傅里叶变换//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////高通滤波处理/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//高通滤波
		for (int j = 0 ; j < width ;j++)
		{
			if (sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)) > 0.02*width)
			{
				continue;
			}
			arr[i][j].x = 0;
			arr[i][j].y = 0;
		}
	}
	
	////////////////////////////傅里叶反变换回去/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////将得到的复数数组变换回图像///////////////////////////////////
	for (int i = 0 ; i < height ;i++)
	{
		for(int j = 0 ; j < width ;j++)
		{
			double tmp=sqrt(arr[i][j].x * arr[i][j].x + arr[i][j].y*arr[i][j].y);
			if (tmp>255)
			{
				rgb[i][j].blue=255;
				rgb[i][j].green=255;
				rgb[i][j].red=255;
			}
			else
			{
				rgb[i][j].blue=(unsigned char)tmp;
				rgb[i][j].green=(unsigned char)tmp;
				rgb[i][j].red=(unsigned char)tmp;
			}
		}
	}
	//////////////////////////////////文件输出//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出理想高通滤波图像成功!!!\n");
	///////////////////////////////////////////关闭文件指针,释放内存////////////////////////////
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		free(arr[i]);
	}
	free(rgb);
	free(arr);
	fclose(pFin);
	fclose(pFout);
}
/////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////
int high_pass_Butterworth(char *in,char *out)
{
	FILE *pFin,*pFout;												//定义文件指针 
	BITMAPFILEHEADER bfile;											//定义文件头
	BITMAPINFOHEADER binfo;											//定义信息头
	pFin=fopen(in,"rb");											//读取文件

	if(!pFin)
	{	//判断文件是否打开成功
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////图像信息的读取/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//读取文件头
	fread(&binfo,sizeof(binfo),1,pFin);									//读取信息头
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//创建输入文件二维指针
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//给指针动态分配内存
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//读取图像
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////定义二维复数数组///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////图像的预处理（灰度化）和复数数组的处理/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//将原图变为灰度图
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//处理同时将值赋给实部
			arr[i][j].y=0;		//虚部处理为0
		}
	}

	/////////////////////////////傅里叶变换//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////Butterworth低通滤波处理/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//Butterworth高通滤波
		for (int j = 0 ; j < width ;j++)
		
		{
			double tmp = H1(sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)),0.02*width);
			arr[i][j].x *= tmp;
			arr[i][j].y *= tmp;
		}
	}
	
	////////////////////////////傅里叶反变换回去/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////将得到的复数数组变换回图像///////////////////////////////////
	for (int i = 0 ; i < height ;i++)
	{
		for(int j = 0 ; j < width ;j++)
		{
			double tmp=sqrt(arr[i][j].x * arr[i][j].x + arr[i][j].y*arr[i][j].y);
			if (tmp>255)
			{
				rgb[i][j].blue=255;
				rgb[i][j].green=255;
				rgb[i][j].red=255;
			}
			else
			{
				rgb[i][j].blue=(unsigned char)tmp;
				rgb[i][j].green=(unsigned char)tmp;
				rgb[i][j].red=(unsigned char)tmp;
			}

		}
	}
	//////////////////////////////////文件输出//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出Butterworth高通滤波图像成功!!!\n");
	///////////////////////////////////////////关闭文件指针,释放内存////////////////////////////
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		free(arr[i]);
	}
	free(rgb);
	free(arr);
	fclose(pFin);
	fclose(pFout);

}

int main(){
	low_pass_filter("ZMC.bmp","理想低通滤波.bmp");
	low_pass_Butterworth("ZMC.bmp","Butterworth低通滤波.bmp");
	high_pass_filter("ZMC.bmp","理想高通滤波.bmp");
	high_pass_Butterworth("ZMC.bmp","Butterworth高通滤波.bmp");
	return 0;		
}


