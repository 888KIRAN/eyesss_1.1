# eyesss_1.1
# HTTP Header and Content Viewer (C Program)

This C program sends an HTTP request to a specified URL and displays the response’s content and headers in the terminal. It uses the `libcurl` library to make HTTP requests.

## Features:
- **`-n`**: Displays HTTP headers.
- **`-s`**: Suppresses content output (only headers are shown).

## Download:
1. **Compile**:
   ```bash
   git clone https://github.com/888KIRAN/eyesss_1.1
   cd eyesss_1.1/
   gcc eyesss.c -o eyesss -lcurl

