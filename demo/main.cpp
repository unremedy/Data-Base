
#include "FunctionsFileSystem.h"

int main() {
    try{
        ChooseTheFile();
    }
    catch(int i){
        if(i == 1){
            std::cout << "No cathedra with such number" << std::endl;
        } else if(i == 2){
            std::cout << "Faculty with such discipline name not found" << std::endl;
        }
    }
    return 0;
}
