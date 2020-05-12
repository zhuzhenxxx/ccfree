#include "_ccfree.h"

void CallQuit(int sig);

char strLogPath[201]; // 日志文件目录
char strTmpPath[201]; // 进程活动信息文件目录
char strIDCConnStr[201]; // 数据库连接参数
char strAlarmValue[11];
double dusep=0.00;   // CPU的利用率

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

  // 获取CPU报告
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
    printf("此程序用于把本服务器的CPU使用率信息记录在文件，它运行在需要监控的服务器上。\n");

    return -1;
  }

  // 关闭全部的信号和输入输出
  // 设置信号,在shell状态下可用 "kill + 进程号" 正常终止些进程
  // 但请不要用 "kill -9 +进程号" 强行终止
  CloseIOAndSignal(); signal(SIGINT,CallQuit); signal(SIGTERM,CallQuit);

  if (logfile.Open("/tmp/ccfree/log/cpustat.log","a+") == false)
  {
    printf("logfile.Open(/tmp/ccfree/log/cpustat.log) failed.\n"); return -1;
  }

  // 获取CPU报告
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
