#include <iostream>
using namespace std;
int main()
{
	float a = 3.14;
 char p='a';
 char *b=(char*)&a;
 char *pp=(char*)&p;
 char *ppp=&p;
 // printf("%\n");
  printf("%c\n", *pp);
  printf("%c\n", *b);
  printf("%c\n", *ppp);
 cout<<*pp<<' '<<pp<<endl;
 cout<<*ppp<<' '<<ppp<<endl;
}