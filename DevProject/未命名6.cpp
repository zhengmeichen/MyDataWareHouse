#include "stdio.h"/*一个长度为 L 米的材料，需要截成长度为 a 米和 b 米的短材料，
其中 L ， a ， b 从键盘上输入，编程求解两种短材料各截多少根时，剩余的材料最少，
输出a，b的根数，以及剩余材料的长度。L，a，b均为整数。 */
#include "math.h" 
int main()
{
	int l,a,b,c,d,e,f,g,h;
	scanf("%d%d%d",&l,&a,&b);
	h=l;
    for(c=0;c*a<=l;c++)
    {
    	for(d=0;d*b<=l;d++)
    	{
    		e=l-c*a-b*d;
			if(e<0) continue; 
			else 
			{
				if(e<h)
    		    {
    			    h=e;
    			    f=c;
    			    g=d;
			    }
			    else if(e==h) 
			    {
			    	h=e;
			    	f=c;
			    	g=d;
				}
			}
		}
	}
    printf("%d,%d,%d\n",f,g,h);
	return 0;
}
