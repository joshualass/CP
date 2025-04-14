def obfuscate_file(input_filename, output_filename):
    with open(input_filename, 'r', encoding='utf-8') as f:
        code = f.read()

    parts = []
    for c in code:
        n = ord(c)  # Get ASCII value

        # Build a string of length `n` using only spaces and tabs
        filler = ''
        for _ in range(n):
            filler += ' ' if _ % 2 == 0 else '\t'  # alternate space/tab

        parts.append(filler)

    # Join all parts using a delimiter (like ' \t\t ') -> space tab tab
    delimiter = ' \t\t '  # can customize this too if you want
    fake_string = delimiter.join(parts)

    # Now build the final obfuscated code
    final_code = f"exec(''.join(chr(len(i)) for i in '{fake_string}'.split('{delimiter}')))"

    # Save it to the output file
    with open(output_filename, 'w', encoding='utf-8') as f:
        f.write(final_code)

    print(f"Obfuscated code written to {output_filename}")

# Example usage:
# obfuscate_file('input.py', 'output.py')
obfuscate_file('climbingstairs.py', 'climbingstairsgg.py')