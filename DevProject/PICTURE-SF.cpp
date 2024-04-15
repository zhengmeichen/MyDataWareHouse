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
	
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	int type;
	printf("选择最邻近插值缩放处理，请输入:1\n");
	printf("选择双线性插值的缩放处理，请输入：2\n");
	scanf("%d",&type);
	
	/*//输入缩放倍数 
	double Sx,Sy;
	printf("提醒：请在下方输入数据时，数据的范围确定在【0.5，3】之间!!!\n");
	printf("请输入水平缩放倍数：\n");
	scanf("%lf",&Sx);
	printf("请输入垂直缩放倍数：\n");
	scanf("%lf",&Sy);*/
	
	//最邻近插值缩放处理
	if(type==1)
	{
		//输入缩放倍数 
		double Sx,Sy;
		printf("提醒：请在下方输入数据时，数据的范围确定在【0.5，3】之间!!!\n");
		printf("请输入水平缩放倍数：\n");
		scanf("%lf",&Sx);
		printf("请输入垂直缩放倍数：\n");
		scanf("%lf",&Sy);
		
		//申请动态存储空间 
		rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		for (int i = 0 ; i < height ; i ++)//创建动态二维数组
		{
			rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}
		//读取图像数据 
		for (int i = 0 ; i < height ; i++)
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
		//输出图像分辨率 
		int out_height=Sy*height;
		int outwidth=Sx*width; 
		//讲输出图像数据的out_width变为4的倍数
		int out_width= (outwidth+3)/4*4;
		//分配存储空间
		rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * out_height); 
		for(int i=0;i<out_height;i++)
		{
			rgbout[i]= (RGB24BIT *)malloc(sizeof(RGB24BIT*) * out_width);
		}
		double xx;    	//映射的x 
		double yy;    	//映射的y
		int xxx;		//映射的x的整数部分 
		int yyy;		//映射的y的整数部分 
		int x1;			//xxxx+1
		int y1;			//yyy+1
		double xs=0;	
		double ys=0; 
		
		//缩放
		for(int i=0;i<out_height;i++)
		{
			for(int j=0;j<out_width;j++)
			{
				//求映射坐标
				xx=1/Sy*i;
				yy=1/Sx*j;
				//取映射的整数部分
				xxx=(int)xx;
				yyy=(int)yy;
				//双线性插值
				xs=xx-xxx;
				ys=yy-yyy;
				
				x1=xxx+1;
				y1=yyy+1;
				//边缘点处理
				if((xxx+1)>(height-1)) 
				{
					x1=xxx-1;
				}
				if((xxx+1)>(width-1)) 
				{
					y1=yyy-1;
				}
				//最邻近插值
				rgbout[i][j].blue=rgb[xxx][yyy].blue;
				rgbout[i][j].green=rgb[xxx][yyy].green;
				rgbout[i][j].red=rgb[xxx][yyy].red; 
			}
		}
		ih.biWidth=out_width;
		ih.biHeight=out_height;
		fh.bfSize=54+out_width*out_height*3;
		
		FILE *pFout;
		pFout = fopen("最邻近插值.bmp","wb");
		if(pFout==NULL)
    	{
    		printf("文件打开失败！\n");
    		return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("输出文件成功！\n");
		
		//释放指针的内存空间 
		for (int i = 0 ; i<height ;i++)
		{
			free(rgb[i]);
		}
		for (int i = 0 ; i<out_height ;i++)
		{
			free(rgbout[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
			
	return 0;	
	} 
	
//////////////////////////////////////////////////////////////////////////
	//双线性插值的缩放处理	
	if(type==2)
	{
		//输入缩放倍数 
		double Sx,Sy;
		printf("提醒：请在下方输入数据时，数据的范围确定在【0.5，3】之间!!!\n");
		printf("请输入水平缩放倍数：\n");
		scanf("%lf",&Sx);
		printf("请输入垂直缩放倍数：\n");
		scanf("%lf",&Sy);
		
		//申请动态存储空间 
		rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		for (int i = 0 ; i < height ; i ++)//创建动态二维数组
		{
			rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}
		//读取图像数据 
		for (int i = 0 ; i < height ; i++)
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
		//输出图像分辨率 
		int out_height=Sy*height;
		int outwidth=Sx*width; 
		//讲输出图像数据的out_width变为4的倍数
		int out_width= (outwidth+3)/4*4;
		//分配存储空间
		rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * out_height); 
		for(int i=0;i<out_height;i++)
		{
			rgbout[i]= (RGB24BIT *)malloc(sizeof(RGB24BIT*) * out_width);
		}

		double xx;    	//映射的x 
		double yy;    	//映射的y
		int xxx;		//映射的x的整数部分 
		int yyy;		//映射的y的整数部分 
		int x1;			//xxx+1
		int y1;			//yyy+1
		double xs=0;	
		double ys=0; 

		//缩放
		for(int i=0;i<out_height;i++)
		{
			for(int j=0;j<out_width;j++)
			{
				//求映射坐标
				xx=1/Sy*i;
				yy=1/Sx*j;
				//取映射的整数部分
				xxx=(int)xx;
				yyy=(int)yy;
				//双线性插值
				xs=xx-xxx;
				ys=yy-yyy;
				
				x1=xxx+1; 
				y1=yyy+1;
				//边缘点处理
				if((xxx+1)>(height-1)) 
				{
					x1=xxx-1;
				}
				if((xxx+1)>(width-1)) 
				{
					y1=yyy-1;
				}
				//双线性插值
				rgbout[i][j].blue=(unsigned char)(rgb[xxx][yyy].blue*(1-xs)*(1-ys)+rgb[xxx][y1].blue*(1-xs)*ys+rgb[x1][yyy].blue*xs*(1-ys)+rgb[x1][y1].blue*xs*ys);
				rgbout[i][j].green=(unsigned char)(rgb[xxx][yyy].green*(1-xs)*(1-ys)+rgb[xxx][y1].green*(1-xs)*ys+rgb[x1][yyy].green*xs*(1-ys)+rgb[x1][y1].green*xs*ys);
				rgbout[i][j].red=(unsigned char)(rgb[xxx][yyy].red*(1-xs)*(1-ys)+rgb[xxx][y1].red*(1-xs)*ys+rgb[x1][yyy].red*xs*(1-ys)+rgb[x1][y1].red*xs*ys);
			}
		}
		ih.biWidth=out_width;
		ih.biHeight=out_height;
		fh.bfSize=54+out_width*out_height*3;
		
		FILE *pFout;
		pFout = fopen("双线性插值.bmp","wb");
		if(pFout==NULL)
    	{
    		printf("文件打开失败！\n");
    		return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("输出文件成功！\n");
		
		//释放指针的内存空间 
		for (int i = 0 ; i<height ;i++)
		{
			free(rgb[i]);
		}
		for (int i = 0 ; i<out_height ;i++)
		{
			free(rgbout[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);	
		return 0;
	}
	
	return 0; 
}
