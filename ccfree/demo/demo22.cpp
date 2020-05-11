/*
 *  ��������demo22.cpp���˳�����ʾ����freecplus��ܵ�GetXMLBuffer��������xml�ַ�����
 *  ���ߣ�C���Լ�����(www.freecplus.net) ���ڣ�20190525
*/
#include "../_freecplus.h"

// ���ڴ�������˶�Ա���ϵĽṹ�塣
struct st_player
{
  char name[51];    // ����
  char no[6];       // ���º���
  bool striker;     // ����λ���Ƿ���ǰ�棬true-�ǣ�false-���ǡ�
  int  age;         // ����
  double weight;    // ���أ�kg��
  long sal;         // ��н��ŷԪ��
  char club[51];    // Ч���ľ��ֲ�
}stplayer;

int main()
{
  memset(&stplayer,0,sizeof(struct st_player));

  char buffer[301];  
  STRCPY(buffer,sizeof(buffer),"<name>messi</name><no>10</no><striker>true</striker><age>30</age><weight>68.5</weight><sal>21000000</sal><club>Barcelona</club>");

  GetXMLBuffer(buffer,"name",stplayer.name,50);
  GetXMLBuffer(buffer,"no",stplayer.no,5);
  GetXMLBuffer(buffer,"striker",&stplayer.striker);
  GetXMLBuffer(buffer,"age",&stplayer.age);
  GetXMLBuffer(buffer,"weight",&stplayer.weight);
  GetXMLBuffer(buffer,"sal",&stplayer.sal);
  GetXMLBuffer(buffer,"club",stplayer.club,50);

  printf("name=%s,no=%s,striker=%d,age=%d,weight=%.1f,sal=%ld,club=%s\n",\
         stplayer.name,stplayer.no,stplayer.striker,stplayer.age,\
         stplayer.weight,stplayer.sal,stplayer.club);
  // ������:name=messi,no=10,striker=1,age=30,weight=68.5,sal=21000000,club=Barcelona
}

