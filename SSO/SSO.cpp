#include <iostream>
#include <cstring>
using namespace std;

class SSO {
private:
    union {
        char small[14];
        char* large;
    };

    int size;
    int cap;
    bool dynamic;

    const char* data() const {
        if (dynamic)
            return large;

        return small;
    }

    void init(const char* str) {
        if (str == nullptr)
            str = "";

        size = strlen(str);

        if (size < 14) {
            dynamic = false;
            cap = 14;
            strcpy(small, str);
        }
        else {
            dynamic = true;
            cap = size;
            large = new char[cap + 1];
            strcpy(large, str);
        }
    }

public:
    SSO() {
        init("");
    }

    SSO(const char* str) {
        init(str);
    }

    SSO(const SSO& other) {
        init(other.data());
    }

    ~SSO() {
        if (dynamic)
            delete[] large;
    }

    SSO& operator=(const SSO& other) {
        if (this != &other) {
            SSO temp(other);

            if (dynamic)
                delete[] large;

            size = temp.size;
            cap = temp.cap;
            dynamic = temp.dynamic;

            if (dynamic) {
                large = temp.large;
                temp.dynamic = false;
            }
            else {
                strcpy(small, temp.small);
            }
        }

        return *this;
    }

    int getSize() const {
        return size;
    }

    int getCap() const {
        return cap;
    }

    char& operator[](int index) {
        if (dynamic)
            return large[index];

        return small[index];
    }

    SSO& operator+(const char* str) {
        if (str == nullptr || str[0] == '\0')
            return *this;

        int len = strlen(str);
        int newSize = size + len;

        if (!dynamic && newSize < 14) {
            memmove(small + size, str, len + 1);
        }
        else if (dynamic && newSize <= cap) {
            memmove(large + size, str, len + 1);
        }
        else {
            char* temp = new char[newSize + 1];

            strcpy(temp, data());
            strcat(temp, str);

            if (dynamic)
                delete[] large;

            large = temp;
            dynamic = true;
            cap = newSize;
        }

        size = newSize;

        return *this;
    }

    void print() const {
        cout << data() << endl;
    }
};

int main() {
    SSO a("Hello");
    SSO b("This is a longer string");

    a.print();
    b.print();

    cout << a.getSize() << " " << a.getCap() << endl;
    cout << b.getSize() << " " << b.getCap() << endl;

    a + " World";
    a.print();

    a + " and everyone";
    a.print();

    SSO c(a);
    c.print();

    SSO d;
    d = b;
    d.print();

    d[0] = 't';
    d.print();

    cout << sizeof(SSO) << endl;

    return 0;
}