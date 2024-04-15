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
	int type;
	printf("������任���ͣ�\n");
	printf("1:ͼ��ˮƽ����\n");
	printf("2:ͼ��ˮƽ����\n");
	printf("3:ͼ��ֱ����\n");
	printf("4:ͼ��ֱ����\n");
	printf("5:ͼ���Զ����ƶ�\n");
	scanf("%d",&type);
	
	BITMAPFILEHEADER fh;
	fread(&fh, 1, sizeof(BITMAPFILEHEADER), pFin);
	BITMAPINFOHEADER ih;
	fread(&ih, 1, sizeof(BITMAPINFOHEADER), pFin);

	int width = ih.biWidth;
	int height = ih.biHeight;
	
	rgb = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	rgbout= (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
	for (int i = 0 ; i < height ; i ++)//������̬��ά����
	{
		rgb[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
	}
	//��ȡͼ��
	for (int i = 0 ; i < height ; i++) 
	{
		fread(rgb[i], sizeof(RGB24BIT), width, pFin);
	}
	
///////////////////////////////////////////////////////////////////////////
//ͼ��ˮƽ����
	if (type == 1)
	{
		//rgbout = (RGB24BIT **)malloc(sizeof(RGB24BIT*) * height);
		int x;
		printf("�������ƶ���ֵ��");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("����Ĳ���ֵ���ں���Χ\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < height ; i++)
		{
			for (int j = 0; j < width-x; j++)
			{
				rgbout[i][j]=rgb[i][x+j];
			}
		}
		FILE *pFout = fopen("ˮƽ����.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}
	
////////////////////////////////////////////////////////////////////////////////////
//ͼ��ˮƽ����	
	else if(type == 2)
	{
		int x;
		printf("�������ƶ���ֵ��");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("����Ĳ���ֵ���ں���Χ\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < height ; i++)
		{
			for (int j = 0; j < width-x; j++)
			{
				rgbout[i][j+x]=rgb[i][j];
			}
		}
		FILE *pFout = fopen("ˮƽ����.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}

//////////////////////////////////////////////////////////////////////////////
//ͼ��ֱ����		
	else if (type == 3)
	{
		int x;
		printf("�������ƶ���ֵ��");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("����Ĳ���ֵ���ں���Χ\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < width ; i++)
		{
			for (int j = 0; j < height-x; j++)
			{
				rgbout[j+x][i]=rgb[j][i];
			}
		}
		FILE *pFout = fopen("��ֱ����.bmp","wb");
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
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}
	
///////////////////////////////////////////////////////////////////////////////////
//ͼ��ֱ����	
	else if (type == 4)
	{
		int x;
		printf("�������ƶ���ֵ��");
		scanf("%d",&x);
		if(x<0||x>width) 
		{
			printf("����Ĳ���ֵ���ں���Χ\n");
			return 0; 
		}
		/*for (int i = 0 ; i < height ; i ++)
		{	//������̬��ά����
			rgbout[i]	= (RGB24BIT*)malloc(sizeof(RGB24BIT) * width);
		}*/
		for (int i = 0 ; i < height; i++)
		{
			for(int j=0;j<width;j++)
			{
				rgbout[j][i].red=128;
				rgbout[j][i].blue=128;
				rgbout[j][i].green=128;
			}
		}
		for (int i = 0 ; i < width ; i++)
		{
			for (int j = 0; j < height-x; j++)
			{
				rgbout[j][i]=rgb[j+x][i];
			}
		}
		FILE *pFout = fopen("��ֱ����.bmp","wb");
		fwrite(&fh,sizeof(fh),1,pFout);
		fwrite(&ih,sizeof(ih),1,pFout);
		for (int i = 0 ; i < width; i++)
		{
			fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
		}
		printf("���ͼƬ�ɹ�!"); 
		//�ͷ�ָ����ڴ�ռ� 
		for (int i = 0 ; i<height ;i++)
		{
				free(rgb[i]);
		}
		free(rgb);
		free(rgbout);
		fclose(pFin);
		fclose(pFout);
		return 0; 
	}
	
///////////////////////////////////////////////////////////////////////////////////
//ͼ���Զ����ƶ�		
	else if (type == 5)
	{
		int x,y,m;
		printf("������ˮƽ�ƶ���ֵ��");
		scanf("%d",&x);
		printf("�����봹ֱ�ƶ���ֵ��");
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
			FILE *pFout = fopen("�Զ���ƽ��.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < height; i++)
			{
				fwrite(rgb[i], sizeof(RGB24BIT), width, pFout);
			}
			printf("���ͼƬ�ɹ�!"); 
			fclose(pFout);
			//�ͷ�ָ����ڴ�ռ� 
			for (int i = 0 ; i<height ;i++)
			{
				free(rgb[i]);
			}
			free(rgb);
			free(rgbout);
			fclose(pFin);
			return 0;
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
			////////���ͼ�� 
			FILE *pFout = fopen("�Զ���ƽ��.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
			}
			printf("���ͼƬ�ɹ�!"); 
			//�ͷ�ָ����ڴ�ռ� 
			for (int i = 0 ; i<height ;i++)
			{
				free(rgb[i]);
			}
			free(rgb);
			free(rgbout);
			fclose(pFin);
			fclose(pFout);
			return 0;  
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
			////////���ͼ�� 
			FILE *pFout = fopen("�Զ���ƽ��.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
			}
			printf("���ͼƬ�ɹ�!"); 
			//�ͷ�ָ����ڴ�ռ� 
			for (int i = 0 ; i<height ;i++)
			{
				free(rgb[i]);
			}
			free(rgb);
			free(rgbout);
			fclose(pFin);
			fclose(pFout);
			return 0;  
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
			////////���ͼ�� 
			FILE *pFout = fopen("�Զ���ƽ��.bmp","wb");
			fwrite(&fh,sizeof(fh),1,pFout);
			fwrite(&ih,sizeof(ih),1,pFout);
			for (int i = 0 ; i < width; i++)
			{
				fwrite(rgbout[i], sizeof(RGB24BIT), height, pFout);
			}
			printf("���ͼƬ�ɹ�!"); 
			//�ͷ�ָ����ڴ�ռ� 
			for (int i = 0 ; i<height ;i++)
			{
				free(rgb[i]);
			}
			free(rgb);
			free(rgbout);
			fclose(pFin);
			fclose(pFout);
			return 0; 
		} 
	}
	return 0; 
}
