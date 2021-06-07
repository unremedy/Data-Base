
#ifndef DATABASE_GYBRIDFACULTYFUNCTIONS_H
#define DATABASE_GYBRIDFACULTYFUNCTIONS_H

#include <string>
#include <iostream>
#include "IndustryFacultyFunctions.h"
#include "BasicFacultyFunctions.h"
class GybridFacultyFunctions : public IndustryFacultyFunctions, public BasicFacultyFunctions{
public:
    std::string GFNameFile;
    void WriteALine_G(const std::string &FileName);
    void ReadDB_G(const std::string &FileName);
    static size_t NumOfFaculty_G(const std::string &FileName);
    void ReadDBToVector_G(const std::string &FileName, std::vector<IndustryFaculty> &vectorOfBF);
    void ChangeALine_G(const std::string &FileName);
    void DeleteALine_G(const std::string &FileName);
    void ClearDB_G(const std::string &FileName);
    void SavePartOfDB_G(const std::string &FileName);
    void SortByAlphabetFaculty_G(const std::string &FileName);
    void SortByNumCathedra_G(const std::string &FileName);
    void FindByNumCathedra_G(const std::string &FileName);
    void FindByNameDiscipline_G(const std::string &FileName);
};


#endif //DATABASE_GYBRIDFACULTYFUNCTIONS_H
