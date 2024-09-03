import csv
from sys import argv


def main():

    # TODO: Check for command-line usage
    if len(argv) != 3:
        print("Usage: python dna.py [DNA CSV Database] [DNA Sequence]")
        return

    # TODO: Read database file into a variable
    rows = []

    with open(f"{argv[1]}") as file1:
        reader = csv.DictReader(file1)

        for row in reader:
            rows.append(row)
        
    # TODO: Read DNA sequence file into a variable
    with open(f"{argv[2]}") as file2:
        sequence = file2.readline()

    # TODO: Find longest match of each STR in DNA sequence
    longest_runs = []
    for i in reader.fieldnames:
        longest_runs.append(longest_match(sequence, i))

    # TODO: Check database for matching profiles
    i = 0
    while i < len(rows): # cycle through names
        j = 1
        while j < len(reader.fieldnames): # cycle through DNA 'short tandem repeats'

            if longest_runs[j] == int(rows[i][reader.fieldnames[j]]): # if longest match of current STR matches longest STR for current row

                j+=1 # move to next STR and check again
                
                if j == len(reader.fieldnames): # If we reach end of list and still match, print name
                    print(rows[i]['name'])
                    return
            else: # if no match move onto next name (row).
                i+=1
                break

    print("No Match") # if no match at end of rows, print 'no match'
    return

def longest_match(sequence, subsequence):
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1
            
            # If there is no match in the substring
            else:
                break
        
        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return longest_run


main()
