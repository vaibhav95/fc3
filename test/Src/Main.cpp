#include <algorithm>
#include <numeric>
#include <functional>
#include <random>
#include "cfl/Macros.hpp"
#include "test/Output.hpp"
#include "test/Main.hpp"

using namespace std;
using namespace cfl;

using namespace std;
using namespace cfl;

// accessor functions

std::valarray<double> test::getArg(double dL, double dR, unsigned iN)
{
  ASSERT(iN > 0);
  std::valarray<double> uResult(iN);
  double dH = (dR - dL) / (iN - 1);
  double dX = dL;
  for (unsigned iI = 0; iI < iN; iI++)
  {
    uResult[iI] = dX;
    dX += dH;
  }
  uResult[uResult.size() - 1] = dR;
  return uResult;
}

std::valarray<double> test::getRandArg(double dL, double dR, unsigned iN)
{
  ASSERT(iN > 0);
  std::valarray<double> uResult(iN);
  std::minstd_rand uGen(1);
  std::uniform_real_distribution<double> uRand(dL,dR);
  for (unsigned iI = 0; iI < iN; iI++)
  {
    uResult[iI] = uRand(uGen);
  }
  std::sort(begin(uResult), end(uResult));
  POSTCONDITION((dL < uResult[0]) && (uResult[uResult.size() - 1] < dR));
  return uResult;
}

std::valarray<double> test::
    getValues(const Function &rF, const std::valarray<double> &rArg)
{
  std::valarray<double> uResult(rArg.size());
  std::transform(begin(rArg), end(rArg), begin(uResult), [&rF](double dX) {
    return rF(dX);
  });
  return uResult;
}

// print functions

void test::print(const std::string &sMessage)
{
  std::cerr << sMessage.c_str() << endl
            << endl;
  std::cout << sMessage.c_str() << endl
            << endl;
}

void test::printValues(const cfl::Function &rF, const std::valarray<double> &rArg)
{
  std::valarray<double> uValues = getValues(rF, rArg);
  print(begin(uValues), end(uValues));
}

void printAtStart(const std::string &sMessage)
{
  std::string sOut(sMessage);
  sOut.append(" by ");
  sOut.append(STUDENT_ID);
  test::print(sOut);
}

void printAtEnd(const std::string &sFileName)
{
  cout << "The output is written to the file " << sFileName.c_str() << endl
       << endl;
}

void test::print(const std::vector<std::valarray<double>> &rValues,
                 const std::vector<std::string> &rNames,
                 const std::string &sMessage, unsigned iColumn,
                 unsigned iSpace, unsigned iRows)
{
  PRECONDITION(rValues.size() == rNames.size());
  cout << sMessage.c_str() << endl
       << endl;

  for (unsigned i = 0; i < rValues.size(); i++)
  {
    std::cout << std::setw(iColumn) << rNames[i].c_str() << std::setw(iSpace) << "";
  }
  std::cout << endl;

  unsigned iSize = rValues.front().size();
  unsigned iStart = (iSize - iRows) / 2;
  unsigned iEnd = (iSize + iRows) / 2;
  iEnd = min(iEnd, iSize);

  for (unsigned j = iStart; j < iEnd; j++)
  {
    for (unsigned i = 0; i < rValues.size(); i++)
    {
      ASSERT(rValues[i].size() == iSize);
      std::cout << std::setw(iColumn) << rValues[i][j] << std::setw(iSpace) << "";
    }
    std::cout << endl;
  }
  std::cout << std::endl;
}

void test::print(const std::vector<cfl::Function> &rF, const std::vector<std::string> &rNames,
                 const std::valarray<double> &rArg, const std::string &sMessage,
                 unsigned iColumn, unsigned iSpace)
{
  PRECONDITION(rF.size() == rNames.size());
  std::vector<std::string> uNames(rNames.size() + 1);
  uNames.front() = "arg";
  std::copy(rNames.begin(), rNames.end(), uNames.begin() + 1);
  std::vector<std::valarray<double>>
      uValues(rF.size() + 1, std::valarray<double>(rArg.size()));
  uValues.front() = rArg;
  for (unsigned i = 0; i < rF.size(); i++)
  {
    uValues[i + 1] = getValues(rF[i], rArg);
  }
  print(uValues, uNames, sMessage, iColumn, iSpace, uValues.front().size());
}

double total_err(const cfl::Function &rErr, const std::valarray<double> &rArg)
{
  std::valarray<double> uErr = test::getValues(rErr, rArg);
  double dErr = std::inner_product(begin(uErr), end(uErr), begin(uErr), 0.);
  return std::sqrt(dErr);
}

void test::printTotalErr(const cfl::Function &rEstErr, const cfl::Function &rActErr,
                         const std::valarray<double> &rArg)
{
  cout << "Total estimated error = " << total_err(rEstErr, rArg)
       << ". Total actual error = " << total_err(rActErr, rArg) << "." << endl
       << endl;
}

std::string fileName(const std::string &sDir1, const std::string &sDir2, const std::string & sFile)
{
  std::string a(sDir1);
  a += std::string("/");
  a += sDir2;
  a += std::string("/");
  a+= sFile;
  a += std::string(".txt");
  return a;
}

void test::project(const std::function<void()> &rF, const std::string &sProjectDir,
const std::string & sFileName, const std::string &sTitle)
{
  std::string sFile = fileName(OUTPUT_DIR, sProjectDir, sFileName);
  std::ofstream fOut(sFile.c_str());
  std::streambuf *strmBuffer = std::cout.rdbuf();
  std::cout.rdbuf(fOut.rdbuf());
  printAtStart(sTitle);
  rF();
  std::cout.rdbuf(strmBuffer);
  printAtEnd(sFile);
}
