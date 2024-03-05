// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <sstream>
#include "project.h"

// TODO Write a constructor that takes one parameter, a string identifier and
// initialises the object and member data.
//
// Example:
//  Project p{"projectIdent"};
Project::Project(std::string ident) : ident(ident), tasks(std::vector<Task>()) {}
// TODO Write a function, size, that takes no parameters and returns an unsigned
// int of the number of Tasks in the Project contains.
//
// Example:
//  Project p{"projectIdent"};
//  auto size = p.size();
unsigned int Project::size() const noexcept
{
    return this->tasks.size();
}
// TODO Write a function, getIdent, that returns the identifier for the Project.
//
// Example:
//  Project pObj{"projectIdent"};
//  auto ident = pObj.getIdent();
const std::string &Project::getIdent() const noexcept
{
    return ident;
}
// TODO Write a function, setIdent, that takes one parameter, a string for a new
// Project identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.setIdent("projectIdent2");
void Project::setIdent(std::string pIdent) noexcept
{
    this->ident = pIdent;
}
// TODO Write a function, newTask, that takes one parameter, a Task identifier,
// (a string) and returns the Task object as a reference. If an object with the
// same identifier already exists, then the existing object should be returned.
// Throw a std::runtime_error if the Task object cannot be inserted into the
// container for whatever reason.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
Task &Project::newTask(const std::string &tIdent) // throw error?
{
    for (Task &i : this->tasks)
    {
        if (!i.getIdent().compare(tIdent))
        {
            return i;
        }
    }

    Task task{tIdent};
    this->tasks.push_back(task);
    return this->tasks[this->tasks.size() - 1]; // to not return local variable
}
// TODO Write a function, addTask, that takes one parameter, a Task object, and
// returns true if the object was successfully inserted. If an object with the
// same identifier already exists, then:
//  - the tags should be merged
//  - completed status overwritten by the task being added
//  - dueDate overwritten by the task being added
//  - false should be returned.
//
// Example:
//  Project pObj{"projectIdent"};
//  Task tObj{"taskIdent"};
//  pObj.addTask(tObj);
bool Project::addTask(Task task)
{
    auto position = std::find(this->tasks.begin(), this->tasks.end(), task);
    if (position != this->tasks.end()) // found
    {
        // TODO!!!!!!!!!!!!!!!!! need to get tags that exist in task
        // merge tags
        // for (const std::string &i : task.tagContainer)
        // {
        // }
        position->setComplete(task.isComplete());
        position->setDueDate(task.getDueDate());
        return false;
    }
    this->tasks.push_back(task);
    return true;
}
// TODO Write a function, getTask, that takes one parameter, a Task identifier
// (a string) and returns the Task as a reference. If no Task exists, throw an
// appropriate exception.
//
// Hint:
//  See the test scripts for the exception expected.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  auto tObj = pObj.getTask("newTaskName");
Task &Project::getTask(const std::string &tIdent)
{
    for (Task &i : this->tasks)
    {
        if (!i.getIdent().compare(tIdent))
        {
            return i;
        }
    }

    throw NoTaskError(tIdent);
}
// TODO Write a function, deleteTask, that takes one parameter, a Task
// identifier (a string), deletes it from the container, and returns true if the
// Task was deleted. If no Task exists, throw an appropriate exception.
//
// Example:
//  Project pObj{"projectIdent"};
//  pObj.newTask("newTaskName");
//  bool result = pObj.deleteTask("newTaskName");
bool Project::deleteTask(const std::string &tIdent)
{
    for (unsigned int i = 0; i < this->tasks.size(); i++)
    {
        if (!this->tasks[i].getIdent().compare(tIdent))
        {
            this->tasks.erase(begin() + i);
            return true;
        }
    }
    throw NoTaskError(tIdent);
}
// TODO Write an == operator overload for the Project class, such that two
// Project objects are equal only if they have the same identifier and same
// Tasks.
//
// Example:
//  Project pObj{"projectIdent1"};
//  pObj.newTask("newTaskName");
//  Project pObj1{"projectIdent2"};
//  if(pObj1 == pObj2) {
//    ...
//  }
bool operator==(const Project &c1, const Project &c2)
{
    bool sameTasks = c1.tasks.size() == c2.tasks.size();
    int numberOfTasks = c1.tasks.size();
    int c1Counter = 0;

    while (sameTasks && c1Counter != numberOfTasks)
    {
        Task task1 = c1.tasks[c1Counter];
        bool sameTaskFound = false;
        for (int i = 0; i < numberOfTasks; i++)
        {
            Task task2 = c2.tasks[i];
            if (task1 == task2)
            {
                sameTaskFound = true;
                break;
            }
        }
        sameTasks = sameTaskFound;
    }

    // https://stackoverflow.com/a/12648810 vector comparisons
    return !c1.ident.compare(c2.ident) && sameTasks;
}

// TODO Write a function, str, that takes no parameters and returns a
// std::string of the JSON representation of the data in the Project.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Project pObj{"projectIdent"};
//  std::string s = pObj.str();
std::string Project::str() const
{

    std::stringstream ss;
    ss << "\"" << this->ident << "\":{";

    for (const Task &i : this->tasks)
    {
        ss << i.str() << ",";
    }
    ss.seekp(-1, ss.cur); // remove last ,
    ss << "}";

    return ss.str();
}
