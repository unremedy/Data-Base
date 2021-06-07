#include "University.h"
#include <iostream>
#ifndef DATABASE_FACULTY_H
#define DATABASE_FACULTY_H
//extern std::string NameOfDBFile;
class Faculty : public University{
public:
    //std::string NameOfDBFile;
    std::string FacultyName;
    Faculty() = default;
    virtual size_t NumOfUniqueDisciplines(const std::string &FileName) = 0;
    virtual size_t FindFaculty(const std::string &FileName) = 0;
};
#endif //DATABASE_FACULTY_H
