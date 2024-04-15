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
		//unsigned char alpha;
	}**rgb;
int main()
{	
	FILE *pFin,*pFout;
	pFin = fopen("ZMC.bmp","rb");
	pFout= fopen("CHANGE.bmp","wb");
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	//文件头和信息头 
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//创建动态二维数组
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}

	for (int i = 0 ; i < height ; i++)//读取图像 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}

	//改变第1行,改变第50，51行，改变最后2行 
	for(int i=0;i<width;i++)
	{
		//改变第1行，变红 
		rgb[511][i].red=255;
		rgb[511][i].blue=0;
		rgb[511][i].green=0;
		
		//改变第50，51行，变黑 
		rgb[511-50][i].red=0;
		rgb[511-50][i].blue=0;
		rgb[511-50][i].green=0;
		rgb[511-51][i].red=0;
		rgb[511-51][i].blue=0;
		rgb[511-51][i].green=0;
		
		//改变最后2行,变白 
		rgb[0][i].red=255;
		rgb[0][i].blue=255;
		rgb[0][i].green=255;
		rgb[1][i].red=255;
		rgb[1][i].blue=255;
		rgb[1][i].green=255;
	 } 
	 
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for(int i=0;i<height;i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	} 
	printf("输出图像成功!\n");
	//关闭文件 
	fclose(pFin);
	fclose(pFout);
	
	//释放指针 
	for(int i=0;i<height;i++)
	{
		free(rgb[i]);
	} 
	free(rgb);
////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
	FILE *pFin256;	
	pFin256 = fopen("ZMC256.bmp","rb");	
	if(pFin256==NULL)
	{
		printf("256文件打开失败！");
		return 0;
	}
	//256调色板
	RGB24BIT*rgb256; 
	rgb256 = (RGB24BIT*)malloc(sizeof(RGB24BIT*) * height);
	//头信息不会改变，直接跳过 
	fseek(pFin256,54,SEEK_SET);
	 
	fread(rgb256, sizeof(RGB24BIT), width, pFin256);
	
	//图像索引数据指针 
	unsigned char ** data256;
	data256=(unsigned char**)malloc(sizeof(unsigned char*)*height);
	
	for (int i = 0 ; i < height ; i ++)//创建动态二维数组
	{
		data256[i]= (unsigned char*)malloc(sizeof(unsigned char)* width);
	}
	//索引读取
	for (int i = 0 ; i < height ; i ++)//读取图像 
	{
		fread(data256[i],sizeof(unsigned char), width,pFin256);
	} 
	int x;//像素点位置 
	x=data256[0][0]-1;
	printf("256图像的最后一行第一个像素点的位置是：%d\n",x);
	printf("像素点的调色板数据是：B=%d,G=%d,R=%d\n",rgb256[x].blue,rgb256[x].green,rgb256[x].red);
	printf("程序运行结束！\n");
	
	//关闭文件	
	fclose(pFin256);
	
	//释放动态指针 
	for(int i=0;i<height;i++)
	{
		free(data256[i]);
	}
	free(rgb256);
	free(data256);
	return 0; 

}
