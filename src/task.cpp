// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------

#include <algorithm>
#include <string>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "task.h"

// TODO Write a constructor that takes one parameter, a string identifier
//  and initialises the object and member data.
//
// Example:
//  Task tObj{"Task Name"};
Task::Task(std::string ident) : ident(ident),
                                tagContainer(), // TODO  CHECK!!!!!!!!!!!!!!
                                dueDate(Date()),
                                complete(false)
{
}
// TODO Write a function, getIdent, that returns the identifier for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.getIdent();
std::string Task::getIdent() const
{
    return this->ident;
}
// TODO Write a function, setIdent, that takes one parameter, a string for a new
//  Task identifier, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  auto ident = tObj.setIdent("New Task Name");
void Task::setIdent(const std::string ident)
{
    this->ident = ident;
}
// TODO Write a function, addTag, that takes one parameters, a tag
//  string and returns true if the entry was inserted into the
//  container or false if the tag already existed.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
bool Task::addTag(const std::string tag)
{
    long unsigned int prevLength = tagContainer.size();
    tagContainer.insert(tag);
    return prevLength != tagContainer.size();
}
// TODO Write a function, deleteTag, that takes one parameter, a tag
// string, deletes it from the container, and returns true if the tag
// string was deleted. If no tag exists with that name, throw an appropriate
// exception.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.deleteTag("tag");
bool Task::deleteTag(const std::string tag)
{
    auto search = this->tagContainer.find(tag);
    if (search == this->tagContainer.end())
    {
        throw std::out_of_range("tag not found");
    }
    this->tagContainer.erase(tag);
    return true;
}
// TODO Write a function, numTags, that takes no parameters and returns an
// unsigned int of the number of tags in the Task contains.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.numTags();
unsigned int Task::numTags() const
{
    return this->tagContainer.size();
}
// TODO Write a function, containsTag, that takes one parameter, a tag string.
// If the tag exists, return true. Otherwise return false.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.addTag("tag");
//  tObj.containsTag("tag");
bool Task::containsTag(const std::string tag) const
{
    auto search = this->tagContainer.find(tag);
    return search != this->tagContainer.end();
}
// TODO Write a function, getDueDate, that returns the due date for the Task.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.getDueDate();
Date Task::getDueDate() const
{
    return dueDate;
}
// TODO Write a function, setDueDate, that takes one parameter, a Date for
// a new due date, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  Date d = Date();
//  tObj.setDueDate(d);
void Task::setDueDate(const Date dueDate)
{
    this->dueDate = dueDate;
}
// TODO Write a function, setComplete, that takes one parameter, a bool for
// a new completed state, and updates the member variable. It returns nothing.
//
// Example:
//  Task tObj{"Task Name"};
//  tObj.setComplete(true);
void Task::setComplete(const bool isComplete)
{
    this->complete = isComplete;
}
// TODO Write a function, isComplete, that returns the completed state for the
// Task.
//
// Example:
//  Task tObj{"Task Name"};
//  if(tObj.isComplete()) {
//   ...
//  }
bool Task::isComplete() const
{
    return this->complete;
}
// TODO Write an == operator overload for the Task class, such that two
// Tasks objects are equal only if they have the same identifier, dueDate,
// completed state, and tags.
//
// Example:
//  Task tObj1{"Task Name"};
//  Task tObj2{"Task Name"};
//  if(tObj1 == tObj2) {
//   ...
//  }
bool Task::operator==(const Task &rhs) const
{
    return rhs.ident == this->ident &&
           rhs.tagContainer == this->tagContainer &&
           rhs.dueDate == this->dueDate &&
           rhs.complete == this->complete;
}
// TODO Write a function, str, that takes no parameters and returns a
//  std::string of the JSON representation of the data in the Item.
//
// See the coursework specification for how this JSON should look.
//
// Example:
//  Item iObj{"itemIdent"};
//  std::string s = iObj.str();
std::string Task::str() const
{
    std::stringstream ss;
    ss << "\"" << this->ident << "\":{"
       << "\"completed\":" << (this->complete ? "true" : "false") // TODO!!! surely there's a better way..
       << ",\"dueDate\":\"" << this->dueDate.str() << "\""

       << ",\"tags\":[";

    for (const std::string &i : this->tagContainer)
    {
        ss << "\"" << i << "\",";
    }
    ss.seekp(-1, ss.cur); // remove last ,

    ss << "]}";
    return ss.str();
}
