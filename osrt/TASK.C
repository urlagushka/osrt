/******************************************************************************/
/* task.c                                                                     */
/*                                                                            */
/* ���� ���� �������� ��� �������� ������ � �������, ����������� ���          */
/* ���������� �������� � OS class A                                           */
/*                                                                            */
/* �����: ���������� �.�.                                                     */
/*                                                                            */
/* ���� ��������: 10 ���� 2000 �.                                             */
/******************************************************************************/

#include  "rtos_api.h"
#include  "sys.h"

/******************************************************************************/
/* ����������� ��������� �������                                              */
/******************************************************************************/

/* ����������� ����� */
void _Schedule (char task)
{
     char Cur,  Old;
     char prior;

     Cur = gRunningTask;
     Old = _NULL;
     prior = gTaskQueue[task].eff_priority;

     /* ������� ����� ��������� ����� � ����������� prior. */
     while (Cur != _NULL && gTaskQueue[Cur].eff_priority >= prior)
     {
         Old = Cur;
         Cur = gTaskQueue[Cur].link;
     }

     /* ��������� ������ � ������. */
     gTaskQueue[task].link = Cur;
     if (Old == _NULL)
     {
         gRunningTask = task;
     }
     else
     {
         gTaskQueue[Old].link = task;
     }
}

/* ��������� ����� */
void _Dispatch (char source)
{
     do
     {
         EI();
         WfSwitchTask (gRunningTask);
         gTaskQueue[gRunningTask].entry();
         DI();
     }
     while (gRunningTask != source);
     WfSwitchTask (gRunningTask);
}

/******************************************************************************/
/* ������� API                                                                */
/******************************************************************************/

/* ����������� �� ����� */
void _Activate (_pfn entry, char priority)
{
     char OurTask, NewPlace;

     DI();
     OurTask = gRunningTask;

     /* ����������� ����� ��� ������ � ������� */
     NewPlace = gFreeTask;
     gFreeTask = gTaskQueue[gFreeTask].link;

     /* ���������� ��������� ������ */
     gTaskQueue[NewPlace].eff_priority = priority;
     gTaskQueue[NewPlace].priority = priority;
     gTaskQueue[NewPlace].entry = entry;

     /* ������������ ������ */
     _Schedule (NewPlace);

     WfActivateTask (NewPlace, priority);

     /* ������ � ������ ������������� */
     if (OurTask != gRunningTask)
     {
        _Dispatch (OurTask);
     }

     EI();
}

/* ���������� ������ */
void TerminateTask (void)
{
     char OurTask;

     DI();

     /* ������� ������ �� ������ �����. �������� ��������� � ������ ���������. */
     OurTask = gRunningTask;
     gRunningTask = gTaskQueue[OurTask].link;
     gTaskQueue[OurTask].link = gFreeTask;
     gFreeTask = OurTask;

     WfTerminateTask (OurTask);
     EI();
}
