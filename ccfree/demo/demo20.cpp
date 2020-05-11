/*
 *  ��������demo20.cpp���˳�����ʾfreecplus��ܲ���ַ�������CCmdStr��ʹ�á�
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
  STRCPY(buffer,sizeof(buffer),"messi,10,true,30,68.5,2100000,Barcelona");

  CCmdStr CmdStr;
  CmdStr.SplitToCmd(buffer,",");        // ���buffer
  CmdStr.GetValue(0, stplayer.name,50); // ��ȡ����
  CmdStr.GetValue(1, stplayer.no,5);    // ��ȡ���º���
  CmdStr.GetValue(2,&stplayer.striker); // ����λ��
  CmdStr.GetValue(3,&stplayer.age);     // ��ȡ����
  CmdStr.GetValue(4,&stplayer.weight);  // ��ȡ����
  CmdStr.GetValue(5,&stplayer.sal);     // ��ȡ��н��ŷԪ��
  CmdStr.GetValue(6, stplayer.club,50); // ��ȡЧ���ľ��ֲ�
  
  printf("name=%s,no=%s,striker=%d,age=%d,weight=%.1f,sal=%ld,club=%s\n",\
         stplayer.name,stplayer.no,stplayer.striker,stplayer.age,\
         stplayer.weight,stplayer.sal,stplayer.club);
  // ������:name=messi,no=10,striker=1,age=30,weight=68.5,sal=21000000,club=Barcelona
}

