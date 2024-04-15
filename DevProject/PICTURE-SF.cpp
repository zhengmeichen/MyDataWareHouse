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
	}**rgb, **rgbout;
int main()
{	
	FILE *pFin;
	pFin = fopen("ZMC.bmp","rb");	
	if(pFin==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	int type;
	printf("ѡ�����ڽ���ֵ���Ŵ���������:1\n");
	printf("ѡ��˫���Բ�ֵ�����Ŵ��������룺2\n");
	scanf("%d",&type);
	
	/*//�������ű��� 
	double Sx,Sy;
	printf("���ѣ������·���������ʱ�����ݵķ�Χȷ���ڡ�0.5��3��֮��!!!\n");
	printf("������ˮƽ���ű�����\n");
	scanf("%lf",&Sx);
	printf("�����봹ֱ���ű�����\n");
	scanf("%lf",&Sy);*/
	
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
		for (int i = 0 ; i < height ; i ++)//������̬��ά����
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
		
		FILE *pFout;
		pFout = fopen("���ڽ���ֵ.bmp","wb");
		if(pFout==NULL)
    	{
    		printf("�ļ���ʧ�ܣ�\n");
    		return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("����ļ��ɹ���\n");
		
		//�ͷ�ָ����ڴ�ռ� 
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
		for (int i = 0 ; i < height ; i ++)//������̬��ά����
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
		
		FILE *pFout;
		pFout = fopen("˫���Բ�ֵ.bmp","wb");
		if(pFout==NULL)
    	{
    		printf("�ļ���ʧ�ܣ�\n");
    		return 0;
		}
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for(int i=0;i<out_height;i++)
		{
			fwrite(rgbout[i],sizeof(RGB24BIT)*out_width,1,pFout);
		}
		printf("����ļ��ɹ���\n");
		
		//�ͷ�ָ����ڴ�ռ� 
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
