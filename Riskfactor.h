#ifndef RISKFACTOR_H
#define RISKFACTOR_H


class RiskFactor
{
public:
    RiskFactor();
    virtual void setVulnerable(bool vulnerable) = 0;
    bool getVulnerable();
    virtual void setResistant(bool resistant) = 0;
    bool getResistant();

private:
    bool vulnerable;
    bool resistant;
};

#endif // RISKFACTOR_H
