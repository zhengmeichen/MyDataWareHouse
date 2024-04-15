#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<math.h>
 
#include<fstream>

#pragma pack(1)

using namespace std;

//定义像素结构体,顺序是蓝绿红
struct RGB24BIT
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
	
	//获得图像的最大灰度值与最小灰度值
	int MAXGray=0;
	int MINGray=255;
	int temp;
	//灰度化 
	for (int i = 0 ; i < height ; i++) 
	{
		for (int j = 0 ; j < width ; j++)
		{
			unsigned char temp=(rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgbout[i][j].blue=temp;
			rgbout[i][j].green=temp;
			rgbout[i][j].red=temp;
			if(temp<MINGray)//MINGray==a
			{
				MINGray=temp;
			} 
			if(temp>MAXGray)//MAXGray==b
			{
				MAXGray=temp;
			}  
		} 
	}
	printf("图像的最小灰度值为：MINGray=%d\n",MINGray);
	printf("图像的最大灰度值为：MAXGray=%d\n",MAXGray);
	 

	int type;
	printf("对图像做线性变换对比度增强  请输入1：\n");
	printf("对图像做非线性对比度增强 请输入2：\n");
	scanf("%d",&type);
	 
	if(type==1)
	{
		int m;
		printf("第一种情况拉伸或缩小,请选择1：\n"); 
		printf("第二种情况平移变暗,请选择2：\n");
		printf("第三种情况平移变亮,请选择3：\n");
		scanf("%d",&m);
		
		
		//拉伸的动态范围：x<MINGray  y>MAXGray
		//缩小的动态范围：x>MINGray  y<MAXGray
		switch(m)
		{
			
			
			case(1):
			
				double x;
				double y;
				printf("请输入拉伸或缩小动态范围：\n");
				scanf("%lf%lf",&x,&y);
				double z;
			
				//拉伸 
				if(x < MINGray && y > MAXGray)
				{
					for (int i = 0 ; i < height ; i++) 
					{
						for (int j = 0 ; j < width ; j++)
						{ 
							if(rgb[i][j].blue< 0)
							{
								temp = 0;
							} 
							else if(rgb[i][j].blue>= 0 && rgb[i][j].blue<= MINGray)
							{
								z=x;
								temp=(int)z; 
							}
							else if(rgb[i][j].blue>=MAXGray && rgb[i][j].blue<= 255)
							{
								z=y;
								temp=(int)z;
							}
							else if(rgb[i][j].blue > 255)
							{
								temp = 255;
							}
							else
							{
								z=(double) ((y - x) / (MAXGray - MINGray) * (rgb[i][j].blue - MINGray)) + x;
								temp=(int)z;
								if(temp > 255)
								{
									temp = 255;
								}	
							}
							rgbout[i][j].blue = temp;
							rgbout[i][j].green = temp;
							rgbout[i][j].red = temp;			
						} 
					}
				}
				
			
				//缩小
				if(x > MINGray && y < MAXGray)
				{
					for (int i = 0 ; i < height ; i++) 
					{
						for (int j = 0 ; j < width ; j++)
						{ 
							if(rgb[i][j].blue< 0)
							{
								temp = 0;
							} 
							else if(rgb[i][j].blue>=0 && rgb[i][j].blue<=MINGray)
							{
								z=x;
								temp=(int)z; 
							}
							else if(rgb[i][j].blue>=MAXGray && rgb[i][j].blue<=255)
							{
								z=y;
								temp=(int)z;
							}
							else if(rgb[i][j].blue > 255)
							{
								temp = 255;
							}
							else
							{
								temp = (double) (y - x) / (MAXGray - MINGray) * (rgb[i][j].blue - MINGray) + x;
								if(temp > 255)
								{
									temp = 255;
								}	
							}
							rgbout[i][j].blue = temp;
							rgbout[i][j].green = temp;
							rgbout[i][j].red = temp;			
						} 
					}
				}
				
				break;
/////////////////////////////////////////////////////////////////////////////////////	
			case(2):
				//图像平移变暗，减一个数值
				for (int i = 0 ; i < height ; i++) 
				{
					for (int j = 0 ; j < width ; j++)
					{
						temp=rgb[i][j].blue-50;
						if(temp<0)
						{
							temp=0;
						} 
						rgbout[i][j].blue=temp;
						rgbout[i][j].green=temp;
						rgbout[i][j].red=temp;
					} 
				} 
				break;	
/////////////////////////////////////////////////////////////////////////////////////
			case(3):
				//图像平移变亮，加一个数值 
				for (int i = 0 ; i < height ; i++) 
				{
					for (int j = 0 ; j < width ; j++)
					{
						temp=rgb[i][j].blue+90;
						if(temp>255)
						{
							temp=255;
						} 
						rgbout[i][j].blue=temp;
						rgbout[i][j].green=temp;
						rgbout[i][j].red=temp;
					} 
				} 
				break;			   
		}

	} 
	
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////

	if(type==2)
	{
		//对图像做非线性对比度增强，指数变换对比度增强
		//指数变换  r>1  r<1
		double r;
		printf("请输入图像做指数变换的参数：\n");
		scanf("%lf",&r);
		if(r==0)
		{
			printf("输入参数有误！"); 
			return 0;
		}
		else
		{
			for (int i = 0 ; i < height ; i++) 
			{
				for (int j = 0 ; j < width ; j++)
				{
					temp=pow((double)rgb[i][j].blue/255,r)*255+0.5;
					rgbout[i][j].blue=temp;
					rgbout[i][j].green=temp;
					rgbout[i][j].red=temp;
				}  
			}  
		}
	} 
	
	
	//输出文件
	FILE *pFout;
	pFout = fopen("Contrast Enhancement.bmp","wb");	
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
	printf("输出图片成功!程序运行已结束！\n"); 
	
	
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
