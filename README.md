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
	void	ReadLine::enable_raw_mode(void)
	{
		struct termios	t;

		tcgetattr(STDIN_FILENO, &t);
		t.c_lflag &= ~(ICANON | ECHO);
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
	void	ReadLine::disable_raw_mode(void)
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
		void	ReadLine::handle_backspace(std::string &input)
		{
			if (!input.empty() && input.length() >= 1)
			{
				input.pop_back();	// Remove last character 
				std::cout << "\b \b";	// Erase character from 
				std::cout.flush();
			}
		}
	```
3. escape sequence handling
	- in raw mode, the terminal sends raw input data directly to the program including multi-character escape sequence for special keys
	- without handling these sequences:
		+ special keys will not work
		+ the terminal may behave unpredictably, waiting for sequences to complete or misinterpreting input.
	```
		int	ReadLine::is_escape_sequence(char c)
		{
			char		seq;
			std::string	escape_sequence(1, c);

			std::unordered_set<std::string>	sequence({
				/* arrow keys */
				ESCAPE_UP_ARROW, ESCAPE_DOWN_ARROW, ESCAPE_RIGHT_ARROW, ESCAPE_LEFT_ARROW,

				/* function keys */
				ESCAPE_F1, ESCAPE_F2, ESCAPE_F3, ESCAPE_F4, ESCAPE_F5, ESCAPE_F6,
				ESCAPE_F7, ESCAPE_F8, ESCAPE_F9, ESCAPE_F10, ESCAPE_F11, ESCAPE_F12,

				/* navigation keys */
				ESCAPE_INSERT, ESCAPE_DELETE, ESCAPE_HOME,
				ESCAPE_END, ESCAPE_PAGE_UP, ESCAPE_PAGE_DOWN,

				/* alt keys */
				ESCAPE_ALT_A, ESCAPE_ALT_B, ESCAPE_ALT_C, ESCAPE_ALT_D, ESCAPE_ALT_E,
				ESCAPE_ALT_F, ESCAPE_ALT_G, ESCAPE_ALT_H, ESCAPE_ALT_I, ESCAPE_ALT_J,
				ESCAPE_ALT_K, ESCAPE_ALT_L, ESCAPE_ALT_M, ESCAPE_ALT_N, ESCAPE_ALT_O,
				ESCAPE_ALT_P, ESCAPE_ALT_Q, ESCAPE_ALT_R, ESCAPE_ALT_S, ESCAPE_ALT_T,
				ESCAPE_ALT_U, ESCAPE_ALT_V, ESCAPE_ALT_W, ESCAPE_ALT_X, ESCAPE_ALT_Y, ESCAPE_ALT_Z});

			if (c != '\033')
				return (NONE);

			if (read(this->_fd, &seq, 1) == 1)
			{
				escape_sequence += std::string(1, seq);
				if ('a' <= seq && seq <= 'z')
				{
					/* alt keys */
					if (sequence.find(escape_sequence) != sequence.end())
						return (SEQUENCE_ALT);
				}
				else if (seq == '[' || seq == 'O')
				{
					while (read(this->_fd, &seq, 1) == 1)
					{
						escape_sequence += std::string(1, seq);
						if ('A' <= seq && seq <= 'D')
						{
							/* arrow keys */
							if (sequence.find(escape_sequence) != sequence.end())
								return (SEQUENCE_ARROW);
							/* unrecognized sequence */
							break ;
						}
						if (seq == '~' || ('P' <= seq && seq <= 'S')
							|| seq == 'H' || seq == 'F')
						{
							/* function keys, navigation keys */
							if (sequence.find(escape_sequence) != sequence.end())
								return (SEQUENCE_FUNCTION_NAVIGATION);
							/* unrecognized sequence */
							break ;
						}
						/* unrecognized sequence */
						if (seq == ';' || seq == '/')
							break ;
						
					}
				}
			}
			return (UNRECOGNIZED_SEQUENCE);
		}
	```
