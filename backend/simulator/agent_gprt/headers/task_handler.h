#ifndef HEADERS_TASK_HANDLER_H_
#define HEADERS_TASK_HANDLER_H_

#include <vector>

#include "../headers/task.h"

using namespace std;

class TaskHandler{
public:
    vector<Task*> create_df_tasks(const char*,int);
    vector<Task*> read_tasks_from_json(string path, int);
    Task* createTask();
    Task* cloneTask(Task*);
    ~TaskHandler();
};


#endif /* HEADERS_TASK_HANDLER_H_ */
