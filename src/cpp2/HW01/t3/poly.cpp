#include "poly.h"

std::vector<int> poly_plus(const std::vector<int> &poly0, const std::vector<int> &poly1)
{
	std::vector<int> res;
	// TODO #1: Compute res = poly0 + poly1 here
  auto len0 = poly0.size(), len1 = poly1.size();
  auto len = len0 >= len1 ? len0 : len1;
  res.resize(len);
  for (auto i = 0; i < len; i++) {
    auto a = i < len0 ? poly0[i] : 0;
    auto b = i < len1 ? poly1[i] : 0;
    res[i] = a + b;
  }
	return res;
}

std::vector<int> poly_mul(const std::vector<int> &poly0, const std::vector<int> &poly1)
{
	std::vector<int> res;
	// TODO #2: Compute res = poly0 * poly1 here
  auto len0 = poly0.size(), len1 = poly1.size();
  auto len = len0 + len1 - 1;
  res.resize(len);
  for (auto i = 0; i < len0; i++) {
    for (auto j = 0; j < len1; j++) {
      res[i + j] += poly0[i] * poly1[j];
    }
  }
	return res;
}

// TODO #3: Submit this code file to the OJ
