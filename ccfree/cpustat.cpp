#include "_ccfree.h"

void CallQuit(int sig);

char strLogPath[201]; // ��־�ļ�Ŀ¼
char strTmpPath[201]; // ���̻��Ϣ�ļ�Ŀ¼
char strIDCConnStr[201]; // ���ݿ����Ӳ���
char strAlarmValue[11];
double dusep=0.00;   // CPU��������

void Trim(char *in_string);                                                                                                                                                                                                     ;;

class CCPUSTAT
{
public:
  struct st_CPUSTAT
  {
    char cpu[11];
    int user;
    int system;
    int nice;
    char idle[16];
    int iowait;
    int irq;
    int softirq;
  };

  st_CPUSTAT m_stCPUSTAT;
  vector<struct st_CPUSTAT> m_vCPUSTAT;


  CCPUSTAT();
 ~CCPUSTAT();

  // ��ȡCPU����
  bool GETCPUSTAT();


};

CLogFile       logfile;
CCPUSTAT       CPUSTAT;

int main(int argc,char *argv[])
{
  if (argc != 2)
  {
    printf("\n");
    printf("Using:./cpu \n");

    printf(" /home/zhuzx/ccfree/ccfree/cpu 50\n\n");
    printf("�˳������ڰѱ���������CPUʹ������Ϣ��¼���ļ�������������Ҫ��صķ������ϡ�\n");

    return -1;
  }

  // �ر�ȫ�����źź��������
  // �����ź�,��shell״̬�¿��� "kill + ���̺�" ������ֹЩ����
  // ���벻Ҫ�� "kill -9 +���̺�" ǿ����ֹ
  CloseIOAndSignal(); signal(SIGINT,CallQuit); signal(SIGTERM,CallQuit);

  if (logfile.Open("/tmp/ccfree/log/cpustat.log","a+") == false)
  {
    printf("logfile.Open(/tmp/ccfree/log/cpustat.log) failed.\n"); return -1;
  }

  // ��ȡCPU����
  if (CPUSTAT.GETCPUSTAT() == false)
  {
    logfile.Write("CPUSTAT.GETCPUSTAT failed.\n"); return -1;
  }

  return 0;
}

void CallQuit(int sig)
{
  if (sig > 0) signal(sig,SIG_IGN);

  logfile.Write("catching the signal(%d).\n",sig);

  logfile.Write("cpustat exit.\n");

  exit(0);
}


CCPUSTAT::CCPUSTAT()
{
}

CCPUSTAT::~CCPUSTAT()
{
  m_vCPUSTAT.clear();
}


bool CCPUSTAT::GETCPUSTAT()
{
  FILE *fp=0;

  if ( (fp=FOPEN("/proc/stat","r")) == NULL )
  {
    logfile.Write("open /proc/stat failed.\n"); return false;
  }

  m_vCPUSTAT.clear();

  char strLine[512];

  CCmdStr CmdStr;

  while (true)
  {
    memset(strLine,0,sizeof(strLine));
    memset(&m_stCPUSTAT,0,sizeof(m_stCPUSTAT));

    if (FGETS(fp,strLine,500) == false) break;

    // ɾ���ַ���ǰ��Ŀո�
    Trim(strLine);

    // ���ַ����м�Ķ���ո�ȫ��ת��Ϊһ���ո�
    UpdateStr(strLine,"  "," ");

    CmdStr.SplitToCmd(strLine," ");

    CmdStr.GetValue(0, m_stCPUSTAT.cpu,10);
    CmdStr.GetValue(1,&m_stCPUSTAT.user);
    CmdStr.GetValue(2,&m_stCPUSTAT.system);
    CmdStr.GetValue(3,&m_stCPUSTAT.nice);
    CmdStr.GetValue(4, m_stCPUSTAT.idle,15);
    CmdStr.GetValue(5,&m_stCPUSTAT.iowait);
    CmdStr.GetValue(6,&m_stCPUSTAT.irq);
    CmdStr.GetValue(7,&m_stCPUSTAT.softirq);

    // ��CPU������ת����Сд
    ToLower(m_stCPUSTAT.cpu);

    if (strcmp(m_stCPUSTAT.cpu,"cpu") != 0) continue;

    m_vCPUSTAT.push_back(m_stCPUSTAT);
  }

  fclose(fp);

  return true;
}


void Trim(char *in_string)
{
  DeleteLChar(in_string,' ');
  DeleteRChar(in_string,' ');
}
