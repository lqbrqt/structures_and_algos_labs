#include <iostream>
#include <string>
#include <map>
#include <algorithm>
//task1

class Mem{
public:

    Mem(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 32; j++){
                dynamic[i][j] = -1;
                stack[j] = -1;
            }
        }
    }

    enum class Type { Byte = 1, Int = 2, Longint = 4 };

    std::int8_t stack [32];
    std::int8_t dynamic [4][32];

    bool NewPointer(std::string name, Mem::Type type) {

        short freeMemAddrBegin = 0;
        short freeMemAddrEnd = 0;
        short bytesNeeded = static_cast<short>(type);

        for (int i = 0; i < 32; i++){
            try {
                pointerNames.at(i);
            }catch (std::out_of_range& e){

                for (int j = 0; j < 32 * 4; j++){

                    auto currentBlock = std::find(std::begin(stack), std::end(stack), j ) ;

                    if ( currentBlock == std::end(stack)){
                        freeMemAddrEnd = j;
                    }else{
                        short endOfBlockAddr;

                        for(int k=0; k<32; k++){
                            try {
                                if (stack[k] == *currentBlock) {
                                    endOfBlockAddr = k + static_cast<short>(pointerNames.at(k).second);
                                    if (endOfBlockAddr + bytesNeeded >= 32 * 4) {
                                        return false;
                                    }
                                }
                            }catch (std::out_of_range& e){};
                        }

                        freeMemAddrBegin = endOfBlockAddr;
                        continue;
                    }

                    if(freeMemAddrEnd - freeMemAddrBegin >= bytesNeeded - 1){
                        stack[i] = freeMemAddrBegin;

                        pointerNames[i].first = name;
                        pointerNames[i].second = type;

                        return true;

                    }else{

                    }
                }

            }
        }

        return false;
    }

    bool WritePointer(std::string name, long value){
        auto currentPointerNamesStructure = std::find_if(pointerNames.begin(), pointerNames.end(), [name] (auto it) {return it.second.first == name;});
        if(currentPointerNamesStructure == pointerNames.end()){
            return false;
        }

        Type type = currentPointerNamesStructure->second.second;
        int stackAddr = currentPointerNamesStructure->first;
        int dynamicAddr = static_cast<int>(stack[stackAddr]);

        switch(type){
            case Type::Byte:{
                dynamic[dynamicAddr/32][dynamicAddr%32] = static_cast<std::int8_t>(value);
                break;
            }
            case Type::Int:{

                dynamic[dynamicAddr/32][dynamicAddr%32] = static_cast<std::int8_t>(value / 128);
                ++dynamicAddr;
                dynamic[dynamicAddr/32][dynamicAddr%32] = static_cast<std::int8_t>(value % 128);
                break;
            }
            case Type::Longint:{
                dynamic[dynamicAddr/32][dynamicAddr%32] = value / (128*128*128);
                ++dynamicAddr;
                dynamic[dynamicAddr/32][dynamicAddr%32] = abs(value / (128*128));
                ++dynamicAddr;
                dynamic[dynamicAddr/32][dynamicAddr%32] = abs(value / 128);
                ++dynamicAddr;
                dynamic[dynamicAddr/32][dynamicAddr%32] = value % 128;

                break;
            }
        }

    }
    int ReadPointer(std::string name){
        auto currentPointerNamesStructure = std::find_if(pointerNames.begin(), pointerNames.end(), [name] (auto it) {return it.second.first == name;});
        if(currentPointerNamesStructure == pointerNames.end()){
            return false;
        }

        Type type = currentPointerNamesStructure->second.second;
        int stackAddr = currentPointerNamesStructure->first;
        int dynamicAddr = static_cast<int>(stack[stackAddr]);

        long value;

        switch(type){
            case Type::Byte:{
                value = dynamic[dynamicAddr/32][dynamicAddr%32];
                break;
            }
            case Type::Int:{

                value = dynamic[dynamicAddr/32][dynamicAddr%32] * 128;
                ++dynamicAddr;
                value += dynamic[dynamicAddr/32][dynamicAddr%32];
                break;
            }
            case Type::Longint:{
                value = dynamic[dynamicAddr/32][dynamicAddr%32] * 128 * 128 * 128;
                ++dynamicAddr;
                value += dynamic[dynamicAddr/32][dynamicAddr%32] * (128*128);
                ++dynamicAddr;
                value += dynamic[dynamicAddr/32][dynamicAddr%32] * 128;
                ++dynamicAddr;
                value += dynamic[dynamicAddr/32][dynamicAddr%32];

                break;
            }
        }
        return value;
    }

    bool SetPointer(std::string lhs, std::string rhs){

        auto lhsPointerNamesStructure = std::find_if(pointerNames.begin(), pointerNames.end(), [lhs] (auto it) {return it.second.first == lhs;});
        auto rhsPointerNamesStructure = std::find_if(pointerNames.begin(), pointerNames.end(), [rhs] (auto it) {return it.second.first == rhs;});
        if(lhsPointerNamesStructure == pointerNames.end() || rhsPointerNamesStructure == pointerNames.end()){
            return false;
        }

        Type rhsType = rhsPointerNamesStructure->second.second;

        int lhsStackAddr = lhsPointerNamesStructure->first;
        int rhsStackAddr = rhsPointerNamesStructure->first;
        int rhsDynamicAddr = static_cast<int>(stack[rhsStackAddr]);

        stack[lhsStackAddr] = rhsDynamicAddr;

        pointerNames[lhsStackAddr].second = rhsType;
        return true;
    }

    bool FreePointer(std::string name){
        auto currentPointerNamesStructure = std::find_if(pointerNames.begin(), pointerNames.end(), [name] (auto it) {return it.second.first == name;});
        if(currentPointerNamesStructure == pointerNames.end()){
            return false;
        }

        pointerNames.erase(currentPointerNamesStructure);
        return true;
    }

    void printMem(){
        std::cout << "dynamic" << std::endl;
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < 32; j++){
                std::cout << static_cast<int>(dynamic[i][j]) << '\t';
            }
            std::cout << std::endl;
        }

        std::cout << "static" << std::endl;

        for(int i = 0; i < 32; i++){
            std::cout << static_cast<int>(stack[i]) << '\t';

        }

    }

private:

    std::map<short, std::pair<std::string, Type>> pointerNames;

};




int main() {
    Mem mem;
    mem.NewPointer("a", Mem::Type::Byte);

    mem.WritePointer("a", 10);

    mem.NewPointer("p", Mem::Type::Int);

    mem.NewPointer("e", Mem::Type::Longint);


    mem.WritePointer("p", 22);

    mem.WritePointer("p", 15000);
    mem.WritePointer("e", 140000);

    mem.SetPointer("c", "p");
    //mem.FreePointer("e");
    std::cout << mem.ReadPointer("a") << std::endl;

    mem.printMem();











}
