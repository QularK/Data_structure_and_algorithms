#include <iostream>
#include <string>
using namespace std;

class Client {
private:
    // Поля класса
    string fio;        // ФИО клиента
    string phone;      // телефон
    string email;      // электронная почта
    int appeals;       // количество обращений

public:
    // Конструктор по умолчанию
    Client() {
        fio = "Неизвестно";
        phone = "Нет телефона";
        email = "Нет почты";
        appeals = 0;
        cout << "Создан клиент (по умолчанию)" << endl;
    }

    // Конструктор с параметрами
    Client(string name, string ph, string em, int app) {
        fio = name;
        phone = ph;
        email = em;
        
        // Проверка: обращения не могут быть отрицательными
        if (app >= 0) {
            appeals = app;
        } else {
            appeals = 0;
            cout << "Обращения не могут быть < 0. Установлено 0." << endl;
        }
        cout << "Создан клиент: " << fio << endl;
    }

    // Деструктор
    ~Client() {
        cout << "Клиент " << fio << " удален" << endl;
    }

    // Геттеры
    string getFio() {
        return fio;
    }

    int getAppeals() {
        return appeals;
    }

    // Сеттеры с проверкой
    void setPhone(string ph) {
        if (ph != "") {
            phone = ph;
        } else {
            cout << "Телефон не может быть пустым!" << endl;
        }
    }

    void setEmail(string em) {
        // Простая проверка: в email должна быть '@'
        if (em.find('@') != -1) {
            email = em;
        } else {
            cout << "Некорректный email!" << endl;
        }
    }

    // Метод: добавить обращение
    void addAppeal() {
        appeals++;
        cout << "Новое обращение от " << fio << ". Всего: " << appeals << endl;
    }
    // Метод: проверка активности (если обращений больше порога)
    void checkActive(int threshold) {
        if (appeals > threshold) {
            cout << fio << " - активный клиент (> " << threshold << " обращений)" << endl;
        } else {
            cout << fio << " - неактивный клиент (<= " << threshold << " обращений)" << endl;
        }
    }
    // Метод: показать информацию
    void showInfo() {
        cout << "\n--- Информация о клиенте ---" << endl;
        cout << "ФИО: " << fio << endl;
        cout << "Телефон: " << phone << endl;
        cout << "Email: " << email << endl;
        cout << "Обращений: " << appeals << endl;
        cout << "----------------------------\n" << endl;
    }
};
int main() {
    setlocale(LC_ALL, "Russian");
    cout << "=== Программа для работы с клиентами ===\n" << endl;
    
    // 1. Создаем клиента через конструктор по умолчанию
    cout << "--- Тест 1: Конструктор по умолчанию ---" << endl;
    Client client1;
    client1.showInfo();
    
    // Устанавливаем данные через сеттеры
    cout << "--- Устанавливаем данные клиенту 1 ---" << endl;
    client1.setPhone("+7-999-123-4567");
    client1.setEmail("ivanov@mail.ru");
    client1.showInfo();
    
    // Пробуем установить неправильные данные
    cout << "--- Проверка валидации ---" << endl;
    client1.setPhone("");  // пустой телефон
    client1.setEmail("ivanov.mail.ru");  // без @
    client1.showInfo();
    
    // 2. Создаем клиента через конструктор с параметрами
    cout << "--- Тест 2: Конструктор с параметрами ---" << endl;
    Client client2("Петрова Анна", "+7-911-987-6543", "petrova@mail.ru", 3);
    client2.showInfo();
    
    // 3. Демонстрируем методы
    cout << "--- Тест 3: Работа с обращениями ---" << endl;
    client2.addAppeal();  // добавляем обращение
    client2.addAppeal();  // еще одно
    cout << "Всего обращений у " << client2.getFio() << ": " << client2.getAppeals() << endl;
    
    // Проверяем активность
    cout << "\n--- Тест 4: Проверка активности ---" << endl;
    client2.checkActive(3);  // порог 3
    client1.checkActive(2);  // порог 2
    
    // 4. Создаем клиента с неправильными данными
    cout << "\n--- Тест 5: Отрицательные обращения ---" << endl;
    Client client3("Сидоров Петр", "+7-123-456-7890", "sidorov@mail.ru", -5);
    client3.showInfo();
    
    cout << "\n=== Программа завершена ===\n" << endl;
    
    return 0;
}
