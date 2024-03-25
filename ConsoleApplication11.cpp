#include <iostream>
#include <string>
#include <Windows.h>
#include <vector>
#include <limits>
#pragma execution_character_set("utf-8")

class BankAccount {
private:
    int accountNumber; // уникальный номер счета
    double balance;    // текущая сумма на счету
    double interestRate; // процентная ставка

public:
    BankAccount(int accountNumber, double startBalance)
    {
        this->accountNumber = accountNumber;
        this->balance = startBalance;
        this->interestRate = 0.0;
    }

    void deposit(double summ)// пополнение счета
    {
        if (summ > 0)
        {
            balance += summ;
            std::cout << "Пополение прошло успешно." <<" "<< "Внесение " << summ << " рублей" << std::endl;
            std::cout << "Текущий баланс: " << balance << " рублей" << std::endl;
        }
        else {
            std::cout << "Для пополнения счета введите другую сумму:" << std::endl;
        }
    }
    void withdraw(double summ)// снятие со счета
    {
        if (summ > 0 && summ <= balance)
        {
            balance -= summ;
            std::cout << "Снятие прошло успешно." << " "<< "Снятие " << summ << " рублей" << std::endl;
            std::cout << "Текущий баланс: " << balance << " рублей" << std::endl;
        }
        else
        {
            std::cout << "Недостаточно средств на счете" << std::endl;
        }
    }
    double getBalance() // рассчитать и вернуть текущий баланс
    {
        std::cout << "Текущий баланс: " << balance << " рублей" << std::endl;
        return balance;
    }
    double globalInterestRate = 0.16;
    double getInterest() const// рассчитать и вернуть сумму процентов, заработанных на счете
    {
        double otvet = balance * globalInterestRate * (1.0 / 12.0);
        return otvet;
    }
    void setInterestRate(double newInterestRate) // обновить процентную ставку
    {
        std::cout << "Обновленая процентная ставка:" << newInterestRate << std::endl;
        globalInterestRate = newInterestRate;
    }
    int getAccountNumber() const//получить номер банковского счёта 
    {
        std::cout << "Номер банковского счета:" << std::endl;
        return accountNumber;
    }
    bool transfer(std::vector<BankAccount>& accounts, int recipientAccountNumber, double summ)
    {
        BankAccount* recipientAccount = nullptr;

        for (BankAccount& acc : accounts) {
            if (acc.getAccountNumber() == recipientAccountNumber) {
                recipientAccount = &acc;
                break;
            }
        }

        if (recipientAccount == nullptr) {
            std::cout << "Счет получателя не найден." << std::endl;
            return false;
        }

        if (summ > 0 && summ <= getBalance()) {
            withdraw(summ);
            recipientAccount->deposit(summ);
            std::cout << "Перевод средств успешен: " << summ << std::endl;
            return true;
        }
        else {
            std::cout << "Перевод не удался. Неверная сумма или недостаточно средств на счете отправителя." << std::endl;
            return false;
        }
    }
    // Она должна возвращать true, если перевод был успешным
    //  (т. е. если на первом счете было
    //  достаточно средств для покрытия перевода), и false в противном случае.
   
};


int main()
{

    
    SetConsoleCP(65001); // устанавливаем кодировку входящего потока данных на UTF-8
    SetConsoleOutputCP(65001); // устанавливаем кодировку исходящего потока данных на UTF-8
    
    int choice;
    double amount;

    std::vector<BankAccount> accounts = {
        {123, 1000.0},
        {456, 500.0},
        // Добавьте остальные счета
    };

    BankAccount myAccount(123, 1000.0);

    do {
        std::cout << "Выберите операцию:" << std::endl;
        std::cout << "1. Внести средства" << std::endl;
        std::cout << "2. Снять средства" << std::endl;
        std::cout << "3. Получить баланс" << std::endl;
        std::cout << "4. Установить процентную ставку" << std::endl;
        std::cout << "5. Получить проценты" << std::endl;
        std::cout << "6. Перевести на другой счет" << std::endl;
        std::cout << "7. Выйти из программы" << std::endl;
        std::cout << "Выберите операцию (1-7): ";
        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Некорректный выбор. Попробуйте ещё раз." << std::endl;
            std::cin.clear();
            std::cin.ignore(1000, '\n');
        }


        switch (choice) {
            case 1:
                while (true) {
                    std::cout << "Введите сумму для внесения: ";
                    if (!(std::cin >> amount)) {
                        std::cin.clear(); // очистить флаг ошибки ввода
                        std::cin.ignore(1000, '\n'); // очистить буфер ввода
                        std::cout << "Сумма не может быть строкой. Попробуйте ещё раз: ";
                    }
                    else if (amount < 0) {
                        std::cout << "Сумма не может быть отрицательной. Попробуйте ещё раз: ";
                    }
                    else {
                        break;
                    }
                }
                myAccount.deposit(amount);
                break;
            case 2:
                std::cout << "Введите сумму для снятия: ";
                while (true) {

                    if (!(std::cin >> amount)) {
                        std::cin.clear(); // очистить флаг ошибки ввода
                        std::cin.ignore(1000, '\n'); // очистить буфер ввода
                        std::cout << "Сумма не может быть строкой. Попробуйте ещё раз: ";
                    }
                    else if (amount < 0) {
                        std::cout << "Сумма не может быть отрицательной. Попробуйте ещё раз: ";
                    }
                    else {
                        break;
                    }
                }
                myAccount.withdraw(amount);
                break;
            case 3:
                myAccount.getBalance();
                break;
            case 4:
                myAccount.setInterestRate(0.13);
                break;
            case 5:
            {
                double otvet = myAccount.getInterest();
                std::cout << "Проценты на счете: " << otvet << std::endl;
                break;
            }
            case 6:
                int recipientAccountNumber;
                double transferAmount;

                bool validRecipient = false;
                while (!validRecipient) {
                    std::cout << "Введите номер счета получателя (доступные номера: 123, 456): ";
                    if (!(std::cin >> recipientAccountNumber)) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;
                    }
                    else {
                        bool found = false;
                        for (const auto& account : accounts) {
                            if (account.getAccountNumber() == recipientAccountNumber) {
                                found = true;
                                break;
                            }
                        }
                        if (found) {
                            validRecipient = true;
                        }
                        else {
                            std::cout << "Номер счета не существует. Попробуйте ещё раз." << std::endl;
                        }
                    }
                }

                bool validAmount = false;
                while (!validAmount) {
                    std::cout << "Введите сумму для перевода: ";
                    if (!(std::cin >> transferAmount)) {
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cout << "Некорректный ввод. Попробуйте ещё раз." << std::endl;
                    }
                    else if (transferAmount < 0) {
                        std::cout << "Сумма не может быть отрицательной. Попробуйте ещё раз." << std::endl;
                    }
                    else {
                        validAmount = true;
                    }
                }

                myAccount.transfer(accounts, recipientAccountNumber, transferAmount);
                break; 

        }

    } while (choice != 7);

    return 0;

}  


