import nltk

class Analyzer():
    """Implements sentiment analysis."""

    def __init__(self, pos, neg):
        self.positives_set = set()
        work = open(pos, "r")
        for line in work:
            if line.startswith(';') == False:
                self.positives_set.add(line.rstrip("\n"))
        work.close()

        self.negatives_set = set()
        work = open(neg, "r")
        for line in work:
            if line.startswith(';') == False:
                self.negatives_set.add(line.rstrip("\n"))
        work.close()

    def analyze(self, text):
        token_cal = nltk.tokenize.TweetTokenizer()
        token = token_cal.tokenize(text)
        Total = 0
        for word in token:
            if word.lower() in self.positives_set:
                Total = Total + 1
            elif word.lower() in self.negatives_set:
                Total = Total - 1
            else:
                continue
        return Total