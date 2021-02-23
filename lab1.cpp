#include <iostream>
#include <algorithm>
#include <set>
#include <string>
#include <sstream>



//Task 1
template<typename T>
void printSet(const std::set<T>& A){
    std::cout << "Total set size: " << A.size() << std::endl;
    std::cout << "{ ";
    for(auto it = A.begin(); it!=A.end(); ++it ){
        std::cout << *it << ' ';
    }
    std::cout << "}" << std::endl;

}

template<typename T>
std::set<T> findCrossing(const std::set<T>& A, const std::set<T>& B){
    std::set<T> out;

    for(auto it = A.begin(); it!=A.end(); ++it ){
        if(B.find(*it) != B.end()){
            out.insert(*it);
        }
    }

    return out;
}

void splitIntoSet(std::set<std::string>& A, std::string& s){
    std::stringstream ss;
    ss = std::stringstream(s);
    while (ss){
        std::string tmp;
        ss >> tmp;
        A.insert(tmp);
    }
}

int main(){

    setlocale(LC_ALL, "");

    {
        std::set<int> A;

        std::cout << "Enter numbers: (for exit enter \"exit\")" << std::endl;

        std::string inputString;
        while (true) {
            std::cout << ">> ";
            std::cin >> inputString;

            try {
                A.insert(std::stoi(inputString));
            }catch (...){
                std::transform(inputString.begin(), inputString.end(), inputString.begin(), tolower);
                if(inputString == "exit"){
                    break;
                }
                std::cout << "Entered a string, not a number\nTry again" << std::endl;
            }

        }

        printSet(A);
    }


    //Task 2


    {
        std::string firstSentence, secondSentence;
        std::set<std::string> firstSet, secondSet;

        std::cout << "Now enter two sentences" << std::endl;

        std::cout << "Enter first sentence: ";
        std::getline(std::cin, firstSentence);

        std::cout << "Enter second sentence: ";
        std::getline(std::cin, secondSentence);

        splitIntoSet(firstSet, firstSentence);
        splitIntoSet(secondSet, secondSentence);

        std::cout << "First word set:";
        printSet(firstSet);
        std::cout << "Second word set:";
        printSet(secondSet);

        std::cout << "Crossing elements is:";
        printSet(findCrossing(firstSet, secondSet));
    }



    //Task 3
    {

        const std::string Cyrillic = "йцукенгшщзхъфывапролджэячсмитьбюё";
        const std::string Latin = "qwertyuiopasdfghjklzxcvbnm";
        const std::string Digits = "1234567890";



        std::string inputString;

        std::cout << "Enter string with symbols in Latin, Cyrillic or numbers: ";
        std::getline(std::cin, inputString);

        std::set<char> S, A, B, C;

        std::stringstream ss;
        ss = std::stringstream(inputString);

        while (ss){
            char tmp;
            ss >> tmp;
            S.insert(tmp);
        }

        for(auto it = S.begin(); it!=S.end(); ++it ){
            std::cout << *it << ' ';

            if(Cyrillic.find(*it) != std::string::npos || Cyrillic.find(tolower(*it)) != std::string::npos) A.insert(*it);
            if(Latin.find(*it) != std::string::npos || Latin.find(tolower(*it)) != std::string::npos) B.insert(*it);
            if(Digits.find(*it) != std::string::npos || Digits.find(tolower(*it)) != std::string::npos) C.insert(*it);

        }

        std::cout<< "All Cyrillic: ";
        printSet(A);
        std::cout<< "All Latin: ";
        printSet(B);
        std::cout<< "All Digits: ";
        printSet(C);


    }
    return 0;



}