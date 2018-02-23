from starspace_wrapper import Args
from starspace_wrapper import StarSpaceWrapper

def build_args():
    pass

class StarSpace:

    def train(self,
              lr = 0.01,
              termLr = 1e-9,
              norm = 1.0,
              margin = 0.05,
              wordWeight = 0.5,
              initRandSd = 0.001,
              dropoutLHS = 0.0,
              dropoutRHS = 0.0,
              p = 0.5,
              dim = 10,
              epoch = 5,
              ws = 5,
              maxTrainTime = 60*60*24*100,
              thread = 10,
              maxNegSamples = 10,
              negSearchLimit = 50,
              minCount = 1,
              minCountLabel = 1,
              K = 5,
              verbose = False,
              debug = False,
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
              useWeight = False,
              trainWord = False,):

        a = Args()
        spw = StarSpaceWrapper(a)
        spw.init()
        print(a.lr)