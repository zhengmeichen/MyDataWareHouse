#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<fstream>

#pragma pack(1)

using namespace std;
struct RGB24BIT//�������ؽṹ��,˳�������̺�
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
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	//�ļ�ͷ����Ϣͷ 
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//������̬��ά����
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}

	for (int i = 0 ; i < height ; i++)//��ȡͼ�� 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}

	//�ı��1��,�ı��50��51�У��ı����2�� 
	for(int i=0;i<width;i++)
	{
		//�ı��1�У���� 
		rgb[511][i].red=255;
		rgb[511][i].blue=0;
		rgb[511][i].green=0;
		
		//�ı��50��51�У���� 
		rgb[511-50][i].red=0;
		rgb[511-50][i].blue=0;
		rgb[511-50][i].green=0;
		rgb[511-51][i].red=0;
		rgb[511-51][i].blue=0;
		rgb[511-51][i].green=0;
		
		//�ı����2��,��� 
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
	printf("���ͼ��ɹ�!\n");
	//�ر��ļ� 
	fclose(pFin);
	fclose(pFout);
	
	//�ͷ�ָ�� 
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
		printf("256�ļ���ʧ�ܣ�");
		return 0;
	}
	//256��ɫ��
	RGB24BIT*rgb256; 
	rgb256 = (RGB24BIT*)malloc(sizeof(RGB24BIT*) * height);
	//ͷ��Ϣ����ı䣬ֱ������ 
	fseek(pFin256,54,SEEK_SET);
	 
	fread(rgb256, sizeof(RGB24BIT), width, pFin256);
	
	//ͼ����������ָ�� 
	unsigned char ** data256;
	data256=(unsigned char**)malloc(sizeof(unsigned char*)*height);
	
	for (int i = 0 ; i < height ; i ++)//������̬��ά����
	{
		data256[i]= (unsigned char*)malloc(sizeof(unsigned char)* width);
	}
	//������ȡ
	for (int i = 0 ; i < height ; i ++)//��ȡͼ�� 
	{
		fread(data256[i],sizeof(unsigned char), width,pFin256);
	} 
	int x;//���ص�λ�� 
	x=data256[0][0]-1;
	printf("256ͼ������һ�е�һ�����ص��λ���ǣ�%d\n",x);
	printf("���ص�ĵ�ɫ�������ǣ�B=%d,G=%d,R=%d\n",rgb256[x].blue,rgb256[x].green,rgb256[x].red);
	printf("�������н�����\n");
	
	//�ر��ļ�	
	fclose(pFin256);
	
	//�ͷŶ�ָ̬�� 
	for(int i=0;i<height;i++)
	{
		free(data256[i]);
	}
	free(rgb256);
	free(data256);
	return 0; 

}
