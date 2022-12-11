
#include <string>
#include <vector>
#include <fstream>
#include <Windows.h>

class DataCost
{
public:
    DataCost() = default;
    DataCost(const std::string& name, double Y, double F, double L)
        : name_(name)
        , Y_(Y)
        , F_(F)
        , L_(L)
    {
    }
public:
    const std::string& getName() const {
        return name_;
    }
    double getY() const {
        return Y_;
    }
    double getF() const {
        return F_;
    }
    double getL() const {
        return L_;
    }

private:
    std::string name_;
    double Y_;
    double F_;
    double L_;
};

using container = std::vector< DataCost >;

struct AlphaData {
    double A_;
    double alpha_;
};

AlphaData DataReading(const std::string& filename, container& container);
void Prognosis(const AlphaData& val, container& container);
void IncomeMax(const AlphaData& val);
void CostsMin(const AlphaData& val);
void MarginalProduct(const AlphaData& val);