/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */


#include "doc_data.h"
#include "utils/utils.h"
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
#include <numeric>
#include <random>

using namespace std;

namespace starspace {

LayerDataHandler::LayerDataHandler(shared_ptr<Args> args) :
  InternDataHandler(args) {
}

void LayerDataHandler::insert(
    vector<Base>& rslt,
    const vector<Base>& ex,
    float dropout) const {

  if (dropout < 1e-8) {
    // if dropout is not enabled, copy all elements
    rslt.insert(rslt.end(), ex.begin(), ex.end());
  } else {
    // dropout enabled
    auto rnd = [&] {
      static thread_local std::mt19937 generator;
      std::uniform_real_distribution<double> distribution(0.0, 1.0);
      return distribution(generator);
    };
    for (const auto& it : ex) {
      auto p = rnd();
      if (p > dropout) {
        rslt.push_back(it);
      }
    }
  }
}

void LayerDataHandler::getWordExamples(
    int idx,
    vector<ParseResults>& rslts) const {

  assert(idx < size_);
  const auto& example = examples_[idx];
  assert(example.RHSFeatures.size() > 0);

  // take one random sentence and train on word
  auto r = rand() % example.RHSFeatures.size();
  InternDataHandler::getWordExamples(example.RHSFeatures[r], rslts);
}

void LayerDataHandler::convert(
    const ParseResults& example,
    ParseResults& rslt) const {

  rslt.weight = example.weight;
  rslt.LHSTokens.clear();
  rslt.RHSTokens.clear();

  if (args_->trainMode == 0) {
    assert(example.LHSTokens.size() > 0);
    assert(example.RHSFeatures.size() > 0);
    insert(rslt.LHSTokens, example.LHSTokens, args_->dropoutLHS);
    auto idx = rand() % example.RHSFeatures.size();
    insert(rslt.RHSTokens, example.RHSFeatures[idx], args_->dropoutRHS);
  } else {
    assert(example.RHSFeatures.size() > 1);
    if (args_->trainMode == 1) {
      // pick one random rhs as label, the rest becomes lhs features
      auto idx = rand() % example.RHSFeatures.size();
      for (int i = 0; i < example.RHSFeatures.size(); i++) {
        if (i == idx) {
          insert(rslt.RHSTokens, example.RHSFeatures[i], args_->dropoutRHS);
        } else {
          insert(rslt.LHSTokens, example.RHSFeatures[i], args_->dropoutLHS);
        }
      }
    } else
    if (args_->trainMode == 2) {
      // pick one random rhs as lhs, the rest becomes rhs features
      auto idx = rand() % example.RHSFeatures.size();
      for (int i = 0; i < example.RHSFeatures.size(); i++) {
        if (i == idx) {
          insert(rslt.LHSTokens, example.RHSFeatures[i], args_->dropoutLHS);
        } else {
          insert(rslt.RHSTokens, example.RHSFeatures[i], args_->dropoutRHS);
        }
      }
    } else
    if (args_->trainMode == 3) {
      // pick one random rhs as input
      auto idx = rand() % example.RHSFeatures.size();
      insert(rslt.LHSTokens, example.RHSFeatures[idx], args_->dropoutLHS);
      // pick another random rhs as label
      int idx2;
      do {
        idx2 = rand() % example.RHSFeatures.size();
      } while (idx == idx2);
      insert(rslt.RHSTokens, example.RHSFeatures[idx2], args_->dropoutRHS);
    } else
    if (args_->trainMode == 4) {
      // the first one as lhs and the second one as rhs
      insert(rslt.LHSTokens, example.RHSFeatures[0], args_->dropoutLHS);
      insert(rslt.RHSTokens, example.RHSFeatures[1], args_->dropoutRHS);
    }
  }
}

void LayerDataHandler::getRandomRHS(vector<Base>& result, bool trainWord) const {
  assert(size_ > 0);
  auto& ex = examples_[rand() % size_];
  int r = rand() % ex.RHSFeatures.size();

  result.clear();
  if (args_->trainMode == 5 || trainWord) {
    // pick random word
    int wid = rand() % ex.RHSFeatures[r].size();
    result.push_back(ex.RHSFeatures[r][wid]);
  } else if (args_->trainMode == 2) {
    // pick one random, the rest is rhs features
    for (int i = 0; i < ex.RHSFeatures.size(); i++) {
      if (i != r) {
        insert(result, ex.RHSFeatures[i], args_->dropoutRHS);
      }
    }
  } else {
    insert(result, ex.RHSFeatures[r], args_->dropoutRHS);
  }
}

void LayerDataHandler::save(ostream& out) {
  for (auto example : examples_) {
    out << "lhs: ";
    for (auto t : example.LHSTokens) {
      out << t.first << ':' << t.second << ' ';
    }
    out << "\nrhs: ";
    for (auto feat : example.RHSFeatures) {
      for (auto r : feat) { cout << r.first << ':' << r.second << ' '; }
      out << "\t";
    }
    out << endl;
  }
}

} // namespace starspace
