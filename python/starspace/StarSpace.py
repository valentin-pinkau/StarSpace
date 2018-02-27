from starspace_wrapper import Args
from starspace_wrapper import StarSpaceWrapper

import numpy as np

def build_args(args):
    a = Args()
    for (k, v) in args.items():
        if k != "self":
            setattr(a, k, v)
    return a

class StarSpace:

    def __init__(self):
        self.spw = None

    def train(self,
              trainFile,
              model = "model",
              initModel = "",
              lr = 0.01,
              termLr = 1e-9,
              norm = 1.0,
              margin = 0.05,
              initRandSd = 0.001,
              dropoutLHS = 0.0,
              dropoutRHS = 0.0,
              dim = 10,
              epoch = 5,
              ws = 5,
              maxTrainTime = 60*60*24*100,
              thread = 1,
              maxNegSamples = 10,
              negSearchLimit = 50,
              minCount = 1,
              minCountLabel = 1,
              verbose = False,
              adagrad = True,
              normalizeText = False,
              trainMode = 0,
              fileFormat = "fastText",
              label = "__label__",
              bucket = 2000000,
              ngrams = 1,
              loss = "hinge",
              similarity = "cosine",
              shareEmb = True,
              saveEveryEpoch = False,
              saveTempModel = False,
              useWeight = False):

        a = build_args(locals())
        a.isTrain = True
        self.spw = StarSpaceWrapper(a)
        self.spw.init(a.initModel)
        self.spw.train()

    def getVector(self, input_data,  model="", sep="\t ", side="LHS"):

        assert side in ["LHS", "RHS"]

        if model != "":
            self.spw = StarSpaceWrapper(Args())
            self.spw.init(model)

        assert self.spw is not None


        for data in input_data:
            if side == "LHS":
                yield np.array(self.spw.getDocVector(data, sep))[0, :]
            elif side == "RHS":
                yield np.array(self.spw.getLabelVector(data, sep))[0, :]










