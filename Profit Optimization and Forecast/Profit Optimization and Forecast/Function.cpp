#include "Function.h"
#include <iostream>

AlphaData DataReading(const std::string& filename, container& container)
{
    std::ifstream reading(filename);
    std::string name_timed;
    double Y_timed;
    double F_timed;
    double L_timed;


    while (reading) {
        reading >> name_timed >> Y_timed >> F_timed >> L_timed;
        container.push_back({ name_timed, Y_timed, F_timed, L_timed });

    }

    const int sizeOfInput = container.size();
    double Sum_xy = 0;
    double Sum_x = 0;
    double Sum_y = 0;
    double Sum_x2 = 0;

    for (int i = 0; i < sizeOfInput; ++i)
    {
        Sum_xy += std::log(container[i].getF() / container[i].getL()) * std::log(container[i].getY() / container[i].getL());
        Sum_x += std::log(container[i].getF() / container[i].getL());
        Sum_y += std::log(container[i].getY() / container[i].getL());
        Sum_x2 += std::log(container[i].getF() / container[i].getL()) * std::log(container[i].getF() / container[i].getL());
    }
    double alpha = (sizeOfInput * Sum_xy - Sum_x * Sum_y) / (sizeOfInput * Sum_x2 - Sum_x * Sum_x);
    double c = Sum_y / sizeOfInput - alpha / sizeOfInput * Sum_x;

    double A = exp(c);

    return { A, alpha };
}

void Prognosis(const AlphaData& val, container& container)
{
    int n;
    std::cout << "������� ���������� ������������� ��������: ";
    std::cin >> n;
    const double sredneeF = (container[container.size() - 1].getF() - container[0].getF()) / (container.size() - 1);
    double tmpF = sredneeF + container[container.size() - 1].getF();
    const double sredneeL = (container[container.size() - 1].getL() - container[0].getL()) / (container.size() - 1);
    double tmpL = sredneeL + container[container.size() - 1].getL();

    auto lastVal = std::stoi(container[container.size() - 1].getName());
    for (int i = 0; i < n; ++i)
    {
        tmpF += sredneeF;
        tmpL += sredneeL;
        container.push_back({ std::to_string(++lastVal), val.A_ * pow(tmpF, val.alpha_) * pow(tmpL, 1 - val.alpha_), tmpF, tmpL });
        
    }
    for (auto&& var : container)
    {

        std::cout << var.getName() << "\t Y: " <<
            var.getY() << "\t F: " <<
            var.getF() << "\t L: " <<
            var.getL() << std::endl;

    }
}

void IncomeMax(const AlphaData& val)
{
    std::cout << "C���� ��������: ";
    double c_input;
    std::cin >> c_input; std::cout << std::endl;
    double F_output = (val.alpha_) * c_input;
    double L_output = c_input - F_output;
    double Y_output = val.A_ * pow(F_output, val.alpha_) * pow(L_output, 1 - val.alpha_);

    std::cout << "����������� ��������� �������     " << Y_output << std::endl 
              << "��� ��������� �������� �� ����    " << L_output << std::endl
              << "��� ��������� �������� �� ������� " << F_output << std::endl
        << std::endl;
}

void CostsMin(const AlphaData& val)
{
    std::cout << "������ �������, ������� ���� �������: ";
    double Y_input;
    std::cin >> Y_input; std::cout <<  std::endl;
    double F_output = pow((val.alpha_ / (1 - val.alpha_)), -val.alpha_) * Y_input / val.A_;
    double L_output = pow((val.alpha_ / (1 - val.alpha_)), 1 - val.alpha_) * Y_input / val.A_;
    double C_output = F_output + L_output;

    std::cout << "���������� ��������� ��������     " << C_output << std::endl
              << "��� ��������� �������� �� ����    " << L_output << std::endl
              << "��� ��������� �������� �� ������� " << F_output << std::endl
        << std::endl;
}

void MarginalProduct(const AlphaData& val)
{
    std::cout << "������� ������ ������������� ��� ������: " << std::endl;
    std::cout << "�������: ";
    double Y_input;
    std::cin >> Y_input; std::cout << std::endl;
    std::cout << "���. �������: ";
    double F_input;
    std::cin >> F_input; std::cout << std::endl;
    std::cout << "����. �������: ";
    double L_input;
    std::cin >> L_input; std::cout << std::endl;
    double PPF = val.A_* val.alpha_ * pow((F_input / L_input), val.alpha_-1);
    double PPL = val.A_ * (1 - val.alpha_) * pow((F_input / L_input), val.alpha_);


    std::cout << "���������� ������� �������� = " << PPF << std::endl
        << "���������� ������� ����� = " << PPL << std::endl
        << "���������� ����� ��������� ����� �� ������� = " << PPL/PPF << std::endl
        << "���������� ����� ��������� �������� �� ���� = " << PPF/PPL << std::endl
        << std::endl;
}
