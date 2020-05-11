#pragma once

#include "MysqlTask.h"
#include <stdint.h>

#define MAX_TASK_NUM 1000

class CTaskList
{
public:
    CTaskList();
    ~CTaskList(void);

    bool push(IMysqlTask* poTask);                  // �߼��߳��޸� 
    IMysqlTask* pop();				                // ���ݿ��߳��޸� 

private:
	uint16_t            m_uReadIndex;               // ���ݿ��߳��޸� 
	uint16_t            m_uWriteIndex;              // �߼��߳��޸�   
	IMysqlTask*         m_pTaskNode[MAX_TASK_NUM];
};



