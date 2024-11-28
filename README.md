Currently working on the project

## Terminal input handling with termios

### What is `termios`?

`termios` is a POSIX library used to control terminal I/O behavior.

It allows configuring how the terminal processes input and output,

make it possible to:

- enable or disable canonical mode(line-buffered input)
- enable or disable echoing of type characters\
- control other terminal setting


### Canoncial mode and Non-canonical mode

- canonical mode(default)
	+ inpyt is line-buffered
	+ the terminal waits for the user to press `Enter` before processing input
	+ backspace handling and other input editing features are handled by the terminal

- non-canonical mode
	+ input is processed character-by-character
	+ no need to press `Enter` for inpuyt to be available
	+ the program handles special keys(ex. backspace, arrow keys) directly

### Why use non-canonical mode?

- real-time input handling
	+ process key presses immediately without waiting for `Enter`
- custom input behavior
	+ handle special keys like arrow keys, backspace, and Ctrl+C priogrammatically
- interactive programs
	+ useful for creating applications like games, shells, or text editors

### How to enable non-canonical mode

```
	#include <termios.h>
	#include <unistd.h>

	void	enable_raw_mode(void)
	{
		struct termios	t;

		tcgetattr(STDIN_FILENO, &t);
		t.c_lfalg &= ~(ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
```
- `tcgetattr(STDIN_FILENO, &t)`
	+ fetches the current terminal attributes for standard input
- `t.c_lfalg &= ~(ICANON | ECHO)`
	+ `~(ICANON | ECHO)` clears the `ICANON`(canonical mode) and `ECHO`(echo mode) bits
	+ disabling `ICANON` processes input character-by-character
	+ disableing `ECHO` prevents typed characters from being displayed automatically
- `tcsetattr(STDIN_FILENO, TCSANOW, &t)`
	+ applies the modified settings immediately

### How to disable non-canoncial mode

```
	void	disable_raw_mode(void)
	{
		struct termios	t;
		tcgetattr(STDIN_FILENO, &t);
		t.c_lflag |= (ICANON | ECHO);
		tcsetattr(STDIN_FILENO, TCSANOW, &t);
	}
```
- `t.c_lflag |= (ICANON | ECHO)`
	+ enabling `ICANON` and `ECHO`

### When to use non-canoncial mode

1. always restore terminal setting
	- ensure `disable_raw_mode()` is called when the program exits
	- use `atexit()` or signal handlers(`SIGINT`) to guarantee cleansup:

	```
		#include <cstdlib>
		atexit(disable_raw_mode);
	```
	- if not, terminal may rtemain in raw mode, causing unusual behavior like:
		+ characters not being echoed when typed
		+ input being processed character-by-character instead of line-by-line
		+ backspace andf enter not working as expected
2. backspace handling
	- non-canonial mode doesn't handle backspace automatically
	- need to be processed manually by detecting `127` or `\b`, and removing the last character from the input buffer
	```
		#include <iostream>
		#include <unistd.h>

		int	main(void)
		{
			enable_raw_mode();

			std::string	input;
			char		c;

			while (1)
			{
				read(STDIN_FILENO, &c, 1);	// Read one character

				if (c == 127 || c == '\b')	// Detect Backspace
				{
					if (!input.empty())
					{
						input.pop_back();	// Remove last character from buffer
						std::cout << "\b \b";	// Erase character from terminal
						std::cout.flush();
					}
				}
				else if (c == '\n')		// Enter key
					break;
				else
				{
					input += c;			// Add character to input
					std::cout << c;			// Echo character
					std::cout.flush();
				}
			}

			disable_raw_mode();
			std::cout << "\ninput: " << input << std::endl;
			return 0;
		}
	```
3. special keys
	- arraw keys and function keys send escape sequence.
	- need to be handled these explicitly in the program
