/******************************************************************************/
/* log.h                                                                      */
/*                                                                            */
/* ���� ���� �������� ���������� �������, �������������� ������ � ������      */
/* ��������� �������, � ����� �������, �������� ��� ������������              */
/*                                                                            */
/* �����: ���������� �.�.                                                     */
/*                                                                            */
/* ���� ��������: 29 �������� 2000 �.                                         */
/******************************************************************************/

#ifndef  __LOG_H
#define  __LOG_H

/******************************************************************************/
/* ��������������� �������                                                    */
/******************************************************************************/

/* �������� �� ��������� ����� */
void  DELAY (int t);

/******************************************************************************/
/* ������� ������ � ������ ��������������� ��������� �������                  */
/******************************************************************************/

#ifdef __LOGGING__

   void  WfInitLog         (char* filename);

   #define  WfDeclareName(Name)                                                \
      char* Name##name = #Name

   void  WfAssignName      (char* name);
   void  WfActivateTask    (char TaskNo, char priority);
   void  WfTerminateTask   (char TaskNo);
   void  WfSwitchTask      (char TaskNo);
   void  WfGetResource     (char TaskNo, char priority, char ceiling);
   void  WfReleaseResource (char TaskNo, char priority);
   void  WfStartOS         (void);
   void  WfShutdownOS      (void);

#else

   #define  WfInitLog(filename)
   #define  WfDeclareName(name)
   #define  WfAssignName(name)
   #define  WfActivateTask(TaskNo, priority)
   #define  WfTerminateTask(TaskNo)
   #define  WfSwitchTask(TaskNo)
   #define  WfGetResource(TaskNo, priority, ceiling)
   #define  WfReleaseResource(TaskNo, priority)
   #define  WfStartOS()
   #define  WfShutdownOS()

#endif

#endif
