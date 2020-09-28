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
  friend void setAmount(Money &money, long long rubles, int kopecks);
  friend void addAmount(Money &money, long long rubles, int kopecks);
  friend bool operator==(Money money1, Money money2);
  friend bool operator!=(Money money1, Money money2);
  friend bool operator>(Money money1, Money money2);
  friend bool operator>=(Money money1, Money money2);
  friend bool operator<(Money money1, Money money2);
  friend bool operator<=(Money money1, Money money2);
  friend Money operator+(Money money1, Money money2);
  friend Money operator-(Money money1, Money money2);
  friend Money operator*(Money money1, double number);
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
    };
    rubles = a, kopecks = b;
    if (kopecks >= 100) {
      rubles += kopecks / 100;
      kopecks %= 100;
    };
  };
};

bool operator==(Money money1, Money money2) {
  return (money1.rubles == money2.rubles && money1.kopecks == money2.kopecks);
};

bool operator!=(Money money1, Money money2) {
  return !(money1.rubles == money2.rubles && money1.kopecks == money2.kopecks);
};

bool operator>(Money money1, Money money2) {
  return ((money1.rubles > money2.rubles) ||
          (money1.rubles == money2.rubles && money1.kopecks > money2.kopecks));
};

bool operator>=(Money money1, Money money2) {
  return (money1 == money2 || money1 > money2);
};

bool operator<(Money money1, Money money2) {
  return ((money1.rubles < money2.rubles) ||
          (money1.rubles == money2.rubles && money1.kopecks < money2.kopecks));
};

bool operator<=(Money money1, Money money2) {
  return (money1 == money2 || money1 < money2);
};

Money operator+(Money money1, Money money2) {
  Money money;
  money.rubles += money1.rubles + money2.rubles;
  money.kopecks += money1.kopecks + money2.kopecks;
  if (money.kopecks >= 100) {
    money.rubles += money.kopecks / 100;
    money.kopecks %= 100;
  };
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
    };
  };
  return money;
};

Money operator*(Money money1, double number) {
  if (number <= 0) {
    cout << "You can't multiply by zero and negative numbers.\n";
    return money1;
  };
  unsigned int value = (money1.rubles * 100 + money1.kopecks) * number;
  Money money2;
  money2.rubles = value / 100;
  money2.kopecks = value % 100;
  return money2;
};

Money operator/(Money money1, double number) {
  if (number <= 0) {
    cout << "You can't divide by zero and negative numbers.\n";
    return money1;
  };
  unsigned int value = (money1.rubles * 100 + money1.kopecks) / number;
  Money money2;
  money2.rubles = value / 100;
  money2.kopecks = value % 100;
  return money2;
};

double operator/(Money money1, Money money2) {
  if (money2.rubles == 0 && money2.kopecks == 0) {
    cout << "You can't divide by zero.\n";
  };
  unsigned long long money_left = money1.rubles * 100 + money1.kopecks;
  unsigned long long money_right = money2.rubles * 100 + money2.kopecks;
  return (money_left * 1.0) / money_right;
};

void Money::printMoney() { cout << rubles << "," << (int)kopecks << "\n"; };

unsigned long long Money::getRubles() { return rubles; };

unsigned int Money::getKopecks() { return kopecks; };

void setAmount(Money &money, long long rubles, int kopecks) {
  if (rubles < 0 || kopecks < 0) {
    cout << "Incorrect entry, amount can't be negative.\n";
  } else {
    money.rubles = rubles + kopecks / 100;
    money.kopecks = kopecks % 100;
  };
};

void addAmount(Money &money, long long rubles, int kopecks) {
  if (rubles < 0 || kopecks < 0) {
    cout << "Incorrect entry, amount can't be negative.\n";
  } else {
    money.rubles += rubles + kopecks / 100;
    money.kopecks += kopecks % 100;
  };
};

void help() {
  cout << "Menu:\n-1 - To exit.\n0 - To print this information.\n1 - To set "
          "amount "
          "manually.\n2 - To add money to exists account.\n3 - To print "
          "amount.\n";
};

int main() {
  Money money(0, 0);
  Money temp_money(0, 0);
  unsigned long long rubs = 0;
  unsigned int kops = 0;
  cout << "Created account with empty balance.\n";
  int select = 0;
  help();
  while (select != -1) {
    cin >> select;
    cin.clear();
    cin.ignore(10000, '\n');
    rubs = 0;
    kops = 0;
    switch (select) {
    case -1:
      break;
    case 0:
      help();
      break;
    case 1:
      cout << "\nSetting new amount.\nEnter a rubles: ";
      cin >> rubs;
      cout << "Enter a kopecks: ";
      cin >> kops;
      setAmount(money, rubs, kops);
      break;
    case 2:
      cout << "\nAdding amount to exists account.\nEnter a rubles: ";
      cin >> rubs;
      cout << "Enter a kopecks: ";
      cin >> kops;
      addAmount(money, rubs, kops);
      break;
    case 3:
      money.printMoney();
      break;
    default:
      cout << "Unknown command.\n";
      break;
    };
  };
};
