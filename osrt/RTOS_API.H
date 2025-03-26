/******************************************************************************/
/* rtos_api.h                                                                 */
/*                                                                            */
/* Этот файл содержит объявления функций пользовательского API.               */
/* Его необходимо включать во все модули пользовательских приложений.         */
/*                                                                            */
/*                                                                            */
/* Автор: Кожевников К.А.                                                     */
/*                                                                            */
/* Дата создания: 4 июля 2000 г.                                              */
/******************************************************************************/

#ifndef  __RTOS_API_H
#define  __RTOS_API_H

#include  "hardware.h"
#include  "log.h"

/******************************************************************************/
/* Макроопределения                                                           */
/******************************************************************************/

/* Объявление задачи */
#define DeclareTask(taskID)                                                    \
            extern const _TaskStruct taskID[1];                                \
            WfDeclareName (taskID)

/* Объявление ресурса */
#define  DeclareResource(ResID, priority)                                      \
            WfDeclareName (ResID);                                             \
            enum {ResID = priority};

/* Объявление тела задачи */
#define TASK(taskID, priority)                                                 \
            void taskID##body(void);                                           \
            const _TaskStruct taskID[1] =                                      \
               { {taskID##body, priority} };                                   \
            void taskID##body(void)

/* Активизация задачи из задачи */
#define  ActivateTask(taskID)                                                  \
            WfAssignName (taskID);                                             \
            _Activate(taskID->entry, taskID->priority)

/* Захват ресурса */
#define  GetResource(ResID)                                                    \
            WfAssignName (ResID##name);                                        \
            _Get (ResID)

/* Освобождение ресурса */
#define  ReleaseResource(ResID)                                                \
            WfAssignName (ResID##name);                                        \
            _Release (ResID)

/* Запуск ОС */
#define  StartOS(TaskID)                                                       \
            WfAssignName (TaskID##name);                                       \
            _Start (TaskID->entry, TaskID->priority)

/******************************************************************************/
/* Определения типов                                                          */
/******************************************************************************/

/* Указатель на функцию типа 'void fn(void)' */
typedef void (*_pfn)(void);

/* Структура с информацией о задаче (точка входа и приоритет) */
typedef struct
{
   _pfn entry;
   char priority;
} _TaskStruct, *_PTaskStruct;

/* Тип задачи */
typedef _PTaskStruct TTask;

/* Тип ресурса */
typedef  char  TResource;

/******************************************************************************/
/* Функции API для управления задачами                                        */
/******************************************************************************/

/* Активизация задачи из задачи */
void  _Activate (_pfn entry, char priority);

/* Завершение задачи */
void  TerminateTask (void);

/******************************************************************************/
/* Функции API для управления ресурсами                                       */
/******************************************************************************/

/* Захват ресурса */
void  _Get (TResource priority);

/* Освобождение ресурса */
void  _Release (TResource priority);

/******************************************************************************/
/* Функции API для управления работой ОС                                      */
/******************************************************************************/

/* Запуск ОС */
void  _Start (_pfn entry, char priority);

/* Завершение ОС */
void  ShutdownOS (void);

#endif
