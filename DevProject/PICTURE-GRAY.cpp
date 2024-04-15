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
	FILE *fpout3;
	
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
	}rgb[512][512];//,rgb2[512][512];
	
	
	fpin=fopen("ZMC.bmp","rb");
	//fpout=fopen("Gray.bmp","wb");
	//fpout1=fopen("Red.bmp","wb");
	//fpout2=fopen("Green.bmp","wb");
	//fpout3=fopen("Blue.bmp","wb");
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
	
	printf("\n");
	int type;
	printf("������任���ͣ�\n");
	printf("1:�Ҷ�ͼ��\n");
	printf("2:Rͨ��ͼ��\n");
	printf("3:Gͨ��ͼ��\n");
	printf("4:Bͨ��ͼ��\n");	
	scanf("%d",&type);
	
	
	
	//�Ҷ�ͼ�� 
	if(type==1)
	{
		fpout=fopen("Gray.bmp","wb");
		unsigned char temp=0;
		for(int i=0;i<512;i++)
		{
			for(int j=0;j<512;j++)
			{
				temp=(rgb[i][j].Blue+rgb[i][j].Green+rgb[i][j].Red)/3;
				rgb[i][j].Blue=temp;
				rgb[i][j].Green=temp;
				rgb[i][j].Red=temp;
			}
		}
		
		fwrite(&bh,sizeof(bh),1,fpout);
		fwrite(&bi,sizeof(bi),1,fpout);
		fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout);
		printf("����Ҷ�ͼ��ɹ�!\n");
		printf("�������н���\n");
		fclose(fpout);
		
		return 0;
	} 
	
	
	//Rͨ��ͼ��
	else if(type==2)
	{
		fpout1=fopen("Red.bmp","wb");
		for(int m=0;m<512;m++)
		{
			for(int n=0;n<512;n++)
			{
				rgb[m][n].Blue=0;
				rgb[m][n].Green=0;
			}
		}
		fwrite(&bh,sizeof(bh),1,fpout1);
		fwrite(&bi,sizeof(bi),1,fpout1);
		fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout1);
		printf("���Rͨ��ͼ��ɹ�!");
		
		fclose(fpout1);

		return 0;
	}
	
	//Gͨ��ͼ��
	else if(type==3)
	{
		fpout2=fopen("Green.bmp","wb");
		for(int i=0;i<512;i++)
		{
			for(int j=0;j<512;j++)
			{
				rgb[i][j].Blue=0;
				rgb[i][j].Red=0;
			}
		}
		fwrite(&bh,sizeof(bh),1,fpout2);
		fwrite(&bi,sizeof(bi),1,fpout2);
		fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout2);
		printf("���Gͨ��ͼ��ɹ�!");
		
		fclose(fpout2);
		
		return 0;
	}
	
	//Bͨ��ͼ��
	else if(type==4)
	{
		fpout3=fopen("Blue.bmp","wb");
		for(int i=0;i<512;i++)
		{
			for(int j=0;j<512;j++)
			{
				rgb[i][j].Green=0;
				rgb[i][j].Red=0;
			}
		}
		fwrite(&bh,sizeof(bh),1,fpout3);
		fwrite(&bi,sizeof(bi),1,fpout3);
		fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout3);
		printf("���Bͨ��ͼ��ɹ�!");
		
		fclose(fpout3);
		
		return 0;
	} 

	return 0;
 } 

