#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    char *name[10];
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Function prototypes
bool vote(int voter, int rank, char *name, int candidate_count);
void tabulate(int voter_count, int candidate_count);
bool print_winner(int voter_count, int candidate_count);
int find_min(int candidate_count);
bool is_tie(int min, int candidate_count);
void eliminate(int min, int candidate_count);

int main(int argc, char *argv[])
{
    // Numbers of voters and candidates
    int voter_count;
    int candidate_count;

    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        *candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    printf("Number of voters: ");
    scanf("%i", &voter_count);

    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            char name[10];
            printf("Rank %i: ", j+1);
            scanf("%s", &name);

            // Record vote, unless it's invalid
            if (!vote(i, j, name, candidate_count))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate(voter_count, candidate_count);

        // Check if election has been won
        bool won = print_winner(voter_count, candidate_count);
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min(candidate_count);
        bool tie = is_tie(min, candidate_count);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("%s\n", *candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min, candidate_count);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, char *name, int candidate_count)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(strcmp(*candidates[i].name, name)==0) {
            preferences[voter][rank] = i;

            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(int voter_count, int candidate_count)
{
    for (int i = 0; i < voter_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
            if(!(candidates[preferences[i][j]].eliminated)) {
                candidates[preferences[i][j]].votes++;
                break;
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(int voter_count, int candidate_count)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if(candidates[i].votes > (voter_count/2)) {
            printf("%s\n", *candidates[i].name);

            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(int candidate_count)
{
    int current_min = 100;

    for (int i = 0; i < candidate_count; i++) { 
        if(!(candidates[i].eliminated))
            if(current_min >= candidates[i].votes) {
                current_min = candidates[i].votes;
            }    
    }
    return current_min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min, int candidate_count)
{
    for (int i = 0; i < candidate_count; i++) { 
        if(!(candidates[i].eliminated))
            if(candidates[i].votes != min) {
                return false;
            }    
    }
    return true;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min, int candidate_count)
{
    for (int i = 0; i < candidate_count; i++) { 
        if(!(candidates[i].eliminated))
            if(candidates[i].votes == min) {
                candidates[i].eliminated = true;
            }
            else {
                candidates[i].eliminated = false;
            }
    }
    return;
}
