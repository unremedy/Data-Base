
#ifndef DATABASE_INDUSTRYFACULTY_H
#define DATABASE_INDUSTRYFACULTY_H

#include "Faculty.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

struct CathedraIF{
    std::string NameCathedra;
    std::map<std::string, size_t> Discipline;
    ~CathedraIF(){
        NameCathedra = "";
        Discipline.clear();
    }
};

struct Organization{
    std::string NameOrganization;
    std::map<std::string, size_t> DisciplineOrg;
    ~Organization(){
        NameOrganization = "";
        DisciplineOrg.clear();
    }
};

class IndustryFaculty : public Faculty{
public:
    std::string NameIF;
    std::string NUK;
    size_t NumCathedra = 0;
    size_t NumOrganizations = 0;
    std::vector<CathedraIF> AllCathedra;
    std::vector<Organization> AllOrganizations;

    IndustryFaculty() = default;
    ~IndustryFaculty(){
        Destruct();
    }
    void Destruct(){
        NameIF = "";
        NUK = "";
        NumCathedra = 0;
        NumOrganizations = 0;
        AllCathedra.clear();
        AllOrganizations.clear();
    }

    size_t NumOfUniqueDisciplines(const std::string &FileName) override;
    size_t FindFaculty(const std::string &FileName) override;

    friend std::ostream& operator<<(std::ostream& out, const IndustryFaculty& indfac){
        out << indfac.NameIF << std::endl;
        out << indfac.NUK << std::endl;
        out << indfac.NumCathedra << std::endl;
        for (size_t i = 0; i < indfac.NumCathedra; ++i) {
            out << indfac.AllCathedra[i].NameCathedra << std::endl;
            auto print = [&](auto element) { out << element.first << ", " << element.second << std::endl; };
            std::for_each(indfac.AllCathedra[i].Discipline.begin(), indfac.AllCathedra[i].Discipline.end(),
                          print);
            out << std::endl;
        }
        for (size_t i = 0; i < indfac.NumOrganizations; ++i) {
            out << indfac.AllOrganizations[i].NameOrganization << std::endl;
            auto print = [&](auto element) { out << element.first << ", " << element.second << std::endl; };
            std::for_each(indfac.AllOrganizations[i].DisciplineOrg.begin(), indfac.AllOrganizations[i].DisciplineOrg.end(),
                          print);
            out << std::endl;
        }
        return out;
    }

};
#endif //DATABASE_INDUSTRYFACULTY_H
