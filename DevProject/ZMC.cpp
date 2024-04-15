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
		LONG    biWidth; //图像宽度 
		LONG    biHeight; //图像高度 
		WORD    biPlanes; 
		WORD    biBitCount; //像素位数目 
		DWORD	biCompression; // 压缩类型
		DWORD	biSizeImage; // 图像的大小
		LONG    biXPelsPerMeter; // 水平分辨率 
		LONG    biYPelsPerMeter; // 垂直分辨率 
		DWORD	biClrUsed; // 使用的色彩数 
		DWORD	biClrImportant; // 重要的颜色数 
	}bi;
	struct bmprgb 
	{
		unsigned char Blue;      
		unsigned char Green;    
		unsigned char Red;      
	}rgb[512][512],rgb1[512][512];//,rgb2[512][512];
	
	
	fpin=fopen("ZMC.bmp","rb");
	fpout=fopen("CLN.bmp","wb");
	//fpout1=fopen("CLN1.bmp","wb");//水平镜像 
	//fpout2=fopen("CLN2.bmp","wb");//垂直镜像 
	
	if(fpin==NULL)
	{
		cout<<"ERROR"<<endl;
		return 0;
	}
	
	fread(&bh,sizeof(bh),1,fpin);
	fread(&bi,sizeof(bi),1,fpin);
	fread(&rgb, sizeof(rgb), 1, fpin);
	
	printf("文件标识符 = 0X%X\n", bh.bfType);
	printf("BMP文件的");
	printf("文件头大小= %d字节\n",bh.bfSize);
	printf("信息头大小= %d字节\n",bi.biSize);
	printf("图像宽度= %d\n",bi.biWidth);	
	printf("图像高度= %d\n",bi.biHeight);	
	printf("像素位数目= %d\n",bi.biBitCount);
	printf("图像的大小 = %d 字节\n", bi.biSizeImage); 
	printf("水平分辨率= %d\n",bi.biXPelsPerMeter);	
	printf("垂直分辨率= %d\n",bi.biYPelsPerMeter);
	
	fclose(fpin);
	
	//原图 
	fwrite(&bh,sizeof(bh),1,fpout);
	fwrite(&bi,sizeof(bi),1,fpout);
	fwrite(rgb, sizeof(rgb[0][0]),512*512, fpout);
	fclose(fpout);
	
	
	//水平镜像 
	fpout1=fopen("CLN1.bmp","wb");//水平镜像 
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
	
	
	//垂直镜像
	fpout2=fopen("CLN2.bmp","wb");//垂直镜像 
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

