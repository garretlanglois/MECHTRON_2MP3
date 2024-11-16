from vader import SentimentIntensityAnalyzer

# Create a SentimentIntensityAnalyzer object
analyzer = SentimentIntensityAnalyzer()
sentences = [
    "VADER is very smart, handsome, and funny.",
    "The movie was not good.",
    "I am so excited about the concert tonight!",
    "What a terrible experience.",
]

# Analyze each sentence
for sentence in sentences:
    scores = analyzer.polarity_scores(sentence)
    print(f"Sentence: {sentence}")
    print(f"Sentiment Scores: {scores}")
    print()