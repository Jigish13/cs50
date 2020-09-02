#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
            preferences[i][j] = 0;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(name, candidates[i]) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]]++;
        }
    }
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    pair p;
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                p.winner = i;
                p.loser = j;
                pairs[pair_count] = p;
                pair_count++;
            }
            if (preferences[i][j] < preferences[j][i])
            {
                p.winner = j;
                p.loser = i;
                pairs[pair_count] = p;
                pair_count++;
            }
        }
    }
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i = 0; i < pair_count; i++)
    {
        int max = preferences[pairs[i].winner][pairs[i].loser];
        for (int j = i + 1; j < pair_count; j++)
        {
            if (preferences[pairs[j].winner][pairs[j].loser] > max)
            {
                // Swap pair
                pair tmp = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = tmp;
            }
        }
    }
}

bool cycle(int p)
{
    if (p == 0)
    {
        return false;
    }

    else
    {
        // To Check whether curr. winner has lost before nd vice versa
        bool winner_flag = false;
        bool loser_flag = false;

        // Curr. pair's winner & loser
        int cur_winner = pairs[p].winner; // For 3rd pair, w = 1
        int cur_loser = pairs[p].loser; // For 3rd pair, l = 2
        for (int i = p - 1; i >= 0; i--)
        {
            int prev_winner = pairs[i].winner;
            int prev_loser = pairs[i].loser;

            if (cur_loser == prev_winner)
            {
                loser_flag = true;
            }

            if (cur_winner == prev_loser)
            {
                winner_flag = true;
            }
        }

        if (winner_flag == true && loser_flag == true)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    // 1. Lock AB => Win. A Los. B = A-B
    // 2. Lock CA => Win. C Los. A = C-A
    // 3. Lock BC => B-C+C-A+A-B = 0 so ignore

    // Eg2.
    // 1. Lock AB => A-B
    // 2. Lock BC => C-B
    // 3. Lock CA => C-A

    for (int i = 0; i < pair_count; i++)
    {
        if (!cycle(i))
        {
            locked[pairs[i].winner][pairs[i].loser] = true;
        }
    }

}

bool find_winner(int col)
{
    for (int row = 0; row < candidate_count; row++)
    {
        if (locked[row][col])
        {
            return false;
        }
    }
    return true;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    for (int col = 0; col < candidate_count; col++)
    {
        if (find_winner(col))
        {
            printf("%s\n", candidates[col]);
            break;
        }
    }
}