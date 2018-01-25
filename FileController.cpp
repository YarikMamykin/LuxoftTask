#ifndef FILECONTROLLER_CPP
#define FILECONTROLLER_CPP

#include "FileController.h"
#include <stdlib.h>

WordInverter::FileController :: FileController(QString exampleFilepath, QString exampleOutFilepath)
    : exampleFile(exampleFilepath),
      exampleOutFile(exampleOutFilepath),
      outBuffer(NULL),
      wcontroller()

{

}

WordInverter::FileController :: ~FileController()
{
    buffer.clear();
    wcontroller.~WordController();
}


void WordInverter::FileController :: openFiles() throw(QString*)
{
    if(!exampleFile.exists())
    { throw new QString("File " + exampleFile.fileName() + " doesn't exist!\n"); }
    if(!exampleOutFile.exists())
    { throw new QString("File " + exampleOutFile.fileName() + " doesn't exist!\n"); }

    if(!exampleFile.open(QIODevice :: ReadOnly))
    { throw new QString("Can't open file " + exampleFile.fileName()); }
    if(!exampleOutFile.open(QIODevice :: WriteOnly))
    { throw new QString("Can't open file " + exampleOutFile.fileName()); }
}


bool WordInverter::FileController :: isLetterOrNumber(char c)
{    
    switch(c)
    {
        case '\'':
        case '\"':
        case '\n':
        case '\r':
        case '\t':
        case ':':
        case ' ':
        case ',': { return false; }  break;
        default : { return true; }    break;
    }
}

void WordInverter::FileController :: writeWord()
{
    if(buffer.size() == 0) return;

    wcontroller.handleWord(&buffer);

    outBuffer = new char[buffer.size()]();
    copy(buffer.begin(), buffer.end(), outBuffer);

    exampleOutFile.flush();
    exampleOutFile.write(outBuffer, buffer.size());
    buffer.clear();
}

void WordInverter::FileController :: makeTransaction()
{
    char* c = new char[1]();                           // buffer for incoming chars
    bool charIsLetterOrNumber = false;

    exampleFile.seek(exampleFile.size() - 1);          // move to the last char in file

    while(exampleFile.pos() > 0)                       // while moving to file start
    {        
        c = new char[1]();                             // allocating memory for input buffer

        exampleFile.read(c, 1);                        // read char from file
        charIsLetterOrNumber = isLetterOrNumber(*c);   // check char if it is letter or number

        if(charIsLetterOrNumber)                       // if char is letter or number
        {
            buffer.push_front(*c);                     // compile word from chars

            if(exampleFile.pos() == 2)
            {
                exampleFile.seek(0);
                exampleFile.read(c, 1);

                buffer.push_front(*c);
                writeWord();
                break;
            }
        }

        if(!charIsLetterOrNumber)                      // if char is NOT letter or number
        {
            writeWord();                               // write word to file

            if(*c != ' ' && *c != '\n')                // skip space and line feed
            {
                if(*c == ',') *c = '.';                // changing comas to points

                exampleOutFile.flush();                // clearing output buffer
                exampleOutFile.write(c, 1);            // writing char
            }
        }

        delete [] c;                                   // clear allocated memory
        delete [] outBuffer;

        if(exampleFile.pos() != 0)                     // avoid infinite loop
            exampleFile.seek(exampleFile.pos() - 2);   // move to position before next char
        else break;
    }
}

void WordInverter::FileController :: writeAdditionalInfo()
{
    std::map<QString, int>::iterator mostFrequentConnection = wcontroller.getMostFrequentDoubleCharConnection();
    exampleOutFile.write("\n\nThe most frequent double char connection is '");
    exampleOutFile.write(mostFrequentConnection->first.toStdString().c_str());
    exampleOutFile.write("': frequency = ");

    if(!outBuffer) outBuffer = new char[3]();
    sprintf(outBuffer, "%d", mostFrequentConnection->second);
    exampleOutFile.write(outBuffer);

    delete outBuffer;
}

void WordInverter::FileController :: closeFiles()
{
    exampleFile.close();
    exampleOutFile.close();
}

#endif

