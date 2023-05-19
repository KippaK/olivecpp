@echo off
set output_file=main
set source_files=   main.cpp ^
                    examples.cpp ^
                    src\canvas.cpp ^
                    src\shapes\circle.cpp ^
                    src\shapes\rectangle.cpp ^
                    src\shapes\shape.cpp ^
                    src\shapes\octagon.cpp ^
                    src\shapes\ring.cpp ^
                    src\shapes\line.cpp

g++ -o %output_file% %source_files%

if %errorlevel% equ 0 (
    echo Build successful.
    echo Running %output_file%...
    start cmd /k "cd /d %cd% && %output_file%"
) else (
    echo Build failed.
)