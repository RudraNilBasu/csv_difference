#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <assert.h>

#define internal static
#define global static
#define Assert assert

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef s32 b32;
typedef s32 b32x;

typedef float f32;
typedef double f64;

#define ArrayCount(Array) (sizeof(Array) / sizeof((Array)[0]))

b32 Hash[10000000] = {};

internal b32
CheckIfPresent(u32 HashId)
{
    b32 Result = Hash[HashId];

    return(Result);
}

int main(int ArgCount, char **Args)
{
    printf("CSV Reader\n");

    if (ArgCount != 4)
    {
        printf("Error: Usage: ./csv_reader <source_filename> <compare_to_filename> <output_file_name>\n");
        return(1);
    }

    FILE *SourceCsvFile;
    FILE *ToCompareCsvFile;
    // CsvFile = fopen("test.csv", "r");
    SourceCsvFile = fopen(Args[1], "r");
    ToCompareCsvFile = fopen(Args[2], "r");
    if (SourceCsvFile == NULL)
    {
        printf("Unable to open file: %s\n", Args[1]);
        return(0);
    }
    if (ToCompareCsvFile == NULL)
    {
        printf("Unable to open file: %s\n", Args[2]);
        return(0);
    }

    FILE *OutFile = fopen(Args[3], "wb");
    if(!OutFile)
    {
        fprintf(stderr, "[ERROR] Unable to open output file %s.\n", Args[3]);
    }

    // TODO(@rudra): Compress!
    char LineBuffer[1024];
    u32 LineNumber = 0;
    while (!feof(SourceCsvFile))
    {
        if (fgets(LineBuffer, ArrayCount(LineBuffer)-1, SourceCsvFile) == NULL)
        {
            break;
        }

        if (++LineNumber == 1)
        {
            printf("Skipping first line as header\n");
            continue;
        }
        if (LineBuffer[0] == '\n')
        {
            printf("Skipping blank lines\n");
            continue;
        }

        // printf("Line: %s\n", LineBuffer);
        u32 HashId = 0;
        for (u32 Index = 0;
             Index < ArrayCount(LineBuffer);
             Index++)
        {
            if (LineBuffer[Index] == 0)
            {
                break;
            }
            if (LineBuffer[Index] == ',')
            {
                break;
            }
            HashId = HashId*10 + (LineBuffer[Index]-'0');
        }
        Hash[HashId] = 1;
        // CheckIfPresent(HashId);
    }

    // Checker
    // char LineBuffer[1024];
    LineNumber = 0;
    while (!feof(ToCompareCsvFile))
    {
        if (fgets(LineBuffer, ArrayCount(LineBuffer)-1, ToCompareCsvFile) == NULL)
        {
            break;
        }

        if (++LineNumber == 1)
        {
            // printf("Skipping first line as header\n");
            continue;
        }
        if (LineBuffer[0] == '\n')
        {
            // printf("Skipping blank lines\n");
            continue;
        }

        // printf("Line: %s\n", LineBuffer);
        u32 HashId = 0;
        for (u32 Index = 0;
             Index < ArrayCount(LineBuffer);
             Index++)
        {
            if (LineBuffer[Index] == 0)
            {
                break;
            }
            if (LineBuffer[Index] == ',')
            {
                break;
            }
            HashId = HashId*10 + (LineBuffer[Index]-'0');
        }
        if (!CheckIfPresent(HashId))
        {
            printf("Not present: %d\n", HashId);

            u32 LineLength = 0;
            for (u32 Index = 0;
                 Index < ArrayCount(LineBuffer);
                 Index++)
            {
                LineLength++;
                if (LineBuffer[Index] == '\n')
                {
                    break;
                }
            }
            // fwrite(&LineBuffer, sizeof(LineBuffer), 1, OutFile);
            fwrite(&LineBuffer, sizeof(LineBuffer[0])*LineLength, 1, OutFile);
        }
    }

    fclose(SourceCsvFile);
    fclose(ToCompareCsvFile);
    fclose(OutFile);
}


















    // fp = fopen(Args[1], "r");

    /*
    char Buffer[1024];
    size_t Count = fread(&Buffer, sizeof(Buffer[0]), ArrayCount(Buffer), CsvFile);
    */

    // printf("CLOCKS_PER_SECOND: %d\n", CLOCKS_PER_SECOND);
    /*
    printf("CLOCKS_PER_SECOND: %d\n", CLOCKS_PER_SEC); // 1000 clocs per sec: millisec cloc


    while(Queue.TileRetiredCount < TotalTileCount)
    {
        if (RenderTile(&Queue))
        {
            fprintf(stderr, "\rRaycasting %d%%", (100 * (u32)Queue.TileRetiredCount / TotalTileCount));
            fflush(stdout);
        }
    }

    clock_t EndClock = clock();
    clock_t TimeElapsed = EndClock - StartClock;
    fprintf(stderr, "\n");
    printf("Raycasting time: %d ms\n", TimeElapsed);
    printf("Total Bounces: %llu\n", Queue.BouncesComputed);
    if((f64)Queue.BouncesComputed != 0)
    {
        printf("Performance:  %fms/ bounce\n", (f64)TimeElapsed / (f64)Queue.BouncesComputed);
    }

    WriteImage(Image, "test.bmp");

    fprintf(stderr, "\nDone\n");

    return(0);
    */
