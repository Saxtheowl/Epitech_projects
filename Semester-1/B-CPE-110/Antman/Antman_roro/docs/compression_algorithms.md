# Antman - Compression Algorithms Documentation

## Overview
Antman implements lossless compression algorithms tailored for three specific file types:
1. **Text files** (type 1): Song lyrics with words, spaces, punctuation
2. **HTML files** (type 2): Any character content
3. **PPM images** (type 3): Binary image data

## Algorithm Strategies

### Text Compression (Type 1)
**Algorithm**: Dictionary-based word replacement

**Process**:
1. **Dictionary Building**: Extract unique words from text
2. **Word Indexing**: Assign sequential indices to words
3. **Replacement**: Replace words with their dictionary indices
4. **Output Format**: `word1@word2@word3@@123 456 789`

**Example**:
- Input: `"Hello world Hello test"`
- Dictionary: `Hello@world@test@`
- Compressed: `Hello@world@test@@0 1 0 2`

**Advantages**: Effective for repetitive text with common words

### HTML Compression (Type 2)
**Algorithm**: Run-Length Encoding (RLE) with smart encoding

**Process**:
1. **Character Counting**: Count consecutive identical characters
2. **Selective Encoding**: Only encode runs > 3 chars or control chars
3. **Format**: `\x01[count][character]` for encoded runs
4. **Fallback**: Regular characters for short runs

**Example**:
- Input: `"aaaa<br>bbbb"`
- Compressed: `\x01\x04a<br>\x01\x04b`

**Advantages**: Handles any character, efficient for repetitive HTML

### PPM Image Compression (Type 3)
**Algorithm**: Same as HTML (RLE)

**Rationale**: PPM images often contain:
- Large areas of solid color (pixel repetition)
- Gradual color transitions
- Binary patterns suitable for RLE

## Implementation Details

### Data Structures
- **buffer_t**: Dynamic buffer for file I/O
- **dictionary_t**: Word dictionary with index mapping
- **dict_entry_t**: Dictionary entry structure

### Memory Management
- Dynamic buffer resizing
- Proper cleanup of all allocations
- Error handling for memory failures

### File Operations
- Read-only file access (no write permissions needed)
- Standard I/O for compressed output
- Error handling for file access issues

## Compression Efficiency

### Expected Compression Ratios
- **Text files**: 30-60% reduction (high word repetition)
- **HTML files**: 20-40% reduction (tag repetition)
- **PPM images**: 10-50% reduction (color area repetition)

### Performance Characteristics
- **Time Complexity**: O(n) for all algorithms
- **Space Complexity**: O(n) worst case
- **Scalability**: Linear with file size

## Error Handling
- Invalid file types return error code 84
- File access errors return error code 84
- Memory allocation failures handled gracefully
- Lossless guarantee: decompression always produces original

## Testing Strategy
- Round-trip testing (compress → decompress → compare)
- Edge cases (empty files, single characters)
- Error conditions (invalid args, missing files)
- Performance testing on large files