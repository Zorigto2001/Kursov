
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <Windows.h>
#include "Function.h"
#include <functional>


int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Приветствую!" << std::endl;
    std::cout << "Введите имя файла с необходимыми данными для создания равновесной модели" << std::endl;
    std::cout << "Пример данных в вашем имени файла \n";
    std::cout << "( Месяц | Чистая прибыль | Финасовые расходы на капитал | Трудовые расходы )\n\n\n";
    std::cout << "Имя вашего файла: ";
    std::string filename{};
    std::getline(std::cin, filename);

    // container keeps all values from data
    container container{};
    auto alpha_a = DataReading(filename, container);

    std::cout << std::endl;
    std::cout << "Данные успешно загружены:\n" <<
        "|Месяц | Y - Прибыль | F - Фин. расходы | L - Труд. расходы|\n";
    std::cout << std::fixed;
    std::cout << std::setprecision(3);
    for (auto&& dataCost : container)
    {
        std::cout << dataCost.getName() << ' '
            << dataCost.getY() << ' '
            << dataCost.getF() << ' '
            << dataCost.getL() << std::endl;
    }
    system("pause");
    system("cls");

    while (true) {
        std::cout << std::endl;
        std::cout << "Выберите следующее действие" << std::endl;
        std::cout << "1 - Прогнозирование прибыли на заданый период\n"
            << "2 - Максимизация прибыли, при следующей суммы издержек\n"
            << "3 - Минимизация издержек, при следующей планируемой прибыли\n"
            << "4 - Рассчитать предельный продукт капитала/ предельный продукт труда\n"
            << "    Предельную норму замещения труда на капитал/ Предельную норму замещения капитала на труд/\n"
            << "5 - Рассчитать коофицент структуры и масштаба \n"
            << "q - Выйти из программы\n\n"
           << "Ваше действие: ";

        auto action = std::getchar();
        switch (action)
        {
        case '1':
        {
            Prognosis(alpha_a, container);
            break;
        }
        case '2':
        {
            IncomeMax(alpha_a);
            system("pause");
            system("cls");
            break;
        }
        case '3':
        {
            CostsMin(alpha_a);
            system("pause");
            system("cls");
            break;
        }
        case '4':
        {
            MarginalProduct(alpha_a);
            system("pause");
            system("cls");
            break;
        }
        case '5':
        {
            std::cout << "A : " << alpha_a.A_ << ", Alpha: " << alpha_a.alpha_ << ", Beta: " << 1 - alpha_a.alpha_ << std::endl;
            system("pause");
            system("cls");
            break;
        }
        case 'q':
        default:
            return 0;
        }
        std::cin.ignore(200, '\n');
    }
}