#include <iostream>
#include <sstream>
#include <iomanip>

/**
 * URI decoder.
 * Translates %xx (xx = two hex digits) to the character with the
 * appropriate ASCII code. Translates '+' into space. Leaves all
 * other characters unchanged.
 *
 * Example:
 * - In:  "Hello+world%21"
 * - Out: "Hello world!"
 *
 * @param s The string to decode.
 * @returns The decoded string.
 */
std::string uridecode(const std::string &s) {
    std::ostringstream decoded;
    for (std::size_t i = 0; i < s.length(); ++i) {
        if (s[i] == '%') {
            if (i + 2 < s.length()) {
                int value;
                std::istringstream is(s.substr(i + 1, 2));
                if (is >> std::hex >> value) {
                    decoded << static_cast<char>(value);
                    i += 2;
                }
            }
        } else if (s[i] == '+') {
            decoded << ' ';
        } else {
            decoded << s[i];
        }
    }
    return decoded.str();
}

/*
 * Test program.
 * Reads a pattern from stdin, decodes it, and writes the
 * result to stdout.
 */
int main() {
    std::string uri(
        std::istreambuf_iterator<char>(std::cin),
        std::istreambuf_iterator<char>()
    );
    std::cout << uridecode(uri);
}
