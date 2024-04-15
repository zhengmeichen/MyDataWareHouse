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
	int type;
	printf("请输入变换类型：\n");
	printf("1:图像水平左移\n");
	printf("2:图像水平右移\n");
	printf("3:图像垂直上移\n");
	printf("4:图像垂直下移\n");
	printf("5:图像自定义移动\n");
	scanf("%d",&type);
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//创建动态二维数组
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	//读取图像
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
///////////////////////////////////////////////////////////////////////////
//图像水平左移
	if (type == 1)
	{
		//rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		int x;
		printf("请输入移动的值：");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("输入的参数值不在合理范围\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//创建动态二维数组
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < height ; i++)
		{
			for (int j = 0; j < width-x; j++)
			{
				rgbout[i][j]=rgb[i][x+j];
			}
		}
		FILE *pFout = fopen("水平左移.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}
	
////////////////////////////////////////////////////////////////////////////////////
//图像水平右移	
	else if(type == 2)
	{
		int x;
		printf("请输入移动的值：");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("输入的参数值不在合理范围\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//创建动态二维数组
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < height ; i++)
		{
			for (int j = 0; j < width-x; j++)
			{
				rgbout[i][j+x]=rgb[i][j];
			}
		}
		FILE *pFout = fopen("水平右移.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}

//////////////////////////////////////////////////////////////////////////////
//图像垂直上移		
	else if (type == 3)
	{
		int x;
		printf("请输入移动的值：");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("输入的参数值不在合理范围\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//创建动态二维数组
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < width ; i++)
		{
			for (int j = 0; j < height-x; j++)
			{
				rgbout[j+x][i]=rgb[j][i];
			}
		}
		FILE *pFout = fopen("垂直上移.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}
	
///////////////////////////////////////////////////////////////////////////////////
//图像垂直下移	
	else if (type == 4)
	{
		int x;
		printf("请输入移动的值：");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("输入的参数值不在合理范围\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//创建动态二维数组
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < width ; i++)
		{
			for (int j = 0; j < height-x; j++)
			{
				rgbout[j][i]=rgb[j+x][i];
			}
		}
		FILE *pFout = fopen("垂直下移.bmp","wb");
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < width; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
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
	
///////////////////////////////////////////////////////////////////////////////////
//图像自定义移动		
	else if (type == 5)
	{
		int x,y,m;
		printf("请输入水平移动的值：");
		scanf("%d",&x);
		printf("请输入垂直移动的值：");
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
			FILE *pFout = fopen("自定义平移.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < height; i++)
			{
				fwrite(rgb[i], sizeof(RGB24BIT), width, pFout);
			}
			printf("输出图片成功!"); 
			fclose(pFout);
			//释放指针的内存空间 
			for (int i = 0 ; i<height ;i++)
			{
				free(rgb[i]);
			}
			free(rgb);
			free(rgbout);
			fclose(pFin);
			return 0;
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
			////////输出图像 
			FILE *pFout = fopen("自定义平移.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
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
			////////输出图像 
			FILE *pFout = fopen("自定义平移.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
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
			////////输出图像 
			FILE *pFout = fopen("自定义平移.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
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
	}
	return 0; 
}
