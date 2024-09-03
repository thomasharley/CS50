import re

def main():
    
    text = input("Text: ")
    grade = int(round(compute_grade(text), 0))

    if grade < 1:
        print("Before Grade 1")
    elif grade >= 16:
        print("Grade 16+")
    else:
        print("Grade "+str(grade))

def compute_grade(text):

    word_count = len(re.split(' ', text))
    sentence_count = len(re.split('\.|\?|\!', text)) - 1
    letter_count = len(re.findall('[a-zA-Z]', text))

    L = (letter_count/word_count)*100
    S = (sentence_count/word_count)*100

    grade = (0.0588 * L) - (0.296 * S) - 15.8
    return grade

main()


