#include <QCoreApplication>
#include <iostream>
#include "FileController.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QString exampleFilepath("example.txt");
    QString exampleOutFilepath("example_out.txt");

    WordInverter::FileController controller(exampleFilepath, exampleOutFilepath);

    try
    {
        std::cout << "Opening files..." << std::endl;
        controller.openFiles();
        std::cout << "Making transaction..." << std::endl;
        controller.makeTransaction();
        std::cout << "Writing additional info..." << std::endl;
        controller.writeAdditionalInfo();
        std::cout << "Closing files..." << std::endl;
        controller.closeFiles();
    }
    catch(QString* e)
    {
        std::cerr << e->toStdString() << std::endl;
        delete e;
    }

    std::cout << "GoodBye!" << std::endl;
    return a.exec();
}
