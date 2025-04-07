#include <iostream> // Підключення бібліотеки для введення/виведення
#include <cmath>    // Підключення для математичних функцій (тут не строго потрібно, але може знадобитися)

// Використання стандартного простору імен
using namespace std;

// --- Клас AdHocSquare ---
// Розраховує площу "на льоту" (ad hoc) тільки тоді, коли викликається get_area().
// Не зберігає площу як змінну члена класу.
// **Завдання з PDF: Implement the AdHocSquare approach** [source: 6, 7, 12]
class AdHocSquare
{
private:
    // **Виправлення помилки:** Переміщено 'side' в private секцію
    double side; // Довжина сторони квадрата
    bool changed_since_construction; // Прапорець для методу was_side_changed

public:
    // Конструктор: ініціалізує сторону, перевіряючи на валідність
    AdHocSquare(double initial_side) {
        if (initial_side >= 0) {
            side = initial_side;
        } else {
            cout << "(AdHocSquare) Помилка: Сторона не може бути від'ємною. Встановлено 0." << endl;
            side = 0;
        }
        changed_since_construction = false; // Сторона ще не змінювалася після створення
        cout << "(AdHocSquare) Створено об'єкт зі стороною " << side << endl;
    }

    // Метод set_side: встановлює нову сторону (сеттер)
    // **Завдання 2: Додайте метод set** [source: 13]
    void set_side(double new_side) {
        cout << "(AdHocSquare) Спроба встановити сторону: " << new_side << endl;
        if (new_side >= 0) {
            if (side != new_side) {
                side = new_side;
                changed_since_construction = true; // Відмічаємо, що сторона змінилася
                 cout << "(AdHocSquare) Сторону успішно змінено на " << side << endl;
            } else {
                 cout << "(AdHocSquare) Нове значення сторони таке ж, як поточне. Змін не відбулося." << endl;
            }
        } else {
            cout << "(AdHocSquare) Помилка: Сторона не може бути від'ємною. Значення " << new_side << " проігноровано." << endl;
        }
    }

    // Метод get_area: обчислює та повертає площу "на льоту"
    // **Завдання 3: Доробіть метод get_aria** [source: 6, 13]
    double get_area() {
        cout << "(AdHocSquare) Обчислення площі для сторони " << side << "..." << endl;
        // Площа обчислюється кожного разу при виклику цього методу
        return side * side;
    }

     // Метод get_side: повертає поточну сторону (геттер)
    double get_side() {
        return side;
    }

    // Метод was_side_changed: перевіряє, чи змінювалась сторона *після створення*
    // **Завдання 3: Доробіть метод changet**
    // В AdHoc підході немає "зміни з часу останнього обчислення",
    // тому реалізуємо як перевірку, чи змінювалась сторона взагалі після конструктора.
    bool was_side_changed() {
        return changed_since_construction;
    }

     // Метод print: виводить інформацію про квадрат
    void print() {
        // Викликаємо get_area(), щоб показати, що обчислення відбувається тут
        cout << "(AdHocSquare) Квадрат: Сторона = " << side << ", Площа (обчислена зараз) = " << get_area() << endl;
    }
};

// --- Клас LazySquare ---
// Зберігає площу і перераховує її лише тоді, коли це необхідно ("лінивий" підхід),
// тобто коли сторона змінилася з моменту останнього запиту площі.
// **Завдання з PDF: Implement the LazySquare approach** [source: 8, 9, 10, 11, 13]
class LazySquare
{
private:
    // **Виправлення помилки:** Переміщено члени класу в private секцію
    double side;          // Довжина сторони
    double area;          // Збережене значення площі
    bool side_changed;    // Прапорець: чи змінилася сторона з останнього обчислення площі? [source: 9, 13]

    // Приватний метод для оновлення площі (використовується в get_area)
    void update_area() {
        area = side * side;
        side_changed = false; // Скидаємо прапорець після перерахунку
         cout << "(LazySquare) Площу перераховано. Нова площа: " << area << endl;
    }

public:
    // Конструктор: ініціалізує сторону, обчислює початкову площу
    // **Виправлення помилки:** Правильна назва конструктора
    LazySquare(double initial_side) {
         if (initial_side >= 0) {
            side = initial_side;
        } else {
            cout << "(LazySquare) Помилка: Сторона не може бути від'ємною. Встановлено 0." << endl;
            side = 0;
        }
        // Початковий розрахунок площі та встановлення прапорця
        update_area(); // Викликаємо update_area для початкового розрахунку і скидання прапорця
        cout << "(LazySquare) Створено об'єкт зі стороною " << side << " та площею " << area << endl;
    }

    // Метод set_side: встановлює нову сторону і ставить прапорець 'side_changed'
    // **Завдання 2: Додайте метод set** [source: 13]
    void set_side(double new_side) {
         cout << "(LazySquare) Спроба встановити сторону: " << new_side << endl;
        if (new_side >= 0) {
             if (side != new_side) {
                side = new_side;
                side_changed = true; // Важливо: Встановлюємо прапорець, що сторона змінилась [source: 9]
                cout << "(LazySquare) Сторону успішно змінено на " << side << ". Площа буде перерахована при наступному запиті." << endl;
            } else {
                 cout << "(LazySquare) Нове значення сторони таке ж, як поточне. Змін не відбулося." << endl;
                 // side_changed залишається як було
            }
        } else {
            cout << "(LazySquare) Помилка: Сторона не може бути від'ємною. Значення " << new_side << " проігноровано." << endl;
        }
    }

    // Метод get_area: повертає збережену площу, перераховуючи її лише за потреби
    // **Завдання 3: Доробіть метод get_aria** [source: 10, 11, 13]
    double get_area() {
        cout << "(LazySquare) Запит площі...";
        // Перевіряємо, чи потрібно перераховувати площу
        if (side_changed) {
            cout << " Сторона змінилася, перераховуємо..." << endl;
            update_area(); // Перераховуємо площу і скидаємо прапорець
        } else {
             cout << " Сторона не змінювалася, повертаємо збережене значення." << endl;
        }
        // Повертаємо збережене (можливо, щойно оновлене) значення площі
        return area;
    }

    // Метод get_side: повертає поточну сторону (геттер)
    double get_side() {
        return side;
    }

    // Метод was_side_changed: перевіряє, чи змінювалась сторона *з моменту останнього обчислення площі*
    // **Завдання 3: Доробіть метод changet**
    bool was_side_changed() {
        // Просто повертає стан прапорця side_changed
        return side_changed;
    }

     // Метод print: виводить інформацію про квадрат
    void print() {
        // Виводимо поточну сторону і збережену площу (без її перерахунку тут)
        cout << "(LazySquare) Квадрат: Сторона = " << side << ", Збережена площа = " << area << ", Сторона змінювалась? " << (side_changed ? "Так" : "Ні") << endl;
    }
};


// Головна функція програми
int main()
{
    // Встановлення української локалі
    setlocale(LC_ALL, "uk_UA.UTF-8");

    cout << "======= Тестування AdHocSquare =======" << endl;
    // **Завдання 1: Створіть кілька нових об'єктів**
    AdHocSquare adhoc_sq1(5.0);
    AdHocSquare adhoc_sq2(10.0);

    cout << "\n--- Початковий стан ---" << endl;
    adhoc_sq1.print(); // Обчислить площу зараз
    cout << "Чи змінювалася сторона adhoc_sq1? " << (adhoc_sq1.was_side_changed() ? "Так" : "Ні") << endl;


    cout << "\n--- Зміна сторони adhoc_sq1 ---" << endl;
    adhoc_sq1.set_side(6.0); // Змінюємо сторону
    cout << "Чи змінювалася сторона adhoc_sq1? " << (adhoc_sq1.was_side_changed() ? "Так" : "Ні") << endl;
    cout << "Поточна сторона adhoc_sq1: " << adhoc_sq1.get_side() << endl;
    // Площа ще не перерахована, бо get_area() не викликали
    cout << "Виклик get_area() для adhoc_sq1:" << endl;
    double current_area_adhoc = adhoc_sq1.get_area(); // Обчислення площі тут
    cout << "Отримана площа adhoc_sq1: " << current_area_adhoc << endl;
    adhoc_sq1.print(); // Знову обчислить площу


    cout << "\n======= Тестування LazySquare =======" << endl;
    // **Завдання 1: Створіть кілька нових об'єктів**
    LazySquare lazy_sq1(7.0); // Площа обчислюється в конструкторі
    LazySquare lazy_sq2(12.0);

    cout << "\n--- Початковий стан ---" << endl;
    lazy_sq1.print(); // Виводить збережену площу
    cout << "Чи потрібно перераховувати площу lazy_sq1? " << (lazy_sq1.was_side_changed() ? "Так" : "Ні") << endl;
    cout << "Виклик get_area() для lazy_sq1 (вперше після створення): " << lazy_sq1.get_area() << endl; // Не має перераховувати


    cout << "\n--- Зміна сторони lazy_sq1 ---" << endl;
    lazy_sq1.set_side(8.0); // Змінюємо сторону, встановлюється прапорець side_changed
    lazy_sq1.print(); // Показує нову сторону, стару площу, прапорець "Так"
    cout << "Чи потрібно перераховувати площу lazy_sq1? " << (lazy_sq1.was_side_changed() ? "Так" : "Ні") << endl;

    cout << "\n--- Перший виклик get_area() після зміни ---" << endl;
    double current_area_lazy = lazy_sq1.get_area(); // ПЕРЕРАХУНОК площі тут, прапорець скидається
    cout << "Отримана площа lazy_sq1: " << current_area_lazy << endl;
    lazy_sq1.print(); // Показує нову сторону, нову площу, прапорець "Ні"
     cout << "Чи потрібно перераховувати площу lazy_sq1? " << (lazy_sq1.was_side_changed() ? "Так" : "Ні") << endl;


    cout << "\n--- Другий виклик get_area() після зміни ---" << endl;
     double area_again_lazy = lazy_sq1.get_area(); // НЕ МАЄ перераховувати площу
     cout << "Отримана площа lazy_sq1 (знову): " << area_again_lazy << endl;


     cout << "\n--- Спроба встановити ту саму сторону ---" << endl;
     lazy_sq1.set_side(8.0); // Не має змінити прапорець side_changed
     lazy_sq1.print();
     cout << "Виклик get_area() після спроби встановити ту саму сторону: " << lazy_sq1.get_area() << endl; // Не має перераховувати


    return 0;
}
