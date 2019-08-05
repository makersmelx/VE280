#include<iostream>
#include<queue>
#include<stack>
#include<list>
#include<algorithm>
#include<string>
#include<map>
using namespace std;
class Animal {
public:
    virtual void Speak() = 0;

    virtual void Eat() = 0;
};

class Sick {

public:
    void TakeMed();

protected:
    int med;
};

class Cow : public Animal {

public:
    Cow(int f = 0);

    virtual void Speak();

    void Eat();

protected:
    int grass;
};

class SickCow : public virtual Cow, public Sick {

public:
    SickCow(int f = 0, int m = 0);

    void Speak();
};

class MadCow : public virtual Cow {

public:
    MadCow(int f = 0, int p = 0);

    void Speak();

    void TakePills();

protected:
    int pills;
};

class SickMadCow : public SickCow, public MadCow {

public:
    SickMadCow(int f = 0, int m = 0, int p = 0);

    void Speak();
};

void Sick::TakeMed() {
    if (med > 0) {
        med--;
        cout << "I feel better\n";
    }

    else cout << "I'm dying\n";
}

Cow::Cow(int f) { grass = f; }

void Cow::Speak() { cout << "Moo.\n"; }

void Cow::Eat() {
    if (grass > 0) {
        grass--;
        cout << "Thanks I'm full\n";
    }

    else cout << "I'm hungry\n";
}

SickCow::SickCow(int f, int m) {
    grass = f;
    med = m;
}

void SickCow::Speak() { cout << "Ahem... Moo\n"; }

MadCow::MadCow(int f, int p) {
    grass = f;
    pills = p;
}

void MadCow::Speak() { cout << "Woof\n"; }

void MadCow::TakePills() {

    if (pills > 0) {
        pills--;
        cout << "Moof, that's better\n";
    }

    else cout << "Woof woof woof!\n";
}

SickMadCow::SickMadCow(int f, int m, int p) {
    grass = f;
    med = m;
    pills = p;
}

void SickMadCow::Speak() { cout << "Ahem... Woof\n"; }


static SickMadCow smc;
Animal *getSickMadCow()
{
    return &smc;
}

int main()
{
    SickCow c1(1, 1);
    c1.Speak();
    c1.Eat();
    c1.TakeMed();
    c1.Eat();
    c1.TakeMed();
    cout << endl;
    MadCow c2(1, 1);
    c2.Speak();
    c2.Eat();
    c2.TakePills();
    c2.Eat();
    c2.TakePills();
    cout << endl;
    SickMadCow c3(1, 1, 1);
    c3.Speak();
    c3.Eat();
    c3.TakePills();
    c3.TakeMed();
    c3.Eat();
    c3.TakePills();
    c3.TakeMed();
    SickMadCow c4(1, 1, 0);
    Cow *c5 = &c4;
    c4.Speak();
    c4.Eat();
    c4.TakePills();
    c4.TakeMed();
    c5->Speak();
    c5->Eat(); //c5->TakePills(); c5->TakeMed();
    Animal *lhs = getSickMadCow();
    lhs->Speak();
    return 0;
}