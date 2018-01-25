#ifndef WORDCONTROLLER_CPP
#define WORDCONTROLLER_CPP

#include "WordController.h"

WordInverter::WordController :: WordController()
    : doubleCharConnection(),
      buffer()
{

}

WordInverter::WordController :: ~WordController()
{

}

void WordInverter::WordController :: handleWord(std::deque<char>* word)
{
    for(std::deque<char>::iterator i = word->begin(); i != word->end();)
    {
        buffer = *i;
        buffer.append(*(++i));

        doubleCharConnectionIterator = doubleCharConnection.find(buffer);
        if(doubleCharConnectionIterator == doubleCharConnection.end())
        {
            doubleCharConnection.insert(std::make_pair(buffer, 1));
        }
        else
        {
            doubleCharConnectionIterator->second++;
        }

    }
}

std::map<QString, int>::iterator WordInverter::WordController :: getMostFrequentDoubleCharConnection()
{
    std::map<QString, int>::iterator result = doubleCharConnection.begin();
    for(std::map<QString, int>::iterator i = doubleCharConnection.begin(); i != doubleCharConnection.end();i++)
    {
        if(i->second > result->second)
        {
            result = i;
        }
    }
    return result;
}

#endif // WORDCONTROLLER_CPP
