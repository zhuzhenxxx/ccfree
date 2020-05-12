#include "_ccfree.h"

void CallQuit(int sig);

char strLogPath[201]; // 日志文件目录
double dusep=0.00;   // CPU的利用率

class CCPUSTAT
{
public:
  char   m_hostname[31];
  struct st_CPUSTAT
  {
    char cpu[11];
    UINT user;
    UINT system;
    UINT nice;
    char idle[16];
    UINT iowait;
    UINT irq;
    UINT softirq;
  };

  st_CPUSTAT m_stCPUSTAT;
  vector<struct st_CPUSTAT> m_vCPUSTAT;

  CCPUSTAT();
 ~CCPUSTAT();

  void BindConnLog(connection *in_conn,CLogFile *in_logfile);

  // 获取CPU报告
  BOOL GETCPUSTAT();
};

CLogFile       logfile;
CCPUSTAT       CPUSTAT;

int main(int argc,char *argv[])
{
  if (argc != 2)
  {
    printf("\n");
    printf("Using:./cpustat \n");

    printf("Example:/htidc/htidc/bin/cpustat\n\n");

    return -1;
  }

  // 关闭全部的信号和输入输出
  // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  CloseIOAndSignal(); signal(SIGINT,CallQuit); signal(SIGTERM,CallQuit);

  if (logfile.Open("/tmp/log/cpustat.log","a+") == FALSE)
  {
    printf("logfile.Open(/tmp/log/cpustat.log) failed.\n"); return -1;
  }

  // 获取CPU报告
  if (CPUSTAT.GETCPUSTAT() == FALSE)
  {
    logfile.Write("CPUSTAT.GETCPUSTAT failed.\n"); return -1;
  }

  // 把CPU报告更新到表中
  if (CPUSTAT.UptCPUSTAT() != 0)
  {
    logfile.Write("CPUSTAT.UptCPUSTAT failed.\n"); return -1;
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
  memset(m_hostname,0,sizeof(m_hostname));
  memset(m_AlarmSTR,0,sizeof(m_AlarmSTR));
  m_conn=0; m_logfile=0;
}

CCPUSTAT::~CCPUSTAT()
{
  m_vCPUSTAT.clear();
}


BOOL CCPUSTAT::GETCPUSTAT()
{
  FILE *fp=0;

  if ( (fp=FOPEN("/proc/stat","r")) == NULL )
  {
    logfile.Write("open /proc/stat failed.\n"); return FALSE;
  }

  m_vCPUSTAT.clear();

  char strLine[512];

  CCmdStr CmdStr;

  while (TRUE)
  {
    memset(strLine,0,sizeof(strLine));
    memset(&m_stCPUSTAT,0,sizeof(m_stCPUSTAT));

    if (FGETS(strLine,500,fp) == FALSE) break;

    // 删除字符串前后的空格
    Trim(strLine);

    // 把字符串中间的多个空格全部转换为一个空格
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

    // 把CPU的名称转换成小写
    ToLower(m_stCPUSTAT.cpu);

    if (strstr(m_stCPUSTAT.cpu,"cpu") == 0) continue;

    m_vCPUSTAT.push_back(m_stCPUSTAT);
  }

  fclose(fp);

  return TRUE;
}
// 关闭全部的信号和输入输出
void CloseIOAndSignal()
{
  int ii=0;

  for (ii=0;ii<100;ii++)
  {
    signal(ii,SIG_IGN); close(ii);
  }
}