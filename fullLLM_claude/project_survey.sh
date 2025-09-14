#!/bin/bash

PROJECT_ROOT="/home/roro/work/projects/Epitech_projects/fullLLM_claude"

echo "# EPITECH PROJECT IMPLEMENTATION SURVEY"
echo "# Generated on $(date)"
echo

for semester in {1..5}; do
    semester_dir="$PROJECT_ROOT/Semester-$semester"
    
    if [ ! -d "$semester_dir" ]; then
        continue
    fi
    
    echo "## SEMESTER-$semester"
    echo
    
    # Find all project directories (B-XXX-XXX pattern)
    find "$semester_dir" -maxdepth 1 -type d -name "B-*" | sort | while read -r category_dir; do
        category=$(basename "$category_dir")
        echo "### $category"
        
        # Find project subdirectories
        find "$category_dir" -maxdepth 1 -type d ! -path "$category_dir" | sort | while read -r project_dir; do
            project=$(basename "$project_dir")
            echo "#### $project"
            
            # Check for source files
            source_count=$(find "$project_dir" -name "*.c" -o -name "*.cpp" -o -name "*.py" -o -name "*.hs" -o -name "*.java" -o -name "*.js" -o -name "*.rs" 2>/dev/null | wc -l)
            
            # Check for Makefiles
            makefile_count=$(find "$project_dir" -name "Makefile" -o -name "makefile" 2>/dev/null | wc -l)
            
            # Check for PDFs
            pdf_count=$(find "$project_dir" -name "*.pdf" 2>/dev/null | wc -l)
            
            # Check for binaries/executables
            binary_count=$(find "$project_dir" -type f -executable ! -name "*.sh" ! -name "*.py" ! -name "*.pl" 2>/dev/null | wc -l)
            
            # Status determination
            if [ "$source_count" -gt 0 ] && [ "$makefile_count" -gt 0 ]; then
                if [ "$binary_count" -gt 0 ]; then
                    status="✅ COMPLETED"
                else
                    status="⚠️ PARTIAL"
                fi
            elif [ "$source_count" -gt 0 ]; then
                status="⚠️ PARTIAL"
            elif [ "$pdf_count" -gt 0 ]; then
                status="❌ MISSING (PDF Only)"
            else
                status="❌ EMPTY"
            fi
            
            echo "  Status: $status"
            echo "  Sources: $source_count files"
            echo "  Makefiles: $makefile_count"
            echo "  PDFs: $pdf_count"
            echo "  Binaries: $binary_count"
            echo
        done
    done
    echo
done