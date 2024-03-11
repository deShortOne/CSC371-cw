// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
// The root object that holds all data for 371todo. This
// class contains Projects, which in turn hold Tasks,
// which have a name, due date, completed status, and tags.
// -----------------------------------------------------

#ifndef TODOLIST_H
#define TODOLIST_H

#include "project.h"

using namespace nlohmann;

class TodoList
{
private:
    std::vector<Project> todoList;

public:
    TodoList();
    unsigned int size() const;
    Project &newProject(std::string projectIdent);
    bool addProject(const Project &project);
    Project &getProject(std::string projectIdent);
    bool deleteProject(std::string projectIdent);
    bool containsProject(const std::string &projectIdent) const noexcept;
    bool load(std::string filename);
    bool save(std::string filename);
    friend bool operator==(const TodoList &c1, const TodoList &c2);
    std::string str() const;
};

struct FileNotFoundError : public std::runtime_error
{
    explicit FileNotFoundError(const std::string &filename)
        : std::runtime_error("could not find file '" + filename + "'")
    {
        /* do nothing */
    }

    ~FileNotFoundError() override = default;
};

struct JSONFormatError : public std::runtime_error
{
    explicit JSONFormatError(const std::string &filename)
        : std::runtime_error("file '" + filename + "' does not have valid JSON data")
    {
        /* do nothing */
    }

    ~JSONFormatError() override = default;
};

#endif // TODOLIST_H
