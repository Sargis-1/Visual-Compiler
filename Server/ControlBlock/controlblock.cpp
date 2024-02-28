#include "controlblock.h"
#include "../Ram/test.h"
#include <QDebug>
// will be changed

ControlBlock* ControlBlock::cbinstance = nullptr;

ControlBlock::ControlBlock(): cbRC(RamController::getRamController())
{
    std::unique_ptr<Scope> global = std::make_unique<Function>("global", 0);
    scopes.push_back(std::move(global));
    // qDebug() << "CB created " << scopes.top()->scopeName << "\n";
    generalTypes = { {"bool", {1, "bool"}}, {"char", {1, "char"}}, {"short", {2, "short"}}, {"short int", {2, "short"}},
                     {"int", {4, "int"}}, {"float", {4, "float"}}, {"wchar_t", {2, "wchar_t"}},
                     {"long", {4, "int"}}, {"long int", {4, "int"}}, {"long long int", {8, "long long"}},
                     {"long long", {8, "long long"}},{"double", {8, "double"}},{"size_t", {8, "size_t"}},
                     {"long double", {8, "double"}} };

    statements = {"if", "else if", "else", "while", "for", "switch", "case:"};
}

void ControlBlock::processString(std::string &str, int row)
{
    //This string resolving logic will be changed later
    if(str == "main()"){//is Function call
        addnewScope(str, row + 1);
        //std::cout << "main scope must already be created\n";
    }
    else if(str == "if(){"){
        addnewScope(str, row);
        //std::cout << "if() scope must already be created\n";
    }else if(str == "}"){
        qDebug() << scopes.back()->scopeName << " must be released";
        scopes.pop_back();
        return;
    }

    addslottest(str);

    std::vector<std::string> tokens;//to store all tokens(words) in the given input
    std::string word;//to store current word

    std::istringstream iss(str);//to treat str as an input stream

    while (std::getline(iss, word, ' ')) {//getline() simply iterates over charachters and add them to word until given delimiter
        if(!word.empty()){                //is not met
            tokens.push_back(word);
        }
    }

    int length = str.size();

    //This for loop find which case is given as an input in current line
    for(int i = 0; i < tokens.size(); ++i){
        //std::cout << "current token " << tokens[i] << std::endl;
        if(generalTypes.find(tokens[i]) != nullptr){
            std::string extendedType;
            ++i;
            while(generalTypes.find(tokens[i]) != generalTypes.end()){
                extendedType += " " + tokens[i];
                ++i;
            }
            if(generalTypes.find(tokens[i]) == generalTypes.end()){
                --i;
            }
            std::string realType = generalTypes[extendedType].second;

            if(i + 2 < tokens.size() && tokens[i + 2] == "="){
                //processTypeLine(tokens[i], i, generalTypes[tokens[i]], i + 2);//variable of Type generalTypes[tokens[i]]
                //declaration and definition accroding to one of 4, 5, 6 cases below
                std::cout << "4 or 5 or 6" << std::endl;
                break;
            }else if(length >= 2 && str[length - 2] == ')'){//case 2 and 7, 9
                if(scopes.back()->scopeName != "global"){
                    if(str[length - 2] == ')' && str[length - 3] == '('){//case 7.2
                        //function pointer declaration returning tokens[i] with no parameters
                        std::cout << "case 7.2" << std::endl;
                        break;
                    }else{//case 2
                        //variable declaration and defintion
                        std::cout << "case 2 if global";
                        break;
                    }
                }else{
                    if(str[length - 2] == ')' && str[length - 3] == '('){//case 7.1
                        //function prototype;
                        std::cout << "case 7.1" << std::endl;
                        break;
                    }

                    int index = -1;
                    for(int j = 0; j < tokens[i + 1].size(); ++j){
                        if(tokens[i + 1][j] == '('){
                            index = j;
                            break;
                        }
                    }

                    //std::cout << "tokens i + 1 is " << tokens[i + 1] << std::endl;
                    std::string collectArgType;
                    for(int k = index + 1; k < tokens[i + 1].size(); ++k){
                        if(tokens[i + 1][k] == ' ')
                            break;
                        collectArgType += tokens[i + 1][k];
                    }

                    //std::cout << "collectArgType is " << collectArgType << std::endl;
                    if(generalTypes[collectArgType].first){//case 9 i.e. in parentheses I have argument(type)
                        //function prototype;
                        std::cout << "case 9" << std::endl;
                    }else{//case 2
                        std::cout << "case 2"<< std::endl;
                        //tokens[i] type of variable declaration
                    }
                    break;
                }
            }else if(str[length - 1] == ')'){// i.e. case 8 and 10
                //Create function(Scope) object returning generalTypes[tokens[i]]
                std::cout << "case 8 or 10" << std::endl;
                break;
            }else{//case 1 and 3
                //variable of Type tokens[i] declaration or definition
                std::cout << "str[length - 1] = " << str[length - 1] << " case 1 or 3" << std::endl;
                break;
            }
            //processTypeLine(tokens[i], i, generalTypes[tokens[i]]);
        }else{
            //std::cout << "no type deteceted" << std::endl;
        }
    }


    //1/ int x;
    //2/ int x(5);
    //3/ int x{5};

    //4/ int x = foo();
    //5/ int x = 5;
    //6/ int x = {5};

    //7/  int x(); //7.1 Scope must be global, if not -> 7.2 its a function pointer declaration, function is returning int and accepting no arguments
    //8/  int x() //Function declaration
    //9/  int x(int arg); //Scope must be global
    //10/ int x(int arg) //Scope must be global
}

void ControlBlock::addnewScope(const std::string &name, int startrow)
{
    //Creates a Scope object and pushes it to vector of scopes
    std::unique_ptr<Scope> newscope = std::make_unique<Function>(name, startrow);
    scopes.push_back(std::move(newscope));
}

void ControlBlock::removeLastScope()
{
    scopes.pop_back();//Deletes last created scope
}

ControlBlock *ControlBlock::getControlBlock()
{

    if (!cbinstance) {//If no ControlBlock instance was created create one and return it
        cbinstance = new ControlBlock();
    }
    return cbinstance;
}

ControlBlock::~ControlBlock()
{
    //qDebug() << "entered  CB dtor\n";
    while(!scopes.empty()){//Delete all scopes(actually by the end of the execution of source code only Global Scope object will be left here)
        scopes.pop_back();
    }
}
