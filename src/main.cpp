/**
 * Copyright (c) 2016-present, Facebook, Inc.
 * All rights reserved.
 *
 * This source code is licensed under the BSD-style license found in the
 * LICENSE file in the root directory of this source tree. An additional grant
 * of patent rights can be found in the PATENTS file in the same directory.
 */

#include "starspace.h"
#include <iostream>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace starspace;

int main(int argc, char** argv) {
  shared_ptr<Args> args = make_shared<Args>();
  args->parseArgs(argc, argv);
  args->printArgs();

  StarSpace sp(args);
  if (args->isTrain) {
    // load model, if given
    if (sp.load_model_if_set(args->initModel)) {
    } else {
      sp.init();
    }
    sp.train();
  } else {
    if(!sp.load_model_if_set(args->model)) return -1;
    sp.evaluate();
  }

  return 0;
}
