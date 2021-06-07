#ifndef DATABASE_BASICFACULTY_H
#define DATABASE_BASICFACULTY_H

#include "Faculty.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <map>

struct Cathedra{
    std::string NameCathedra;
    std::map<std::string, size_t> Discipline;
    ~Cathedra(){
        NameCathedra = "";
        Discipline.clear();
    }
};
class BasicFaculty : public Faculty{
public:
    std::string NameBF;
    std::string NUK;
    size_t NumCathedra = 0;

    std::vector<Cathedra> AllCathedra;
    BasicFaculty() = default;
    ~BasicFaculty(){
        Destruct();
    }
    void Destruct(){
        NameBF = "";
        NUK = "";
        NumCathedra = 0;
        AllCathedra.clear();
    }

    size_t NumOfUniqueDisciplines(const std::string &FileName) override;
    size_t FindFaculty(const std::string &FileName) override;

    friend std::ostream& operator<<(std::ostream& out, const BasicFaculty& basicfac){
        out << basicfac.NameBF << std::endl;
        out << basicfac.NUK << std::endl;
        out << basicfac.NumCathedra << std::endl;
        for (size_t i = 0; i < basicfac.NumCathedra; ++i) {
            out << basicfac.AllCathedra[i].NameCathedra << std::endl;
            auto print = [&](auto element) { out << element.first << ", " << element.second << std::endl; };
            std::for_each(basicfac.AllCathedra[i].Discipline.begin(), basicfac.AllCathedra[i].Discipline.end(),
                          print);
            out << std::endl;
        }
        return out;
    }


};

#endif //DATABASE_BASICFACULTY_H
