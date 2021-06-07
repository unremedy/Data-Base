#include "BasicFacultyFunctions.h"

void BasicFacultyFunctions::WriteALine_B(const std::string &FileName) {
    size_t NumDiscipline = 0;
    std::string name_discipline;
    size_t num_teachers;
    BasicFaculty NewFaculty;
    Cathedra NCath;

    std::cout << "Enter name of faculty" << std::endl;
    getline(std::cin, NewFaculty.NameBF);
    std::cout << "Enter name of NUK" << std::endl;
    getline(std::cin, NewFaculty.NUK);
    std::cout << "Enter number of cathedra" << std::endl;
    std::cin >> NewFaculty.NumCathedra;
    for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
        std::cout << "Enter name of cathedra" << std::endl;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        getline(std::cin, NCath.NameCathedra);
        std::cout << "Enter number of disciplines" << std::endl;
        std::cin >> NumDiscipline;
        for (size_t k = 0; k < NumDiscipline; ++k) {
            std::cout << "Enter name of discipline" << std::endl;
            std::cin >> name_discipline;
            std::cout << "Enter number of teachers" << std::endl;
            std::cin >> num_teachers;
            NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
        }
        NewFaculty.AllCathedra.push_back(NCath);
        NCath.Discipline.clear();
    }

    std::cout << NewFaculty << std::endl;

    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::ofstream WriteBF(FileName, std::ios::app); //std::ios::out
    if (WriteBF.is_open()) {
        WriteBF << '-' << std::endl;
        WriteBF << NewFaculty.NameBF << std::endl;
        WriteBF << NewFaculty.NUK << std::endl;
        WriteBF << NewFaculty.NumCathedra << std::endl;
        for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
            WriteBF << '{' << std::endl;
            WriteBF << NewFaculty.AllCathedra[i].NameCathedra << std::endl;
            auto record = [&](auto element) { WriteBF << element.first << ", " << element.second << std::endl; };
            std::for_each(NewFaculty.AllCathedra[i].Discipline.begin(), NewFaculty.AllCathedra[i].Discipline.end(),
                          record);
            std::cout << std::endl;
        }
        WriteBF << '{' << std::endl;
        WriteBF.close();
    } else {
        std::cout << "error_write" << std::endl;
    }
}

void BasicFacultyFunctions::ReadDB_B(const std::string &FileName) {
    BasicFaculty NewFaculty;
    std::string String;
    std::ifstream ReadBF(FileName, std::ios::in);
    if (ReadBF.is_open()) {
        while (!ReadBF.eof()) {
            getline(ReadBF, String);
            std::cout << String << std::endl;
        }
        ReadBF.close();
    } else {
        std::cout << "error_read" << std::endl;
    }
}

size_t BasicFacultyFunctions::NumOfFaculty_B(const std::string &FileName) {
    size_t counter = 0;
    std::string String;
    std::ifstream ReadBF(FileName, std::ios::in);
    if (ReadBF.is_open()) {
        while (!ReadBF.eof()) {
            getline(ReadBF, String);
            if (String == "-") {
                ++counter;
            }
        }
        ReadBF.close();
    } else {
        std::cout << "error_read" << std::endl;
    }
    return counter;
}

void BasicFacultyFunctions::ReadDBToVector_B(const std::string &FileName, std::vector<BasicFaculty> &vectorOfBF) {
    size_t NumFac = NumOfFaculty_B(FileName);
    std::string name_discipline;
    size_t num_teachers;
    BasicFaculty NewFaculty;
    Cathedra NCath;
    std::string String;
    std::ifstream ReadBF(FileName, std::ios::in);
    if (ReadBF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            getline(ReadBF, String);
            getline(ReadBF, NewFaculty.NameBF);
            getline(ReadBF, NewFaculty.NUK);
            ReadBF >> NewFaculty.NumCathedra;
            ReadBF.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(ReadBF, String);
            for (size_t i = 0; i < NewFaculty.NumCathedra; ++i) {
                getline(ReadBF, NCath.NameCathedra);
                do {
                    getline(ReadBF, String);
                    if (String != "{") {
                        size_t pos = String.find(',');
                        name_discipline = String.substr(0, pos);
                        num_teachers = std::stoi(String.substr(pos + 2));
                        NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
                    }
                } while (String != "{");

                NewFaculty.AllCathedra.push_back(NCath);
                NCath.Discipline.clear();
            }
            vectorOfBF.push_back(NewFaculty);
            NewFaculty.Destruct();
        }
        ReadBF.close();

    }
}

void BasicFacultyFunctions::ChangeALine_B(const std::string &FileName) {
    size_t NumDiscipline = 0;
    Cathedra NCath;
    std::string name_discipline;
    size_t num_teachers;

    size_t index = 0;
    size_t NumFac = NumOfFaculty_B(FileName);
    std::vector<std::string> NameFacVec(NumFac);
    std::vector<std::string>::iterator ItNameFacVec;
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    std::string Name;
    size_t Case = 0;

    std::cout << "enter name of faculty for changes: " << std::endl;
    getline(std::cin, Name);
    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = VectorOfBF[j].NameBF;
    }
    index = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));
    std::cout << "which parameter you want to change: " << std::endl;
    std::cout << "1: NameBF\n2: NUK\n3: NumCathedra" << std::endl;
    std::cin >> Case;
    switch (Case) {
        case 1:
            std::cout << "enter new basic faculty name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, Name);
            VectorOfBF[index].NameBF = Name;
            break;
        case 2:
            std::cout << "enter new NUK name: " << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            getline(std::cin, Name);
            VectorOfBF[index].NUK = Name;
            break;
        case 3:
            size_t number = 0;
            std::cout << "enter 1 to add cathedra, enter 2 to delete cathedra: " << std::endl;
            std::cin >> number;
            switch (number) {
                case 1:
                    std::cout << "Enter name of cathedra" << std::endl;
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    getline(std::cin, NCath.NameCathedra);
                    std::cout << "Enter number of disciplines" << std::endl;
                    std::cin >> NumDiscipline;
                    for (size_t k = 0; k < NumDiscipline; ++k) {
                        std::cout << "Enter name of discipline" << std::endl;
                        std::cin >> name_discipline;
                        std::cout << "Enter number of teachers" << std::endl;
                        std::cin >> num_teachers;
                        NCath.Discipline.insert(NCath.Discipline.end(), std::make_pair(name_discipline, num_teachers));
                    }
                    VectorOfBF[index].AllCathedra.push_back(NCath);
                    ++VectorOfBF[index].NumCathedra;
                    break;
                case 2:
                    if (VectorOfBF[index].NumCathedra == 1) {
                        std::cout << "faculty can't be without at least 1 cathedra" << std::endl;
                        break;
                    }
                    VectorOfBF[index].AllCathedra.pop_back();
                    --VectorOfBF[index].NumCathedra;
                    break;
            }
            break;


    }
    std::ofstream ChangeBF(FileName, std::ios::out);
    if (ChangeBF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            ChangeBF << '-' << std::endl;
            ChangeBF << VectorOfBF[k].NameBF << std::endl;
            ChangeBF << VectorOfBF[k].NUK << std::endl;
            ChangeBF << VectorOfBF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfBF[k].NumCathedra; ++i) {
                ChangeBF << '{' << std::endl;
                ChangeBF << VectorOfBF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeBF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfBF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfBF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeBF << '{' << std::endl;
        }
        ChangeBF.close();
    }
}

void BasicFacultyFunctions::ClearDB_B(const std::string &FileName) {
    std::ofstream ChangeBF(FileName, std::ios::out);
    if (ChangeBF.is_open()) {
        ChangeBF << ' ' << std::endl;
        ChangeBF.close();
    }
}

void BasicFacultyFunctions::SavePartOfDB_B(const std::string &FileName) {
    std::vector<BasicFaculty> OldVectorOfBF;
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(BFNameFile, OldVectorOfBF);
    std::string Name;
    size_t index1 = 0;
    size_t index2 = 0;
    size_t NumFac = NumOfFaculty_B(BFNameFile);
    std::vector<std::string> NameFacVec(NumFac);


    for (size_t j = 0; j < NumFac; ++j) {
        NameFacVec[j] = OldVectorOfBF[j].NameBF;
    }
    std::cout << "enter first name of faculty: " << std::endl;
    getline(std::cin, Name);
    index1 = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));

    std::cout << "enter second name of faculty: " << std::endl;
    getline(std::cin, Name);
    index2 = std::distance(NameFacVec.begin(), std::find(NameFacVec.begin(), NameFacVec.end(), Name));
    //std::cout << index1 << ":" << index2 << std::endl;
    for (size_t i = index1; i < index2 - index1 + 2; ++i) {
        VectorOfBF.push_back(OldVectorOfBF[i]);
    }
    //std::cout << "here" << std::endl;
    std::ofstream ChangeBF(FileName, std::ios::out);
    if (ChangeBF.is_open()) {
        for (size_t k = 0; k < index2 - index1 + 1; ++k) {
            ChangeBF << '-' << std::endl;
            ChangeBF << VectorOfBF[k].NameBF << std::endl;
            ChangeBF << VectorOfBF[k].NUK << std::endl;
            ChangeBF << VectorOfBF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfBF[k].NumCathedra; ++i) {
                ChangeBF << '{' << std::endl;
                ChangeBF << VectorOfBF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeBF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfBF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfBF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeBF << '{' << std::endl;
        }
        ChangeBF.close();
        //BFNameFileVec.push_back(FileName);
    } else {
        std::cout << "error_read" << std::endl;
    }
}

void BasicFacultyFunctions::DeleteALine_B(const std::string &FileName) {
    BasicFacultyFunctions BaFa;
    size_t position = BaFa.FindFaculty(FileName);
    size_t NumFac = NumOfFaculty_B(FileName) - 1;
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    VectorOfBF.erase(VectorOfBF.begin() + position);
    std::ofstream ChangeBF(FileName, std::ios::out);
    if (ChangeBF.is_open()) {
        for (size_t k = 0; k < NumFac; ++k) {
            ChangeBF << '-' << std::endl;
            ChangeBF << VectorOfBF[k].NameBF << std::endl;
            ChangeBF << VectorOfBF[k].NUK << std::endl;
            ChangeBF << VectorOfBF[k].NumCathedra << std::endl;
            for (size_t i = 0; i < VectorOfBF[k].NumCathedra; ++i) {
                ChangeBF << '{' << std::endl;
                ChangeBF << VectorOfBF[k].AllCathedra[i].NameCathedra << std::endl;
                auto record = [&](auto element) { ChangeBF << element.first << ", " << element.second << std::endl; };
                std::for_each(VectorOfBF[k].AllCathedra[i].Discipline.begin(),
                              VectorOfBF[k].AllCathedra[i].Discipline.end(),
                              record);
                std::cout << std::endl;
            }
            ChangeBF << '{' << std::endl;
        }
        ChangeBF.close();
    }
}

void BasicFacultyFunctions::SortByAlphabetFaculty_B(const std::string &FileName) {
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    std::sort(VectorOfBF.begin(), VectorOfBF.end(), [](const BasicFaculty& a, const BasicFaculty& b) {
        return a.NameBF < b.NameBF;
    });

    auto Print = [](auto element) {
        std::cout << "faculty:" << std::endl;
        std::cout << element << std::endl;
    };
    std::for_each(VectorOfBF.begin(), VectorOfBF.end(), Print);
    std::cout << std::endl;
}

void BasicFacultyFunctions::SortByNumCathedra_B(const std::string &FileName) {
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    std::sort(VectorOfBF.begin(), VectorOfBF.end(), [](const BasicFaculty& a, const BasicFaculty& b) {
        return a.NumCathedra <= b.NumCathedra;
    });

    auto Print = [](auto element) {
        std::cout << "faculty:" << std::endl;
        std::cout << element << std::endl;
    };
    std::for_each(VectorOfBF.begin(), VectorOfBF.end(), Print);
    std::cout << std::endl;
}

void BasicFacultyFunctions::FindByNumCathedra_B(const std::string &FileName) {
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    size_t number = 0;
    size_t counter = 0;
    std::cout << "Enter minimum number of cathedra " << std::endl;
    std::cin >> number;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for(size_t i = 0; i < VectorOfBF.size(); ++i){
        if(VectorOfBF[i].NumCathedra > number){
            std::cout << "faculty:" << std::endl;
            std::cout << VectorOfBF[i] << std::endl;
            ++counter;
        }
    }
    if (counter == 0){
        throw 1;
    }
}

void BasicFacultyFunctions::FindByNameDiscipline_B(const std::string &FileName) {
    std::vector<BasicFaculty> VectorOfBF;
    ReadDBToVector_B(FileName, VectorOfBF);
    std::string Name;
    size_t counter = 0;
    std::cout << "Enter name of discipline to find in faculty " << std::endl;
    getline(std::cin, Name);
    for(size_t i = 0; i < VectorOfBF.size(); ++i){
        for(size_t k = 0; k < VectorOfBF[i].NumCathedra; ++k){
            for(auto it = VectorOfBF[i].AllCathedra[k].Discipline.begin(); it != VectorOfBF[i].AllCathedra[k].Discipline.end(); ++it){
                if(it->first == Name){
                    ++counter;
                    std::cout << "faculty:" << std::endl;
                    std::cout << VectorOfBF[i] << std::endl;
                    k = VectorOfBF[i].NumCathedra;
                    break;
                }
            }

        }

    }
    if(counter == 0){
        throw 2;
    }

}