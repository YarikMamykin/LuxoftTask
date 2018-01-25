#include <QString>
#include <QtTest>
#include <deque>
#include "../WordController.cpp"

class Test_WordController : public QObject
{
    Q_OBJECT

public:
    Test_WordController();
    void makeWord(std::deque<char> word);

private Q_SLOTS:
    void getMostFrequentDoubleCharConnection();
};

Test_WordController::Test_WordController()
{
}

void Test_WordController::getMostFrequentDoubleCharConnection()
{
    WordInverter::WordController wcontroller;
    std::deque<char> word;
    for(char i = 'a'; i < 'e'; i++)
    {
        word.push_front(i);
    }
    wcontroller.handleWord(&word);
    word.clear();
    for(char i = 'c'; i < 'g'; i++)
    {
        word.push_front(i);
    }
    wcontroller.handleWord(&word);

    int x = wcontroller.getMostFrequentDoubleCharConnection()->second;

    QCOMPARE(x, 2);
}

QTEST_APPLESS_MAIN(Test_WordController)

#include "test_wordcontroller.moc"
