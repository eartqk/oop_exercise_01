/*
   Артамонов Олег
   https://github.com/eartqk
   Создать класс Money для работы с денежными суммами.
   Сумма денег должна быть представлено двумя полями:
   типа unsigned long long для рублей и типа unsigned char – для копеек.
   Дробная часть (копейки) при выводе на экран должна быть отделена от целой
   части запятой. Реализовать сложение сумм, вычитание, деление сумм, деление
   суммы на дробное число, умножение на дробное число и операции сравнения.
 */

#include <iostream>

using namespace std;

class Money {
private:
  unsigned long long rubles;
  unsigned char kopeks;

public:
  void printMoney();
  unsigned long long getRubles();
  int getKopeks();
  friend Money operator+(Money money1, Money money2);

  Money(unsigned long long a = 0, int b = 0) {
    if (a < 0 && b < 0) {
      cout << "Incorrect entry of rubles and kopecks.\nAn instance will be "
              "created with 0 rubles and 0 kopecks.\n";
      a = 0, b = 0;
    } else if (a < 0) {
      cout << "Incorrect entry of rubles.\nAn instance will be created with 0 "
              "rubles.\n";
      a = 0;
    } else if (b < 0) {
      cout << "Incorrect entry of kopecks.\nAn instance will be created with 0 "
              "kopecks.\n";
      b = 0;
    }
    rubles = 0, kopeks = 0;
    if (b >= 100) {
      rubles += b / 100;
      b = b % 100;
    }
    rubles += a;
    kopeks += b;
  };
};

Money operator+(Money money1, Money money2) {
  Money money;
  money.rubles += money1.getRubles() + money2.getRubles();
  money.kopeks += money1.getKopeks() + money2.getKopeks();
  if (money.kopeks >= 100) {
    money.rubles += money.kopeks / 100;
    money.kopeks %= 100;
  }
  return money;
};

void Money::printMoney() { cout << rubles << "," << (int)kopeks; };

unsigned long long Money::getRubles() { return rubles; };

int Money::getKopeks() { return kopeks; };

int main() {
  Money money1(2000, -900);
  Money money2(0, 1000);
  money1 = money1 + money2;
  money1.printMoney();
};
