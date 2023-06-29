//домашнє завдання № 26 артyp
#include <iostream>

#include <vector>

using namespace std;

struct ptrList {
    void* ptr = NULL;
    int count = 0;
};

static vector<ptrList> listP;

template<class T>
class SmartPointer
{
    T* ptr;

    //    static ptrList*  listP;
    //    static int size;

public:
    SmartPointer(T* p)
    {
        ptr = p;
        bool found = false;
        for (int i = 0; i < listP.size(); ++i)
        {
            if (listP[i].ptr == ptr) {
                listP[i].count++;
                found = true;
                break;
            }
        }

        if (found == false)
        {
            ptrList pp;
            pp.ptr = ptr;
            pp.count = 1;

            listP.push_back(pp);
        }
    }
    SmartPointer(const SmartPointer& obj) {
        ptr = obj.ptr;

        if (ptr == NULL) {
            return;
        }

        bool found = false;
        for (int i = 0; i < listP.size(); ++i)
        {
            if (listP[i].ptr == ptr) {
                listP[i].count++;
                found = true;
                break;
            }
        }
    }
    ~SmartPointer() {

        if (ptr != NULL) {
            bool found = false;
            for (int i = 0; i < listP.size(); ++i)
            {
                if (listP[i].ptr == ptr) {
                    listP[i].count--;
                    if (listP[i].count < 1) {
                        delete ptr;
                        listP.erase(listP.begin() + i);
                    }
                    break;
                }
            }

        }

    }

    T& operator* () {
        return *ptr;
    }
    T* operator->() {
        return ptr;
    }
};

//vector<ptrList> listP{vector<ptrList>()};
//static ptrList* SmartPointer::listP = new ptrList[10];
//static int SmartPointer::size = 10;

int main() {
    {
        SmartPointer<int> p = new int(43);
        cout << *p << endl;

        SmartPointer<int> p1 = new int(55);
        cout << *p1 << endl;

        {
            SmartPointer<int> p2(p);
            cout << *p2 << endl;

            SmartPointer<int> p3 = new int(66);
            cout << *p3 << endl;
        }
        cout << *p << endl;
        cout << *p1 << endl;
    }


    SmartPointer<int> p = new int(43);
    cout << *p << endl;
    return 0;
}
