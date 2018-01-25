#ifndef WORDCONTROLLER_H
#define WORDCONTROLLER_H

#include <QString>
#include <deque>
#include <map>

namespace WordInverter
{
    class WordController
    {
    private:
        std::map<QString, int> doubleCharConnection;
        std::map<QString, int>::iterator doubleCharConnectionIterator;
        QString buffer;
    public:
        WordController();
        ~WordController();

        void handleWord(std::deque<char>* word);
        std::map<QString, int>::iterator getMostFrequentDoubleCharConnection();
    };
}
#endif // WORDCONTROLLER_H
