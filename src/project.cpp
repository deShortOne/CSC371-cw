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

/**
 * Constructs a project with the specified identifier which stores a list of tasks.
 */
Project::Project(std::string ident) : ident(ident), tasks(std::vector<Task>()) {}

/**
 * Returns the number of tasks in this project.
 *
 * @return unsigned int of number of tasks
 */
unsigned int Project::size() const noexcept
{
    return this->tasks.size();
}

/**
 * Returns the identifier for this project.
 *
 * @return identifier of project
 */
const std::string &Project::getIdent() const noexcept
{
    return ident;
}

/**
 * Sets the identifier for this project.
 *
 * @param pIdent new project identifier
 */
void Project::setIdent(std::string pIdent) noexcept
{
    this->ident = pIdent;
}

/**
 * Returns tasks stored in this project.
 *
 * @return const TaskContainer&
 */
const TaskContainer &Project::getTasks() const noexcept
{
    return this->tasks;
}

// TODO: Throw a std::runtime_error if the Task object cannot be inserted into the
// container for whatever reason.
/**
 * Returns a task with the specified identifier. If a task with the specified identifier already
 * exists, then that task is returned, otherwise a new task is created and returned.
 *
 * @param tIdent identifier for the task
 * @return task with the specified identifier
 */
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

/**
 * Returns the iterator position of the task in the list.
 * Throws if specified task identifier not found in task list.
 *
 * @param tIdent
 * @return TaskContainer::iterator
 * @throw NoTaskError if task is not found
 */
TaskContainer::iterator Project::findTask(const std::string &tIdent)
{
    for (TaskContainer::iterator taskWithSameIdentifier = begin();
         taskWithSameIdentifier != end();
         taskWithSameIdentifier++)
    {
        if (taskWithSameIdentifier->getIdent() == tIdent)
        {
            return taskWithSameIdentifier;
        }
    }

    throw NoTaskError(tIdent);
}

/**
 * Returns true if sepcified task identifier is found.
 *
 * @param tIdent
 * @return true
 */
bool Project::containsTask(const std::string &tIdent) const noexcept
{
    for (Task task : tasks)
    {
        if (task.getIdent() == tIdent)
        {
            return true;
        }
    }
    return false;
}

/**
 * Inserts the specified task into the list.
 * If a task already exist with the specified task's identifier, then the tasks are merged and false is returned.
 * If task was inserted into the list, true is returned.
 *
 * @param task
 * @return true if task was added, false if merged
 */
bool Project::addTask(Task task)
{
    for (Task &taskCurr : tasks)
    {
        if (taskCurr.getIdent() == task.getIdent())
        {
            for (const std::string &i : task.getTags())
            {
                taskCurr.addTag(i);
            }
            taskCurr.setComplete(task.isComplete());
            taskCurr.setDueDate(task.getDueDate());
            return false;
        }
    }

    this->tasks.push_back(task);
    return true;
}

/**
 * Returns task with the specified identifier if it exists, exception thrown if
 * task with specified identifier is not found.
 *
 * @param tIdent task identifier
 * @return task with the identifier
 * @throw NNoTaskError if no task with specified identifier found
 */
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

/**
 * Removes the task with the specified identifier and true is returned.
 * If no task exists with the specified identifier, exception is thrown.
 *
 * @param tIdent task identifier
 * @return true if task was removed
 * @throw NoTaskError if no task with specified identifier found
 */
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

/**
 * Compares identifier and tasks.
 *
 * @param c1 first project to compare
 * @param c2 second project to compare
 * @return true if the first and second projects are the same
 */
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
        c1Counter++;
    }

    // https://stackoverflow.com/a/12648810 vector comparisons
    return !c1.ident.compare(c2.ident) && sameTasks;
}

/**
 * Returns JSON representation of this project.
 *
 * @return nlohmann::json
 */
nlohmann::json Project::json() const
{
    using json = nlohmann::json;
    return json::parse(str());
}

/**
 * Returns JSON representation of this project.
 *
 * @return JSON representation of this project
 */
std::string Project::str() const
{
    if (tasks.empty())
    {
        return "{}";
    }
    std::stringstream ss;
    ss << "{";

    for (const Task &i : this->tasks)
    {
        ss << "\"" << i.getIdent() << "\":" << i.str() << ",";
    }
    ss.seekp(-1, ss.cur); // remove last ,
    ss << "}";

    return ss.str();
}
