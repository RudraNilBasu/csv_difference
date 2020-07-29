Store the extra entries in a csv file (compare.csv) when compared to
another csv file (source.csv) and store the result (result.csv)

USAGE

Run the build script:
  .\build.bat

And use source and compare files with:
  ..\build\csv_reader.exe source.csv compare.csv result.csv

Example:

source.csv:

    id,name,name,name

    1112222,some_string_value,Hello,World
    4442222,other_string_value,Bye,World

compare.csv:

    id,name,name,name

    1112222,some_string_value,Hello,World
    9112222,some_string_value,Hello,World
    5552222,some_string_value,Hello,World
    8888222,other_string_value,Hello,World

result.csv:

    9112222,some_string_value,Hello,World
    5552222,some_string_value,Hello,World

- Rudra
