#ifndef RISKFACTOR_H
#define RISKFACTOR_H


class RiskFactor
{
public:
    RiskFactor();
    virtual void setVulnerable(int vulnerablility) = 0;
    bool getVulnerable();
    virtual void setResistant(int resistance) = 0;
    bool getResistant();

protected:
    bool vulnerable;
    bool resistant;
};

#endif // RISKFACTOR_H
