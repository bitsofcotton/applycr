#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include <random>
#include <assert.h>
#include <stdlib.h>

//#define int int64_t
#define int int32_t
#include "lieonn.hh"
typedef myfloat num_t;

using std::cout;
using std::cerr;
using std::endl;
using std::atoi;
using std::string;
using std::to_string;
using std::vector;
using std::sort;
using std::binary_search;
using std::make_pair;
using std::istringstream;

static inline const int ceilLg(const int& x) {
  int res(0);
  for(int scan = 1; scan <= sizeof(x) * 8; scan ++)
    if(scan ? x & (int(1) << scan) : x & int(1)) res = scan; 
  return res + 1;
}

template <typename T> static inline T wholeBCW(vector<SimpleVector<T> >& op, const int& k, const int& i, const int& rowlg, const int& j, const int& collg) {
}

#undef int
int main(int argc, const char* argv[]) {
  int dim(0);
  int w(8);
  int h(8);
  vector<vector<SimpleVector<num_t> > > op;
  std::vector<SimpleMatrix<num_t> > res;
  if(argc < 2) goto usage;
  dim = std::atoi(argv[1]);
  if(dim <= 0) goto usage;
  if(2 < argc) w = std::atoi(argv[2]);
  if(3 < argc) h = std::atoi(argv[3]);
  if(w <= 0 || h <= 0) goto usage;
  op.resize(dim);
  for(int i = 0; i < dim; i ++) {
    op[i].resize(dim);
    for(int j = 0; j < dim; j ++)
      std::cin >> op[i][j];
  }
  res.resize(1, SimpleMatrix<num_t>(h, w).O());
  {
    const auto rowlg(ceilLg(res[0].rows()));
    const auto collg(ceilLg(res[0].cols()));
    for(int i = 0; i < res[0].rows(); i ++)
      for(int j = 0; j < res[0].cols(); j ++) {
        // N.B. op[bitcount][bit on] any bitcount wise combinations.
        for(int k = 0; k < op.size() - rowlg - collg; k ++) {
          num_t ncr(1);
          for(int m = 0; m <= k; m ++)
            ncr *= num_t(op.size() - rowlg - collg - m);
          res[0](i, j) +=
            wholeBCW<num_t>(op[k], k, i, rowlg, j, collg) / ncr;
        }
      }
  }
  if(! savep2or3<num_t>("applycr.pgm", res) )
    cerr << "failed to save." << endl;
  return 0;
 usage:
  cerr << "Usage:" << endl;
  cerr << argv[0] << " <dim> <width> <height> < ..." << std::endl;
  return - 1;
}

