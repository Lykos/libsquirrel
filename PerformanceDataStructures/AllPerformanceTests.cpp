#include <cstdlib>
#include <QtTest/QTest>
#include "longinttest.h"
#include "compositeperformanceresult.h"
#include "performanceresult.h"
#include <cstdlib>
#include <unistd.h>
#include <fstream>

int main(int argc, char *argv[])
{
  // get hostname
  char hostname[1024];
  hostname[1023] = '\0';
  gethostname(hostname, 1023);

  // get time
  struct tm * timeinfo;
  time_t rawtime;
  time(&rawtime);
  timeinfo = localtime(&rawtime);

  // description
  std::string version_name ("chunk_div_mod");
  std::ostringstream oss;
  oss << version_name << " " << hostname << " " << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << " " << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
  std::string description = oss.str();

  typedef CompositePerformanceResult<PerformanceResult> ClassResult;
  CompositePerformanceResult<ClassResult> whole_result (description);

  // Execute tests
  LongIntTest long_int_test;
  QTest::qExec(&long_int_test, argc, argv);
  whole_result.add_sub_result(long_int_test.accumulate_results());

  // Write result to file
  std::ostringstream oss2;
  oss2 << "../performance_results/" << version_name << "_" << hostname << "_" << (1900 + timeinfo->tm_year) << "-" << timeinfo->tm_mon << "-"
      << timeinfo->tm_mday << "_" << timeinfo->tm_hour << ":" << timeinfo->tm_min << ":" << timeinfo->tm_sec;
  std::string file_name = oss2.str();
  std::ofstream result_file (file_name.c_str());
  result_file << whole_result;

  return EXIT_SUCCESS;
}
