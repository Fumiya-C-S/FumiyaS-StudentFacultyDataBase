#include "LBBST.h"
#include "Student.h"
#include "Faculty.h"
#include "MainMenu.h"

int main(int argc, char const *argv[])
{
    MainMenu *myMM = new MainMenu(); //create MainMenu object
    myMM->mainMenuPrompt(); //call prompt
    delete myMM; //delete MainMenu object

    return 0; //end program
}
