# Linux Utils

Recreation of essential Unix command-line utilities in C, implementing core file I/O and string processing operations.

## Build

```bash
gcc -o wcat wcat.c
gcc -o wgrep wgrep.c
gcc -o wzip wzip.c
gcc -o wunzip wunzip.c
```

## Utilities

### wcat - File Concatenation
Reads and displays file contents to standard output.

```bash
./wcat file1.txt file2.txt
```

**Implementation:**
- Uses 1KB buffer for efficient file reading
- Processes multiple files sequentially
- Handles file access errors gracefully

**Key Functions:**
- `fopen()` for file access
- `fgets()` for buffered reading
- Proper file handle cleanup

### wgrep - Pattern Search
Searches for substring patterns in files or standard input.

```bash
./wgrep "pattern" file.txt
echo "hello world" | ./wgrep "world"
```

**Implementation:**
- Custom string matching algorithm (no regex)
- Supports both file input and stdin
- Uses `getline()` for dynamic line reading

**Algorithm:**
```c
// Sliding window substring search
int searchSubstring(char subStr[], char line[]) {
    // Custom implementation with match counter
    // Returns 0 if found, 1 if not found
}
```

### wzip - Run-Length Encoding
Compresses files by encoding consecutive identical characters.

```bash
./wzip file.txt > compressed.z
echo "aaabbbccc" | ./wzip > test.z
```

**Implementation:**
- Counts consecutive character occurrences
- Binary output format: 4-byte count + 1-byte character
- Single-pass compression algorithm

**File Format:**
```
[4-byte count][1-byte char][4-byte count][1-byte char]...
```

### wunzip - Run-Length Decoding
Decompresses files created by wzip.

```bash
./wunzip compressed.z
```

**Implementation:**
- Reads binary format pairs (count, character)
- Outputs repeated characters based on count
- Error checking for malformed input

**Process:**
1. Read 4-byte integer (count)
2. Read 1-byte character
3. Output character `count` times
4. Repeat until EOF

## Technical Details

### Memory Management
- **wgrep**: Uses `getline()` for dynamic memory allocation
- **All utilities**: Proper file handle cleanup
- **Error handling**: Graceful resource deallocation

### File I/O Patterns
- **Text processing**: `fgets()`, `getline()` for line-based input
- **Binary operations**: `fread()`, `fwrite()` for precise data handling
- **Buffering**: Efficient reading strategies for performance

### Error Handling
- File access permissions and existence
- Invalid file formats (wunzip)
- Memory allocation failures
- Malformed input validation

## Testing

```bash
# Test wcat
echo "Hello World" > test.txt
./wcat test.txt

# Test wgrep
echo "search this line" | ./wgrep "this"

# Test compression roundtrip
echo "aaabbbccc" | ./wzip > test.z
./wunzip test.z

# Clean up
rm test.txt test.z
```
