/*
 *  ��������demo32.cpp���˳�����ʾfreecplus����в���CDir���ȡĳĿ¼������Ŀ¼�е��ļ��б���Ϣ��
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  CDir Dir;

  if (Dir.OpenDir("/tmp/root","*.h,*cpp",100,true,true)==false)
  { 
    printf("Dir.OpenDir(/tmp/root) failed.\n"); return -1; 
  }

  while(Dir.ReadDir()==true)
  {
    printf("filename=%s,mtime=%s,size=%d\n",Dir.m_FullFileName,Dir.m_ModifyTime,Dir.m_FileSize);
  }
}

