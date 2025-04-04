/******************************************************************************/
/* rtos_api.h                                                                 */
/*                                                                            */
/* ���� ���� �������� ���������� ������� ����������������� API.               */
/* ��� ���������� �������� �� ��� ������ ���������������� ����������.         */
/*                                                                            */
/*                                                                            */
/* �����: ���������� �.�.                                                     */
/*                                                                            */
/* ���� ��������: 4 ���� 2000 �.                                              */
/******************************************************************************/

#ifndef  __RTOS_API_H
#define  __RTOS_API_H

#include  "hardware.h"
#include  "log.h"

/******************************************************************************/
/* ����������������                                                           */
/******************************************************************************/

/* ���������� ������ */
#define DeclareTask(taskID)                                                    \
            extern const _TaskStruct taskID[1];                                \
            WfDeclareName (taskID)

/* ���������� ������� */
#define  DeclareResource(ResID, priority)                                      \
            WfDeclareName (ResID);                                             \
            enum {ResID = priority};

/* ���������� ���� ������ */
#define TASK(taskID, priority)                                                 \
            void taskID##body(void);                                           \
            const _TaskStruct taskID[1] =                                      \
               { {taskID##body, priority} };                                   \
            void taskID##body(void)

/* ����������� ������ �� ������ */
#define  ActivateTask(taskID)                                                  \
            WfAssignName (taskID);                                             \
            _Activate(taskID->entry, taskID->priority)

/* ������ ������� */
#define  GetResource(ResID)                                                    \
            WfAssignName (ResID##name);                                        \
            _Get (ResID)

/* ������������ ������� */
#define  ReleaseResource(ResID)                                                \
            WfAssignName (ResID##name);                                        \
            _Release (ResID)

/* ������ �� */
#define  StartOS(TaskID)                                                       \
            WfAssignName (TaskID##name);                                       \
            _Start (TaskID->entry, TaskID->priority)

/******************************************************************************/
/* ����������� �����                                                          */
/******************************************************************************/

/* ��������� �� ������� ���� 'void fn(void)' */
typedef void (*_pfn)(void);

/* ��������� � ����������� � ������ (����� ����� � ���������) */
typedef struct
{
   _pfn entry;
   char priority;
} _TaskStruct, *_PTaskStruct;

/* ��� ������ */
typedef _PTaskStruct TTask;

/* ��� ������� */
typedef  char  TResource;

/******************************************************************************/
/* ������� API ��� ���������� ��������                                        */
/******************************************************************************/

/* ����������� ������ �� ������ */
void  _Activate (_pfn entry, char priority);

/* ���������� ������ */
void  TerminateTask (void);

/******************************************************************************/
/* ������� API ��� ���������� ���������                                       */
/******************************************************************************/

/* ������ ������� */
void  _Get (TResource priority);

/* ������������ ������� */
void  _Release (TResource priority);

/******************************************************************************/
/* ������� API ��� ���������� ������� ��                                      */
/******************************************************************************/

/* ������ �� */
void  _Start (_pfn entry, char priority);

/* ���������� �� */
void  ShutdownOS (void);

#endif
