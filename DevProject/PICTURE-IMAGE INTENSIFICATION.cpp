#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<math.h>
 
#include<fstream>

#pragma pack(1)

using namespace std;

//�������ؽṹ��,˳�������̺�
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
		printf("�ļ���ʧ�ܣ�");
		return 0;
	}
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
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
	
	//���ͼ������Ҷ�ֵ����С�Ҷ�ֵ
	int MAXGray=0;
	int MINGray=255;
	int temp;
	//�ҶȻ� 
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
	printf("ͼ�����С�Ҷ�ֵΪ��MINGray=%d\n",MINGray);
	printf("ͼ������Ҷ�ֵΪ��MAXGray=%d\n",MAXGray);
	 

	int type;
	printf("��ͼ�������Ա任�Աȶ���ǿ  ������1��\n");
	printf("��ͼ���������ԶԱȶ���ǿ ������2��\n");
	scanf("%d",&type);
	 
	if(type==1)
	{
		int m;
		printf("��һ������������С,��ѡ��1��\n"); 
		printf("�ڶ������ƽ�Ʊ䰵,��ѡ��2��\n");
		printf("���������ƽ�Ʊ���,��ѡ��3��\n");
		scanf("%d",&m);
		
		
		//����Ķ�̬��Χ��x<MINGray  y>MAXGray
		//��С�Ķ�̬��Χ��x>MINGray  y<MAXGray
		switch(m)
		{
			
			
			case(1):
			
				double x;
				double y;
				printf("�������������С��̬��Χ��\n");
				scanf("%lf%lf",&x,&y);
				double z;
			
				//���� 
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
				
			
				//��С
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
				//ͼ��ƽ�Ʊ䰵����һ����ֵ
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
				//ͼ��ƽ�Ʊ�������һ����ֵ 
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
		//��ͼ���������ԶԱȶ���ǿ��ָ���任�Աȶ���ǿ
		//ָ���任  r>1  r<1
		double r;
		printf("������ͼ����ָ���任�Ĳ�����\n");
		scanf("%lf",&r);
		if(r==0)
		{
			printf("�����������"); 
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
	
	
	//����ļ�
	FILE *pFout;
	pFout = fopen("Contrast Enhancement.bmp","wb");	
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
	printf("���ͼƬ�ɹ�!���������ѽ�����\n"); 
	
	
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
