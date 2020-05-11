/*
 *  ��������demo14.cpp���˳�����ʾfreecplus������ַ����滻UpdateStr������ʹ�á�
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  char str[301];

  STRCPY(str,sizeof(str),"name:messi,no:10,job:striker.");
  UpdateStr(str,":","=");    // ��ð���滻�ɵȺš�
  printf("str=%s=\n",str);    // ��������str1=name=messi,no=10,job=striker.=

  STRCPY(str,sizeof(str),"name:messi,no:10,job:striker.");
  UpdateStr(str,"name:","");    // ��"name:"�滻��""���൱��ɾ������"name:"��
  printf("str=%s=\n",str);    // ��������str1=messi,no:10,job:striker.=

  STRCPY(str,sizeof(str),"messi----10----striker");  
  UpdateStr(str,"--","-",false);    // ������"--"�滻��һ��"-"��bLoop����Ϊfalse��
  printf("str=%s=\n",str);    // ��������str1=messi--10--striker=

  STRCPY(str,sizeof(str),"messi----10----striker");  
  UpdateStr(str,"--","-",true);    // ������"--"�滻��һ��"-"��bLoop����Ϊtrue��
  printf("str=%s=\n",str);    // ��������str1=messi-10-striker=

  STRCPY(str,sizeof(str),"messi-10-striker");  
  UpdateStr(str,"-","--",false);    // ��һ��"-"�滻������"--"��bLoop����Ϊfalse��
  printf("str=%s=\n",str);    // ��������str1=messi--10--striker=

  STRCPY(str,sizeof(str),"messi-10-striker");  
  // ���´����"-"�滻��"--"��bloop����Ϊtrue�������߼�����UpdateStr����ִ���滻��
  UpdateStr(str,"-","--",true);    // ��һ��"-"�滻������"--"��bloop����Ϊtrue��
  printf("str=%s=\n",str);    // ��������str1=messi-10-striker=
}

