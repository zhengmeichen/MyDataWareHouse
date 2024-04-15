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

struct RGB24BIT //�������ؽṹ��,˳�������̺�
{	
	unsigned char blue;
	unsigned char green;
	unsigned char red;
}**rgb, **rgbout;

struct RGB24BIT1 //�������ؽṹ��,˳�������̺�
{	
	double blue;
	double green;
	double red;
}**rgbh, **rgbv;
//////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////
//����ɫBMPͼ��ҶȻ����� 
int Grey(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//��ԭͼ��Ϊ�Ҷ�ͼ
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
	
	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("����ҶȻ�ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ�����һ���߿򣬱߿�Ĵ�С������������ͱ߿���ɫ�ڳ�����ȷ�� 
int Add(char *in,char *out) 
{
	
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//��ԭͼ��Ϊ�ӱ߿��ͼ��
	int x;//width�����ϼӵı߿��� 
	int y;//height�����ϼӵı߿���
	printf("������Ҫ�ӵı߿��ȣ�\n");
	printf("width�����ϼӵı߿���:");
	scanf("%d",&x);
	printf("height�����ϼӵı߿���:");
	scanf("%d",&y); 
	
	//������ά��ָ̬�� 
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * (height+y+y));
	//������̬��ά����
	for (int i = 0 ; i < height+2*y ; i ++)
	{
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * (width+x+x));
	}
	
	//���ñ߿���ɫΪ��ɫRGB(255,255,0) 
	//�Ƚ�ͼ����չ�����ñ�����ɫ 
	for (int i = 0 ; i < height+2*y; i++)
	{
		for(int j=0;j< width+2*x;j++)
		{
			rgbout[i][j].red=255;
			rgbout[i][j].blue=0;
			rgbout[i][j].green=255;
		}
	}
	//���ͼ�� 
	for (int i = y ; i < height+y; i++)
	{
		for(int j=x ;j< width+x ;j++)
		{
			rgbout[i][j].red=rgb[i-y][j-x].red;
			rgbout[i][j].blue=rgb[i-y][j-x].blue;
			rgbout[i][j].green=rgb[i-y][j-x].green;
		}
	}

	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	//�����ļ�ͷ��С 
	ih.biWidth  = width +2*x;
	ih.biHeight = height+2*y;
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height+2*y; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width+2*x,pFout);
	}
	printf("����ӱ߿�ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ����������˴�������������С��Ϊ����
int Mosaic(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	printf("��������С��(����һ�μ��ɣ�x*x):\n");
	int x;
	scanf("%d",&x); 
	//x*x��ͼ�� 
	//��ͼ�������˴��� 
	int ii,jj; 
	for (int i = 0 ; i < height ;i+=x)
	{	
		ii=i;//����ȼ�i����һ������ͬʱ����ı�i���� 
		for(int j = 0 ; j < width ;j+=x)
		{
			jj=j;//����ȼ�j����һ������ͬʱ����ı�j����
			
			//��������е�R,G,Bֵ�ĺ�
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
			
			//��ͺ��ֵƽ����ÿ�������� 
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
	
	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("���������ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ����м��α任����ƽ��
int Move(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//��ͼ���Զ���ƽ�� 
	int x,y,m;
	printf("�����ֵ����Ϊ�Ǹ�������\n"); 
	printf("������ˮƽ�ƶ���ֵ����0-512��");
	scanf("%d",&x);
	printf("�����봹ֱ�ƶ���ֵ����0-512��");
	scanf("%d",&y);
	if(x<0||x>width||y<0||y>height) 
	{
		printf("����Ĳ���ֵ���ں���Χ\n");
		return 0; 
	}
	/*for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}*/
	//////////////////////////////////////
	//û��ƽ�� 
	if(x==0&&y==0)
	{
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ���ƽ��ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
	//����ƽ�� 
	else if(x==0&&y!=0)
	{
		printf("��ֱ����ѡ��1\n");
		printf("��ֱ����ѡ��2\n");
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
	
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ���ƽ��ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
	//����ƽ��  
	else if(x!=0&&y==0)
	{
		printf("ˮƽ����ѡ��1\n");
		printf("ˮƽ����ѡ��2\n");
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
		
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ���ƽ��ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
	//�Զ��� 
	else if(x!=0&&y!=0)
	{
		printf("������ѡ��1\n");
		printf("������ѡ��2\n");
		printf("������ѡ��3\n");
		printf("������ѡ��4\n");
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
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ���ƽ��ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ����м��α任������ת
int Revolve(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//�����ɫͼ�� 
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
	printf("������ת�ĽǶ�Ϊ�� ����תΪ��ʱ����ת��\n");
	scanf("%lf",&degree);
	degree=degree*pi/180;//�Ƕ�ת��Ϊ��Ӧ���� 
	
	//ͼ�����ĵ�λ��
	int x0=width/2;
	int y0=height/2;
	
	//��ת
	int x;
	int y; 
	int x1;
	int y1;
	
	int temp;
	printf("������Ҫ����ת����ʽ��\n");
	printf("ѡ��1������ת��Ŀ����ԭͼ\n");
	printf("ѡ��2��˫���Բ�ֵ����ת\n");
	scanf("%d",&temp);
	
	//����ת��Ŀ����ԭͼ
	//��ԭͼ�����ص���ֵ��������ת��ĸ���λ�õ����ص�.
	if(temp==1)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j<width;j++)
			{
				//Ŀ����ԭͼ
				x=j-x0;//����
				y=i-y0;//���� 
				x1=(int)(cos(degree)*x+sin(degree)*y)+x0;//���� 
				y1=(int)(cos(degree)*y-sin(degree)*x)+y0;//���� 
				//��ȡֵ
				if(x1>=0 && x1<width && y1>=0 && y1<height) //����������� 
				{
					rgbout[i][j].blue=rgb[y1][x1].blue;
					rgbout[i][j].green=rgb[y1][x1].green;
					rgbout[i][j].red=rgb[y1][x1].red;
				}
			}
		} 
		
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ�����תͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
	
	//˫���Բ�ֵ����ת
	if(temp==2)
	{
		for (int i = 0 ; i < height; i++)	
		{
			for(int j=0;j < width;j++)
			{
				x=j-x0;//����
				y=i-y0;//���� 
				
				double xx;
				double yy;
				
				xx=(double)(cos(degree)*x+sin(degree)*y)+x0;//���� 
				yy=(double)(cos(degree)*y-sin(degree)*x)+y0;//���� 
				
				int xi;
				int yi;
				
				xi=(int)xx;//ȡ�� 
				yi=(int)yy;//ȡ�� 
				
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
				
				//˫���Բ�ֵ
				rgbout[i][j].blue=(unsigned char)(rgb[yi][xi].blue*(1-xs)*(1-ys)+rgb[yyy][xi].blue*(1-xs)*ys+rgb[yi][xxx].blue*xs*(1-ys)+rgb[yyy][xxx].blue*xs*ys);
				rgbout[i][j].green=(unsigned char)(rgb[yi][xi].green*(1-xs)*(1-ys)+rgb[yyy][xi].green*(1-xs)*ys+rgb[yi][xxx].green*xs*(1-ys)+rgb[yyy][xxx].green*xs*ys);
				rgbout[i][j].red=(unsigned char)(rgb[yi][xi].red*(1-xs)*(1-ys)+rgb[yyy][xi].red*(1-xs)*ys+rgb[yi][xxx].red*xs*(1-ys)+rgb[yyy][xxx].red*xs*ys);
				
				
			}
		} 
		
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < height; i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
		}
		printf("����Զ�����תͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ����м��α任�������� 
int SF(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	/*//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}*/ 
	
	int type;
	printf("ѡ�����ڽ���ֵ���Ŵ���������:1\n");
	printf("ѡ��˫���Բ�ֵ�����Ŵ��������룺2\n");
	scanf("%d",&type);
	
	//���ڽ���ֵ���Ŵ���
	if(type==1)
	{
		//�������ű��� 
		double Sx,Sy;
		printf("���ѣ������·���������ʱ�����ݵķ�Χȷ���ڡ�0.5��3��֮��!!!\n");
		printf("������ˮƽ���ű�����\n");
		scanf("%lf",&Sx);
		printf("�����봹ֱ���ű�����\n");
		scanf("%lf",&Sy);
		
		//���붯̬�洢�ռ� 
		rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		
		//������̬��ά����
		for (int i = 0 ; i < height ; i ++)
		{
			rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}
		
		//��ȡͼ������ 
		for (int i = 0 ; i < height ; i++)
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
		
		//���ͼ��ֱ��� 
		int out_height=Sy*height;
		int outwidth=Sx*width; 
		
		//�����ͼ�����ݵ�out_width��Ϊ4�ı���
		int out_width= (outwidth+3)/4*4;
		
		//����洢�ռ�
		rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * out_height); 
		
		for(int i=0;i<out_height;i++)
		{
			rgbout[i]= (RGB24BIT *)malloc(sizeof(RGB24BIT*) * out_width);
		}
		 
		double xx;    	//ӳ���x 
		double yy;    	//ӳ���y
		int xxx;		//ӳ���x���������� 
		int yyy;		//ӳ���y���������� 
		int x1;			//xxxx+1
		int y1;			//yyy+1
		double xs=0;	
		double ys=0; 
		
		//����
		for(int i=0;i<out_height;i++)
		{
			for(int j=0;j<out_width;j++)
			{
				//��ӳ������
				xx=1/Sy*i;
				yy=1/Sx*j;
				//ȡӳ�����������
				xxx=(int)xx;
				yyy=(int)yy;
				//˫���Բ�ֵ
				xs=xx-xxx;
				ys=yy-yyy;
				
				x1=xxx+1;
				y1=yyy+1;
				//��Ե�㴦��
				if((xxx+1)>(height-1)) 
				{
					x1=xxx-1;
				}
				if((xxx+1)>(width-1)) 
				{
					y1=yyy-1;
				}
				//���ڽ���ֵ
				rgbout[i][j].blue=rgb[xxx][yyy].blue;
				rgbout[i][j].green=rgb[xxx][yyy].green;
				rgbout[i][j].red=rgb[xxx][yyy].red; 
			}
		}
		ih.biWidth=out_width;
		ih.biHeight=out_height;
		fh.bfSize=54+out_width*out_height*3;
		
		
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("����Զ�������ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
	
	//˫���Բ�ֵ�����Ŵ���	
	if(type==2)
	{
		//�������ű��� 
		double Sx,Sy;
		printf("���ѣ������·���������ʱ�����ݵķ�Χȷ���ڡ�0.5��3��֮��!!!\n");
		printf("������ˮƽ���ű�����\n");
		scanf("%lf",&Sx);
		printf("�����봹ֱ���ű�����\n");
		scanf("%lf",&Sy);
		
		//���붯̬�洢�ռ� 
		rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		//rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		//������̬��ά����
		for (int i = 0 ; i < height ; i ++)
		{
			rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
			//rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}
		
		//��ȡͼ������ 
		for (int i = 0 ; i < height ; i++)
		{
			fread(rgb[i], sizeof(RGB24BIT), width, pFin);
		}
		
		//���ͼ��ֱ��� 
		int out_height=Sy*height;
		int outwidth=Sx*width; 
		
		//�����ͼ�����ݵ�out_width��Ϊ4�ı���
		int out_width= (outwidth+3)/4*4;
		
		//����洢�ռ�
		rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * out_height); 
		for(int i=0;i<out_height;i++)
		{
			rgbout[i]= (RGB24BIT *)malloc(sizeof(RGB24BIT*) * out_width);
		}

		double xx;    	//ӳ���x 
		double yy;    	//ӳ���y
		int xxx;		//ӳ���x���������� 
		int yyy;		//ӳ���y���������� 
		int x1;			//xxx+1
		int y1;			//yyy+1
		double xs=0;	
		double ys=0; 

		//����
		for(int i=0;i<out_height;i++)
		{
			for(int j=0;j<out_width;j++)
			{
				//��ӳ������
				xx=1/Sy*i;
				yy=1/Sx*j;
				//ȡӳ�����������
				xxx=(int)xx;
				yyy=(int)yy;
				//˫���Բ�ֵ
				xs=xx-xxx;
				ys=yy-yyy;
				
				x1=xxx+1; 
				y1=yyy+1;
				//��Ե�㴦��
				if((xxx+1)>(height-1)) 
				{
					x1=xxx-1;
				}
				if((xxx+1)>(width-1)) 
				{
					y1=yyy-1;
				}
				//˫���Բ�ֵ
				rgbout[i][j].blue=(unsigned char)(rgb[xxx][yyy].blue*(1-xs)*(1-ys)+rgb[xxx][y1].blue*(1-xs)*ys+rgb[x1][yyy].blue*xs*(1-ys)+rgb[x1][y1].blue*xs*ys);
				rgbout[i][j].green=(unsigned char)(rgb[xxx][yyy].green*(1-xs)*(1-ys)+rgb[xxx][y1].green*(1-xs)*ys+rgb[x1][yyy].green*xs*(1-ys)+rgb[x1][y1].green*xs*ys);
				rgbout[i][j].red=(unsigned char)(rgb[xxx][yyy].red*(1-xs)*(1-ys)+rgb[xxx][y1].red*(1-xs)*ys+rgb[x1][yyy].red*xs*(1-ys)+rgb[x1][y1].red*xs*ys);
			}
		}
		
		ih.biWidth=out_width;
		ih.biHeight=out_height;
		fh.bfSize=54+out_width*out_height*3;
		
		//�ļ����
		FILE *pFout;
		pFout = fopen(out,"wb");
		if(pFout==NULL)
		{
			printf("�ļ���ʧ�ܣ�");
			return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("����Զ�������ͼ��ɹ�!!!\n");
		
		//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ�����Աȶ���ǿ����ֱ��ͼ���⴦��
int ZFTJHH(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//ͳ�Ƹ��Ҷ���Ϣ 
	int count[256]={0};
	
	//ͼ��ҶȻ� 
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
	
	//ֱ��ͼ���⻯
	double Pi[256]={0};  //ԭʼͼ��ֱ��ͼ
	double Pj[256]={0};	 //�ۻ�ֱ��ͼ
	
	int sum=ih.biWidth*ih.biHeight;
	
	//����ԭʼֱ��ͼ
	for(int i=0;i<256;i++)
	{
		Pi[i]=1.00*count[i]/sum;
	} 

	
	//�����ۻ�ֱ��ͼ
	for(int i=0;i<256;i++)
	{
		for(int j=0;j<=i;j++)
		{ 
			Pj[i]+=Pi[j];
		}
	} 
	
	//����任��ĻҶ�ֵ 
	unsigned char after[256]={0};
	for(int i=0;i<256;i++)
	{
		after[i]=(int)(255 * Pj[i] + 0.5);	
	}
	
	//ȷ���Ҷȱ任��ϵ
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
		
	//������⻯��ͼ��
    FILE *pFout = fopen(out,"wb");
    if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i], sizeof(RGB24BIT), width, pFout);
	}
	printf("���ֱ��ͼ���⻯ͼ��ɹ�!!!\n");  
	
	//�ͷ�ָ����ڴ�ռ� 
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
//��ͼ����뽷������
int SaltPepper(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
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
	//��ͼ����ӽ������� 
	double SNR;
	//���������
	printf("���������SNR��SNR�ķ�Χ��0-1������\n");
	scanf("%lf",&SNR);
	srand((unsigned)time(NULL));
	 
	unsigned char temp;
	
	//������������������Ϊ height*width*(1-SNR)
	for(int i=0;i<height*sqrt(1-SNR);i++)
	{
		for(int j=0;j<width*sqrt(1-SNR);j++)
		{
			temp=(rand()%2)*255;//����Ϊ0��tempΪ0������Ϊ1��tempΪ255�� 
			//temp��ֵΪ0Ϊ��������temp��ֵΪ255Ϊ������
			int RandomH=rand()%height;//���������� 
			int RandomW=rand()%width;//����������  
			rgbout[RandomH][RandomW].blue=temp;
			rgbout[RandomH][RandomW].green=temp;
			rgbout[RandomH][RandomW].red=temp;
		}
	} 
	
	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("�����������ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
//�Լ��뽷��������ͼ�������ֵ�˲�����
int Filter(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	
	//��ȡͼ��
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
	//��ͼ����ӽ������� 
	double SNR;
	//���������
	printf("���������SNR��SNR�ķ�Χ��0-1������\n");
	scanf("%lf",&SNR);
	srand((unsigned)time(NULL));
	 
	unsigned char temp;
	
	//������������������Ϊ height*width*(1-SNR)
	for(int i=0;i<height*sqrt(1-SNR);i++)
	{
		for(int j=0;j<width*sqrt(1-SNR);j++)
		{
			temp=(rand()%2)*255;//����Ϊ0��tempΪ0������Ϊ1��tempΪ255�� 
			//temp��ֵΪ0Ϊ��������temp��ֵΪ255Ϊ������
			int RandomH=rand()%height;//���������� 
			int RandomW=rand()%width;//����������  
			rgbout[RandomH][RandomW].blue=temp;
			rgbout[RandomH][RandomW].green=temp;
			rgbout[RandomH][RandomW].red=temp;
		}
	} 
	
	//����ӽ���������ͼ�񣬽�����ֵ�˲����� 
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
	
	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("�����ֵ�˲�����ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
//��ͼ��ͨ��Sobel������ȡ��Ե
int Sobel(char *in,char *out) 
{
	//�����ļ�ָ��  
	FILE *pFin;	
	//��ȡ�ļ�		
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	//�����ļ�ͷ
	BITMAPFILEHEADER fh;
	//��ȡ�ļ�ͷ
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	//������Ϣͷ
	BITMAPINFOHEADER ih;
	//��ȡ��Ϣͷ
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	//������ά��ָ̬�� 
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbv = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
	rgbh = (RGB24BIT1 **)malloc(sizeof(RGB24BIT1*) * height);
	
	//������̬��ά����
	for (int i = 0 ; i < height ; i ++)
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbv[i]	= (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
		rgbh[i]	= (RGB24BIT1*)malloc(sizeof(RGB24BIT1) * width);
	}
	
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
	//Sobel���Ӵ���ͼ�� 
	double T;
	printf("��������ֵTΪ��\n");
	scanf("%lf",&T);
	//���ۣ�T��120-150֮�䣬ͼ��Ч�����
	
	for (int i = 1; i < height - 1; i ++)
	{
		for (int j = 1; j < width - 1; j ++)
		{
			//ˮƽģ�� 
			rgbh[i][j].blue=(-rgb[i-1][j-1].blue+rgb[i-1][j+1].blue-rgb[i][j-1].blue*2+
		rgb[i][j+1].blue*2-rgb[i+1][j-1].blue+rgb[i+1][j+1].blue) /4;
			rgbh[i][j].green=(-rgb[i-1][j-1].green+rgb[i-1][j+1].green-rgb[i][j-1].green*2+
		rgb[i][j+1].green*2-rgb[i+1][j-1].green+rgb[i+1][j+1].green) /4;
			rgbh[i][j].red=(-rgb[i-1][j-1].red+rgb[i-1][j+1].red-rgb[i][j-1].red*2+
		rgb[i][j+1].red*2-rgb[i+1][j-1].red+rgb[i+1][j+1].red) /4;
			//��ֱģ�� 
			rgbv[i][j].blue=(-rgb[i-1][j-1].blue-rgb[i-1][j].blue*2-rgb[i-1][j+1].blue+
		rgb[i+1][j-1].blue+rgb[i+1][j].blue*2+rgb[i+1][j+1].blue) /4;
			rgbv[i][j].green=(-rgb[i-1][j-1].green-rgb[i-1][j].green*2-rgb[i-1][j+1].green+
		rgb[i+1][j-1].green+rgb[i+1][j].green*2+rgb[i+1][j+1].green) /4;
			rgbv[i][j].red=(-rgb[i-1][j-1].red-rgb[i-1][j].red*2-rgb[i-1][j+1].red+
		rgb[i+1][j-1].red+rgb[i+1][j].red*2+rgb[i+1][j+1].red) /4;
		
			//���ݶȷ��� 
			rgbout[i][j].blue=pow(rgbh[i][j].blue*rgbh[i][j].blue+rgbv[i][j].blue*rgbv[i][j].blue,0.5); 
			rgbout[i][j].green=pow(rgbh[i][j].green*rgbh[i][j].green+rgbv[i][j].green*rgbv[i][j].green,0.5); 
			rgbout[i][j].red=pow(rgbh[i][j].red*rgbh[i][j].red+rgbv[i][j].red*rgbv[i][j].red,0.5); 

			//�ݶ�ͼ���ֵ�� 
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
	
	//�ļ����
	FILE *pFout;
	pFout = fopen(out,"wb");
	if(pFout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	fwrite(&fh,sizeof(fh),1,pFout);
	fwrite(&ih,sizeof(ih),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgbout[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("���Sobel������ȡ��Ե����ͼ��ɹ�!!!\n");
	
	//�ر��ļ�ָ��,�ͷ��ڴ�
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
	printf("ZMC'S��ĩ���Գ���ʼִ��!!!\n");
	printf("*************************\n");
	printf("ִ��1:��ͼ��ҶȻ�����\n");
	Grey("ZMC.bmp","��ĩ����-ͼ��ҶȻ�����.bmp"); 
	printf("ͼ��ҶȻ��������!!!\n");
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��2:��ͼ��ӱ߿���\n");
	Add("ZMC.bmp","��ĩ����-ͼ��ӱ߿���.bmp");
	printf("ͼ��ӱ߿������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��3:��ͼ�������˴���\n");
	Mosaic("ZMC.bmp","��ĩ����-ͼ�������˴���.bmp");
	printf("ͼ�������˴������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n"); 
	printf("ִ��4:��ͼ���Զ���ƽ�ƴ���\n");
	Move("ZMC.bmp","��ĩ����-ͼ���Զ���ƽ�ƴ���.bmp");
	printf("ͼ���Զ���ƽ�ƴ������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��5:��ͼ���Զ�����ת����\n");
	Revolve("ZMC.bmp","��ĩ����-ͼ���Զ�����ת����.bmp");
	printf("ͼ���Զ�����ת�������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��6:��ͼ���Զ������Ŵ���\n");
	SF("ZMC.bmp","��ĩ����-ͼ���Զ������Ŵ���.bmp");
	printf("ͼ���Զ������Ŵ������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��7:��ͼ��ֱ��ͼ���⴦��\n");
	ZFTJHH("ZMC.bmp","��ĩ����-ͼ��ֱ��ͼ���⴦��.bmp");
	printf("ͼ��ֱ��ͼ���⴦�����!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��8:��ͼ����ӽ�����������\n");
	SaltPepper("ZMC.bmp","��ĩ����-ͼ������������.bmp");
	printf("ͼ����ӽ��������������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��9:��ͼ����ֵ�˲�����\n");
	Filter("ZMC.bmp","��ĩ����-ͼ����ֵ�˲�����.bmp");
	printf("ͼ����ֵ�˲��������!!!\n"); 
	printf("/////////////////////////\n");
	printf("/////////////////////////\n");
	printf("ִ��10:��ͼ�����Sobel������ȡ��Ե����\n");
	Sobel("ZMC.bmp","��ĩ����-ͼ��Sobel������ȡ��Ե����.bmp");
	printf("ͼ�����Sobel������ȡ��Ե�������!!!\n"); 
	printf("*************************\n");
	printf("ZMC'S��ĩ���Գ���ִ�н���!!!\n");
	printf("��ӭ�´μ���ʹ�ñ�����!!!\n");
	return 0; 
} 
