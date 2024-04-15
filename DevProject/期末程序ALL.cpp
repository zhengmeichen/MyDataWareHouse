#include<iostream>
#include<malloc.h>
#include<windows.h>
#include <math.h>
#include<fstream>
#include<time.h>
#include<stdlib.h>

#pragma pack(1)
#define pi 3.1415926
using namespace std;

struct RGB24BIT //定义像素结构体,顺序是蓝绿红
{	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}**rgb, **rgbout;

struct RGB24BIT1 //定义像素结构体,顺序是蓝绿红
{	
	double blue;
	double green;
	double red;
}**rgbh, **rgbv;
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//将彩色BMP图像灰度化处理 
int Grey(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	//将原图变为灰度图
	for (int i = 0 ; i < height ;i++)
	{	
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgbout[i][j].blue=temp;
			rgbout[i][j].green=temp;
			rgbout[i][j].red=temp;
		}
	}
	
	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出灰度化图像成功!!!\n");
	
	//关闭文件指针,释放内存
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

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//在图像外加一个边框，边框的大小允许输入参数和边框颜色在程序内确定 
int Add(char *in,char *out) 
{
	
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//创建二维动态指针 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//创建动态二维数组
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//读取图像
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//将原图变为加边框的图像
	int x;//width方向上加的边框宽度 
	int y;//height方向上加的边框宽度
	printf("请输入要加的边框宽度：\n");
	printf("width方向上加的边框宽度:");
	scanf("%d",&x);
	printf("height方向上加的边框宽度:");
	scanf("%d",&y); 
	
	//创建二维动态指针 
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * (height+y+y));
	//创建动态二维数组
	for (int i = 0 ; i < height+2*y ; i ++)
	{
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * (width+x+x));
	}
	
	//设置边框颜色为黄色RGB(255,255,0) 
	//先将图像扩展，设置背景颜色 
	for (int i = 0 ; i < height+2*y; i++)
	{
		for(int j=0;j< width+2*x;j++)
		{
			rgbout[i][j].red=255;
			rgbout[i][j].blue=0;
			rgbout[i][j].green=255;
		}
	}
	//输出图像 
	for (int i = y ; i < height+y; i++)
	{
		for(int j=x ;j< width+x ;j++)
		{
			rgbout[i][j].red=rgb[i-y][j-x].red;
			rgbout[i][j].blue=rgb[i-y][j-x].blue;
			rgbout[i][j].green=rgb[i-y][j-x].green;
		}
	}

	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	//更改文件头大小 
	ih.biWidth  = width +2*x;
	ih.biHeight = height+2*y;
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height+2*y; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width+2*x,pFout);
	}
	printf("输出加边框图像成功!!!\n");
	
	//关闭文件指针,释放内存
	for (int i = 0 ; i<height ;i++)
	{
		free(rgb[i]);
		//free(rgbout[i]); 
	}
	for (int i = 0 ; i<height+2*y ;i++)
	{
		//free(rgb[i]);
		free(rgbout[i]); 
	}
	free(rgb);
	free(rgbout);
	fclose(pFin);
	fclose(pFout);
	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像进行马赛克处理，允许输入块大小作为参数
int Mosaic(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	printf("请输入块大小：(输入一次即可，x*x):\n");
	int x;
	scanf("%d",&x); 
	//x*x块图像 
	//将图像马赛克处理 
	int ii,jj; 
	for (int i = 0 ; i < height ;i+=x)
	{	
		ii=i;//定义等价i的另一变量，同时不会改变i自身 
		for(int j = 0 ; j < width ;j+=x)
		{
			jj=j;//定义等价j的另一变量，同时不会改变j自身
			
			//求块内所有的R,G,B值的和
			int rr=0,gg=0,bb=0;
			for(int m = ii; m < ii + x && m < height; m ++)
			{
				for(int n = jj; n < jj + x && n < width; n ++)
				{
					bb += rgb[m][n].blue;
					gg += rgb[m][n].green;
					rr += rgb[m][n].red;
				}
			}
			
			//求和后的值平均到每块像素上 
			for(int m = ii; m < ii + x && m < height; m ++)
			{
				for(int n = jj; n < jj + x && n < width; n ++)
				{
					rgbout[m][n].blue = bb/ (x*x);
					rgbout[m][n].green = gg/ (x*x);
					rgbout[m][n].red = rr/ (x*x);
				}
			}
		}
	}
	
	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出马赛克图像成功!!!\n");
	
	//关闭文件指针,释放内存
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

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像进行几何变换处理：平移
int Move(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	//将图像自定义平移 
	int x,y,m;
	printf("输入的值必须为非负整数！\n"); 
	printf("请输入水平移动的值：【0-512】");
	scanf("%d",&x);
	printf("请输入垂直移动的值：【0-512】");
	scanf("%d",&y);
	if(x<0||x>width||y<0||y>height) 
	{
		printf("输入的参数值不在合理范围\n");
		return 0; 
	}
	/*for (int i = 0 ; i < height ; i ++)
	{	//创建动态二维数组
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}*/
	//////////////////////////////////////
	//没有平移 
	if(x==0&&y==0)
	{
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义平移图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	////////////////////////////////////////////
	//上下平移 
	else if(x==0&&y!=0)
	{
		printf("垂直上移选择1\n");
		printf("垂直下移选择2\n");
		scanf("%d",&m);
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		switch(m)
		{
			case(1):
			
			for (int i = 0 ; i < width ; i++)
			{
				for (int j = 0; j < height-y; j++)
				{
					rgbout[j+y][i]=rgb[j][i];
				}
			}
			break; 
			/////////// 
			case(2):
			
			for (int i = 0 ; i < width ; i++)
			{
				for (int j = 0; j < height-y; j++)
				{
					rgbout[j][i]=rgb[j+y][i];
				}
			}
			break;
		}
	
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义平移图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	////////////////////////////////////////////
	//左右平移  
	else if(x!=0&&y==0)
	{
		printf("水平左移选择1\n");
		printf("水平右移选择2\n");
		scanf("%d",&m);
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		switch(m)
		{
			case(1):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j]=rgb[i][x+j];
				}
			}
			break; 
			/////////// 
			case(2):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j+x]=rgb[i][j];
				}
			}
			break;
		}
		
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义平移图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	///////////////////////////////////////
	//自定义 
	else if(x!=0&&y!=0)
	{
		printf("左上移选择1\n");
		printf("右上移选择2\n");
		printf("左下移选择3\n");
		printf("右下移选择4\n");
		scanf("%d",&m);
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		} 
		switch(m)
		{
			case(1):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j]=rgb[i][x+j];
				}
			}
			for (int i = 0 ; i < height; i++)
			{
				for(int j=0;j<width;j++)
				{
					rgbout[j][i].red=128;
					rgbout[j][i].blue=128;
					rgbout[j][i].green=128;
				}
			}
			for (int u = 0 ; u < width-x; u++)
			{
				for (int v = 0; v < height-y; v++)
				{
					rgbout[v+y][u]=rgb[v][x+u];
				}
			}
			break; 
			/////////// 
			case(2):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j+x]=rgb[i][j];
				}
			}
			for (int i = 0 ; i < height; i++)
			{
				for(int j=0;j<width;j++)
				{
					rgbout[j][i].red=128;
					rgbout[j][i].blue=128;
					rgbout[j][i].green=128;
				}
			}
			for (int i = 0 ; i < width-x ; i++)
			{
				for (int j = 0; j < height-y; j++)
				{
					rgbout[j+y][i+x]=rgb[j][i];
				}
			}
			break;
			//////////// 
			case(3):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j]=rgb[i][x+j];
				}
			}
			for (int i = 0 ; i < height; i++)
			{
				for(int j=0;j<width;j++)
				{
					rgbout[j][i].red=128;
					rgbout[j][i].blue=128;
					rgbout[j][i].green=128;
				}
			}
			for (int i = 0 ; i < width-x ; i++)
			{
				for (int j = 0; j < height-y; j++)
				{
					rgbout[j][i]=rgb[j+y][x+i];
				}
			}
			break; 
			/////////// 
			case(4):
			
			for (int i = 0 ; i < height ; i++)
			{
				for (int j = 0; j < width-x; j++)
				{
					rgbout[i][j+x]=rgb[i][j];
				}
			}
			for (int i = 0 ; i < height; i++)
			{
				for(int j=0;j<width;j++)
				{
					rgbout[j][i].red=128;
					rgbout[j][i].blue=128;
					rgbout[j][i].green=128;
				}
			}
			for (int i = 0 ; i < width-x ; i++)
			{
				for (int j = 0; j < height-y; j++)
				{
					rgbout[j][i+x]=rgb[j+y][i];
				}
			}
			break;
		}
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义平移图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像进行几何变换处理：旋转
int Revolve(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	double degree;
	printf("输入旋转的角度为： （旋转为逆时针旋转）\n");
	scanf("%lf",&degree);
	degree=degree*pi/180;//角度转换为对应弧度 
	
	//图像中心点位置
	int x0=width/2;
	int y0=height/2;
	
	//旋转
	int x;
	int y; 
	int x1;
	int y1;
	
	int temp;
	printf("输入想要的旋转处理方式：\n");
	printf("选择1：简单旋转后目标推原图\n");
	printf("选择2：双线性插值的旋转\n");
	scanf("%d",&temp);
	
	//简单旋转后目标推原图
	//由原图的像素点数值，给到旋转后的各个位置的像素点.
	if(temp==1)
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
		
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义旋转图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	
	//双线性插值的旋转
	if(temp==2)
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
		
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("输出自定义旋转图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像进行几何变换处理：缩放 
int SF(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	/*//创建二维动态指针 
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
	}*/ 
	
	int type;
	printf("选择最邻近插值缩放处理，请输入:1\n");
	printf("选择双线性插值的缩放处理，请输入：2\n");
	scanf("%d",&type);
	
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
		
		//创建动态二维数组
		for (int i = 0 ; i < height ; i ++)
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
		
		
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("输出自定义缩放图像成功!!!\n");
		
		//关闭文件指针,释放内存
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
		
	} 
	
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
		//创建动态二维数组
		for (int i = 0 ; i < height ; i ++)
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
		
		//文件输出
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("文件打开失败！");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("输出自定义缩放图像成功!!!\n");
		
		//关闭文件指针,释放内存
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

	}	
	return 0;
}

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像做对比度增强处理：直方图均衡处理
int ZFTJHH(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	//直方图均衡化
	double Pi[256]={0};  //原始图像直方图
	double Pj[256]={0};	 //累积直方图
	
	int sum=ih.biWidth*ih.biHeight;
	
	//计算原始直方图
	for(int i=0;i<256;i++)
	{
		Pi[i]=1.00*count[i]/sum;
	} 

	
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
		
	//输出均衡化后图像
    FILE *pFout = fopen(out,"wb");
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
	printf("输出直方图均衡化图像成功!!!\n");  
	
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
 
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像加入椒盐噪声
int SaltPepper(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	for (int i = 0 ; i < height ; i++) 
	{
		for (int j = 0 ; j < width ; j++)
		{
			rgbout[i][j].blue=rgb[i][j].blue;
			rgbout[i][j].green=rgb[i][j].green;
			rgbout[i][j].red=rgb[i][j].red;
		}  
	} 
	//将图像添加椒盐噪声 
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
			rgbout[RandomH][RandomW].blue=temp;
			rgbout[RandomH][RandomW].green=temp;
			rgbout[RandomH][RandomW].red=temp;
		}
	} 
	
	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出椒盐噪声图像成功!!!\n");
	
	//关闭文件指针,释放内存
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
 
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对加入椒盐噪声的图像进行中值滤波处理
int Filter(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
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
	
	for (int i = 0 ; i < height ; i++) 
	{
		for (int j = 0 ; j < width ; j++)
		{
			rgbout[i][j].blue=rgb[i][j].blue;
			rgbout[i][j].green=rgb[i][j].green;
			rgbout[i][j].red=rgb[i][j].red;
		}  
	} 
	//将图像添加椒盐噪声 
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
			rgbout[RandomH][RandomW].blue=temp;
			rgbout[RandomH][RandomW].green=temp;
			rgbout[RandomH][RandomW].red=temp;
		}
	} 
	
	//将添加椒盐噪声的图像，进行中值滤波处理 
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
			rgbout[i][j].blue = B[4];
			rgbout[i][j].green = G[4];
			rgbout[i][j].red = R[4];
		}
	} 
	
	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出中值滤波处理图像成功!!!\n");
	
	//关闭文件指针,释放内存
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

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//对图像通过Sobel算子求取边缘
int Sobel(char *in,char *out) 
{
	//定义文件指针  
	FILE *pFin;	
	//读取文件		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	
	//定义文件头
	BITMAPFILEHEADER fh;
	//读取文件头
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//定义信息头
	BITMAPINFOHEADER ih;
	//读取信息头
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//创建二维动态指针 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbv = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
	rgbh = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
	
	//创建动态二维数组
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbv[i]	= (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
		rgbh[i]	= (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
	}
	
	//读取图像
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//Sobel算子处理图像 
	double T;
	printf("请输入阈值T为：\n");
	scanf("%lf",&T);
	//结论：T在120-150之间，图像效果最好
	
	for (int i = 1; i < height - 1; i ++)
	{
		for (int j = 1; j < width - 1; j ++)
		{
			//水平模板 
			rgbh[i][j].blue=(-rgb[i-1][j-1].blue+rgb[i-1][j+1].blue-rgb[i][j-1].blue*2+
		rgb[i][j+1].blue*2-rgb[i+1][j-1].blue+rgb[i+1][j+1].blue) /4;
			rgbh[i][j].green=(-rgb[i-1][j-1].green+rgb[i-1][j+1].green-rgb[i][j-1].green*2+
		rgb[i][j+1].green*2-rgb[i+1][j-1].green+rgb[i+1][j+1].green) /4;
			rgbh[i][j].red=(-rgb[i-1][j-1].red+rgb[i-1][j+1].red-rgb[i][j-1].red*2+
		rgb[i][j+1].red*2-rgb[i+1][j-1].red+rgb[i+1][j+1].red) /4;
			//垂直模板 
			rgbv[i][j].blue=(-rgb[i-1][j-1].blue-rgb[i-1][j].blue*2-rgb[i-1][j+1].blue+
		rgb[i+1][j-1].blue+rgb[i+1][j].blue*2+rgb[i+1][j+1].blue) /4;
			rgbv[i][j].green=(-rgb[i-1][j-1].green-rgb[i-1][j].green*2-rgb[i-1][j+1].green+
		rgb[i+1][j-1].green+rgb[i+1][j].green*2+rgb[i+1][j+1].green) /4;
			rgbv[i][j].red=(-rgb[i-1][j-1].red-rgb[i-1][j].red*2-rgb[i-1][j+1].red+
		rgb[i+1][j-1].red+rgb[i+1][j].red*2+rgb[i+1][j+1].red) /4;
		
			//求梯度幅度 
			rgbout[i][j].blue=pow(rgbh[i][j].blue*rgbh[i][j].blue+rgbv[i][j].blue*rgbv[i][j].blue,0.5); 
			rgbout[i][j].green=pow(rgbh[i][j].green*rgbh[i][j].green+rgbv[i][j].green*rgbv[i][j].green,0.5); 
			rgbout[i][j].red=pow(rgbh[i][j].red*rgbh[i][j].red+rgbv[i][j].red*rgbv[i][j].red,0.5); 

			//梯度图像二值化 
			if(rgbout[i][j].blue+rgbout[i][j].green+rgbout[i][j].red>T)
			{
				rgbout[i][j].blue=255;
				rgbout[i][j].green=255;
				rgbout[i][j].red=255;
			}
			else
			{
				rgbout[i][j].blue=0;
				rgbout[i][j].green=0;
				rgbout[i][j].red=0;
			}
		}
	}
	
	//文件输出
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("文件打开失败！");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("输出Sobel算子求取边缘处理图像成功!!!\n");
	
	//关闭文件指针,释放内存
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

//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
int main()
{
	printf("ZMC'S期末考试程序开始执行!!!\n");
	printf("*************************\n");
	printf("执行1:将图像灰度化处理\n");
	Grey("ZMC.bmp","期末程序-图像灰度化处理.bmp"); 
	printf("图像灰度化处理完毕!!!\n");
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行2:将图像加边框处理\n");
	Add("ZMC.bmp","期末程序-图像加边框处理.bmp");
	printf("图像加边框处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行3:将图像马赛克处理\n");
	Mosaic("ZMC.bmp","期末程序-图像马赛克处理.bmp");
	printf("图像马赛克处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n"); 
	printf("执行4:将图像自定义平移处理\n");
	Move("ZMC.bmp","期末程序-图像自定义平移处理.bmp");
	printf("图像自定义平移处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行5:将图像自定义旋转处理\n");
	Revolve("ZMC.bmp","期末程序-图像自定义旋转处理.bmp");
	printf("图像自定义旋转处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行6:将图像自定义缩放处理\n");
	SF("ZMC.bmp","期末程序-图像自定义缩放处理.bmp");
	printf("图像自定义缩放处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行7:将图像直方图均衡处理\n");
	ZFTJHH("ZMC.bmp","期末程序-图像直方图均衡处理.bmp");
	printf("图像直方图均衡处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行8:将图像添加椒盐噪声处理\n");
	SaltPepper("ZMC.bmp","期末程序-图像椒盐噪声处理.bmp");
	printf("图像添加椒盐噪声处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行9:将图像中值滤波处理\n");
	Filter("ZMC.bmp","期末程序-图像中值滤波处理.bmp");
	printf("图像中值滤波处理完毕!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("执行10:将图像添加Sobel算子求取边缘处理\n");
	Sobel("ZMC.bmp","期末程序-图像Sobel算子求取边缘处理.bmp");
	printf("图像添加Sobel算子求取边缘处理完毕!!!\n"); 
	printf("*************************\n");
	printf("ZMC'S期末考试程序执行结束!!!\n");
	printf("欢迎下次继续使用本程序!!!\n");
	return 0; 
} 
