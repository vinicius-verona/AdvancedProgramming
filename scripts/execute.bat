echo Executing %1 challenge with input %2.in ...
if [%1]==[] (
    echo "Syntax: .\execute.sh <Challenge - REQUIRED> <Test number - OPTIONAL>"
) else (
    if EXIST "..\%1\" (
        if EXIST "..\%1\src\%1.cpp" (
            g++ "..\%1\src\%1.cpp" -o "..\bin\%1.exe" -Wall

            if [%2]==[] (
                "..\bin\%1.exe" < "..\%1\input\0.in" > "..\%1\output\0.out"
            ) else (
                "..\bin\%1.exe" < "..\%1\input\%2.in" > "..\%1\output\%2.out"
            )

        ) else (
            if EXIST "..\%1\src\%1.c" (
                gcc "..\%1\src\%1.c" -o "..\bin\%1.exe" -Wall

                if [%2]==[] (
                    "..\bin\%1.exe" < "..\%1\input\0.in" > "..\%1\output\0.out"
                ) else (
                    "..\bin\%1.exe" < "..\%1\input\%2.in" > "..\%1\output\%2.out"
                )
            ) else (
                echo "Could not find a C/C++ source file for %1."
            )
        )
    ) else (
        echo "%1 does not exist." 
    )
)