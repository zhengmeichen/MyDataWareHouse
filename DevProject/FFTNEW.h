#ifndef _FFT_H
#define _FFT_H

#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

const double PI = 3.14159265;
struct Complex{
	double x,y;	//x����ʵ��,y�����鲿
	Complex(double _x = 0.0,double _y = 0.0){
		x = _x;
		y = _y;
	}
	Complex operator-(const Complex &b)const{
		return Complex(x - b.x,y - b.y);
	}
	Complex operator+(const Complex &b)const{
		return Complex(x + b.x,y + b.y);
	}
	Complex operator*(const Complex &b)const{
		return Complex(x*b.x - y*b.y,x*b.y + y*b.x);
	}
};

void change(Complex **y,int h,int w)
{	//�任�±�,�����������
	int i,j,k;
	int a;
	for (a = 0 ; a < h;a++)
	{	//�ȶ����е�����һ��һ�±��ת��
		for(int i = 1,j = w/2;i<w-1;i++)
		{
			if(i < j)
			{
				Complex temp=y[a][i];
				y[a][i]=y[a][j];
				y[a][j]=temp;
			}
			//������ΪС�귴ת��Ԫ�أ�i<j��֤����һ��
			//i��������+1��j����ת���͵�+1��ʼ�ձ���i��j�Ƿ�ת��
			k = w/2;
			while(j >= k)
			{
				j = j - k;
				k = k/2;
			} 
			if(j < k)	j+=k;
		}
	}
	for (a = 0 ; a < w;a++)
	{	//�ٶ����е�����һ���±�ı任
		for(int i = 1,j = h/2;i<h-1;i++)
		{
			if(i < j)
			{
				Complex temp=y[i][a];
				y[i][a]=y[j][a];
				y[j][a]=temp;
			}
			//������ΪС�귴ת��Ԫ�أ�i<j��֤����һ��
			//i��������+1��j����ת���͵�+1��ʼ�ձ���i��j�Ƿ�ת��
			k = h/2;
			while(j >= k)
			{
				j = j - k;
				k = k/2;
			} 
			if(j < k)j+=k;
		}
	}
	
} 
void fft_center(Complex **y,int height,int width,int type)
{	//����y�Ǹ����Ķ�άָ��,ͨ����̬�����ڴ�õ�,height�Ǵ���y�ĸ߶�,width�Ǵ����y�Ŀ��,type�Ǳ任���ͣ�1�Ǹ���Ҷ�任,-1�Ƿ�����Ҷ�任
	if (type != 1 && type != -1)
	{	
		printf("����Ĳ�������,type=1�Ǹ���Ҷ�任,type=-1�Ƿ�����Ҷ�任\n");
		return;
	}
	if (type == 1)
	{	//����Ҷ�任,ƽ�Ƶ�����,ÿ��f(u,v)*(-1)^(x+y)����
		for (int i = 0 ; i < height; i++)
		{	//˫��ѭ����ֵ
			for (int j = 0 ; j < width ; j++)
			{
				y[i][j].x *= pow(-1.0,double(i+j));
				y[i][j].y *= pow(-1.0,double(i+j));
			}
		}
	}
	
	change(y,height,width);
	for (int i = 0 ; i < height ; i ++)
	{	//������fft
		for(int h = 2;h <= width;h<<=1)
		{
			Complex wn(cos(-type*2*PI/h),sin(-type*2*PI/h));		//wn��k=1����ת����
			for(int j = 0;j < width;j += h)
			{
				Complex w(1,0);
				for(int k = j;k < j + h/2;k++)
				{
					Complex u = y[i][k];
					Complex t = w*y[i][k + h/2];
					y[i][k] = u + t;
					y[i][k + h/2] = u - t;
					w = w*wn;	//��ת����
				}
			}
		}
	}

	for (int i = 0 ; i < width ; i ++)
	{	//������fft
		for(int h = 2;h <= height;h<<=1)
		{
			Complex wn(cos(-type*2*PI/h),sin(-type*2*PI/h));		//wn��k=1����ת����
			for(int j = 0;j < height;j += h)
			{
				Complex w(1,0);
				for(int k = j;k < j + h/2;k++)
				{
					Complex u = y[k][i];
					Complex t = w*y[k + h/2][i];
					y[k][i] = u + t;
					y[k + h/2][i] = u - t;
					w = w*wn;	//��ת����
				}
			}
		}
	}

	if(type == -1){
		for (int i = 0 ; i < height ;i++)
		{
			for(int j = 0;j < width;j++)
			{
				y[i][j].x /= (width*height);
				y[i][j].y /= (width*height);
			}
		}
	}
	if (type == -1)
	{	//������Ҷ�任,��ԭ,ÿ��f(u,v)*(-1)^(x+y)����,�÷������һ��ִ��
		for (int i = 0 ; i < height; i++)
		{	//˫��ѭ����ֵ
			for (int j = 0 ; j < width ; j++)
			{
				y[i][j].x *= pow(-1.0,double(i+j));
				y[i][j].y *= pow(-1.0,double(i+j));
			}
		}
	}
} 
#endif
