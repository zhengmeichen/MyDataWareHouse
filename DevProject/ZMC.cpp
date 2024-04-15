#include <iostream>
#include <malloc.h>
#include <windows.h>
#pragma pack(1)

using namespace std;

int main()
{
	FILE *fpin,*fpout;
	FILE *fpout1;
	FILE *fpout2;
	
	struct bmphead
	{
		WORD bfType;
		DWORD bfSize;
		WORD bfReserved1;
		WORD bfReserved2;
		DWORD bfOffbits;
	}bh;
	struct bmpinfo
	{
		DWORD	biSize;
		LONG    biWidth; //ͼ���� 
		LONG    biHeight; //ͼ��߶� 
		WORD    biPlanes; 
		WORD    biBitCount; //����λ��Ŀ 
		DWORD	biCompression; // ѹ������
		DWORD	biSizeImage; // ͼ��Ĵ�С
		LONG    biXPelsPerMeter; // ˮƽ�ֱ��� 
		LONG    biYPelsPerMeter; // ��ֱ�ֱ��� 
		DWORD	biClrUsed; // ʹ�õ�ɫ���� 
		DWORD	biClrImportant; // ��Ҫ����ɫ�� 
	}bi;
	struct bmprgb 
	{
		unsigned char Blue;      
		unsigned char Green;    
		unsigned char Red;      
	}rgb[512][512],rgb1[512][512];//,rgb2[512][512];
	
	
	fpin=fopen("ZMC.bmp","rb");
	fpout=fopen("CLN.bmp","wb");
	//fpout1=fopen("CLN1.bmp","wb");//ˮƽ���� 
	//fpout2=fopen("CLN2.bmp","wb");//��ֱ���� 
	
	if(fpin==NULL)
	{
		cout<<"ERROR"<<endl;
		return 0;
	}
	
	fread(&bh,sizeof(bh),1,fpin);
	fread(&bi,sizeof(bi),1,fpin);
	fread(&rgb, sizeof(rgb), 1, fpin);
	
	printf("�ļ���ʶ�� = 0X%X\n", bh.bfType);
	printf("BMP�ļ���");
	printf("�ļ�ͷ��С= %d�ֽ�\n",bh.bfSize);
	printf("��Ϣͷ��С= %d�ֽ�\n",bi.biSize);
	printf("ͼ����= %d\n",bi.biWidth);	
	printf("ͼ��߶�= %d\n",bi.biHeight);	
	printf("����λ��Ŀ= %d\n",bi.biBitCount);
	printf("ͼ��Ĵ�С = %d �ֽ�\n", bi.biSizeImage); 
	printf("ˮƽ�ֱ���= %d\n",bi.biXPelsPerMeter);	
	printf("��ֱ�ֱ���= %d\n",bi.biYPelsPerMeter);
	
	fclose(fpin);
	
	//ԭͼ 
	fwrite(&bh,sizeof(bh),1,fpout);
	fwrite(&bi,sizeof(bi),1,fpout);
	fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout);
	fclose(fpout);
	
	
	//ˮƽ���� 
	fpout1=fopen("CLN1.bmp","wb");//ˮƽ���� 
	fwrite(&bh,sizeof(bh),1,fpout1);
	fwrite(&bi,sizeof(bi),1,fpout1);
	for(int i=0;i<512;i++)
	{
		for(int j=0;j<512;j++)
			{
				rgb1[i][j]=rgb[i][511-j];
			}
	}
	
	fwrite(rgb1, sizeof(rgb1[0][0]),512*512, fpout1);
	fclose(fpout1);
	
	
	//��ֱ����
	fpout2=fopen("CLN2.bmp","wb");//��ֱ���� 
	fwrite(&bh,sizeof(bh),1,fpout2);
	fwrite(&bi,sizeof(bi),1,fpout2);
	for(int m=0;m<512;m++)
	{
		for(int n=0;n<512;n++)
			{
				rgb1[m][n]=rgb[511-m][n];
			}
	}
	
	fwrite(rgb1, sizeof(rgb1[0][0]),512*512, fpout2);
	fclose(fpout2); 
	
	return 0;
 } 

