#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>

#define pi 3.1415926

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
	
	double degree;
	printf("输入旋转的角度为： （旋转为逆时针旋转）\n");
	scanf("%lf",&degree);
	degree=degree*pi/180;//角度转换为对应弧度 
	
	//图像中心点位置
	int x0=width/2;
	int y0=height/2;
	
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
	//输出灰色图像 
	for (int i = 0 ; i < height; i++)	
	{
		for(int j=0;j<width;j++)
		{
			rgbout[j][i].red=128;
			rgbout[j][i].blue=128;
			rgbout[j][i].green=128;
		}
	}
	
	//旋转
	int x;
	int y; 
	int x1;
	int y1;
	
	int temp;
	printf("输入想要的旋转处理方式：\n");
	printf("选择1：简单旋转后原图推目标\n"); 
	printf("选择2：简单旋转后目标推原图\n");
	printf("选择3：双线性插值的旋转\n");
	scanf("%d",&temp);
	
	//简单旋转
	//坐标不能涵盖目标像素的所有有效坐标点，尤其在取整过程中会遗漏不少点, 就会造成空点状况 
	if(temp==1)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j<width;j++)
			{
				//原图推目标
				x=j-x0;//横轴
				y=i-y0;//纵轴 
				x1=(int)(cos(degree)*x-sin(degree)*y)+x0;//横轴 
				y1=(int)(cos(degree)*y+sin(degree)*x)+y0;//纵轴 
				//简单取值
				if(x1>=0 && x1<width && y1>=0 && y1<height) //符合输出条件 
				{
					rgbout[y1][x1].blue=rgb[i][j].blue;
					rgbout[y1][x1].green=rgb[i][j].green;
					rgbout[y1][x1].red=rgb[i][j].red;
				}
			}
		} 
		FILE *pFout = fopen("xuanzhuan1.bmp","wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
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
	}
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////	
	//简单旋转后目标推原图
	//由原图的像素点数值，给到旋转后的各个位置的像素点.
	if(temp==2)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j<width;j++)
			{
				//目标推原图
				x=j-x0;//横轴
				y=i-y0;//纵轴 
				x1=(int)(cos(degree)*x+sin(degree)*y)+x0;//横轴 
				y1=(int)(cos(degree)*y-sin(degree)*x)+y0;//纵轴 
				//简单取值
				if(x1>=0 && x1<width && y1>=0 && y1<height) //符合输出条件 
				{
					rgbout[i][j].blue=rgb[y1][x1].blue;
					rgbout[i][j].green=rgb[y1][x1].green;
					rgbout[i][j].red=rgb[y1][x1].red;
				}
			}
		} 
		FILE *pFout = fopen("xuanzhuan2.bmp","wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
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
	}
	
///////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////	
	//双线性插值的旋转
	if(temp==3)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j < width;j++)
			{
				x=j-x0;//横轴
				y=i-y0;//纵轴 
				
				double xx;
				double yy;
				
				xx=(double)(cos(degree)*x+sin(degree)*y)+x0;//横轴 
				yy=(double)(cos(degree)*y-sin(degree)*x)+y0;//纵轴 
				
				int xi;
				int yi;
				
				xi=(int)xx;//取整 
				yi=(int)yy;//取整 
				
				int xxx;
				int yyy;
				
				xxx=xi+1;
				yyy=yi+1; 
				
				if(xi<0 || xi>width-1 || yi<0 || yi>height-1)
				{
					continue;
				}
				if(xi==width-1)
				{
					xxx=xi;
				}
				if(yi==height-1)
				{
					yyy=yi;
				}
				
				double xs=xx-xi;	
				double ys=yy-yi; 
				
				//双线性插值
				rgbout[i][j].blue=(unsigned char)(rgb[yi][xi].blue*(1-xs)*(1-ys)+rgb[yyy][xi].blue*(1-xs)*ys+rgb[yi][xxx].blue*xs*(1-ys)+rgb[yyy][xxx].blue*xs*ys);
				rgbout[i][j].green=(unsigned char)(rgb[yi][xi].green*(1-xs)*(1-ys)+rgb[yyy][xi].green*(1-xs)*ys+rgb[yi][xxx].green*xs*(1-ys)+rgb[yyy][xxx].green*xs*ys);
				rgbout[i][j].red=(unsigned char)(rgb[yi][xi].red*(1-xs)*(1-ys)+rgb[yyy][xi].red*(1-xs)*ys+rgb[yi][xxx].red*xs*(1-ys)+rgb[yyy][xxx].red*xs*ys);
				
				
			}
		} 
		FILE *pFout = fopen("xuanzhuan3.bmp","wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT)*width,1,pFout);
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
