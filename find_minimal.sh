#!/bin/bash

cd /home/roro/work/projects/Epitech_projects

echo "Projects needing implementation (no C files OR no Makefiles):"
echo "=========================================================="

find . -path "./fullLLM_claude/Semester-[123]/*" -name "*.pdf" -type f > /tmp/pdf_list.txt

while read pdf; do
    dir=$(dirname "$pdf")

    # Count implementation files
    c_files=$(find "$dir" -maxdepth 1 -name "*.c" -type f 2>/dev/null | wc -l)
    makefiles=$(find "$dir" -maxdepth 1 -name "[Mm]akefile*" -type f 2>/dev/null | wc -l)

    # If no C files OR no Makefiles (indicating incomplete/unimplemented)
    if [ "$c_files" -eq 0 ] || [ "$makefiles" -eq 0 ]; then
        # Check if it's mostly just PDF and README
        total_non_doc_files=$(ls -1 "$dir" 2>/dev/null | grep -v "README" | grep -v "\.pdf$" | grep -v "\.md$" | wc -l)
        if [ "$total_non_doc_files" -le 2 ]; then
            echo "$dir"
            echo "  C files: $c_files, Makefiles: $makefiles"
            echo "  Contents: $(ls -1 "$dir" | tr '\n' ' ')"
            echo ""
        fi
    fi
done < /tmp/pdf_list.txt

rm /tmp/pdf_list.txt