/*
 *  ��������demo18.cpp���˳�����ʾfreecplus���������ʾMatchStr������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char filename[301];  
  STRCPY(filename,sizeof(filename),"_freecplus.h");
  
  // ���´��뽫���yes��
  if (MatchStr(filename,"*.h,*.cpp")==true) printf("yes\n");
  else printf("no\n");

  // ���´��뽫���yes��
  if (MatchStr(filename,"*.H")==true) printf("yes\n");
  else printf("no\n");

  // ���´��뽫���no��
  if (MatchStr(filename,"*.cpp")==true) printf("yes\n");
  else printf("no\n");
}

