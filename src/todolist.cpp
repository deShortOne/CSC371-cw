// -----------------------------------------------------
// CSC371 Advanced Object Oriented Programming (2023/24)
// Department of Computer Science, Swansea University
//
// Author: 2010573
//
// Canvas: https://canvas.swansea.ac.uk/courses/44636
// -----------------------------------------------------
#include <fstream>
#include <iostream>
#include <sstream>

#include "lib_json.hpp"
#include "todolist.h"

/**
 * Construct a new Todo List
 *
 */
TodoList::TodoList() : todoList(std::vector<Project>()) {}

/**
 * Returns number of projects.
 *
 * @return unsigned int number of projects
 */
unsigned int TodoList::size() const
{
    return this->todoList.size();
}

/**
 * Returns a project with that identifier. If a project already exists with
 * that specified identifier, then that project is returned, otherwise new
 * project is created and inserted.
 *
 * @param projectIdent project identifier
 * @return Project
 */
Project &TodoList::newProject(std::string projectIdent)
{
    for (Project &i : todoList)
    {
        if (!i.getIdent().compare(projectIdent))
        {
            return i;
        }
    }

    Project newProj{projectIdent};
    this->todoList.push_back(newProj);
    return this->todoList[todoList.size() - 1];
}

/**
 * Inserts the project into the list unless another project with the same
 * identifier already exists.
 *
 * @param project to be inserted
 * @return true if project is inserted into list, false otherwise
 */
bool TodoList::addProject(const Project &project)
{
    for (Project &i : this->todoList)
    {
        if (!i.getIdent().compare(project.getIdent()))
        {
            for (const Task &j : project.getTasks())
            {
                i.addTask(j);
            }
            return false;
        }
    }

    this->todoList.push_back(project);
    return true;
}

/**
 * Returns project with the specified identifier. If no project with specified
 * identifier exists, then exception is thrown.
 *
 * @param projectIdent
 * @return Project&
 * @throw project with specified identifier not found
 */
Project &TodoList::getProject(std::string projectIdent)
{
    for (Project &i : this->todoList)
    {
        if (i.getIdent().compare(projectIdent) == 0)
        {
            return i;
        }
    }
    throw std::out_of_range("That project doesn't exist!");
}

/**
 * Removes the project with the specified identifier from the list.
 * If no project with the specified identifier is found, then exception is thrown.
 *
 * @param projectIdent
 * @return true
 * @throw project with specified identifier not found
 */
bool TodoList::deleteProject(std::string projectIdent)
{
    for (unsigned int i = 0; i < this->todoList.size(); i++)
    {
        if (!this->todoList[i].getIdent().compare(projectIdent))
        {
            this->todoList.erase(this->todoList.begin() + i);
            return true;
        }
    }
    throw std::out_of_range("That project doesn't exist!");
}

/**
 * Find project.
 *
 * @param projectIdent
 * @return true if project with specified identifier is found
 */
bool TodoList::containsProject(const std::string &projectIdent) const noexcept
{
    for (const Project &i : this->todoList)
    {
        if (!i.getIdent().compare(projectIdent))
        {
            return true;
        }
    }
    return false;
}
/**
 * Open the specified file and load the data into this todo list. If no file is found, exception
 * is thrown.
 * If the data was successfully loaded into the todo list, true is returned.
 * If the data in the file was not in JSON format, exception is thrown.
 * If duplicate projects with the same name are found, only one project is created.
 * TODO: If you attempt to load the same file twice, false is returned.
 *
 * @return true if data is loaded into todo list
 * @throw FileNotFoundError file doesn't exist
 * @throw JSONFormatError file doesn't contain a valid JSON object
 */

bool TodoList::load(std::string filename)
{
    std::ifstream f(filename);
    if (!f)
    {
        std::cout << "File does not exist" << std::endl;
        f.close();
        return false;
    }
    if (f.peek() == std::ifstream::traits_type::eof()) // empty file
    {
        f.close();
        return false;
    }
    json data;
    try
    {
        data = json::parse(f);
        f.close();
    }
    catch (const detail::exception &ex)
    {
        std::cerr << "Invalid json: " << ex.what() << std::endl;
        f.close();
        return false;
    }

    for (json::iterator project_iter = data.begin(); project_iter != data.end(); ++project_iter)
    {
        Project newProject{project_iter.key()};
        auto taskList = project_iter.value();

        for (auto task = taskList.begin(); task != taskList.end(); ++task)
        {
            Task newTask{task.key()};

            auto taskValues = task.value();
            if (taskValues.contains("completed"))
            {
                newTask.setComplete(taskValues["completed"].dump().compare("false"));
            }
            if (taskValues.contains("dueDate"))
            {
                std::string jsonToDate = taskValues["dueDate"].dump();
                std::string dateArgs = jsonToDate.substr(1, jsonToDate.length() - 2);
                Date date{dateArgs};
                newTask.setDueDate(date);
            }
            if (taskValues.contains("tags"))
            {
                auto tagLis = taskValues["tags"];
                for (auto tag = tagLis.begin(); tag != tagLis.end(); ++tag)
                {
                    std::string tagName = (*tag).dump();
                    newTask.addTag(tagName.substr(1, tagName.size() - 2));
                }
            }
            newProject.addTask(newTask);
        }
        this->todoList.push_back(newProject); // TODO!!!! Don't like how we have to add at the end
    }
    return true;
}

/**
 * Saves data to file.
 *
 * @param filename
 * @return true
 * @throw FileNotFoundError file not found
 */
bool TodoList::save(std::string filename)
{
    auto jsonToSave = json::parse(this->str());

    std::ofstream myFile;
    myFile.open(filename, std::ios_base::out | std::ofstream::trunc);
    if (!myFile.is_open())
    {
        throw FileNotFoundError(filename);
    }
    myFile << jsonToSave;
    myFile.close();
    return true;
}

/**
 * Equality operator, compares tasks ignores order.
 *
 * @param c1
 * @param c2
 * @return true if both TodoList are the same
 */
bool operator==(const TodoList &c1, const TodoList &c2)
{
    if (c1.todoList.size() != c2.todoList.size())
    {
        return false;
    }

    for (Project project : c1.todoList)
    {
        bool foundProject = false;
        for (Project project2 : c2.todoList)
        {
            if (project == project2)
            {
                foundProject = true;
                break;
            }
        }

        if (!foundProject)
        {
            return false;
        }
    }
    return true;
}

/**
 * Returns JSON representation of the list of projects stored.
 *
 * @return std::string
 */
std::string TodoList::str() const
{
    if (todoList.empty())
    {
        return "{}";
    }
    std::stringstream ss;
    ss << "{";
    for (const Project &project : todoList)
    {
        ss << "\"" << project.getIdent() << "\":"
           << project.str()
           << ",";
    }
    ss.seekp(-1, ss.cur); // remove last ,

    ss << "}";
    return ss.str();
}
