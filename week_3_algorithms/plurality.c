#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    char *name[10];
    int votes;
} candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(char *name);
void print_winner(void);

int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        *candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count;
    printf("Number of voters: ");
    scanf("%i", &voter_count);

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        char name[10];

        printf("Vote: ");
        scanf("%s", &name);

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(char *name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(*candidates[i].name, name)==0) {
            candidates[i].votes++;
            return true;
        }
    }
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    float total_votes = 0;

    for (int i = 0; i < candidate_count; i++) {
        total_votes = total_votes + candidates[i].votes;
    }
    int required_votes = ceil(total_votes/candidate_count);

    for (int i = 0; i < candidate_count; i++) {
        if(candidates[i].votes >= required_votes) {
            printf("%s wins the election!\n", *candidates[i].name);
        }
    }

}