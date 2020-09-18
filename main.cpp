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
  friend Money operator-(Money money1, Money money2);
  friend double operator/(Money money1, Money money2);

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
    rubles = a, kopeks = b;
    if (kopeks >= 100) {
      rubles += kopeks / 100;
      kopeks %= 100;
    }
  };
};

Money operator+(Money money1, Money money2) {
  Money money;
  money.rubles += money1.rubles + money2.rubles;
  money.kopeks += money1.kopeks + money2.kopeks;
  if (money.kopeks >= 100) {
    money.rubles += money.kopeks / 100;
    money.kopeks %= 100;
  }
  return money;
};

Money operator-(Money money1, Money money2) {
  Money money;
  if ((money1.rubles < money2.rubles) ||
      (money1.rubles == money2.rubles && money1.kopeks < money2.kopeks)) {
    cout << "There is not enough money on the first account, the changes will "
            "not be applied.\n";
    return money1;
  } else {
    money.rubles = money1.rubles - money2.rubles;
    if (money1.kopeks < money2.kopeks) {
      money.rubles -= 1;
      money.kopeks = 100 + money1.kopeks - money2.kopeks;
    } else {
      money.kopeks = money1.kopeks - money2.kopeks;
    }
  }
  return money;
};

double operator/(Money money1, Money money2) {
  if (money2.rubles == 0 && money2.kopecks == 0) {
    cout << "One of the sums is zero. You can't divide.\n";
  }
  unsigned long long money_left = money1.rubles * 100 + money1.kopeks;
  unsigned long long money_right = money2.rubles * 100 + money2.kopeks;
  return (money_left * 1.0) / money_right;
}

void Money::printMoney() { cout << rubles << "," << (int)kopeks; };

unsigned long long Money::getRubles() { return rubles; };

int Money::getKopeks() { return kopeks; };

int main(){

};
