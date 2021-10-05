
#include <iostream>
#include <tchar.h>
#include "disphelper.h"

using namespace std;

int main(int argc, char *argv[])
{

  CDhInitialize init;
  CDispPtr cst, project, farFieldArray, FarfieldPlot, plot1d;

  dhToggleExceptions(TRUE);

  try
  {
    dhCheck(dhCreateObject(L"CSTStudio.Application", NULL, &cst));
    dhCheck(dhGetValue(L"%o", &project, cst, L".OpenFile(%s)", argv[1]));
    dhCheck(dhGetValue(L"%o", &FarfieldPlot, project, L".FarfieldPlot()"));
    dhCheck(dhGetValue(L"%o", &plot1d, project, L".Plot1D()"));
  }
  catch (char *errstr)
  {
    std::cerr << "Error:" << errstr << std::endl;
  }

  int Nport = 7;

  char temp[80];
  double dval = 0;
  LPSTR strval;
  for (int i = 0; i < Nport; ++i)
  {
    // select tree
    sprintf(temp, "1D Results\\Discrete Ports\\Voltages\\Port %d [pw]\0", i + 1);
    dhCheck(dhCallMethod(project, L".SelectTreeItem(%s)", temp));
    // get curve label
    dhGetValue(L"%s", &strval, plot1d, L".GetCurveLabelOfCurveIndex(%d)", 0);
    // printf("%s\n", strval);
    // switch format and get values
    sprintf(temp, "Port %d [pw]\0", i + 1);
    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "magnitude"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 4.0);
    printf("%f\t", dval);
    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "phase"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 4.0);
    printf("%f\t", dval);

    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "magnitude"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 6.5);
    printf("%f\t", dval);
    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "phase"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 6.5);
    printf("%f\t", dval);

    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "magnitude"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 9.0);
    printf("%f\t", dval);
    dhCheck(dhCallMethod(plot1d, L".PlotView(%s)", "phase"));
    dhGetValue(L"%e", &dval, plot1d, L".GetCurveValue(%s, %e)", strval, 9.0);
    printf("%f\n", dval);
  }

 dhCheck(dhCallMethod(project, L".Quit()"));

  // // coordinate system switch
  // if (strcmp(argv[2], "azel") == 0)
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".SetCoordinateSystemType(%s)", "ludwig2ae"));
  // }
  // else if (strcmp(argv[2], "elaz") == 0)
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".SetCoordinateSystemType(%s)", "ludwig2ea"));
  // }
  // else
  // {
  //   std::cout << "\nError: Coordinate system <" << argv[2] << "> not supported.";
  // }

  // // side switch
  // if (!strcmp(argv[3], "front"))
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Thetastart(%d,%d,%d)", -1, 0, 0));
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Phistart(%d,%d,%d)", 0, 0, 1));
  // }
  // else if (!strcmp(argv[3], "back"))
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Thetastart(%d,%d,%d)", 1, 0, 0));
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Phistart(%d,%d,%d)", 0, 0, -1));
  // }
  // else if (!strcmp(argv[3], "left"))
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Thetastart(%d,%d,%d)", 0, 0, 1));
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Phistart(%d,%d,%d)", 1, 0, 0));
  // }
  // else if (!strcmp(argv[3], "right"))
  // {
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Thetastart(%d,%d,%d)", 0, 0, -1));
  //   dhCheck(dhCallMethod(FarfieldPlot, L".Phistart(%d,%d,%d)", -1, 0, 0));
  // }
  // else
  // {
  //   std::cout << "\nError: Side not <" << argv[3] << "> not supported.";
  // }

  // release com object
  try
  {
    SAFE_RELEASE(project);
    SAFE_RELEASE(cst);
  }
  catch (string errstr)
  {
    std::cerr << "Fatal error details:" << std::endl
              << errstr << std::endl;
  }
  dhUninitialize(TRUE);
  return 0;
}