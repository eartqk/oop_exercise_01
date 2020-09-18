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
  unsigned char kopecks;

public:
  void printMoney();
  unsigned long long getRubles();
  unsigned int getKopecks();
  friend Money operator+(Money money1, Money money2);
  friend Money operator-(Money money1, Money money2);
  friend Money operator/(Money money1, double number);
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
    rubles = a, kopecks = b;
    if (kopecks >= 100) {
      rubles += kopecks / 100;
      kopecks %= 100;
    }
  };
};

Money operator+(Money money1, Money money2) {
  Money money;
  money.rubles += money1.rubles + money2.rubles;
  money.kopecks += money1.kopecks + money2.kopecks;
  if (money.kopecks >= 100) {
    money.rubles += money.kopecks / 100;
    money.kopecks %= 100;
  }
  return money;
};

Money operator-(Money money1, Money money2) {
  Money money;
  if ((money1.rubles < money2.rubles) ||
      (money1.rubles == money2.rubles && money1.kopecks < money2.kopecks)) {
    cout << "There is not enough money on the first account, the changes will "
            "not be applied.\n";
    return money1;
  } else {
    money.rubles = money1.rubles - money2.rubles;
    if (money1.kopecks < money2.kopecks) {
      money.rubles -= 1;
      money.kopecks = 100 + money1.kopecks - money2.kopecks;
    } else {
      money.kopecks = money1.kopecks - money2.kopecks;
    }
  }
  return money;
};

Money operator/(Money money1, double number) {
  if (number <= 0) {
    cout << "You can't divide by zero and negative numbers.\n";
    return money1;
  }
  unsigned int value = (money1.rubles * 100 + money1.kopecks) / number;
  Money money2;
  money2.rubles = value / 100;
  money2.kopecks = value % 100;
  return money2;
}

double operator/(Money money1, Money money2) {
  if (money2.rubles == 0 && money2.kopecks == 0) {
    cout << "You can't divide by zero.\n";
  }
  unsigned long long money_left = money1.rubles * 100 + money1.kopecks;
  unsigned long long money_right = money2.rubles * 100 + money2.kopecks;
  return (money_left * 1.0) / money_right;
}

void Money::printMoney() { cout << rubles << "," << (int)kopecks; };

unsigned long long Money::getRubles() { return rubles; };

unsigned int Money::getKopecks() { return kopecks; };

int main(){

};
