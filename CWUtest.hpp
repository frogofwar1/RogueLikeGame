#pragma once
#include <string>

namespace cw
{
  class CWUtest
  {
  public:
    CWUtest();
    ~CWUtest();

    void init(const std::string& testName);
    void test(const std::string& msg, const bool condition);
    void report() const;

  private:
    std::string m_testName;
    unsigned long int m_fail;
    unsigned long int m_allCases;
  };
}

