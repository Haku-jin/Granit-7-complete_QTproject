#include <QtCore/QCoreApplication>
#include <QtCore>
#include <vector>

using namespace std;

string to_string(int val) {                                     // Функция перевода int to string
 char buff[32];
 sprintf(buff,"%d",val);
 return string(buff);
}

class sub                                                       // Класс для подпоследовательностей
{
private:
    vector<pair <int,int> > arr;                                // Контейнер содеражащий пары
public:
    sub(int count, int begin, int Y)                            // Конструктор работает по следующей схеме:
    {                                                           // count - число элементов в подпосл.
        for (int i=begin; i<begin+count;i++)                    // begin - с какого значения будет заполнятся X в отсчетах
        {                                                       // Y - значение, одно на все отсчеты в подпосл.
            arr.reserve(sizeof(pair<int,int>)*count);           // резерв памяти для нужного количества pair
            arr.push_back(make_pair(i,Y));
        }
    }
    string show(int N)                                          // Функция возвращает строку типа: (x,y),(x2,y)...
    {                                                           // не модифицируя подпоследовательность, но лишь
        string buf = "";                                        // оставляя в строке то, что проходит по условию
        vector<pair <int,int> >::iterator i, b;
        for(i=b=arr.begin();i!=arr.end();i++)
            if(i-b==0 || i+1==arr.end() || (i-b+1)%N==0)        // условие отбора отсчетов: 1-й, последний, N-й
        {
            buf+=string(" (")+to_string(arr[i-b].first)+string(", ")+to_string(arr[i-b].second)+string(")");
            if(i+1!=arr.end())buf+=",";
        }
        return buf;
    }
};

vector <sub> indications;                                       // Контейнер подпоследовательностей

void hard_load (vector <sub> &v)                                // Функция для вводна начальных данных (Жесткое кодирование)
{
    qDebug()<<"Заполнение последовательности отсчётов...";
    v.push_back(sub(1,1,10));
    v.push_back(sub(4,2,11));
    v.push_back(sub(1,6,10));
    qDebug()<<"Последовательность отсчётов заполнена! \n";
}

int main(int argc, char *argv[])
{
    hard_load(indications);
    string myout="";
    QCoreApplication a(argc, argv);
    vector <sub>::iterator i,b;
    for (int N=1; N<5; N++)                                     // Увеличиваем N и для каждой подпосл-сти вызываем show()
    {                                                           // складывая результат в myout
        if(N==1)myout="  Исходная строка: ";                    // N = 1 - исходная строка
        else myout=string("Результат при N=")+to_string(N)+string(": ");
        for (i=b=indications.begin();i!=indications.end();i++)
            myout+=indications[i-b].show(N);
            qDebug()<<myout.c_str();
    }
    return a.exec();
}
