#ifndef _FFT_H
#define _FFT_H

#include<iostream>
#include<stdio.h>
#include<math.h>

using namespace std;

const double PI = 3.14159265;
struct Complex{
	double x,y;	//x代表实部,y代表虚部
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
{	//变换下标,方便蝶形运算
	int i,j,k;
	int a;
	for (a = 0 ; a < h;a++)
	{	//先对所有的行做一次一下标的转换
		for(int i = 1,j = w/2;i<w-1;i++)
		{
			if(i < j)
			{
				Complex temp=y[a][i];
				y[a][i]=y[a][j];
				y[a][j]=temp;
			}
			//交换互为小标反转的元素，i<j保证交换一次
			//i做正常的+1，j做反转类型的+1，始终保持i和j是反转的
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
	{	//再对所有的列做一次下标的变换
		for(int i = 1,j = h/2;i<h-1;i++)
		{
			if(i < j)
			{
				Complex temp=y[i][a];
				y[i][a]=y[j][a];
				y[j][a]=temp;
			}
			//交换互为小标反转的元素，i<j保证交换一次
			//i做正常的+1，j做反转类型的+1，始终保持i和j是反转的
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
{	//参数y是复数的二维指针,通过动态申请内存得到,height是传入y的高度,width是传入的y的宽度,type是变换类型，1是傅里叶变换,-1是反傅里叶变换
	if (type != 1 && type != -1)
	{	
		printf("传入的参数有误,type=1是傅里叶变换,type=-1是反傅里叶变换\n");
		return;
	}
	if (type == 1)
	{	//傅里叶变换,平移到中心,每项f(u,v)*(-1)^(x+y)即可
		for (int i = 0 ; i < height; i++)
		{	//双重循环赋值
			for (int j = 0 ; j < width ; j++)
			{
				y[i][j].x *= pow(-1.0,double(i+j));
				y[i][j].y *= pow(-1.0,double(i+j));
			}
		}
	}
	
	change(y,height,width);
	for (int i = 0 ; i < height ; i ++)
	{	//横向做fft
		for(int h = 2;h <= width;h<<=1)
		{
			Complex wn(cos(-type*2*PI/h),sin(-type*2*PI/h));		//wn是k=1的旋转因子
			for(int j = 0;j < width;j += h)
			{
				Complex w(1,0);
				for(int k = j;k < j + h/2;k++)
				{
					Complex u = y[i][k];
					Complex t = w*y[i][k + h/2];
					y[i][k] = u + t;
					y[i][k + h/2] = u - t;
					w = w*wn;	//旋转因子
				}
			}
		}
	}

	for (int i = 0 ; i < width ; i ++)
	{	//纵向做fft
		for(int h = 2;h <= height;h<<=1)
		{
			Complex wn(cos(-type*2*PI/h),sin(-type*2*PI/h));		//wn是k=1的旋转因子
			for(int j = 0;j < height;j += h)
			{
				Complex w(1,0);
				for(int k = j;k < j + h/2;k++)
				{
					Complex u = y[k][i];
					Complex t = w*y[k + h/2][i];
					y[k][i] = u + t;
					y[k + h/2][i] = u - t;
					w = w*wn;	//旋转因子
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
	{	//反傅里叶变换,还原,每项f(u,v)*(-1)^(x+y)即可,得放在最后一步执行
		for (int i = 0 ; i < height; i++)
		{	//双重循环赋值
			for (int j = 0 ; j < width ; j++)
			{
				y[i][j].x *= pow(-1.0,double(i+j));
				y[i][j].y *= pow(-1.0,double(i+j));
			}
		}
	}
} 
#endif
