/******************************************************************************/
/* task.c                                                                     */
/*                                                                            */
/* Этот файл содержит все основные модули и функции, необходимые для          */
/* управления задачами в OS class A                                           */
/*                                                                            */
/* Автор: Кожевников К.А.                                                     */
/*                                                                            */
/* Дата создания: 10 июля 2000 г.                                             */
/******************************************************************************/

#include  "rtos_api.h"
#include  "sys.h"

/******************************************************************************/
/* Определения системных функций                                              */
/******************************************************************************/

/* Планировщик задач */
void _Schedule (char task)
{
     char Cur,  Old;
     char prior;

     Cur = gRunningTask;
     Old = _NULL;
     prior = gTaskQueue[task].eff_priority;

     /* Находим хвост подсписка задач с приоритетом prior. */
     while (Cur != _NULL && gTaskQueue[Cur].eff_priority >= prior)
     {
         Old = Cur;
         Cur = gTaskQueue[Cur].link;
     }

     /* Вставляем задачу в список. */
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

/* Диспетчер задач */
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
/* Функции API                                                                */
/******************************************************************************/

/* Активизация из задач */
void _Activate (_pfn entry, char priority)
{
     char OurTask, NewPlace;

     DI();
     OurTask = gRunningTask;

     /* Определение места для задачи в очереди */
     NewPlace = gFreeTask;
     gFreeTask = gTaskQueue[gFreeTask].link;

     /* Запоминаем параметры задачи */
     gTaskQueue[NewPlace].eff_priority = priority;
     gTaskQueue[NewPlace].priority = priority;
     gTaskQueue[NewPlace].entry = entry;

     /* Планирование задачи */
     _Schedule (NewPlace);

     WfActivateTask (NewPlace, priority);

     /* Запуск в случае необходимости */
     if (OurTask != gRunningTask)
     {
        _Dispatch (OurTask);
     }

     EI();
}

/* Завершение задачи */
void TerminateTask (void)
{
     char OurTask;

     DI();

     /* Удаляем задачу из списка задач. Помещаем структуру в список свободных. */
     OurTask = gRunningTask;
     gRunningTask = gTaskQueue[OurTask].link;
     gTaskQueue[OurTask].link = gFreeTask;
     gFreeTask = OurTask;

     WfTerminateTask (OurTask);
     EI();
}
