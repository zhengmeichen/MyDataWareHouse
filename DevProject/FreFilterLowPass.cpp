#include <stdio.h>
#include <math.h>
#include <malloc.h>
#include <Windows.h>
#include "FFTNEW.h"

typedef struct RGB24BIT
{	//�������ؽṹ��,˳�������̺�
	unsigned char blue;
	unsigned char green;
	unsigned char red;
};

double H(double D,double D0)
{	//���ش��ݺ�����ֵ
	return 1.0/(1 + (D/D0)*(D/D0));
}

double H1(double D,double D0)
{	//���ش��ݺ�����ֵ
	return 1.0/(1 + (D0/D)*(D0/D));
}

int low_pass_filter(char *in , char *out)
{
	FILE *pFin,*pFout;												//�����ļ�ָ�� 
	BITMAPFILEHEADER bfile;											//�����ļ�ͷ
	BITMAPINFOHEADER binfo;											//������Ϣͷ
	pFin=fopen(in,"rb");											//��ȡ�ļ�

	if(!pFin)
	{	//�ж��ļ��Ƿ�򿪳ɹ�
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////ͼ����Ϣ�Ķ�ȡ/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//��ȡ�ļ�ͷ
	fread(&binfo,sizeof(binfo),1,pFin);									//��ȡ��Ϣͷ
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//���������ļ���άָ��
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//��ָ�붯̬�����ڴ�
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//��ȡͼ��
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////�����ά��������///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////ͼ���Ԥ�����ҶȻ����͸�������Ĵ���/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//��ԭͼ��Ϊ�Ҷ�ͼ
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//����ͬʱ��ֵ����ʵ��
			arr[i][j].y=0;		//�鲿����Ϊ0
		}
	}

	/////////////////////////////����Ҷ�任//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////��ͨ�˲�����/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//��ͨ�˲�
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
	
	////////////////////////////����Ҷ���任��ȥ/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////���õ��ĸ�������任��ͼ��///////////////////////////////////
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
	//////////////////////////////////�ļ����//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("��������ͨ�˲�ͼ��ɹ�!!!\n");
	///////////////////////////////////////////�ر��ļ�ָ��,�ͷ��ڴ�////////////////////////////
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
	FILE *pFin,*pFout;												//�����ļ�ָ�� 
	BITMAPFILEHEADER bfile;											//�����ļ�ͷ
	BITMAPINFOHEADER binfo;											//������Ϣͷ
	pFin=fopen(in,"rb");											//��ȡ�ļ�

	if(!pFin)
	{	//�ж��ļ��Ƿ�򿪳ɹ�
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////ͼ����Ϣ�Ķ�ȡ/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//��ȡ�ļ�ͷ
	fread(&binfo,sizeof(binfo),1,pFin);									//��ȡ��Ϣͷ
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//���������ļ���άָ��
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//��ָ�붯̬�����ڴ�
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//��ȡͼ��
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////�����ά��������///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////ͼ���Ԥ�����ҶȻ����͸�������Ĵ���/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//��ԭͼ��Ϊ�Ҷ�ͼ
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//����ͬʱ��ֵ����ʵ��
			arr[i][j].y=0;		//�鲿����Ϊ0
		}
	}

	/////////////////////////////����Ҷ�任//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////Butterworth��ͨ�˲�����/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//Butterworth��ͨ�˲�
		for (int j = 0 ; j < width ;j++)
		
		{
			double tmp = H(sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)),0.1*width);
			arr[i][j].x *= tmp;
			arr[i][j].y *= tmp;
		}
	}
	
	////////////////////////////����Ҷ���任��ȥ/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////���õ��ĸ�������任��ͼ��///////////////////////////////////
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
	//////////////////////////////////�ļ����//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("���Butterworth��ͨ�˲�ͼ��ɹ�!!!\n");
	///////////////////////////////////////////�ر��ļ�ָ��,�ͷ��ڴ�////////////////////////////
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
	FILE *pFin,*pFout;												//�����ļ�ָ�� 
	BITMAPFILEHEADER bfile;											//�����ļ�ͷ
	BITMAPINFOHEADER binfo;											//������Ϣͷ
	pFin=fopen(in,"rb");											//��ȡ�ļ�

	if(!pFin)
	{	//�ж��ļ��Ƿ�򿪳ɹ�
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////ͼ����Ϣ�Ķ�ȡ/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//��ȡ�ļ�ͷ
	fread(&binfo,sizeof(binfo),1,pFin);									//��ȡ��Ϣͷ
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//���������ļ���άָ��
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//��ָ�붯̬�����ڴ�
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//��ȡͼ��
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////�����ά��������///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////ͼ���Ԥ�����ҶȻ����͸�������Ĵ���/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//��ԭͼ��Ϊ�Ҷ�ͼ
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//����ͬʱ��ֵ����ʵ��
			arr[i][j].y=0;		//�鲿����Ϊ0
		}
	}

	/////////////////////////////����Ҷ�任//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////��ͨ�˲�����/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//��ͨ�˲�
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
	
	////////////////////////////����Ҷ���任��ȥ/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////���õ��ĸ�������任��ͼ��///////////////////////////////////
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
	//////////////////////////////////�ļ����//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("��������ͨ�˲�ͼ��ɹ�!!!\n");
	///////////////////////////////////////////�ر��ļ�ָ��,�ͷ��ڴ�////////////////////////////
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
	FILE *pFin,*pFout;												//�����ļ�ָ�� 
	BITMAPFILEHEADER bfile;											//�����ļ�ͷ
	BITMAPINFOHEADER binfo;											//������Ϣͷ
	pFin=fopen(in,"rb");											//��ȡ�ļ�

	if(!pFin)
	{	//�ж��ļ��Ƿ�򿪳ɹ�
		printf("Open file error!!\n"); 
		return -1;
	}
	//////////////////////////////ͼ����Ϣ�Ķ�ȡ/////////////////////////////////////////

	fread(&bfile,sizeof(bfile),1,pFin);									//��ȡ�ļ�ͷ
	fread(&binfo,sizeof(binfo),1,pFin);									//��ȡ��Ϣͷ
	int height = binfo.biHeight;
	int width = binfo.biWidth;

	RGB24BIT **rgb;														//���������ļ���άָ��
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);				//��ָ�붯̬�����ڴ�
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		rgb[i] = (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	for (int i = 0 ; i < height ; i++)
	{	//��ȡͼ��
		fread(rgb[i], sizeof(RGB24BIT),width,pFin);
	}
	//////////////////////////////�����ά��������///////////////////////////////////////
	Complex **arr;
	arr=(Complex **)malloc(sizeof(Complex*)*height);
	for (int i = 0 ; i < height ; i ++)
	{	//������̬��ά����
		arr[i] = (Complex *)malloc(sizeof(Complex) * width);
	}
	//////////////////////////////ͼ���Ԥ�����ҶȻ����͸�������Ĵ���/////////////////////
	for (int i = 0 ; i < height ;i++)
	{	//��ԭͼ��Ϊ�Ҷ�ͼ
		for(int j = 0 ; j < width ;j++)
		{
			unsigned char temp = (rgb[i][j].blue+rgb[i][j].green+rgb[i][j].red)/3;
			rgb[i][j].blue=temp;
			rgb[i][j].green=temp;
			rgb[i][j].red=temp;
			arr[i][j].x=temp;	//����ͬʱ��ֵ����ʵ��
			arr[i][j].y=0;		//�鲿����Ϊ0
		}
	}

	/////////////////////////////����Ҷ�任//////////////////////////////////////////////////

	fft_center(arr,height,width,1);

	/////////////////////////////Butterworth��ͨ�˲�����/////////////////////////////////////////////////
	for (int i = 0 ; i < height ; i++)
	{	//Butterworth��ͨ�˲�
		for (int j = 0 ; j < width ;j++)
		
		{
			double tmp = H1(sqrt(pow(height/2.0 - i , 2)+pow(width/2.0 - j , 2)),0.02*width);
			arr[i][j].x *= tmp;
			arr[i][j].y *= tmp;
		}
	}
	
	////////////////////////////����Ҷ���任��ȥ/////////////////////////////////////////////

	fft_center(arr,height,width,-1);

	////////////////////////////���õ��ĸ�������任��ͼ��///////////////////////////////////
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
	//////////////////////////////////�ļ����//////////////////////////////////////////////////
	pFout = fopen(out,"wb");
	fwrite(&bfile,sizeof(bfile),1,pFout);
	fwrite(&binfo,sizeof(binfo),1,pFout);
	for (int i = 0 ; i < height; i++)
	{
		fwrite(rgb[i],sizeof(RGB24BIT),width,pFout);
	}
	printf("���Butterworth��ͨ�˲�ͼ��ɹ�!!!\n");
	///////////////////////////////////////////�ر��ļ�ָ��,�ͷ��ڴ�////////////////////////////
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
	low_pass_filter("ZMC.bmp","�����ͨ�˲�.bmp");
	low_pass_Butterworth("ZMC.bmp","Butterworth��ͨ�˲�.bmp");
	high_pass_filter("ZMC.bmp","�����ͨ�˲�.bmp");
	high_pass_Butterworth("ZMC.bmp","Butterworth��ͨ�˲�.bmp");
	return 0;		
}


