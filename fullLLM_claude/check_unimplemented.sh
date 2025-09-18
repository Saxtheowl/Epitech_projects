#!/bin/bash

# Script to find directories with PDF files but no implementation files

# Function to check if directory has implementation files
check_implementation() {
    local dir="$1"
    
    # Skip documentation directories
    if [[ "$dir" == *"/DOCUMENTS/"* ]]; then
        return 1
    fi
    
    # Check for various implementation files and return 0 if found (has implementation)
    
    # Check for source files
    if find "$dir" -maxdepth 2 -name "*.c" -o -name "*.cpp" -o -name "*.py" -o -name "*.js" -o -name "*.java" -o -name "*.hs" -o -name "*.ml" | grep -q .; then
        return 0
    fi
    
    # Check for Makefile
    if find "$dir" -maxdepth 2 -name "Makefile" -o -name "makefile" | grep -q .; then
        return 0
    fi
    
    # Check for executable files (exclude .pdf, .txt, .md, .o files)
    if find "$dir" -maxdepth 2 -type f -executable ! -name "*.pdf" ! -name "*.txt" ! -name "*.md" ! -name "*.o" | grep -q .; then
        return 0
    fi
    
    # Check for project config files
    if find "$dir" -maxdepth 2 -name "package.json" -o -name "requirements.txt" -o -name "Cargo.toml" -o -name "pom.xml" | grep -q .; then
        return 0
    fi
    
    # No implementation found
    return 1
}

# Function to get project complexity/type from PDF name
get_project_type() {
    local pdf_name="$1"
    local dir="$2"
    
    # Extract project category from directory path
    if [[ "$dir" == *"Pool"* ]]; then
        echo "POOL_EXERCISE"
    elif [[ "$dir" == *"Solo_Stumpers"* ]]; then
        echo "SOLO_STUMPER"
    elif [[ "$dir" == *"Duo_Stumpers"* ]]; then
        echo "DUO_STUMPER"
    elif [[ "$dir" == *"Bootstrap"* ]] || [[ "$pdf_name" == *"bootstrap"* ]]; then
        echo "BOOTSTRAP"
    elif [[ "$dir" == *"B-MUL"* ]]; then
        echo "GRAPHICS_PROJECT"
    elif [[ "$dir" == *"B-SEC"* ]]; then
        echo "SECURITY_PROJECT"
    elif [[ "$dir" == *"B-NWP"* ]] || [[ "$dir" == *"B-PSU"* ]]; then
        echo "SYSTEM_PROJECT"
    else
        echo "REGULAR_PROJECT"
    fi
}

# Function to assess project suitability
is_suitable_project() {
    local project_type="$1"
    local dir="$2"
    local pdf_name="$3"
    
    # Exclude graphics projects (require CSFML/graphics libraries)
    if [[ "$project_type" == "GRAPHICS_PROJECT" ]]; then
        return 1
    fi
    
    # Exclude security projects (often require root/complex setup)
    if [[ "$project_type" == "SECURITY_PROJECT" ]]; then
        return 1
    fi
    
    # Exclude system projects that require complex setup
    if [[ "$project_type" == "SYSTEM_PROJECT" ]]; then
        # Allow simple system projects but exclude complex ones
        if [[ "$pdf_name" == *"sudo"* ]] || [[ "$pdf_name" == *"teams"* ]] || [[ "$pdf_name" == *"42sh"* ]]; then
            return 1
        fi
    fi
    
    # Skip bootcamp days (usually not standalone projects)
    if [[ "$dir" == *"Bootcamp_Phoenix"* ]]; then
        return 1
    fi
    
    # Prefer pool exercises, stumpers, and simple projects
    if [[ "$project_type" == "POOL_EXERCISE" ]] || [[ "$project_type" == "SOLO_STUMPER" ]] || [[ "$project_type" == "DUO_STUMPER" ]] || [[ "$project_type" == "BOOTSTRAP" ]]; then
        return 0
    fi
    
    return 0
}

echo "=== COMPREHENSIVE SEARCH FOR UNIMPLEMENTED EPITECH PROJECTS ==="
echo ""

# Arrays to store results
declare -a unimplemented_suitable=()
declare -a unimplemented_unsuitable=()
declare -a implemented=()

# Find all directories with PDF files
while IFS= read -r dir; do
    # Get PDF file name in this directory
    pdf_file=$(find "$dir" -name "*.pdf" -printf "%f\n" | head -1)
    
    if [[ -n "$pdf_file" ]]; then
        project_type=$(get_project_type "$pdf_file" "$dir")
        
        if check_implementation "$dir"; then
            # Implementation exists
            implemented+=("$dir|$pdf_file|$project_type")
        else
            # No implementation found
            if is_suitable_project "$project_type" "$dir" "$pdf_file"; then
                unimplemented_suitable+=("$dir|$pdf_file|$project_type")
            else
                unimplemented_unsuitable+=("$dir|$pdf_file|$project_type")
            fi
        fi
    fi
done < <(find /home/roro/work/projects/Epitech_projects/fullLLM_claude -name "*.pdf" -exec dirname {} \; | sort -u)

echo "=== SUITABLE UNIMPLEMENTED PROJECTS (READY FOR IMPLEMENTATION) ==="
echo "These projects are simple, manageable, and don't require complex infrastructure:"
echo ""

for project in "${unimplemented_suitable[@]}"; do
    IFS='|' read -r dir pdf_file project_type <<< "$project"
    echo "📁 Directory: $dir"
    echo "📄 PDF: $pdf_file"
    echo "🏷️  Type: $project_type"
    echo ""
done

echo "=== UNSUITABLE UNIMPLEMENTED PROJECTS ==="
echo "These projects require complex setup, graphics libraries, or system privileges:"
echo ""

for project in "${unimplemented_unsuitable[@]}"; do
    IFS='|' read -r dir pdf_file project_type <<< "$project"
    echo "📁 Directory: $dir"
    echo "📄 PDF: $pdf_file"
    echo "🏷️  Type: $project_type"
    echo ""
done

echo "=== SUMMARY ==="
echo "✅ Suitable unimplemented projects: ${#unimplemented_suitable[@]}"
echo "❌ Unsuitable unimplemented projects: ${#unimplemented_unsuitable[@]}"
echo "✅ Already implemented projects: ${#implemented[@]}"
echo ""
echo "Total projects with PDFs: $((${#unimplemented_suitable[@]} + ${#unimplemented_unsuitable[@]} + ${#implemented[@]}))"