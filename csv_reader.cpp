#include <stdio.h>
#include <stdint.h>

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

enum Type
{
    Type_Source,
    Type_Compare,
};

b32 Hash[10000000] = {};

internal b32
CheckIfPresent(u32 HashId)
{
    b32 Result = Hash[HashId];

    return(Result);
}

internal b32
ParseCSV(char *FileName, FILE *OutFile, Type CsvFileType)
{
    FILE *CsvFile;
    CsvFile = fopen(FileName, "r");
    if (CsvFile == NULL)
    {
        fprintf(stderr, "[ERROR] Unable to open file: %s\n", FileName);
        return(1);
    }

    char LineBuffer[1024];
    u32 LineNumber = 0;
    while (!feof(CsvFile))
    {
        if (fgets(LineBuffer, ArrayCount(LineBuffer)-1, CsvFile) == NULL)
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

        if (CsvFileType == Type_Source)
        {
            Hash[HashId] = 1;
        }
        else if (CsvFileType == Type_Compare)
        {
            if (!CheckIfPresent(HashId))
            {
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
                // 1 => sizeof(LineBuffer[0])
                fwrite(&LineBuffer, sizeof(LineBuffer[0])*LineLength, 1, OutFile);
            }
        }

    }
    fclose(CsvFile);

    return(0);
}

int main(int ArgCount, char **Args)
{
    printf("CSV Reader\n");

    if (ArgCount != 4)
    {
        fprintf(stderr, "[ERROR] Usage: ./csv_reader [SOURCE_CSV] [COMPARE_TO_CSV] [OUTPUT_CSV]\n");
        return(1);
    }

    FILE *OutFile = fopen(Args[3], "wb");
    if(!OutFile)
    {
        fprintf(stderr, "[ERROR] Unable to open output file %s.\n", Args[3]);
        return(1);
    }

    if (ParseCSV(Args[1], OutFile, Type_Source))
    {
        return(1);
    }
    if (ParseCSV(Args[2], OutFile, Type_Compare))
    {
        return(1);
    }

    fclose(OutFile);
}
