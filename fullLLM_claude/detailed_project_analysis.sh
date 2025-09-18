#!/bin/bash

# Comprehensive Epitech Project Analysis Script

echo "=== EPITECH PROJECT STRUCTURE ANALYSIS ==="
echo ""

# Initialize counters
total_projects=0
completed_projects=0
incomplete_projects=0
pool_exercises_total=0
pool_exercises_completed=0
pool_exercises_incomplete=0

# Count by semester
declare -A semester_totals
declare -A semester_completed
declare -A semester_incomplete

# Function to check if a directory has substantial implementation
has_implementation() {
    local dir="$1"

    # Skip documentation directories
    if [[ "$dir" == *"/DOCUMENTS/"* ]] || [[ "$dir" == *"/reports/"* ]]; then
        return 1
    fi

    # Count source files
    local source_count=$(find "$dir" -maxdepth 3 -name "*.c" -o -name "*.cpp" -o -name "*.py" -o -name "*.js" -o -name "*.java" -o -name "*.hs" -o -name "*.ml" 2>/dev/null | wc -l)

    # Consider it implemented if it has at least 1 source file
    if [ "$source_count" -gt 0 ]; then
        return 0
    fi

    # Check for executables or Makefiles
    if find "$dir" -maxdepth 2 -name "Makefile" -o -type f -executable ! -name "*.pdf" ! -name "*.txt" ! -name "*.md" 2>/dev/null | grep -q .; then
        return 0
    fi

    return 1
}

# Function to get project type
get_project_category() {
    local path="$1"

    if [[ "$path" == *"/Pool/"* ]]; then
        echo "POOL_EXERCISE"
    elif [[ "$path" == *"/Bootstrap"* ]] || [[ "$path" == *"/Boostrap"* ]]; then
        echo "BOOTSTRAP"
    elif [[ "$path" == *"/Rush"* ]]; then
        echo "RUSH"
    elif [[ "$path" == *"/Stumper"* ]]; then
        echo "STUMPER"
    else
        echo "PROJECT"
    fi
}

# Main analysis
for semester_dir in /home/roro/work/projects/Epitech_projects/fullLLM_claude/Semester-*; do
    if [ ! -d "$semester_dir" ]; then
        continue
    fi

    semester_name=$(basename "$semester_dir")
    echo "=== Analyzing $semester_name ==="

    semester_totals["$semester_name"]=0
    semester_completed["$semester_name"]=0
    semester_incomplete["$semester_name"]=0

    # Find all project directories (directories with PDF files or source files)
    while IFS= read -r project_dir; do
        if [ -z "$project_dir" ]; then
            continue
        fi

        # Skip if it's just a course directory without specific projects
        if [ "$(basename "$project_dir")" = "$(basename "$semester_dir")" ]; then
            continue
        fi

        # Count as a project
        total_projects=$((total_projects + 1))
        semester_totals["$semester_name"]=$((${semester_totals["$semester_name"]} + 1))

        project_category=$(get_project_category "$project_dir")

        if [[ "$project_category" == "POOL_EXERCISE" ]]; then
            pool_exercises_total=$((pool_exercises_total + 1))
        fi

        # Check if implemented
        if has_implementation "$project_dir"; then
            completed_projects=$((completed_projects + 1))
            semester_completed["$semester_name"]=$((${semester_completed["$semester_name"]} + 1))
            if [[ "$project_category" == "POOL_EXERCISE" ]]; then
                pool_exercises_completed=$((pool_exercises_completed + 1))
            fi
            echo "  ✅ $project_dir ($project_category)"
        else
            incomplete_projects=$((incomplete_projects + 1))
            semester_incomplete["$semester_name"]=$((${semester_incomplete["$semester_name"]} + 1))
            if [[ "$project_category" == "POOL_EXERCISE" ]]; then
                pool_exercises_incomplete=$((pool_exercises_incomplete + 1))
            fi
            echo "  ❌ $project_dir ($project_category)"
        fi
    done < <(find "$semester_dir" -type d \( -name "Day*" -o -name "*Bootstrap*" -o -name "*Boostrap*" -o -name "*Rush*" -o -name "*Stumper*" \) -o \( -name "*.pdf" -exec dirname {} \; \) 2>/dev/null | sort -u)

    echo "  Semester totals: ${semester_totals["$semester_name"]} projects (${semester_completed["$semester_name"]} completed, ${semester_incomplete["$semester_name"]} incomplete)"
    echo ""
done

echo "=== COMPREHENSIVE SUMMARY ==="
echo ""
echo "📊 OVERALL STATISTICS:"
echo "  Total projects found: $total_projects"
echo "  Completed projects: $completed_projects"
echo "  Incomplete projects: $incomplete_projects"
echo "  Completion rate: $(( completed_projects * 100 / total_projects ))%"
echo ""

echo "🎯 POOL EXERCISES (Learning exercises):"
echo "  Total pool exercises: $pool_exercises_total"
echo "  Completed pool exercises: $pool_exercises_completed"
echo "  Incomplete pool exercises: $pool_exercises_incomplete"
if [ $pool_exercises_total -gt 0 ]; then
    echo "  Pool completion rate: $(( pool_exercises_completed * 100 / pool_exercises_total ))%"
fi
echo ""

echo "🎓 BY SEMESTER:"
for semester in Semester-0 Semester-1 Semester-2 Semester-3 Semester-4 Semester-5; do
    if [ "${semester_totals["$semester"]}" -gt 0 ]; then
        completion_rate=$(( ${semester_completed["$semester"]} * 100 / ${semester_totals["$semester"]} ))
        echo "  $semester: ${semester_completed["$semester"]}/${semester_totals["$semester"]} completed ($completion_rate%)"
    fi
done
echo ""

# List courses by semester
echo "📚 COURSES BY SEMESTER:"
for semester in Semester-0 Semester-1 Semester-2 Semester-3 Semester-4 Semester-5; do
    semester_path="/home/roro/work/projects/Epitech_projects/fullLLM_claude/$semester"
    if [ -d "$semester_path" ]; then
        courses=$(find "$semester_path" -maxdepth 1 -type d -name "B-*" | wc -l)
        if [ $courses -gt 0 ]; then
            echo "  $semester: $courses courses"
            find "$semester_path" -maxdepth 1 -type d -name "B-*" -exec basename {} \; | sort | sed 's/^/    - /'
        fi
    fi
done

echo ""
echo "=== TOP PRIORITY FOR IMPLEMENTATION ==="
echo "Incomplete projects that are suitable for implementation:"
echo ""

# Find suitable incomplete projects
while IFS= read -r dir; do
    if [ -n "$dir" ] && [ -f "$dir"/*.pdf 2>/dev/null ] || find "$dir" -name "*.pdf" -type f | grep -q .; then
        project_category=$(get_project_category "$dir")
        if ! has_implementation "$dir"; then
            # Skip graphics, security, and complex system projects
            if [[ "$dir" != *"/B-MUL-"* ]] && [[ "$dir" != *"/B-SEC-"* ]] && [[ "$dir" != *"sudo"* ]] && [[ "$dir" != *"teams"* ]] && [[ "$dir" != *"42sh"* ]]; then
                echo "🎯 $dir ($project_category)"
            fi
        fi
    fi
done < <(find /home/roro/work/projects/Epitech_projects/fullLLM_claude -type d \( -name "Day*" -o -name "*Bootstrap*" -o -name "*Boostrap*" -o -name "*Rush*" \) -o \( -name "*.pdf" -exec dirname {} \; \) 2>/dev/null | sort -u) | head -15

echo ""
echo "Analysis complete!"