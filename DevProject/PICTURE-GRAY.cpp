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
	}rgb[512][512];//,rgb2[512][512];
	
	
	fpin=fopen("ZMC.bmp","rb");
	//fpout=fopen("Gray.bmp","wb");
	//fpout1=fopen("Red.bmp","wb");
	//fpout2=fopen("Green.bmp","wb");
	//fpout3=fopen("Blue.bmp","wb");
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
	
	printf("\n");
	int type;
	printf("请输入变换类型：\n");
	printf("1:灰度图像\n");
	printf("2:R通道图像\n");
	printf("3:G通道图像\n");
	printf("4:B通道图像\n");	
	scanf("%d",&type);
	
	
	
	//灰度图像 
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
		printf("输出灰度图像成功!\n");
		printf("程序运行结束\n");
		fclose(fpout);
		
		return 0;
	} 
	
	
	//R通道图像
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
		printf("输出R通道图像成功!");
		
		fclose(fpout1);

		return 0;
	}
	
	//G通道图像
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
		printf("输出G通道图像成功!");
		
		fclose(fpout2);
		
		return 0;
	}
	
	//B通道图像
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
		printf("输出B通道图像成功!");
		
		fclose(fpout3);
		
		return 0;
	} 

	return 0;
 } 

