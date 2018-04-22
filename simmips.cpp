#include <iostream>
#include <sstream>
#include <ostream>
#include <string>
#include <vector>
#include <fstream>
#include <string>

#include <QApplication>

#include "lexer.hpp"
#include "module.hpp"
#include "parser.hpp"

#include "virtual_machine_gui.hpp"

using namespace std;

bool result;
bool ready = true;

string prompt;

int main(int argc, char *argv[])
{
    int i = 0;
    vector<string> the_arguments;


    while (i < argc) { the_arguments.push_back(argv[i]); i++; } //read the file

    if (argc < 1) //error checking
    {
        ready = false;
        return EXIT_FAILURE;
    }

    if (ready == true) //go to the execute function to run the function
    {
        ifstream strings(the_arguments[the_arguments.size()-1], ios::binary);   //read the file and store it in string
        ifstream gui_strings(the_arguments[the_arguments.size()-1], ios::binary);

        if (strings.fail())
        {
            ready = false;
            cout << "Error: not a valid file" << endl;
            return EXIT_FAILURE;
        }
        else
        {
            if (ready == true)
            {
                TokenList the_tokens = tokenize(strings);   //tokenize strings
                VirtualMachine the_module;
                result = the_module.parse(the_tokens);    //parse the_tokens and return the result
                
                if (the_arguments[1] == "--gui")
                {
                    QApplication app(argc, argv);
                    VirtualMachineGUI the_gui_module;
                    
                    the_gui_module.load(QString::fromStdString(the_arguments[the_arguments.size()-1]));
                    the_gui_module.show();
                    
                    return app.exec();
                }
                else
                {
                    while(true)
                    {
                        cout << "simmips> ";
                        getline (cin,prompt);
                        
                        string arr[4];
                        int i = 0;
                        stringstream commandstream(prompt);
                        while (commandstream.good() && i < 4)
                        {
                            commandstream >> arr[i];
                            i++;
                        }
                        
                        string command = arr[0];
                        string target = arr[1];
                        
                        if (command == "print")
                        {
                            if (target.substr(0,1) == "$")
                                the_module.printRegister(target);
                            
                            else if (target.substr(0,1) == "&")
                                the_module.printByteAt(target);
                            else
                                cout << "Error, not a valid command" << endl;
                        }
                        
                        else if (command == "step")
                        {
                            the_module.executeProgram();
                        }
                        
                        else if (command == "run")
                        {
                            the_module.runProgram();
                        }
                        
                        else if (command == "break")
                        {
                            the_module.breakProgram();
                        }
                        
                        else if (command == "status")
                        {
                            the_module.getStatus();
                        }
                        
                        else if (command == "quit")
                        {
                            return EXIT_SUCCESS;
                        }
                        else
                        {
                            cout << "Error, not a valid command" << endl;
                        }
                    }
                    if (result == false)
                        return EXIT_FAILURE;
                    
                    return EXIT_SUCCESS;
                }
            }
        }
    }
}
