/*
 *  ��������demo40.cpp���˳�����ʾfreecplus����в���CDir���CFile�ദ�������ļ����÷���
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  CDir Dir;

  // ɨ��/tmp/dataĿ¼���ļ���ƥ��"surfdata_*.xml"���ļ���
  if (Dir.OpenDir("/tmp/data","surfdata_*.xml")==false)
  {
    printf("Dir.OpenDir(/tmp/data) failed.\n"); return -1;
  }

  CFile File;

  while (Dir.ReadDir()==true)
  {
    printf("�����ļ�%s...",Dir.m_FullFileName);

    if (File.Open(Dir.m_FullFileName,"r")==false)
    {
      printf("failed.File.Open(%s) failed.\n",Dir.m_FullFileName); return -1;
    }

    // ������Բ����ȡ�����ļ������ݡ�����xml�ַ�����������д�����ݿ�Ĵ��롣
    // ��ȡ�ı�������Fgets��FFGETS��������ȡ������������Fread������
    // ����Ĵ����ҾͲ�д�ˡ�

    // �������ļ��е����ݺ󣬹ر��ļ�ָ�룬��ɾ���ļ���
    File.CloseAndRemove();

    printf("ok\n");
  }
}

