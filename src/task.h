// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// A Task class contains multiple 'tags' (e.g., a tag might be 'home' and
// another tag could be 'uni'). A Task also has a identifier (e.g. 'Complete
// Coursework') a completed status (completed or not) and due date. An
// uninitialised due date (see date.cpp/date.h) means the task does not have a
// due date.
// -----------------------------------------------------

#ifndef TASK_H
#define TASK_H

#include "date.h"

class Task
{
private:
    std::string ident;
    std::vector<std::string> tagContainer;
    Date dueDate;
    bool complete;

public:
    Task(const std::string &ident);
    const std::string &getIdent() const noexcept;
    void setIdent(const std::string &ident) noexcept;
    bool addTag(const std::string &tag) noexcept;
    bool deleteTag(const std::string &tag);
    const unsigned int numTags() const noexcept;
    bool containsTag(const std::string &tag) const noexcept;
    const std::vector<std::string> getTags() const noexcept;
    Date &getDueDate() noexcept;
    void setDueDate(const Date &dueDate) noexcept;
    void setComplete(const bool isComplete) noexcept;
    bool isComplete() const noexcept;
    bool operator==(const Task &rhs) const noexcept;
    std::string str() const noexcept;
};

#endif // TASK_H
