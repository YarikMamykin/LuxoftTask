#ifndef FILECONTROLLER_H
#define FILECONTROLLER_H

#include <QFile>
#include <deque>
#include <algorithm>
#include "WordController.h"

namespace WordInverter
{
    class FileController
    {
    private:
        char* outBuffer;
        std::deque<char> buffer;
        QFile exampleFile;
        QFile exampleOutFile;
        WordInverter::WordController wcontroller;

        static bool isLetterOrNumber(char c);
        void writeWord();

    public:
        FileController(QString exampleFilepath, QString exampleOutFilepath);
        ~FileController();

        void openFiles() throw(QString*);
        void makeTransaction();
        void writeAdditionalInfo();
        void closeFiles();
    };
}

#endif // FILECONTROLLER_H
