#include "pch.h"
#include "CWUtest.hpp"

#include <iostream>

namespace cw
{
  CWUtest::CWUtest():
    m_allCases(0), m_fail(0)
  {
  }


  CWUtest::~CWUtest()
  {
  }

  void CWUtest::init( const std::string& testName )
  {
    m_testName = testName;
  }

  void CWUtest::test(const std::string& msg, const bool condition)
  {
    if (!condition)
    {
      m_fail++;
    }

    // count test cases
    m_allCases++;
    // print the message and the condition
    std::cout << msg << " : " << condition << std::endl;
  }

  void CWUtest::report() const
  {
    std::cout << "--------" << m_testName << "----------\n";
    std::cout << "all cases : " << m_allCases << std::endl;
    std::cout << "fail : " << m_fail << std::endl;
    std::cout << "--------------------------------------";
  }

}