#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<fstream>
#include<math.h> 
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
	
	//统计各灰度信息 
	int count[256]={0};
	
	//图像灰度化 
	for (int i = 0 ; i < height ; i++) 
	{
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char temp=(rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			count[temp]++;
			rgbout[i][j].blue=temp;
			rgbout[i][j].green=temp;
			rgbout[i][j].red=temp;
		} 
	}
	
	//输出各灰度级像素个数到txt文件
	FILE *pout;
	pout = fopen("原始图像的各灰度级像素个数.txt","wb");	
	if(pout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	} 
	for(int i=0;i<256;i++)
	{
		fprintf(pout,"%d\n",count[i]);
	}
	fclose(pout);
	
	//直方图均衡化
	double Pi[256]={0};  //原始图像直方图
	double Pj[256]={0};	 //累积直方图
	
	int sum=ih.biWidth*ih.biHeight;
	
	//计算原始直方图
	for(int i=0;i<256;i++)
	{
		Pi[i]=1.00*count[i]/sum;
	} 
	//输出原始图像的直方图信息到txt文件
	FILE *pout1;
	pout1 = fopen("原始图像的直方图信息.txt","wb");	
	if(pout1==NULL)
	{
		printf("文件打开失败！");
		return 0;
	} 
	for(int i=0;i<256;i++)
	{
		fprintf(pout1,"%lf\n",Pi[i]);
	}
	fclose(pout1);	
	
	//计算累积直方图
	for(int i=0;i<256;i++)
	{
		for(int j=0;j<=i;j++)
		{ 
			Pj[i]+=Pi[j];
		}
	} 
	
	//计算变换后的灰度值 
	unsigned char after[256]={0};
	for(int i=0;i<256;i++)
	{
		after[i]=(int)(255 * Pj[i] + 0.5);	
	}
	
	//确定灰度变换关系
	int count1[256]={0};
	int temp2;
	for (int i = 0 ; i < height ; i++) 
	{
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char temp2=after[rgb[i][j].blue];
			rgbout[i][j].blue=temp2;
			rgbout[i][j].green=temp2;
			rgbout[i][j].red=temp2;
		}  
	} 
	
	//输出均衡化后各灰度级像素个数到txt文件
	FILE *pout2;
	pout2 = fopen("均衡化图像的各灰度级像素个数.txt","wb");	
	if(pout2==NULL)
	{
		printf("文件打开失败！");
		return 0; 
	} 
	for(int i = 0; i < height; i ++)
	{
		for(int j = 0; j < width; j ++)
		{ 
			temp2= rgbout[i][j].blue;
			count1[temp2]++;
		}
	}
	for(int i=0;i<256;i++)
	{
		fprintf(pout2,"%d\n",count1[i]);
	}
	fclose(pout2);
	
	//输出均衡化图像的直方图信息到txt文件
	FILE *pout3;
	pout3 = fopen("均衡化图像的直方图信息.txt","wb");	
	if(pout3==NULL)
	{
		printf("文件打开失败！");
		return 0;
	} 
	double Pii[256]={0};
	for(int i=0;i<256;i++)
	{
		Pii[i]=1.00*count1[i]/sum;
	} 
	for(int i=0;i<256;i++)
	{
		fprintf(pout3,"%lf\n",Pii[i]);
	}
	fclose(pout3);	
	
	
	//输出均衡化后图像
    FILE *pFout = fopen("Histogram.bmp","wb");
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
	printf("输出图片成功!");  
	
	
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
