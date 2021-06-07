#ifndef DATABASE_BASICFACULTYFUNCTIONS_H
#define DATABASE_BASICFACULTYFUNCTIONS_H

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <limits>
#include "BasicFaculty.h"

class BasicFacultyFunctions : public BasicFaculty{
public:
    std::string BFNameFile;
    void WriteALine_B(const std::string &FileName);
    void ReadDB_B(const std::string &FileName);
    static size_t NumOfFaculty_B(const std::string &FileName);
    void ReadDBToVector_B(const std::string &FileName, std::vector<BasicFaculty> &vectorOfBF);
    void ChangeALine_B(const std::string &FileName);
    void DeleteALine_B(const std::string &FileName);
    void ClearDB_B(const std::string &FileName);
    void SavePartOfDB_B(const std::string &FileName);
    void SortByAlphabetFaculty_B(const std::string &FileName);
    void SortByNumCathedra_B(const std::string &FileName);
    void FindByNumCathedra_B(const std::string &FileName);
    void FindByNameDiscipline_B(const std::string &FileName);
};


#endif //DATABASE_BASICFACULTYFUNCTIONS_H
