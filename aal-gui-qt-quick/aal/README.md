# Project for Analysis of Algorithms subject at WUT

## Build
Simply run `make` command.

## Usage
Built files are present in `bin/` directory. The following table lists all outputted programs:

| Binary | Usage | Description |
| -- | -- | -- |
| dp | `./dp < input > output` | solve task using dynamic-programming approach |
| graph | `./graph < input > output` | solve task using graphs approach |
| bf | `./bf < input > output` | solve task using brute-force approach |
| gen | `./gen [--amount N] [--min R] [--max R] > output` | generate test case of given size (default = 100), generates real values between min (default = 0.1) and max (default = 100) inclusive |
| tests | `./tests` | run a few predefined tests |
| timer | `./timer [--algorithm [dp\|graph\|bf]] [--repeat N] [--min N] [--max N] [--step N]` | benchmark specified algoritm on randomly generated test cases, performs specified number of tests (default = 1) on each test case size, test case sizes start from min (default = 100) and go up to max (default = 20.000) in increments of step (default = 100) |

N - integers, R - real numbers