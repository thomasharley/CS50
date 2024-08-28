from cs50 import get_int

scores = []

n = get_int("How many scores: ")

for i in range(n):
    score = get_int("Score: ")
    scores.append(score)
    # scores = scores + [score]


average = sum(scores) / len(scores)   
print(f"Average: {average}")