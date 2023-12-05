#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <stdint.h>

uint64_t *getBitBoard(char *rawBoard, uint64_t boardSize);
char countSetBits(uint64_t num);

int main(void)
{
    uint64_t nTestCases;
    scanf("%" SCNu64, &nTestCases);

    for (uint64_t t = 0; t < nTestCases; t++)
    {
        uint64_t boardSize;
        scanf("%" SCNu64, &boardSize);

        uint64_t nEntries = boardSize * boardSize;
        char *rawBoard;
        rawBoard = (char *)malloc(nEntries * sizeof(char));
        for (uint64_t i = 0; i < nEntries; i++)
        {
            scanf(" %c", &rawBoard[i]);
        }

        uint64_t *bitBoard;
        bitBoard = getBitBoard(rawBoard, boardSize);
        free(rawBoard);

        uint64_t nSets = (uint64_t)1 << boardSize;

        uint64_t *dp;
        dp = (uint64_t *)calloc(nSets, sizeof(uint64_t));
        dp[0] = 1;

        uint64_t output = 0;
        for (uint64_t set = 0; set < nSets; set++)
        {
            uint64_t n = countSetBits(set);
            for (uint64_t k = 0; k < boardSize; k++)
            {
               if ((set & ((uint64_t)1 << k)) != 0)
               {
                    if ((bitBoard[n-1] & ((uint64_t)1 << k)) == 0)
                        dp[set] += dp[set - ((uint64_t)1 << k)];
               }
            }
            if (n == boardSize)
                output += dp[set];
        }

        printf("%" PRIu64 "\n", output);

        free(bitBoard);
        free(dp);
    }
}

char countSetBits(uint64_t num)
{
    char nSetBits = 0;
    while (num) {
        num &= num - 1;
        nSetBits++;
    }

    return nSetBits;
}

uint64_t *getBitBoard(char *rawBoard, uint64_t boardSize)
{
    uint64_t *bitBoard;
    bitBoard = (uint64_t *)malloc(boardSize * sizeof(uint64_t));
    for (uint64_t i = 0; i < boardSize; i++)
    {
        uint64_t bitRow = 0;
        for (uint64_t j = 0; j < boardSize; j++)
        {
            uint64_t entry = (rawBoard[boardSize * i + j] == 'o');
            entry <<= (boardSize - j - 1);
            bitRow |= entry;
        }
        bitBoard[i] = bitRow;
    }
    return bitBoard;
}