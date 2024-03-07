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

/**
 * Creates task with identifier string.
 *
 * @param ident identifier for this task
 */
Task::Task(std::string ident) : ident(ident),
                                tagContainer(std::vector<std::string>()),
                                dueDate(Date()),
                                complete(false)
{
}

/**
 * Returns this object's identifier.
 *
 * @return identifier
 */
std::string Task::getIdent() const
{
    return this->ident;
}

/**
 * Sets the identifier.
 *
 * @param ident the new identifier
 */
void Task::setIdent(const std::string ident)
{
    this->ident = ident;
}

/**
 * Add specified tag if not already stored. Return true if tag is added, false otherwise.
 *
 * @param tag tag to be inserted
 * @return true if tag is added
 */
bool Task::addTag(const std::string tag)
{
    if (containsTag(tag))
    {
        return false;
    }

    tagContainer.push_back(tag);
    return true;
}

/**
 * Remove specified tag from list. Return true if removed, throws exception otherwise.
 *
 * @param tag tag to be removed
 * @return true if tag is removed
 */
bool Task::deleteTag(const std::string tag)
{
    if (!containsTag(tag))
    {
        throw std::out_of_range("tag not found");
    }

    for (unsigned long int i = 0; i < tagContainer.size(); i++)
    {
        if (tagContainer[i] == tag)
        {
            tagContainer.erase(tagContainer.begin() + i);
            return true;
        }
    }
    throw std::out_of_range("pulled a houdini");
}

/**
 * Returns unsigned int of the number of tags this task contains.
 *
 * @return unsigned int of tags stored
 */
unsigned int Task::numTags() const
{
    return this->tagContainer.size();
}

/**
 * Returns true if specificed tag exists in list
 *
 * @param tag the tag to find
 * @return returns true if tag exists in list, false otherwise
 */
bool Task::containsTag(const std::string tag) const
{
    for (std::string tagItem : tagContainer)
    {
        if (tagItem == tag)
        {
            return true;
        }
    }
    return false;
}

/**
 * Returns the tags stored in task.
 *
 * @return std::set<std::string>
 */
std::vector<std::string> Task::getTags() const
{
    return tagContainer;
}

/**
 * Returns date object stored in task.
 *
 * @return date object
 */
Date &Task::getDueDate()
{
    return dueDate;
}

/**
 * Sets the due date for the task.
 *
 * @param dueDate due date to be stored
 */
void Task::setDueDate(const Date &dueDate)
{
    this->dueDate = dueDate;
}

/**
 * Sets the status of task.
 *
 * @param isComplete bool if task is complete
 */
void Task::setComplete(const bool isComplete)
{
    this->complete = isComplete;
}

/**
 * Returns bool of task completion.
 *
 * @return bool isComplete
 */
bool Task::isComplete() const
{
    return this->complete;
}

/**
 * Returns true if the tasks are the same.
 *
 * @param rhs task to compare
 * @return true if tasks are the same, false otherwise
 */
bool Task::operator==(const Task &rhs) const
{
    return rhs.ident == this->ident &&
           rhs.tagContainer == this->tagContainer &&
           rhs.dueDate == this->dueDate &&
           rhs.complete == this->complete;
}

/**
 * FIXME: include {} at the start and end
 * Create JSON representation of the data in the task.
 *
 * @return JSON represention of task
 */
std::string Task::str() const
{
    std::stringstream ss;
    ss << "\"" << this->ident << "\":{"
       << "\"completed\":" << (this->complete ? "true" : "false")
       << ",\"dueDate\":\"" << this->dueDate.str() << "\""
       << ",\"tags\":[";

    if (this->tagContainer.size())
    {
        for (const std::string &i : this->tagContainer)
        {
            ss << "\"" << i << "\",";
        }
        ss.seekp(-1, ss.cur); // remove last ,
    }

    ss << "]}";
    return ss.str();
}
