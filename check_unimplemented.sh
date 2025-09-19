#!/bin/bash

cd /home/roro/work/projects/Epitech_projects

echo "Projects with PDF files but no implementation (C files, Makefiles, or binaries):"
echo "================================================================"

find . -path "./fullLLM_claude/Semester-[123]/*" -name "*.pdf" -type f | while read pdf; do
    dir=$(dirname "$pdf")

    # Count implementation files
    c_files=$(find "$dir" -maxdepth 1 -name "*.c" -type f 2>/dev/null | wc -l)
    makefiles=$(find "$dir" -maxdepth 1 -name "[Mm]akefile*" -type f 2>/dev/null | wc -l)
    binaries=$(find "$dir" -maxdepth 1 -type f -executable 2>/dev/null | grep -v '\.sh$' | grep -v '\.pdf$' | wc -l)

    # Check if directory has only PDF and possibly README
    total_files=$(ls -1 "$dir" 2>/dev/null | wc -l)
    pdf_count=$(find "$dir" -maxdepth 1 -name "*.pdf" -type f 2>/dev/null | wc -l)
    readme_count=$(find "$dir" -maxdepth 1 -name "README*" -type f 2>/dev/null | wc -l)

    # If no implementation files found
    if [ "$c_files" -eq 0 ] && [ "$makefiles" -eq 0 ] && [ "$binaries" -eq 0 ]; then
        # Check if directory only contains PDF and possibly README
        expected_files=$((pdf_count + readme_count))
        if [ "$total_files" -eq "$expected_files" ] || [ "$total_files" -eq "$pdf_count" ]; then
            echo "$dir"
            echo "  Files: $(ls -1 "$dir" | tr '\n' ' ')"
            echo ""
        fi
    fi
done