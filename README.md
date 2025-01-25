# eyesss_1.1
# HTTP Header and Content Viewer (C Program)

This C program sends an HTTP request to a specified URL and displays the response’s content and headers in the terminal. It uses the `libcurl` library to make HTTP requests.

## Features:
- **`-n`**: Displays HTTP headers.
- **`-s`**: Suppresses content output (only headers are shown).

## Usage:
1. **Compile**:
   ```bash
   gcc -o http_display http_display.c -lcurl


##Run
./http_display <URL> [-s] [-n]
./http_display https://example.com -s
