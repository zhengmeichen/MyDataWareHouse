#include<iostream>
#include<malloc.h>
#include<windows.h>
#include<fstream>
#include<math.h> 
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
	
	//������Ҷȼ����ظ�����txt�ļ�
	FILE *pout;
	pout = fopen("ԭʼͼ��ĸ��Ҷȼ����ظ���.txt","wb");	
	if(pout==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	} 
	for(int i=0;i<256;i++)
	{
		fprintf(pout,"%d\n",count[i]);
	}
	fclose(pout);
	
	//ֱ��ͼ���⻯
	double Pi[256]={0};  //ԭʼͼ��ֱ��ͼ
	double Pj[256]={0};	 //�ۻ�ֱ��ͼ
	
	int sum=ih.biWidth*ih.biHeight;
	
	//����ԭʼֱ��ͼ
	for(int i=0;i<256;i++)
	{
		Pi[i]=1.00*count[i]/sum;
	} 
	//���ԭʼͼ���ֱ��ͼ��Ϣ��txt�ļ�
	FILE *pout1;
	pout1 = fopen("ԭʼͼ���ֱ��ͼ��Ϣ.txt","wb");	
	if(pout1==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
		return 0;
	} 
	for(int i=0;i<256;i++)
	{
		fprintf(pout1,"%lf\n",Pi[i]);
	}
	fclose(pout1);	
	
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
	
	//������⻯����Ҷȼ����ظ�����txt�ļ�
	FILE *pout2;
	pout2 = fopen("���⻯ͼ��ĸ��Ҷȼ����ظ���.txt","wb");	
	if(pout2==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
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
	
	//������⻯ͼ���ֱ��ͼ��Ϣ��txt�ļ�
	FILE *pout3;
	pout3 = fopen("���⻯ͼ���ֱ��ͼ��Ϣ.txt","wb");	
	if(pout3==NULL)
	{
		printf("�ļ���ʧ�ܣ�");
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
	
	
	//������⻯��ͼ��
    FILE *pFout = fopen("Histogram.bmp","wb");
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
	printf("���ͼƬ�ɹ�!");  
	
	
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
