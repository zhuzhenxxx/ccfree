/*
 *  ��������demo30.cpp���˳�����ʾfreecplus����в���MKDIR�������ݾ���·�����ļ�����Ŀ¼���𼶵Ĵ���Ŀ¼��
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

int main()
{
  MKDIR("/tmp/aaa/bbb/ccc/ddd",false);   // ����"/tmp/aaa/bbb/ccc/ddd"Ŀ¼��

  MKDIR("/tmp/111/222/333/444/data.xml",true);   // ����"/tmp/111/222/333/444"Ŀ¼��
}

